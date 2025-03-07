#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <time.h>
#include <ctype.h>

#include "helpers.h"
#include "lib/json/json.hpp"

using namespace std;
using json = nlohmann::json;

namespace helpers {

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

string generateToken() {
    srand(time(NULL));

    string s = "";
    static const char alphanum[] =
        "-_"
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 48; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return s;
}

/*
* https://stackoverflow.com/a/14530993 - mini url decoder
*/
void urldecode(char *dst, const char *src) {
    char a, b;
    while (*src) {
        if ((*src == '%') &&
            ((a = src[1]) && (b = src[2])) &&
            (isxdigit(a) && isxdigit(b))) {
            if (a >= 'a')
                a -= 'a' - 'A';
            if (a >= 'A')
                a -= ('A' - 10);
            else
                a -= '0';
            if (b >= 'a')
                b -= 'a' - 'A';
            if (b >= 'A')
                b -= ('A' - 10);
            else
                b -= '0';
            *dst++ = 16 * a + b;
            src += 3;
        }
        else if (*src == '+') {
            *dst++ = ' ';
            src++;
        }
        else {
            *dst++ = *src++;
        }
    }
    *dst++ = '\0';
}

char* cStrCopy(const string &str) {
    char *text = new char[str.size() + 1];
    copy(str.begin(), str.end(), text);
    text[str.size()] = '\0';
    // delete[] text from the initiator
    return text;
}

bool hasRequiredFields(const json &input, const vector<string> &keys) {
    for(const string &key: keys) {
        if(!helpers::hasField(input, key)) {
            return false;
        }
    }
    return true;
}

bool hasField(const json &input, const string &key) {
    return input.contains(key) && !input[key].is_null();
}

vector<string> getModes() {
    return {"window", "browser", "cloud", "chrome"};
}

string normalizePath(string &path) {
    #if defined(_WIN32)
    replace(path.begin(), path.end(), '\\', '/');
    #endif
    return path;
}

} // namespace helpers
