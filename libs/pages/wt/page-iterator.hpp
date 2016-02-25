#pragma once

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
