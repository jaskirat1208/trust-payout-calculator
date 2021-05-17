#include <iostream>
#include <cmath>
#include "trust/grat/calculator.h"


namespace calc
{

namespace grat
{

/**
 * @brief Computes the payout schedule for the GRAT
 * 
 * @param inputs Set of inputs supplied to the GRAT
 * @return GRATOutputs 
 */
GRATOutputs GRATCalculator::computePayoutResults(GRATInputs inputs) {
    core::PayoutTable<GRATPayoutTableRow> payout_table;
    core::money_t beginning_principal = inputs.initial_principal();
    core::money_t no_planning_initial_principal = beginning_principal;
    core::rate_t growth_rate = inputs.growth_rate();

    bool success = true;
    core::money_t total_growth = 0;
    core::money_t total_payment_to_grantor = 0;
    core::rate_t initial_payout_rate = inputs.initial_payout_rate();
    if(inputs.solve_for_payout_rate()) {
        initial_payout_rate = solveForInitialPayoutRate(inputs);
    }
    core::money_t payment_to_grantor = initial_payout_rate * beginning_principal;
    core::money_t left_in_trust;

    core::money_t present_value_of_trust = beginning_principal;
    for(int i = 1; i <= inputs.term_in_year(); i++) {
        no_planning_initial_principal += no_planning_initial_principal*growth_rate;
        core::money_t growth = beginning_principal * growth_rate;
        total_growth += growth;
        core::money_t principal_w_growth = beginning_principal + growth;
        core::money_t ending_principal = principal_w_growth - payment_to_grantor;

        if(principal_w_growth <= payment_to_grantor) {
            success = false;
            ending_principal = 0;
            payment_to_grantor = principal_w_growth;
        }
        present_value_of_trust -= payment_to_grantor/pow(1+inputs.hurdle_rate(), i);
        total_payment_to_grantor += payment_to_grantor;

        GRATPayoutTableRow row{
            i, beginning_principal, growth, principal_w_growth, payment_to_grantor, ending_principal, success
        };
        payout_table.insert(row);
        left_in_trust = ending_principal;

        // Update the metrics for next year
        beginning_principal = ending_principal;
        payment_to_grantor = payment_to_grantor*(1+inputs.payout_stepup_rate());
    }

    core::money_t total_value = inputs.initial_principal() + total_growth;

    // Depending on the gift and estate tax rates, the grantor will choose if he wants to transfer the remaining wealth to the beneficiary
    core::money_t no_planning_tax = std::min(inputs.estate_tax_rate(), inputs.gift_tax_rate()) * no_planning_initial_principal;

    core::money_t gift_tax_on_npv = present_value_of_trust*inputs.gift_tax_rate();
    gift_tax_on_npv = std::max(gift_tax_on_npv, 0.0);
    core::money_t estate_tax_on_refunded_amt = total_payment_to_grantor * inputs.estate_tax_rate();
    
    GRATOutputs output(
        inputs.initial_principal(),
        total_growth,
        total_value,
        gift_tax_on_npv + estate_tax_on_refunded_amt,
        no_planning_tax,
        total_value - no_planning_tax,
        left_in_trust + total_payment_to_grantor - estate_tax_on_refunded_amt - gift_tax_on_npv
    );

    output.setPayoutTable(payout_table);
    return output;
}

/**
 * @brief Solves for initial payout rate so that the present value of trust is equal 
 * to target_npv  
 * 
 * 
 * Initial Payout rate = (1 - target NPV/Initial principal) *           (stepup rate - hurdle rate)
 *                                                            ---------------------------------------------
 *                                                              pow((1+stepup)/(1+hurdle), trust term) - 1
 * 
 * The second term on the right hand side is basically the sum of the following geometric progression:
 * 
 * 1/(1 + hurdle rate) + (1+stepup)/(1+hurdle)^2 + (1+stepup)^2/(1+hurdle)^3 + ..... with terms simulating till the year end
 * 
 * Observe that it becomes an indeterminate form when growth and hurdle rates are equal. 
 * So, to handle this case,  
 * 
 * @param inputs Input structure given to the calculator
 * @param target_npv Target net present value
 * @return core::rate_t Initial payout rate for the calculator
 */
core::rate_t GRATCalculator::solveForInitialPayoutRate(
    GRATInputs inputs) {

    core::money_t principal = inputs.initial_principal();
    core::rate_t stepup_rate = inputs.payout_stepup_rate();
    core::rate_t hurdle_rate = inputs.hurdle_rate();
    core::time::year_t term = inputs.term_in_year();
    core::money_t target_npv = inputs.target_npv();
    core::rate_t npv_by_principal = target_npv/principal;

    if(stepup_rate == hurdle_rate) {
        return (1- npv_by_principal) * (inputs.term_in_year()/stepup_rate);
    }
    std::cout << "Payout stepup rate: " << inputs.payout_stepup_rate() << std::endl;
    std::cout << "Hurdle rate: " << inputs.hurdle_rate() << std::endl;

    return (1 - npv_by_principal) * (stepup_rate - hurdle_rate) / (pow((1+inputs.payout_stepup_rate())/(1+inputs.hurdle_rate()), term) - 1);
}

} // namespace grat

} // namespace calc
