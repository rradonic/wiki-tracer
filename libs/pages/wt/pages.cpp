#include "pages.hpp"

namespace wt {
    Pages::Pages(const char* path) :
        inFile(path, "r") {
    }

    void load() {
        // TODO maybe implement an iterator in this class
    }
}
