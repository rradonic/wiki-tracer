#ifndef LIBS_PAGES_WT_PAGE_HPP
#define LIBS_PAGES_WT_PAGE_HPP

#include <vector>

#include <unicode/unistr.h>

namespace wt {
    class Page {
    public:
        Page(icu::UnicodeString title, std::vector<icu::UnicodeString> links);
    };
}

#endif
