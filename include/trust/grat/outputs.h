#pragma once
#include "trust/base.h"
#include "trust/payout_table.h"

namespace calc {
namespace grat {

/**
 * A typical row in a GRAT payout table
 **/
class GRATPayoutTableRow
{
private:
    core::time::year_t m_year;
    core::money_t m_beginning_principal;
    core::money_t m_growth;
    core::money_t m_principal_w_growth;
    core::money_t m_payment_to_grantor;
    core::money_t m_estate_and_gift_tax;
    core::money_t m_ending_principal;
public:
    GRATPayoutTableRow();
    ~GRATPayoutTableRow();
};


/**
 * @brief Output structure of a GRAT calculator
 * 
 */
class GRATOutputs
{
private:
    core::PayoutTable<GRATPayoutTableRow> m_payout_table;
    core::money_t m_initial_principal;
    core::money_t m_growth;
    core::money_t m_total;
    core::money_t m_planning_tax;
    core::money_t m_no_planning_tax;
public:
    GRATOutputs();

    /**
     * @brief Returns estate and gift tax paid on Planning
     * 
     * @return core::money_t Tax paid on planning
     */
    inline core::money_t planning_tax() {
        return m_planning_tax;
    }
    
    /**
     * @brief Returns estate and gift tax paid when no trust planning is made
     * 
     * @return core::money_t No planning tax
     */
    inline core::money_t no_planning_tax() {
        return m_no_planning_tax;
    }

    /**
     * @brief Amount of assets transferred to beneficiary with no planning
     * 
     * @return core::money_t Amount transferred to beneficiary
     */
    inline core::money_t amount_to_heir_no_planning() {
        return m_total - m_no_planning_tax;
    }

    /**
     * @brief Amount of assets transferred to beneficiary with Planning
     * 
     * @return core::money_t Amount transferred to beneficiary
     */
    inline core::money_t amount_to_heir_planning() {
        return m_total - m_planning_tax;
    }
    
    ~GRATOutputs();
};


} // namespace calc

} // namespace grat
