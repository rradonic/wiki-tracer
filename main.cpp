#include "wt/page-iterator.hpp"

#include <unicode/ustdio.h>

int main () {
    wt::PageIterator it;

    wt::Page p = *it;

    u_printf("%.*S", p.title.length(), p.title.getBuffer());

    return 0;
}
