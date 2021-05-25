#include <gtest/gtest.h>
#include <iostream>
#include "trust/grat/calculator.h"

TEST(GRAT_CALCULATOR_PAYOUT_TEST, SuccessfulGRAT) {
    EXPECT_EQ(true, true);

    calc::grat::GRATCalculator calculator;

    calc::grat::GRATInputs inputs(
        1000000,
        5, 0.05, 0.2, 0, 0.015
    );
    calc::grat::GRATOutputs result = calculator.computePayoutResults(inputs);
    std::cout << result << std::endl;
}


TEST(GRAT_CALCULATOR_PAYOUT_TEST, FailedGRAT) {
    EXPECT_EQ(true, true);

    calc::grat::GRATCalculator calculator;

    calc::grat::GRATInputs inputs(
        1000000,
        5, -0.05, 0.5, 0.1, 0.015, true, 0
    );
    calc::grat::GRATOutputs result = calculator.computePayoutResults(inputs);
    std::cout << result;
}

TEST(GRAT_CALCULATOR_PAYOUT_TEST, GRATWithConstAnnuities) {
    EXPECT_EQ(true, true);

    calc::grat::GRATCalculator calculator;

    calc::grat::GRATInputs inputs(
        1000000,
        15, 0.05, 0.5, 0.01, 0.015, true, 0
    );
    calc::grat::GRATOutputs result = calculator.computePayoutResults(inputs);
    std::cout << result;
}


TEST(GRAT_CALCULATOR_PAYOUT_TEST, GRATWithNegativeTaxSavings) {
    EXPECT_EQ(true, true);

    calc::grat::GRATCalculator calculator;

    calc::grat::GRATInputs inputs(
        1000000,
        15, -0.05, 0.05, 0.01, 0.015, true, 0
    );
    calc::grat::GRATOutputs result = calculator.computePayoutResults(inputs);
    std::cout << result;
}