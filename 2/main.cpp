#include <UnitTest++/UnitTest++.h>
#include "/home/student/TIMP2/2/Marsh.h"
#include "/home/student/TIMP2/2/Marsh.cpp"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("DLROWOLLEH",modMarshCypher("21").encrypt("HELLOWORLD"));
    }
    TEST(LetterInKey) {
        CHECK_THROW(modMarshCypher cp("А1"),cypher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modMarshCypher cp("1,2"),cypher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modMarshCypher cp("2 1"),cypher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modMarshCypher cp(""),cypher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modMarshCypher cp("1"),cypher_error);
    }
}

struct KeyB_fixture {
    modMarshCypher * p;
    KeyB_fixture()
    {
        p = new modMarshCypher("21");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("DLROWOLLEH",
                    p->encrypt("HELLOWORLD"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("DLROWOLLEH",
                    p->encrypt("helloworld"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("DLROWOLLEH",
                    p->encrypt("HELLO, WORLD!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("DLROWOLLEH", p->encrypt("1H2E3L4L5O6WORLD"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1234567890"),cypher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("DLROWOLLEH",
                    modMarshCypher("10").encrypt("HELLOWORLD"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("HELLOWORLD",
                    p->decrypt("DLROWOLLEH"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("dlrowolleh"),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("DLROW OLLEH"),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("123DLROWOLLEH"),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt(""),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt("123456789"),cypher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("HELLOWORLD",
                    modMarshCypher("10").decrypt("DLROWOLLEH"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}