#include <gtest/gtest.h>
#include "math_core.h"

TEST(Lifecycle, CreateAndDestroy) {
    MathContext* ctx = mc_create_context();
    ASSERT_NE(ctx, nullptr);
    mc_destroy_context(ctx);
}

TEST(Evaluate, StubReturnsAnything) {
    MathContext* ctx = mc_create_context();

    char* result = nullptr;
    char* error  = nullptr;
    int   status = mc_evaluate_latex(ctx, "2+3", &result, &error);

    EXPECT_EQ(status, 0);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(error, nullptr);

    mc_free_string(result);
    mc_destroy_context(ctx);
}