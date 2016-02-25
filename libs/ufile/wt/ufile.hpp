#ifndef LIBS_UFILE_WT_UFILE_HPP
#define LIBS_UFILE_WT_UFILE_HPP

#include <unicode/ustdio.h>

namespace wt {
    class UFile {
    public:
        UFile(const char* path, const char* mode);
        ~UFile();

        UFile(const UFile&) = delete;
        UFile(UFile&&) = delete;

        UFile& operator=(const UFile&) = delete;
        UFile& operator=(UFile&&) = delete;

        operator UFILE*() const;

    private:
        UFILE* uFile;
    };
}

#endif
