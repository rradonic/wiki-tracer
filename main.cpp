#include <regex>
#include <locale>

#include <unicode/unistr.h>
#include <unicode/ustdio.h>
#include <unicode/regex.h>
#include <unicode/schriter.h>

#include <unordered_set>

int main () {
    icu::UnicodeString s("đrysuwfju[[it:Wikipedia: rstrst|blabla]]");

    icu::UnicodeString t(s[0]);

    t.toUpper();

    s.replace(0, 1, t);

    u_printf("wfp: %S\n", s.getTerminatedBuffer());

    /* UErrorCode status = U_ZERO_ERROR; */

    /* icu::RegexMatcher matcher(icu::UnicodeString("\\[\\[:?(.*?)(\\|.*?)?\\]\\]"), 0, status); */

    /* matcher.reset(s); */

    /* while(matcher.find()) { */
    /*     std::cout << "Found: " << matcher.group(1, status) << std::endl; */
    /* } */

    return 0;
}
