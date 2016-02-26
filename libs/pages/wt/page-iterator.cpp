#include "page-iterator.hpp"

#include <stdexcept>

namespace wt {
    wt::PageIterator::PageIterator() :
        stream(nullptr) {
    }

    wt::PageIterator::PageIterator(const char* stream) :
        stream(stream) {
    }

    bool wt::PageIterator::operator==(const wt::PageIterator& other) {
        return this->stream == other.stream;
    }

    wt::Page wt::PageIterator::operator*() const {
        if(this->stream) {
            return wt::Page("wfp", std::vector<icu::UnicodeString>());
        } else {
            throw std::runtime_error("Iterator is not dereferenceable");
        }
    }
}
