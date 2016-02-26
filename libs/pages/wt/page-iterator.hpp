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
        typedef wt::Page value_type;
        typedef std::ptrdiff_t  difference_type;
        typedef wt::Page* pointer;
        typedef wt::Page& reference;

        bool operator==(const wt::PageIterator& other);
        wt::Page operator*() const;
        wt::PageIterator& operator++() const;

    private:
        const char* stream;
    };
}

#endif
