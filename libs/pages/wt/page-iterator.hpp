#ifndef LIBS_PAGES_WT_PAGE_ITERATOR_HPP
#define LIBS_PAGES_WT_PAGE_ITERATOR_HPP

#include <wt/ufile.hpp>

#include "page.hpp"

namespace wt {
    class PageIterator {
    public:
        PageIterator(const char* path);

        Page next();

    private:
        UFile inFile;
    };
}

#endif
