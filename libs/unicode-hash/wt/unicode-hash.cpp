#include "unicode-hash.hpp"

namespace std {
    size_t hash<icu::UnicodeString>::operator()(const icu::UnicodeString& x) const
    {
        return x.hashCode();
    }
}
