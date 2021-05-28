#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>
#include <iostream>
#include <cctype>
using namespace std;

class modAlphaCypher
{
private:
    std::string numAlpha = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
    std::string numalpha = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec; //кодек UTF-8
    wstring ws = codec.from_bytes(numAlpha);
    std::wstring wa = codec.from_bytes(numalpha);
    std::map <char,int> alphaNum; //ассоциативный массив "номер по символу"
    std::vector <int> key; //ключ
    std::vector<int> convert(const std::string& s); //преобразование строка-вектор
    std::string convert(const std::vector<int>& v); //преобразование вектор-строка
    std::string getValidOpenText(const std::string & s);
    std::string getValidCypherText(const std::string & s);
    std::string getValidKey(const std::string & s);
public:
    modAlphaCypher()=delete; //запретим конструктор без параметров
    modAlphaCypher(const std::string& skey); //конструктор для установки ключа
    std::string encrypt(const std::string& open_text); //зашифрование
    std::string decrypt(const std::string& cypher_text);//расшифрование
};

class cypher_error: public std::invalid_argument
{
public:
    explicit cypher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cypher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};