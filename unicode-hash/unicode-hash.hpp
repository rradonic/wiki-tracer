#pragma once

namespace std {
    template<> struct hash<icu::UnicodeString>
    {
        size_t operator()(const icu::UnicodeString& x) const;
    };
}
