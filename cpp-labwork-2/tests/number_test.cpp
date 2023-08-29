#include <lib/number.h>
#include <gtest/gtest.h>
#include <tuple>

class ConvertingTestsSuite : public testing::TestWithParam<std::tuple<uint32_t, const char*, bool>> {
};

TEST_P(ConvertingTestsSuite, EqualTest) {
    uint2022_t a = from_uint(std::get<0>(GetParam()), 0);
    uint2022_t b = from_string(std::get<1>(GetParam()));

    if(std::get<2>(GetParam()))
        ASSERT_EQ(a,b) << std::get<0>(GetParam()) << " == " << std::get<1>(GetParam());
    else
        ASSERT_NE(a,b) << std::get<0>(GetParam()) << " != " << std::get<1>(GetParam());
}

INSTANTIATE_TEST_SUITE_P(
    Group,
    ConvertingTestsSuite,
    testing::Values(
        // positive
        std::make_tuple(0, "0", true),
        std::make_tuple(239,"239", true),
        std::make_tuple(255,"255", true),
        std::make_tuple(256,"256", true),
        std::make_tuple(10000,"10000", true),
        std::make_tuple(32767,"32767", true),
        std::make_tuple(32768,"32768", true),
        std::make_tuple(65535,"65535", true),
        std::make_tuple(2147483647,"2147483647", true),

        // negative
        std::make_tuple(0, "1", false),
        std::make_tuple(32768,"32769", false),
        std::make_tuple(255,"256", false),
        std::make_tuple(256,"255", false),
        std::make_tuple(31251,"31252", false),
        std::make_tuple(2147483647,"2147483648", false)
    )
);


class OperationTestsSuite
    : public testing::TestWithParam<
        std::tuple<
            const char*, // lhs
            const char*, // rhs
            const char*, // +
            const char*, // -
            const char*  // *
        >
    > {
};

TEST_P(OperationTestsSuite, AddTest) {
    uint2022_t a = from_string(std::get<0>(GetParam()));
    uint2022_t b = from_string(std::get<1>(GetParam()));

    uint2022_t result = a + b;
    uint2022_t expected = from_string((std::get<2>(GetParam())));

    ASSERT_EQ(result, expected);
}

TEST_P(OperationTestsSuite, SubstTest) {
    uint2022_t a = from_string(std::get<0>(GetParam()));
    uint2022_t b = from_string(std::get<1>(GetParam()));

    uint2022_t result = a - b;
    uint2022_t expected = from_string((std::get<3>(GetParam())));

    ASSERT_EQ(result, expected);
}

TEST_P(OperationTestsSuite, MultTest) {
    uint2022_t a = from_string(std::get<0>(GetParam()));
    uint2022_t b = from_string(std::get<1>(GetParam()));

    uint2022_t result = a * b;
    uint2022_t expected = from_string((std::get<4>(GetParam())));

    ASSERT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(
    Group,
    OperationTestsSuite,
    testing::Values(
        std::make_tuple("1", "1", "2", "0", "1"),
        std::make_tuple("1024", "1", "1025", "1023", "1024"),
        std::make_tuple("405272312330606683982498447530407677486444946329741970511324085183808429621437",
                        "1",
                        "405272312330606683982498447530407677486444946329741970511324085183808429621438",
                        "405272312330606683982498447530407677486444946329741970511324085183808429621436",
                        "405272312330606683982498447530407677486444946329741970511324085183808429621437"
        ),
        std::make_tuple("405272312330606683982498447530407677486444946329741977764879002871583477858493",
                        "0",
                        "405272312330606683982498447530407677486444946329741977764879002871583477858493",
                        "405272312330606683982498447530407677486444946329741977764879002871583477858493",
                        "0"
        ),
        std::make_tuple(
            "405272312330606683982498447530407677486444946329741974138101544027695953739965",
            "3626777458843887524118528",
            "405272312330606683982498447530407677486444946329741977764879002871583477858493",
            "405272312330606683982498447530407677486444946329741970511324085183808429621437",
            "1469832487054184013178321496623041557517329857560238757278117847507488415462666081345922349701550571520"
        )
    )
);