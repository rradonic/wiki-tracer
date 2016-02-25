#pragma once

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
