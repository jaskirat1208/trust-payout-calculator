#pragma once
#include <memory>
#include <sstream>


#include "trust/base.h"
#include "trust/payout_table.h"

namespace calc {
namespace grat {

/**
 * A typical row in a GRAT payout table
 **/
struct GRATPayoutTableRow
{
    core::time::year_t m_year;
    core::money_t m_beginning_principal;
    core::money_t m_growth;
    core::money_t m_principal_w_growth;
    core::money_t m_payment_to_grantor;
    core::money_t m_ending_principal;
    bool m_success;

    std::string getValues(int pad=0) {
        std::stringstream ss;
        
        ss << std::setw(pad) << m_year << " ";
        ss << std::setw(pad) << m_beginning_principal << " ";
        ss << std::setw(pad) << m_growth << " ";
        ss << std::setw(pad) << m_principal_w_growth << " ";
        ss << std::setw(pad) << m_payment_to_grantor << " ";
        ss << std::setw(pad) << m_ending_principal << " ";
        ss << std::setw(pad) << m_success << " ";
        return ss.str();
    }

    static std::vector<std::string> getColumns()
    {
        return std::vector<std::string>{
            "Year",
            "Beginning principal",
            "Growth",
            "Principal w Growth",
            "Payment to grantor",
            "Ending Principal",
            "Success"
        };
    }
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
    core::money_t m_amount_to_heir_no_planning;
    core::money_t m_amount_to_heir_planning;
    bool m_success;
public:
    GRATOutputs(core::money_t initial_principal, core::money_t growth, core::money_t total, 
        core::money_t planning_tax, core::money_t no_planning_tax, 
        core::money_t amount_to_heir_no_planning, core::money_t amount_to_heir_planning) : 
        m_initial_principal(initial_principal),
        m_growth(growth),
        m_total(total),
        m_planning_tax(planning_tax),
        m_no_planning_tax(no_planning_tax),
        m_amount_to_heir_no_planning(amount_to_heir_no_planning),
        m_amount_to_heir_planning(amount_to_heir_planning) {}
    
    friend std::ostream& operator<<(std::ostream& os, GRATOutputs output) {
        // Print headers
        os << "Payout Table: " << std::endl;
        os << output.payout_table();
        os << std::endl;

        os << "Summary: " << std::endl;
        os << "Initial principal: " << output.initial_principal() << std::endl;
        os << "Growth: " << output.growth() << std::endl;
        os << "Principal w Growth: " << output.principal_w_growth() << std::endl;
        os << "No planning Tax: " << output.no_planning_tax() << std::endl;
        os << "Amount to heir no Planning: " << output.amount_to_heir_no_planning() << std::endl;
        os << "Amount to heir Planning: " << output.amount_to_heir_planning() << std::endl;
        os << "Planning Tax: " << output.planning_tax() << std::endl;
        os << "Tax Savings: " << output.tax_savings() << std::endl;
        return os;
    }

    /**
     * @brief Set the Payout Table object
     * 
     * @param payout_table Payout table as computed by the calculator
     */
    inline void setPayoutTable(core::PayoutTable<GRATPayoutTableRow> payout_table) {
        m_payout_table = payout_table;
    }

    inline core::PayoutTable<GRATPayoutTableRow> payout_table() {
        return m_payout_table;
    }

    /**
     * @brief Beginning principal of trust
     * 
     * @return core::money_t Initial Principal of trust
     */
    inline core::money_t initial_principal() {
        return m_initial_principal;
    }

    /**
     * @brief Estimated growth of assets during the trust
     * 
     * @return core::money_t 
     */
    inline core::money_t growth() {
        return m_growth;
    }

    /**
     * @brief Returns principal with growth
     * 
     * @return core::money_t Initial Principal + Estimated Growth
     */
    inline core::money_t principal_w_growth() {
        return m_total;
    }

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
        // m_total - m_no_planning_tax == m_amount_to_heir_no_planning;
        return m_amount_to_heir_no_planning;
    }

    /**
     * @brief Amount of assets transferred to beneficiary with Planning
     * 
     * @return core::money_t Amount transferred to beneficiary
     */
    inline core::money_t amount_to_heir_planning() {
        return m_amount_to_heir_planning;// m_total - m_planning_tax;
    }
    
    inline bool success() {
        return m_success;
    }

    inline core::money_t tax_savings() {
        return m_amount_to_heir_planning - m_amount_to_heir_no_planning;
    }
};


} // namespace calc

} // namespace grat
