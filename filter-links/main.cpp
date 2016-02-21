#include <unicode/ustdio.h>

#include <sys/stat.h>
#include <sys/mman.h>

#include <unordered_set>

int main(int argc, char* args[]) {
    if(argc < 2) {
        u_printf("Usage: filter-links [FILE]\n");
        return -1;
    }

    UFILE* file = u_fopen(args[1], "r", nullptr, nullptr);

    struct stat fileStat;
    fstat(fileno(u_fgetfile(file)), &fileStat);

    u_printf("File size is %lld bytes\n", fileStat.st_size);

    u_printf("Memory mapping file...\n");
    char* fileMap = static_cast<char*>(mmap(
        nullptr,
        fileStat.st_size,
        PROT_READ,
        MAP_PRIVATE,
        fileno(u_fgetfile(file)),
        0));
    u_printf("Done!\n");

    u_fclose(file);

    char* p = fileMap;

    // the StringPiece constructor we're using loads characters until the first
    // \0. we put a null character at the end of each line when creating the
    // file so we're basically loading line by line here.

    for(StringPiece piece(p); piece.length() > 1; p += piece.length() + 1) {
        piece.set(p);

        if(piece.length() <= 1) {
            break;
        }

        icu::UnicodeString s = icu::UnicodeString::fromUTF8(piece);

        u_printf("%.*S\n", s.length(), s.getBuffer());
    };

    return 0;
}
