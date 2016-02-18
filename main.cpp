#include <iostream>
#include <regex>
#include <locale>

#include <unicode/unistr.h>
#include <unicode/ustream.h>
#include <unicode/regex.h>

#include <unordered_set>

namespace std {
    template<> struct hash<icu::UnicodeString>
    {
        size_t operator()(const icu::UnicodeString& x) const
        {
            return x.hashCode();
        }
    };
}

int main () {
    /* const char* languages[] = { */
    /*     "aa", "ab", "ae", "af", "ak", "am", "an", "ar", "as", "av", "ay", "az", "ba", "be", "bg", */
    /*     "bh", "bi", "bm", "bn", "bo", "br", "bs", "ca", "ce", "ch", "co", "cr", "cs", "cu", "cv", */
    /*     "cy", "da", "de", "dv", "dz", "ee", "el", "en", "eo", "es", "et", "eu", "fa", "ff", "fi", */
    /*     "fj", "fo", "fr", "fy", "ga", "gd", "gl", "gn", "gu", "gv", "ha", "he", "hi", "ho", "hr", */
    /*     "ht", "hu", "hy", "hz", "ia", "id", "ie", "ig", "ii", "ik", "io", "is", "it", "iu", "ja", */
    /*     "jv", "ka", "kg", "ki", "kj", "kk", "kl", "km", "kn", "ko", "kr", "ks", "ku", "kv", "kw", */
    /*     "ky", "la", "lb", "lg", "li", "ln", "lo", "lt", "lu", "lv", "mg", "mh", "mi", "mk", "ml", */
    /*     "mn", "mr", "ms", "mt", "my", "na", "nb", "nd", "ne", "ng", "nl", "nn", "no", "nr", "nv", */
    /*     "ny", "oc", "oj", "om", "or", "os", "pa", "pi", "pl", "ps", "pt", "qu", "rm", "rn", "ro", */
    /*     "ru", "rw", "sa", "sc", "sd", "se", "sg", "si", "sk", "sl", "sm", "sn", "so", "sq", "sr", */
    /*     "ss", "st", "su", "sv", "sw", "ta", "te", "tg", "th", "ti", "tk", "tl", "tn", "to", "tr", */
    /*     "ts", "tt", "tw", "ty", "ug", "uk", "ur", "uz", "ve", "vi", "vo", "wa", "wo", "xh", "yi", */
    /*     "yo", "za", "zh", "zu" */
    /* }; */

    /* std::string a("[[:it:Wikipedia: rstrst|wfp]]"); */

    /* for(auto const& language : languages) { */
    /*     std::cout << a.compare(2, 2, language) << " "; */
    /* } */

    /* return 0; */

    icu::UnicodeString s("Črysuwfju[[it:Wikipedia: rstrst|blabla]]");
    UErrorCode status = U_ZERO_ERROR;

    icu::RegexMatcher matcher(icu::UnicodeString("\\[\\[:?(.*?)(\\|.*?)?\\]\\]"), 0, status);

    matcher.reset(s);

    while(matcher.find()) {
        std::cout << "Found: " << matcher.group(1, status) << std::endl;
    }

    return 0;

    std::locale::global(std::locale("en_US.UTF-8"));

    std::string t("Č");
    t[0] = std::tolower(t[0], std::locale("en_US.UTF-8"));

    std::cout << t << std::endl;

    return 0;

    std::string a("[[it:Wikipedia: rstrst]]");

    std::smatch results;

    while(std::regex_search(a, results, std::regex("\\[\\[:?(.*?)(\\|.*?)?\\]\\]"))) {
        for(auto value: results) {
            std::cout << value << std::endl;
        }

        a = results.suffix();
    }

    return 0;
}
