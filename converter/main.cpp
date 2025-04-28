#include <iostream>
#include "OscarConverter.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " input.oscar output.McDst.root\n";
        return 1;
    }

    OscarConverter converter;
    if (!converter.Convert(argv[1], argv[2])) {
        std::cerr << "Conversion failed.\n";
        return 1;
    }

    std::cout << "Conversion completed successfully.\n";
    return 0;
}
