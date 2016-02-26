#include "page.hpp"

namespace wt {
    Page::Page(icu::UnicodeString title, std::vector<icu::UnicodeString> links) :
        title(title),
        links(links) {
    }
}
