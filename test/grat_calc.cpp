#include <gtest/gtest.h>
#include <iostream>
#include "trust/grat/calculator.h"

TEST(GRAT_CALCULATOR_TargetNPV_Test, TargetNPV) {
    EXPECT_EQ(true, true);
    calc::grat::GRATCalculator calculator;

    calc::grat::GRATInputs inputs(
        1000000,
        5, 0.05, 0.2, 0, 0.015, 0.4, 0.4
    );
    std::cout << calculator.solveForInitialPayoutRate(inputs, 0) << std::endl;
}



TEST(GRAT_CALCULATOR_PAYOUT_TEST, SuccessfulGRAT) {
    EXPECT_EQ(true, true);

    calc::grat::GRATCalculator calculator;

    calc::grat::GRATInputs inputs(
        1000000,
        5, 0.05, 0.2, 0, 0.015, 0.4, 0.4
    );
    calc::grat::GRATOutputs result = calculator.computePayoutResults(inputs);
    std::cout << result.payout_table();
    std::cout << "GRAT Inputs" << std::endl;
}


TEST(GRAT_CALCULATOR_PAYOUT_TEST, FailedGRAT) {
    EXPECT_EQ(true, true);

    calc::grat::GRATCalculator calculator;

    calc::grat::GRATInputs inputs(
        1000000,
        5, 0.05, 0.5, 0.1, 0.015, 0.4, 0.4
    );
    calc::grat::GRATOutputs result = calculator.computePayoutResults(inputs);
    std::cout << result;
    std::cout << "GRAT Inputs" << std::endl;
}
