#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>
#include <iostream>
#include <cctype>
using namespace std;
class modMarshCypher
{
private:
    int key;
    std::string getValidOpenText(const std::string & s);
    std::string getValidCypherText(const std::string & s);
public:
    modMarshCypher()=delete;
    modMarshCypher(const string& key1);
    std::string encrypt(const std::string& open_text);
    std::string decrypt(const std::string& cipher_text);
};

class cypher_error: public std::invalid_argument
{
public:
    explicit cypher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cypher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};