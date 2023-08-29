#include <lib/parser.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace omfl;

TEST(ParserTestSuite, EmptyTest) {
    std::string data = "";

    auto root = parse(data);

    ASSERT_TRUE(root.valid());
}

TEST(ParserTestSuite, IntTest) {
    std::string data = R"(
        key1 = 100500
        key2 = -22
        key3 = +28)";


    auto root = parse(data);

    ASSERT_TRUE(root.valid());

    ASSERT_TRUE(root.Get("key1").IsInt());
    ASSERT_TRUE(root.Get("key2").IsInt());
    ASSERT_TRUE(root.Get("key3").IsInt());

    ASSERT_EQ(root.Get("key1").AsInt(), 100500);
    ASSERT_EQ(root.Get("key2").AsInt(), -22);
    ASSERT_EQ(root.Get("key3").AsInt(), 28);
}

TEST(ParserTestSuite, InvalidIntTest) {
    std::string data = R"(
        key1 = true
        key2 = -22.1
        key3 = "ITMO")";


    auto root = parse(data);

    ASSERT_TRUE(root.valid());

    ASSERT_FALSE(root.Get("key1").IsInt());
    ASSERT_FALSE(root.Get("key2").IsInt());
    ASSERT_FALSE(root.Get("key3").IsInt());

    ASSERT_EQ(root.Get("key1").AsIntOrDefault(1), 1);
    ASSERT_EQ(root.Get("key2").AsIntOrDefault(-2), -2);
    ASSERT_EQ(root.Get("key3").AsIntOrDefault(3), 3);
}

TEST(ParserTestSuite, FloatTest) {
    std::string data = R"(
        key1 = 2.1
        key2 = -3.14
        key3 = -0.001)";


    auto root = parse(data);

    ASSERT_TRUE(root.valid());

    ASSERT_TRUE(root.Get("key1").IsFloat());
    ASSERT_TRUE(root.Get("key2").IsFloat());
    ASSERT_TRUE(root.Get("key3").IsFloat());

    ASSERT_FLOAT_EQ(root.Get("key1").AsFloat(), 2.1f);
    ASSERT_FLOAT_EQ(root.Get("key2").AsFloat(), -3.14f);
    ASSERT_FLOAT_EQ(root.Get("key3").AsFloat(), -0.001f);
}

TEST(ParserTestSuite, InvalidFloatTest) {
    std::string data = R"(
        key1 = true
        key2 = -2
        key3 = "ITMO")";


    auto root = parse(data);

    ASSERT_TRUE(root.valid());

    ASSERT_FALSE(root.Get("key1").IsFloat());
    ASSERT_FALSE(root.Get("key2").IsFloat());
    ASSERT_FALSE(root.Get("key3").IsFloat());

    ASSERT_FLOAT_EQ(root.Get("key1").AsFloatOrDefault(2.1), 2.1);
    ASSERT_FLOAT_EQ(root.Get("key2").AsFloatOrDefault(-3.14), -3.14);
    ASSERT_FLOAT_EQ(root.Get("key3").AsFloatOrDefault(-0.001), -0.001);
}

TEST(ParserTestSuite, StringTest) {
    std::string data = R"(
        key = "value"
        key1 = "value1")";


    auto root = parse(data);

    ASSERT_TRUE(root.valid());

    ASSERT_TRUE(root.Get("key").IsString());
    ASSERT_TRUE(root.Get("key1").IsString());

    ASSERT_EQ(root.Get("key").AsString(), "value");
    ASSERT_EQ(root.Get("key1").AsString(), "value1");
}

TEST(ParserTestSuite, InvalidStringTest) {
    std::string data = R"(
        key = true
        key1 = ["1", "2", "3"])";


    auto root = parse(data);

    ASSERT_TRUE(root.valid());

    ASSERT_FALSE(root.Get("key").IsString());
    ASSERT_FALSE(root.Get("key1").IsString());

    ASSERT_EQ(root.Get("key").AsStringOrDefault("Hello"), "Hello");
    ASSERT_EQ(root.Get("key1").AsStringOrDefault("World"), "World");
}

