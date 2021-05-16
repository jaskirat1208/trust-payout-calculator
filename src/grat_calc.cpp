#include <iostream>
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

}

/**
 * @brief Solves for initial payout rate so that the present value of trust is equal 
 * to target_npv  
 * 
 * @param inputs Input structure given to the calculator
 * @param target_npv Target net present value
 * @return core::rate_t Initial payout rate for the calculator
 */
core::rate_t GRATCalculator::solveForInitialPayoutRate(
    GRATInputs inputs, core::money_t target_npv) {

}

} // namespace grat

} // namespace calc
