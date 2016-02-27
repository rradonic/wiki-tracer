#include "page-iterator.hpp"

#include <stdexcept>

#include <unicode/regex.h>

namespace wt {
    wt::PageIterator::PageIterator() :
        stream(nullptr),
        position(nullptr),
        good(false),
        page() {
    }

    wt::PageIterator::PageIterator(const char* stream) :
        stream(stream),
        position(stream),
        good(true) {

            this->loadPage();
    }

    bool wt::PageIterator::operator==(const wt::PageIterator& other) {
        return this->stream == other.stream;
    }

    wt::Page wt::PageIterator::operator*() const {
        if(this->good) {
            return this->page;
        } else {
            throw std::runtime_error("Iterator is not dereferenceable.");
        }
    }

    wt::PageIterator& wt::PageIterator::operator++(int dummy) {
        (void)dummy;

        this->position += this->piece.length() + 1;
        this->loadPage();

        return *this;
    }

    void wt::PageIterator::loadPage() {
        this->piece.set(this->position);

        if(this->piece.length() <= 1) {
            this->good = false;
            return;
        }

        icu::UnicodeString line = icu::UnicodeString::fromUTF8(this->piece);

        UErrorCode status = U_ZERO_ERROR;
        icu::RegexMatcher matcher(
            icu::UnicodeString("^\\R?(.*?) (?:#|->)"),
            line,
            0,
            status);

        matcher.find();

        this->page.title = matcher.group(1, status);
    }
}
