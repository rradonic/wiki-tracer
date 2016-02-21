#pragma once

#include <unicode/ustdio.h>

class UFileWrapper {
public:
    UFileWrapper(const char* path, const char* mode);
    ~UFileWrapper();

    UFileWrapper(const UFileWrapper&) = delete;
    UFileWrapper(UFileWrapper&&) = delete;

    UFileWrapper& operator=(const UFileWrapper&) = delete;
    UFileWrapper& operator=(UFileWrapper&&) = delete;

    operator UFILE*() const;

private:
    UFILE* uFile;
};
