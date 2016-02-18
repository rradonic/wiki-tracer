#include <iostream>
#include <memory>
#include <regex>
#include <unordered_set>

#include <unicode/ustream.h>
#include <unicode/regex.h>

#include "sax2-handler.hpp"

namespace std {
    template<> struct hash<icu::UnicodeString>
    {
        size_t operator()(const icu::UnicodeString& x) const
        {
            return x.hashCode();
        }
    };
}

const char* SAX2Handler::languages[] = {
    "aa", "ab", "ae", "af", "ak", "am", "an", "ar", "as", "av", "ay", "az", "ba", "be", "bg",
    "bh", "bi", "bm", "bn", "bo", "br", "bs", "ca", "ce", "ch", "co", "cr", "cs", "cu", "cv",
    "cy", "da", "de", "dv", "dz", "ee", "el", "en", "eo", "es", "et", "eu", "fa", "ff", "fi",
    "fj", "fo", "fr", "fy", "ga", "gd", "gl", "gn", "gu", "gv", "ha", "he", "hi", "ho", "hr",
    "ht", "hu", "hy", "hz", "ia", "id", "ie", "ig", "ii", "ik", "io", "is", "it", "iu", "ja",
    "jv", "ka", "kg", "ki", "kj", "kk", "kl", "km", "kn", "ko", "kr", "ks", "ku", "kv", "kw",
    "ky", "la", "lb", "lg", "li", "ln", "lo", "lt", "lu", "lv", "mg", "mh", "mi", "mk", "ml",
    "mn", "mr", "ms", "mt", "my", "na", "nb", "nd", "ne", "ng", "nl", "nn", "no", "nr", "nv",
    "ny", "oc", "oj", "om", "or", "os", "pa", "pi", "pl", "ps", "pt", "qu", "rm", "rn", "ro",
    "ru", "rw", "sa", "sc", "sd", "se", "sg", "si", "sk", "sl", "sm", "sn", "so", "sq", "sr",
    "ss", "st", "su", "sv", "sw", "ta", "te", "tg", "th", "ti", "tk", "tl", "tn", "to", "tr",
    "ts", "tt", "tw", "ty", "ug", "uk", "ur", "uz", "ve", "vi", "vo", "wa", "wo", "xh", "yi",
    "yo", "za", "zh", "zu"
};

SAX2Handler::SAX2Handler() : redirect(false) {
}

void SAX2Handler::startElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname,
    const xercesc::Attributes& attrs) {

    (void)uri;
    (void)qname;
    (void)attrs;

    icu::UnicodeString nodeName(localname);

    this->state.push(nodeName);

    if(this->state.top() == "redirect") {
        this->redirect = true;
    }
}

void SAX2Handler::endElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname) {

    (void)uri;
    (void)localname;
    (void)qname;

    if(this->state.top() == "page" &&
        !this->redirect &&
        this->allowedTitle(this->title)) {

        std::unordered_set<icu::UnicodeString> links;

        UErrorCode status = U_ZERO_ERROR;
        icu::RegexMatcher matcher(icu::UnicodeString("\\[\\[:?(.*?)(\\|.*?)?\\]\\]"), 0, status);

        while(matcher.find()) {
            icu::UnicodeString link = matcher.group(1, status);

            if(this->allowedLink(link)) {
                links.insert(link);
            }
        }

        std::cout << this->title << ": ";

        for(auto const& link : links) {
            std::cout << " [[" << link << "]]";
        }

        std::cout << std::endl;
    }

    if(this->state.top() == "page") {
        this->title.remove();
        this->content.remove();
        this->redirect = false;
    }

    this->state.pop();
}

void SAX2Handler::characters(
    const XMLCh* const chars,
    const XMLSize_t length) {

    if(this->state.top() != "title" && this->state.top() != "text") {
        return;
    }

    icu::UnicodeString charsUnicode(chars, length);

    if(this->state.top() == "title") {
        this->title.append(charsUnicode);
    } else if(this->state.top() == "text") {
        this->content.append(charsUnicode);
    }
}

bool SAX2Handler::allowedTitle(icu::UnicodeString title) const {
    icu::UnicodeString titleLower(title);
    titleLower.toLower();

    return this->allowed(titleLower);
}

bool SAX2Handler::allowedLink(icu::UnicodeString link) const {
    icu::UnicodeString linkLower(link);
    linkLower.toLower();

    return
        this->allowed(linkLower) &&

        linkLower.compare(0, 2, "m:") != 0 &&
        linkLower.compare(0, 3, "mw:") != 0 &&
        linkLower.compare(0, 5, "wikt:") != 0 &&
        linkLower.compare(0, 11, "wiktionary:") != 0 &&
        linkLower.compare(0, 2, "s:") != 0 &&
        linkLower.compare(0, 11, "wikisource:") != 0 &&
        linkLower.compare(0, 2, "w:") != 0 &&
        linkLower.compare(0, 10, "wikiquote:") != 0 &&
        linkLower.compare(0, 4, "doi:") != 0 &&
        linkLower.compare(0, 4, "hdl:") != 0 &&
        linkLower.compare(0, 8, "species:") != 0 &&
        linkLower.compare(0, 2, "v:") != 0 &&

        !this->interLanguage(linkLower);
}

bool SAX2Handler::allowed(icu::UnicodeString text) const {
    return
        text.compare(0, 10, "wikipedia:") != 0 &&
        text.compare(0, 8, "project:") != 0 &&
        text.compare(0, 3, "wp:") != 0 &&

        text.compare(0, 5, "file:") != 0 &&
        text.compare(0, 6, "image:") != 0 &&
        text.compare(0, 6, "media:") != 0 &&

        text.compare(0, 5, "user:") != 0 &&
        text.compare(0, 10, "mediaWiki:") != 0 &&
        text.compare(0, 9, "template:") != 0 &&
        text.compare(0, 5, "help:") != 0 &&
        text.compare(0, 9, "category:") != 0 &&
        text.compare(0, 7, "portal:") != 0 &&
        text.compare(0, 5, "book:") != 0 &&
        text.compare(0, 6, "draft:") != 0 &&
        text.compare(0, 10, "timedText:") != 0 &&
        text.compare(0, 7, "module:") != 0 &&
        text.compare(0, 6, "topic:") != 0 &&

        text.compare(0, 7, "list of") != 0 &&

        text.indexOf("(disambiguation)") == -1;
}

bool SAX2Handler::interLanguage(icu::UnicodeString link) const {
    for(auto const& language : SAX2Handler::languages) {
        if(link.compare(0, 2, language) == 0) {
            return true;
        }
    }

    return false;
}
