#include "trust/grat/inputs.h"
#include "trust/grat/outputs.h"

namespace calc {
namespace grat {

class GRATCalculator
{
public:
    GRATCalculator() = default;
    core::rate_t solveForInitialPayoutRate(GRATInputs inputs);
    GRATOutputs computePayoutResults(GRATInputs inputs);
};
    
} // namespace grat
} // namespace calc
