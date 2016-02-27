#include "page.hpp"

namespace wt {
    wt::Page::Page() {
    }

    wt::Page::Page(icu::UnicodeString title, std::vector<icu::UnicodeString> links) :
        title(title),
        links(links) {
    }
}
