#include "ufile.hpp"

namespace wt {
    UFile::UFile(const char* path, const char* mode) {
        this->uFile = u_fopen(path, mode, nullptr, nullptr);
    }

    UFile::~UFile() {
        u_fclose(this->uFile);
    }

    UFile::operator UFILE*() const {
        return this->uFile;
    }
}
