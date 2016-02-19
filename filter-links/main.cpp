#include <iostream>
#include <fstream>
#include <vector>

#include <unicode/unistr.h>
#include <unicode/ustream.h>

int main(int argc, char* args[]) {
    if(argc < 2) {
        std::cout << "Usage: filter-links [FILE]" << std::endl;
        return -1;
    }

    std::basic_ifstream<UChar> file(args[1], std::ios::ate);

    std::iostream::pos_type pos(file.tellg());

    std::cout << "File size is " << pos << " bytes" << std::endl;

    std::vector<UChar> buffer(pos);

    file.seekg(0, std::ios::beg);
    file.read(buffer.data(), pos);

    icu::UnicodeString content(false, buffer.data(), 10000);

    std::cout << "Unicode length is " << content.length() << " bytes" << std::endl;

    return 0;
}
