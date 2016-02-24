#pragma once

#include <wt/ufile.hpp>

namespace wt {
    class Pages {
    public:
        Pages(const char* path);

        void load();

    private:
        wt::UFile inFile;
    };
}
