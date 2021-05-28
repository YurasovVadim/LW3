#include "Marsh.h"

modMarshCypher::modMarshCypher(const std::string& skey)
{
    if (skey.empty())
        throw cypher_error("Empty key");
    for (int i=0; i<skey.length(); i++) {
        if (!isdigit(skey[i]))
            throw cypher_error(std::string("Invalid key ")+skey);
    }
    if (stoi(skey) == 1)
        throw cypher_error("WeakKey");
    if (stoi(skey)>0)
        key = stoi(skey);
    else
        throw cypher_error(std::string("Invalid key ")+skey);
}

std::string modMarshCypher::encrypt(const std::string& open_text)
{
    string s = getValidOpenText(open_text);
    string n_s = s;
    int dl, nstrok, index, k;
    dl = s.length();
    nstrok = (dl - 1) / key + 1;
    k = 0;
    for (int i = key; i > 0; i--) {
        for (int j = 0; j < nstrok; j++) {
            index = i+key*j;
            if (index-1 < dl) {
                n_s[k] = s[index-1];
                k++;
            }
        }
    }
    return n_s;
}

std::string modMarshCypher::decrypt(const std::string& cypher_text)
{
    string s = getValidCypherText(cypher_text);
    string n_s = s;
    int dl, nstrok, index, k;
    dl = s.length();
    nstrok = (dl - 1) / key + 1;
    k = 0;
    for (int i = key; i > 0; i--) {
        for (int j = 0; j < nstrok; j++) {
            index = i+key*j;
            if (index-1 < dl) {
                n_s[index-1] = s[k];
                k++;
            }
        }
    }
    return n_s;
}

inline std::string modMarshCypher::getValidOpenText(const std::string & s)
{
    std::string tmp;
    for (auto c:s) {
        if (isalpha(c)) {
            if (islower(c))
                tmp.push_back(toupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cypher_error("Empty open text");
    return tmp;
}

inline std::string modMarshCypher::getValidCypherText(const std::string & s)
{
    if (s.empty())
        throw cypher_error("Empty cypher text");
    for (auto c:s) {
        if (!isupper(c))
            throw cypher_error(std::string("Invalid cypher text ")+s);
    }
    return s;
}