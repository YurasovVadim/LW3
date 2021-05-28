#include <UnitTest++/UnitTest++.h>
#include "/home/student/TIMP2/1/ModAlphaCypher.h"
#include "/home/student/TIMP2/1/ModAlphaCypher.cpp"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("АВДГЕЖ",modAlphaCypher("АБВ").encrypt("АБВГДЕ"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("АВД",modAlphaCypher("АБВГДЕ").encrypt("АБВ"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("АВДГЕЖ",modAlphaCypher("абв").encrypt("АБВГДЕ"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCypher cp("123"),cypher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCypher cp("А!,Б.В"),cypher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCypher cp("А БВ"),cypher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCypher cp(""),cypher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCypher cp("ААА"),cypher_error);
    }
}

struct KeyB_fixture {
    modAlphaCypher * p;
    KeyB_fixture()
    {
        p = new modAlphaCypher("Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ГШБЪБЦЯДБЗЙМВЬМЧЙУСФТЕБОПХБМЭЩЙГЬКЮЛИЁНРМАС",
                    p->encrypt("ВЧАЩАХЮГАЖИЛБЫЛЦИТРУСДАНОФАЛЬШИВЫЙЭКЗЕМПЛЯР"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("ГШБЪБЦЯДБЗЙМВЬМЧЙУСФТЕБОПХБМЭЩЙГЬКЮЛИЁНРМАС",
                    p->encrypt("вчащахюгажилбылцитрусданофальшивыйэкземпляр"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("ГШБЪБЦЯДБЗЙМВЬМЧЙУСФТЕБОПХБМЭЩЙГЬКЮЛИЁНРМАС",
                    p->encrypt("В,.ЧАЩАХ ЮГА ЖИЛ-БЫЛ ЦИТРУС? ДА, НО ФАЛЬШИВЫЙ ЭКЗЕМПЛЯР"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("ГШЪЦЯД", p->encrypt("ВЧ1Щ1ХЮГ342"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("123434512"),cypher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("БЦЯШЯФЭВЯЁЗКАЪКХЗСПТРГЯМНУЯКЫЧЗБЪИЬЙЖДЛОКЮП",
                    modAlphaCypher("Я").encrypt("ВЧАЩАХЮГАЖИЛБЫЛЦИТРУСДАНОФАЛЬШИВЫЙЭКЗЕМПЛЯР"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ВЧАЩАХЮГАЖИЛБЫЛЦИТРУСДАНОФАЛЬШИВЫЙЭКЗЕМПЛЯР",
                    p->decrypt("ГШБЪБЦЯДБЗЙМВЬМЧЙУСФТЕБОПХБМЭЩЙГЬКЮЛИЁНРМАС"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("вчащахюгажилбылцитрусданофальшивыйэкземпляр"),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("В,.ЧАЩАХ ЮГА ЖИЛ-БЫЛ ЦИТРУС? ДА, НО ФАЛЬШИВЫЙ ЭКЗЕМПЛЯР"),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("ВЧ1Щ1ХЮГ342"),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt(""),cypher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt("123434512"),cypher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ВЧАЩАХЮГАЖИЛБЫЛЦИТРУСДАНОФАЛЬШИВЫЙЭКЗЕМПЛЯР",
                    modAlphaCypher("Я").decrypt("БЦЯШЯФЭВЯЁЗКАЪКХЗСПТРГЯМНУЯКЫЧЗБЪИЬЙЖДЛОКЮП"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}