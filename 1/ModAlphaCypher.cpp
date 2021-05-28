#include "ModAlphaCypher.h"

modAlphaCypher::modAlphaCypher(const std::string& skey)
{
    for (unsigned i=0; i<ws.size(); i++) {
        alphaNum[ws[i]]=i;
    }
    key = convert(getValidKey(skey));
      int n = 0;
    for (auto e:key) {
        if (e==0)
            n++;
    }
    if (2*n > key.size())
        throw cypher_error("WeakKey");
}

std::string modAlphaCypher::encrypt(const std::string& open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::string modAlphaCypher::decrypt(const std::string& cypher_text)
{
    std::vector<int> work = convert(getValidCypherText(cypher_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

inline std::vector<int> modAlphaCypher::convert(const std::string& s)
{
    std::vector<int> result;
    wstring w_s = codec.from_bytes(s); // перекодируем
    for (unsigned i=0; i<w_s.size(); i++) {
        result.push_back(alphaNum[w_s[i]]);
    }
    return result;
}

inline std::string modAlphaCypher::convert(const std::vector<int>& v)
{
    std::string result;
    wstring result_s = codec.from_bytes("");
    for (unsigned i=0; i<v.size(); i++) {
        result_s.push_back(ws[v[i]]);
    }
    result = codec.to_bytes(result_s);
    return result;
}

inline std::string modAlphaCypher::getValidKey(const std::string & s)
{
    if (s.empty())
        throw cypher_error("Empty key");
    std::locale loc("ru_RU.UTF-8");
    std::wstring tmp = codec.from_bytes(s);
    for(int i = 0; i < tmp.size(); i++) {
        if (wa.find(tmp[i]) != string::npos) {
            tmp[i] = toupper(tmp[i], loc);
        }
        if (ws.find(tmp[i]) == string::npos)
            throw cypher_error(std::string("Invalid key ")+s);
    }
    string tmp1 = codec.to_bytes(tmp);
    return tmp1;
}

inline std::string modAlphaCypher::getValidOpenText(const std::string & s)
{
    std::locale loc("ru_RU.UTF-8");
    std::wstring tmp = codec.from_bytes(s);
    std::wstring n_tmp;
    for(int i = 0; i < tmp.size(); i++) {
        if (wa.find(tmp[i]) != string::npos) {
            n_tmp.push_back(toupper(tmp[i], loc));
        }
        if (ws.find(tmp[i]) != string::npos)
            n_tmp.push_back(tmp[i]);
    }
    string tmp1 = codec.to_bytes(n_tmp);
    if (tmp1.empty())
        throw cypher_error("Empty text");
    return tmp1;
}

inline std::string modAlphaCypher::getValidCypherText(const std::string & s)
{
    if (s.empty())
        throw cypher_error("Empty cypher text");
    std::locale loc("ru_RU.UTF-8");
    std::wstring tmp = codec.from_bytes(s);
    for(int i = 0; i < tmp.size(); i++) {
        if (ws.find(tmp[i]) == string::npos)
            throw cypher_error(std::string("Invalid cypher text ")+s);
    };
    return s;
}
