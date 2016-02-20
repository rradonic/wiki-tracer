#include <unicode/ustdio.h>

#include <sys/stat.h>
#include <sys/mman.h>

#include <vector>
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

    for(StringPiece piece(p); piece.length() > 1; p += piece.length() + 1) {
        piece.set(p);

        if(piece.length() <= 1) {
            break;
        }

        icu::UnicodeString s = icu::UnicodeString::fromUTF8(piece);

        u_printf("%.*S\n", s.length(), s.getBuffer());
    };

    /* for(int i = 0; i < 10000; i++) { */
    /*     putchar(fileMap[i]); */
    /* } */

    return 0;
}
