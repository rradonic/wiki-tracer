#include "page-iterator.hpp"

namespace wt {
    PageIterator::PageIterator(const char* path) :
        inFile(path, "r") {
    }
}
