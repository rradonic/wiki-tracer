#ifndef LIBS_PAGES_WT_PAGES_HPP
#define LIBS_PAGES_WT_PAGES_HPP

#include "page-iterator.hpp"

#include <wt/ufile.hpp>

namespace wt {
    class Pages {
    public:
        Pages(const char* path);

    private:
        wt::PageIterator iter;
        std::vector<Page> pages;
    };
}

#endif
