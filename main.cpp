#include "wt/page-iterator.hpp"

#include <unicode/ustdio.h>

#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char* args[]) {
    if(argc < 2) {
        u_printf("Usage: filter-links [FILE]\n");
        return -1;
    }

    wt::UFile file(args[1], "r");

    struct stat fileStat;
    fstat(fileno(u_fgetfile(file)), &fileStat);

    char* fileMap = static_cast<char*>(mmap(
        nullptr,
        fileStat.st_size,
        PROT_READ,
        MAP_PRIVATE,
        fileno(u_fgetfile(file)),
        0));

    // the StringPiece constructor we're using loads characters until the first
    // \0. we put a null character at the end of each line when creating the
    // file so we're basically loading line by line here.

    wt::PageIterator iter(fileMap);

    for(int i = 0; i < 10; i++) {
        wt::Page page = *iter;

        u_printf("%.*S\n", page.title.length(), page.title.getBuffer());

        iter++;
    }

    return 0;
}
