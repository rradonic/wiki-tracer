#include "page.hpp"

namespace wt {
    Page::Page(const char* path) :
        inFile(path, "r") {
    }
}
