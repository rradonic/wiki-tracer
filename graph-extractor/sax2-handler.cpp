#include <iostream>
#include <memory>
#include <regex>

#include "sax2-handler.hpp"

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

    auto deleter = [](char* p) {
        xercesc::XMLString::release(&p);
    };

    std::unique_ptr<char, decltype(deleter)> nodeName(
        xercesc::XMLString::transcode(localname),
        deleter);

    this->state.push(std::string(nodeName.get()));

    if(this->state.top() == "redirect") {
        this->redirect = true;
    }
}

void SAX2Handler::endElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname) {

    (void)uri;
    (void)qname;

    auto deleter = [](char* p) {
        xercesc::XMLString::release(&p);
    };

    std::unique_ptr<char, decltype(deleter)> nodeName(
        xercesc::XMLString::transcode(localname),
        deleter);

    if(this->state.top() == "page" &&
        !this->redirect &&
        this->allowedTitle(this->title) &&
        this->title.find("(disambiguation)") == std::string::npos) {

        std::cout << this->title << ": ";

        std::regex regex("\\[\\[.*?\\]\\]");
        std::smatch results;

        while(std::regex_search(this->content, results, regex)) {
            if(this->allowedLink(*results.begin())) {
                std::cout << " " << *results.begin();
            }

            this->content = results.suffix();
        }

        std::cout << std::endl << std::endl;

        exit(0);
    }

    if(this->state.top() == "page") {
        this->title.clear();
        this->content.clear();
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

    std::unique_ptr<char[]> buffer(new char[length + 1]);

    xercesc::XMLString::transcode(chars, buffer.get(), length);

    if(this->state.top() == "title") {
        this->title.append(buffer.get());
    } else if(this->state.top() == "text") {
        this->content.append(buffer.get());
    }
}

bool SAX2Handler::allowedTitle(std::string title) const {
    return this->allowed(title, 0);
}

bool SAX2Handler::allowedLink(std::string link) const {
    return this->allowed(link, 2);
}

bool SAX2Handler::allowed(std::string text, std::size_t pos) const {
    return
        text.compare(pos, 10, std::string("Wikipedia:")) != 0 &&
        text.compare(pos, 8, std::string("Project:")) != 0 &&
        text.compare(pos, 3, std::string("WP:")) != 0 &&

        text.compare(pos, 5, std::string("File:")) != 0 &&
        text.compare(pos, 6, std::string("Image:")) != 0 &&

        text.compare(pos, 5, std::string("User:")) != 0 &&
        text.compare(pos, 10, std::string("MediaWiki:")) != 0 &&
        text.compare(pos, 9, std::string("Template:")) != 0 &&
        text.compare(pos, 5, std::string("Help:")) != 0 &&
        text.compare(pos, 9, std::string("Category:")) != 0 &&
        text.compare(pos, 7, std::string("Portal:")) != 0 &&
        text.compare(pos, 5, std::string("Book:")) != 0 &&
        text.compare(pos, 6, std::string("Draft:")) != 0 &&
        text.compare(pos, 10, std::string("TimedText:")) != 0 &&
        text.compare(pos, 7, std::string("Module:")) != 0 &&
        text.compare(pos, 6, std::string("Topic:")) != 0;
}
