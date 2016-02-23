#include "ufile-wrapper.hpp"

namespace wt {
    UFileWrapper::UFileWrapper(const char* path, const char* mode) {
        this->uFile = u_fopen(path, mode, nullptr, nullptr);
    }

    UFileWrapper::~UFileWrapper() {
        u_fclose(this->uFile);
    }

    UFileWrapper::operator UFILE*() const {
        return this->uFile;
    }
}
