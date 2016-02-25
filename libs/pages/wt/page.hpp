#pragma once

#include <vector>

#include <unicode/unistr.h>

namespace wt {
    class Page {
    public:
        Page(icu::UnicodeString title, std::vector<icu::UnicodeString> links);
    };
}
