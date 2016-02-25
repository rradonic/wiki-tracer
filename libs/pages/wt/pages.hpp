#ifndef LIBS_PAGES_WT_PAGES_HPP
#define LIBS_PAGES_WT_PAGES_HPP

#include <wt/ufile.hpp>

#include "page-iterator.hpp"

namespace wt {
    class Pages {
    public:
        Pages(const char* path);

    private:
        PageIterator iter;
    };
}

#endif
