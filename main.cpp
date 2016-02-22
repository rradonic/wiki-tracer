#include <regex>
#include <locale>

#include <unicode/unistr.h>
#include <unicode/ustdio.h>
#include <unicode/regex.h>
#include <unicode/schriter.h>

#include <wt/unicode-hash.hpp>
#include <unordered_set>

int main () {
    icu::UnicodeString s1("Čwfp");
    icu::UnicodeString s2("rst");
    icu::UnicodeString s3("Čwfp");

    std::unordered_set<icu::UnicodeString> set;

    set.insert(s1);
    set.insert(s2);
    set.insert(s3);

    u_printf("set size: %d\n", set.size());

    if(set.find(s1) != set.end()) {
        u_printf("found s1\n");
    } else {
        u_printf("didn't find s1\n");
    }

    if(set.find(s2) != set.end()) {
        u_printf("found s2\n");
    } else {
        u_printf("didn't find s2\n");
    }

    if(set.find(s3) != set.end()) {
        u_printf("found s3\n");
    } else {
        u_printf("didn't find s3\n");
    }

    return 0;
}
