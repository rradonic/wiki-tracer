#ifndef LIBS_PAGES_WT_PAGE_ITERATOR_HPP
#define LIBS_PAGES_WT_PAGE_ITERATOR_HPP

#include "page.hpp"

#include <wt/ufile.hpp>

namespace wt {
    class PageIterator {
    public:
        PageIterator();
        PageIterator(const char* stream);

        typedef std::forward_iterator_tag iterator_category;
        typedef const wt::Page value_type;
        typedef std::ptrdiff_t  difference_type;
        typedef const wt::Page* pointer;
        typedef const wt::Page& reference;

        bool operator==(const wt::PageIterator& other);
        wt::Page operator*() const;
        wt::PageIterator& operator++(int dummy);

    private:
        void loadPage();

        const char* stream;
        const char* position;
        bool good;

        icu::StringPiece piece;

        wt::Page page;
    };
}

#endif
