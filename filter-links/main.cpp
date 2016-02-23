#include <unicode/ustdio.h>

#include <sys/stat.h>
#include <sys/mman.h>

#include <unicode/regex.h>

#include <wt/ufile.hpp>
#include <wt/unicode-hash.hpp>

#include <unordered_set>

namespace wt {
    std::unordered_set<icu::UnicodeString> loadTitles(char* p) {
        std::unordered_set<icu::UnicodeString> titles;

        int counter = 0;

        for(StringPiece piece(p); piece.length() > 1; p += piece.length() + 1) {
            piece.set(p);

            if(piece.length() <= 1) {
                break;
            }

            icu::UnicodeString line = icu::UnicodeString::fromUTF8(piece);

            UErrorCode status = U_ZERO_ERROR;
            icu::RegexMatcher matcher(
                icu::UnicodeString("^\\R?(.*?)#"),
                line,
                0,
                status);

            matcher.find();

            icu::UnicodeString title = matcher.group(1, status);

            titles.insert(title);

            if(counter % 1000 == 0) {
                u_printf(".");
                fflush(stdout);
            }

            counter++;
        }

        return titles;
    }

    void filterLinks(char* p, const std::unordered_set<icu::UnicodeString>& titles) {
        int counter = 0;

        for(StringPiece piece(p); piece.length() > 1; p += piece.length() + 1) {
            piece.set(p);

            if(piece.length() <= 1) {
                break;
            }

            icu::UnicodeString line = icu::UnicodeString::fromUTF8(piece);

            UErrorCode status = U_ZERO_ERROR;
            icu::RegexMatcher matcher(
                icu::UnicodeString("\\[\\[(.*?)\\]\\]"),
                line,
                0,
                status);

            while(matcher.find()) {
                icu::UnicodeString link = matcher.group(1, status);

                if(titles.find(link) != titles.end()) {
                    u_printf("+");
                    fflush(stdout);
                } else {
                    u_printf("-");
                    fflush(stdout);
                }

                u_printf("%.*S\n", link.length(), link.getBuffer());

                counter++;
            }

            break;
        }
    }
}

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

    char* p = fileMap;

    // the StringPiece constructor we're using loads characters until the first
    // \0. we put a null character at the end of each line when creating the
    // file so we're basically loading line by line here.

    u_printf("Loading page titles...\n");
    std::unordered_set<icu::UnicodeString> titles = wt::loadTitles(p);
    u_printf("\nDone\n");

    p = fileMap;

    u_printf("Removing broken links...\n");
    wt::filterLinks(p, titles);
    u_printf("\nDone\n");

    return 0;
}
