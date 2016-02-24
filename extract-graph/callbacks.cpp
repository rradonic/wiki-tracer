#include <unicode/regex.h>

#include <wt/unicode-hash.hpp>

#include <unordered_set>

#include "callbacks.hpp"

Callbacks::Callbacks(const char* path) :
    redirect(false),
    outFile(path, "w") {
}

void Callbacks::startElement(
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

void Callbacks::endElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname) {

    (void)uri;
    (void)localname;
    (void)qname;

    if(this->state.top() == "page" && this->allowed(this->title)) {
        std::unordered_set<icu::UnicodeString> links;

        UErrorCode status = U_ZERO_ERROR;
        icu::RegexMatcher matcher(
            icu::UnicodeString("\\[\\[w?:?(.*?)(?:\\|.*?)?\\]\\]"),
            this->content,
            0,
            status);

        while(matcher.find()) {
            icu::UnicodeString link = matcher.group(1, status);
            link.toLower();

            if(this->allowed(link)) {
                links.insert(link);
            }
        }

        if(this->redirect &&
            links.size() == 1 &&
            this->title == *(links.begin())) {

            // skip redirects that differed only in capitalization since we've
            // already lowercased everything

            this->cleanUp();
            return;
        }

        if(this->redirect) {
            u_fprintf(this->outFile, "%.*S -> ", this->title.length(), this->title.getBuffer());
        } else {
            u_fprintf(this->outFile, "%.*S # ", this->title.length(), this->title.getBuffer());
        }

        for(auto const& link : links) {
            u_fprintf(this->outFile, "[[%.*S]] ", link.length(), link.getBuffer());
        }

        u_fprintf(this->outFile, "%c\n", '\0');

        static int counter = 0;

        if(counter % 1000 == 0) {
            u_printf(".");
            fflush(stdout);
        }

        counter++;
    }

    if(this->state.top() == "page") {
        this->cleanUp();
    }

    this->state.pop();
}

void Callbacks::cleanUp() {
    this->title.remove();
    this->content.remove();
    this->redirect = false;
}

void Callbacks::characters(const XMLCh* const chars, const XMLSize_t length) {
    if(this->state.top() != "title" && this->state.top() != "text") {
        return;
    }

    icu::UnicodeString charsUnicode(chars, length);

    if(this->state.top() == "title") {
        charsUnicode.toLower();
        this->title.append(charsUnicode);
    } else if(this->state.top() == "text") {
        this->content.append(charsUnicode);
    }
}

bool Callbacks::allowed(icu::UnicodeString text) const {
    return
        text.compare(0, 10, "wikipedia:") != 0 &&
        text.compare(0, 3, "wp:") != 0 &&
        text.compare(0, 8, "project:") != 0 &&

        text.compare(0, 5, "file:") != 0 &&
        text.compare(0, 6, "image:") != 0 &&
        text.compare(0, 6, "media:") != 0 &&

        text.compare(0, 10, "mediawiki:") != 0 &&
        text.compare(0, 9, "template:") != 0 &&
        text.compare(0, 5, "help:") != 0 &&
        text.compare(0, 9, "category:") != 0 &&
        text.compare(0, 7, "portal:") != 0 &&
        text.compare(0, 5, "book:") != 0 &&
        text.compare(0, 6, "draft:") != 0 &&
        text.compare(0, 10, "timedtext:") != 0 &&
        text.compare(0, 7, "module:") != 0 &&
        text.compare(0, 6, "topic:") != 0;
}
