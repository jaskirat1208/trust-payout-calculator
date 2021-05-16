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
    ) {}
    ~GRATInputs();
};


} // namespace grat
} // namespace calc
