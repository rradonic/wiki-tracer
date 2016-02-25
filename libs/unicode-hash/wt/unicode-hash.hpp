#ifndef LIBS_UNICODE_HASH_WT_UNICODE_HASH_HPP
#define LIBS_UNICODE_HASH_WT_UNICODE_HASH_HPP

#include <functional>

#include <unicode/unistr.h>

namespace std {
    template<> struct hash<icu::UnicodeString>
    {
        size_t operator()(const icu::UnicodeString& x) const;
    };
}

#endif