TEST(ParserTestSuite, ArrayTest) {
    std::string data = R"(
        key1 = [1, 2, 3, 4, 5, 6])";


    auto root = parse(data);

    ASSERT_TRUE(root.valid());

    ASSERT_TRUE(root.Get("key1").IsArray());

    ASSERT_EQ(root.Get("key1")[0].AsInt(), 1);
    ASSERT_EQ(root.Get("key1")[1].AsInt(), 2);
    ASSERT_EQ(root.Get("key1")[2].AsInt(), 3);

    ASSERT_EQ(root.Get("key1")[100500].AsIntOrDefault(99), 99);
}

TEST(ParserTestSuite, DiffTypesArrayTest) {
    std::string data = R"(
        key1 = [1, true, 3.14, "ITMO", [1, 2, 3], ["a", "b", 28]])";

    auto root = parse(data);

    ASSERT_TRUE(root.valid());

    ASSERT_TRUE(root.Get("key1").IsArray());

    ASSERT_TRUE(root.Get("key1")[0].IsInt());
    ASSERT_EQ(root.Get("key1")[0].AsInt(), 1);

    ASSERT_TRUE(root.Get("key1")[1].IsBool());
    ASSERT_EQ(root.Get("key1")[1].AsBool(), true);

    ASSERT_TRUE(root.Get("key1")[2].IsFloat());
    ASSERT_FLOAT_EQ(root.Get("key1")[2].AsFloat(), 3.14);

    ASSERT_TRUE(root.Get("key1")[3].IsString());
    ASSERT_EQ(root.Get("key1")[3].AsString(), "ITMO");

    ASSERT_TRUE(root.Get("key1")[4].IsArray());
    ASSERT_EQ(root.Get("key1")[4][0].AsInt(), 1);
    ASSERT_EQ(root.Get("key1")[4][1].AsInt(), 2);
    ASSERT_EQ(root.Get("key1")[4][2].AsInt(), 3);

    ASSERT_TRUE(root.Get("key1")[5].IsArray());
    ASSERT_EQ(root.Get("key1")[5][0].AsString(), "a");
    ASSERT_EQ(root.Get("key1")[5][1].AsString(), "b");
    ASSERT_EQ(root.Get("key1")[5][2].AsInt(), 28);
}

TEST(ParserTestSuite, CommentsTest) {
    std::string data = R"(
        key1 = 100500  # some important value

        # It's more then university)";

    auto root = parse(data);

    ASSERT_TRUE(root.valid());
    ASSERT_EQ(root.Get("key1").AsInt(), 100500);
}

TEST(ParserTestSuite, SectionTest) {
    std::string data = R"(
        [section1]
        key1 = 1
        key2 = true

        [section1]
        key3 = "value")";

    auto root = parse(data);
    ASSERT_TRUE(root.valid());

    ASSERT_EQ(root.Get("section1.key1").AsInt(), 1);
    ASSERT_EQ(root.Get("section1.key2").AsBool(), true);
    ASSERT_EQ(root.Get("section1.key3").AsString(), "value");
}

TEST(ParserTestSuite, MultiSectionTest) {
    std::string data = R"(
        [level1]
        key1 = 1
        [level1.level2-1]
        key2 = 2

        [level1.level2-2]
        key3 = 3)";

    auto root = parse(data);
    ASSERT_TRUE(root.valid());

    ASSERT_EQ(root.Get("level1.key1").AsInt(), 1);
    ASSERT_EQ(root.Get("level1.level2-1.key2").AsInt(), 2);
    ASSERT_EQ(root.Get("level1.level2-2.key3").AsInt(), 3);
}


TEST(ParserTestSuite, GetSectionTest) {
    std::string data = R"(
        [level1.level2.level3]
        key1 = 1)";

    auto root = parse(data);
    ASSERT_TRUE(root.valid());

    ASSERT_EQ(root.Get("level1").Get("level2").Get("level3").Get("key1").AsInt(), 1);
}