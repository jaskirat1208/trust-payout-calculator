#pragma once
#include "trust/base.h"

namespace calc {
namespace grat {

class GRATInputs
{
private:
    core::money_t m_initial_principal;
    core::time::year_t m_term_in_year;
    
    core::rate_t m_growth_rate;
    core::rate_t m_init_payout_rate;
    core::rate_t m_payout_stepup_rate;

    /**
     * US federal estate and gift tax rate, typically 40% each
     **/
    core::rate_t m_estate_tax_rate = 0.4;
    core::rate_t m_gift_tax_rate = 0.4;

    /**
     * Applicable US federal rate. 
     * In a GRAT, this is specifically the IRS Section 7520 rate
     **/
    core::rate_t m_hurdle_rate;
    bool m_solve_for_payout_rate=false;
    core::money_t target_npv = 0;

public:
    GRATInputs(
        core::money_t initial_principal, 
        core::time::year_t term_in_year, 
        core::rate_t growth_rate, 
        core::rate_t initial_payout_rate, 
        core::rate_t payout_stepup_rate, 
        core::rate_t hurdle_rate,
        core::rate_t estate_tax_rate = 0.4,
        core::rate_t gift_tax_rate = 0.4
    ): 
        m_initial_principal(initial_principal),
        m_term_in_year(term_in_year),
        m_growth_rate(growth_rate),
        m_init_payout_rate(initial_payout_rate),
        m_payout_stepup_rate(payout_stepup_rate),
        m_hurdle_rate(hurdle_rate),
        m_estate_tax_rate(estate_tax_rate),
        m_gift_tax_rate(gift_tax_rate) {}

    inline core::money_t initial_principal() {
        return m_initial_principal; 
    }

    inline core::time::year_t term_in_year() {
        return m_term_in_year;
    }

    inline core::rate_t growth_rate() {
        return m_growth_rate;
    }

    inline core::rate_t initial_payout_rate() {
        return m_init_payout_rate;
    }

    inline core::rate_t payout_stepup_rate() {
        return m_payout_stepup_rate;
    }

    inline core::rate_t estate_tax_rate() {
        return m_estate_tax_rate;
    }

    inline core::rate_t gift_tax_rate() {
        return m_gift_tax_rate;
    }

    /**
     * @brief Returns IRS Section 7520 rate
     * 
     * @return core::rate_t Returns hurdle rate
     */
    inline core::rate_t hurdle_rate() {
        return m_hurdle_rate;
    }
};


} // namespace grat
} // namespace calc
