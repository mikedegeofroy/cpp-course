#include <lib/parser.h>
#include <gtest/gtest.h>

#include <sstream>


using namespace omfl;

class ValidFormatTestSuite : public testing::TestWithParam<const char*> {
};

TEST_P(ValidFormatTestSuite, ValidTest) {
    std::string param = GetParam();
    ASSERT_TRUE(parse(param).valid());
}

class InvalidFormatTestSuite : public testing::TestWithParam<const char*> {
};
TEST_P(InvalidFormatTestSuite, InValidTest) {
    std::string param = GetParam();
    ASSERT_FALSE(parse(param).valid());
}

// Key
INSTANTIATE_TEST_SUITE_P(
    KeyValidation,
    ValidFormatTestSuite,
    testing::Values(
        "key = \"value\"",
        " key      =  \"value\"   ",
        " key=  \"value\"",
        " key123 =  \"value\"",
        " key_1-23-abcd =  \"value\"",
        " 23key_ =  \"value\""
    )
);

INSTANTIATE_TEST_SUITE_P(
    KeyValidation,
    InvalidFormatTestSuite,
    testing::Values(
        "!key = \"value\"",
        "key = \n\"value\"",
        "      =  \"value\"   ",
        "=  \"value\"",
        " key**123 =  \"value\"",
        " . =  \"value\"",
        " .key2.key3 =  \"value\"",
        " key1. =  \"value\""
    )
);

// Value
INSTANTIATE_TEST_SUITE_P(
    ValueValidation,
    ValidFormatTestSuite,
    testing::Values(
        "key = \"value\""
    )
);

INSTANTIATE_TEST_SUITE_P(
    ValueValidation,
    InvalidFormatTestSuite,
    testing::Values(
        "key = ",
        "key = abcd"
    )
);


TEST(FormatTestSuite, KeyRedifenitionTest) {
    std::string data = R"(
        key = 1
        key = 2)";

    ASSERT_FALSE(parse(data).valid());
}

// Integer Value
INSTANTIATE_TEST_SUITE_P(
    IntValueValidation,
    ValidFormatTestSuite,
    testing::Values(
        "key1 = 2",
        "key2 = -22",
        "key3 = +48"
    )
);

INSTANTIATE_TEST_SUITE_P(
    IntValueValidation,
    InvalidFormatTestSuite,
    testing::Values(
        "key1 = 2+",
        "key2 = 2-2",
        "key3 = 4+8",
        "key4 = +"
    )
);

// Float Value
INSTANTIATE_TEST_SUITE_P(
    FloatValueValidation,
    ValidFormatTestSuite,
    testing::Values(
        "key1 = 3.14",
        "key2 = -3.14",
        "key3 = +0.00001"
    )
);

INSTANTIATE_TEST_SUITE_P(
    FloatValueValidation,
    InvalidFormatTestSuite,
    testing::Values(
        "key1 = .0",
        "key2 = 1.",
        "key3 = +.1",
        "key4 = +.",
        "key5 = ."
    )
);

// String Value
INSTANTIATE_TEST_SUITE_P(
    StringValueValidation,
    ValidFormatTestSuite,
    testing::Values(
        "key1 = \"Hello world\"",
        "key2 = \"1, 2, 3, 4, 5\"",
        "key3 = \"3.14\"",
        "key4 = \"1\t2\t3\"",
        "key5 = \"[1,2,3,4,5]\""        
    )
);

INSTANTIATE_TEST_SUITE_P(
    StringValueValidation,
    InvalidFormatTestSuite,
    testing::Values(
        "key1 = \"Hello world",
        "key2 = \"ITMO\"University\"",
        "key3 = \"Bjarne\" \"stroustrup\""
    )
);


// Bool Value
INSTANTIATE_TEST_SUITE_P(
    BoolValueValidation,
    ValidFormatTestSuite,
    testing::Values(
        "key1 = true",
        "key2 = false"
    )
);

INSTANTIATE_TEST_SUITE_P(
    BoolValueValidation,
    InvalidFormatTestSuite,
    testing::Values(
        "key1 = tru",
        "key2 = alse",
        "key3 = true true",
        "key4 = fal-se",
        "key5 = truefalse"
    )
);


// Array Value
INSTANTIATE_TEST_SUITE_P(
    ArrayValueValidation,
    ValidFormatTestSuite,
    testing::Values(
        "key1 = []",
        "key2 = [1,2,3,4,5]",
        "key3 = [1, -3.14, true, \"ITMO\"]",
        "key4 = [[1,2],[2,[3,4,5]]]"
    )
);

INSTANTIATE_TEST_SUITE_P(
    ArrayValueValidation,
    InvalidFormatTestSuite,
    testing::Values(
        "key1 = [",
        "key2 = ]",
        "key3 = [1;2;3]",
        "key4 = [1,2,3,4",
        "key5 = [[1,2],[2,[3,4,5]"
    )
);


// Section
INSTANTIATE_TEST_SUITE_P(
    SectionValueValidation,
    ValidFormatTestSuite,
    testing::Values(
        "[section-1]",
        "[section-1.section-2]",
        "[a.b.c.d]"
    )
);

INSTANTIATE_TEST_SUITE_P(
    SectionValueValidation,
    InvalidFormatTestSuite,
    testing::Values(
        "[]",
        "{section-1}",
        "[section-1.]",
        "[.section-1]"
    )
);

// Comment
INSTANTIATE_TEST_SUITE_P(
    CommentValueValidation,
    ValidFormatTestSuite,
    testing::Values(
        "key1 = 1 # comment",
        "# some text"
    )
);

INSTANTIATE_TEST_SUITE_P(
    CommentValueValidation,
    InvalidFormatTestSuite,
    testing::Values(
        "# comment \n newline comment"
    )
);