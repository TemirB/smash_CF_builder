#include <iostream>
#include "OscarConverter.h"
#include "RootConverter.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.oscar> <output.mcDst.root>" << std::endl;
        return 1;
    }
    
    OscarConverter converter;
    bool success = converter.Convert(argv[1], argv[2]);
    
    if (!success) {
        std::cerr << "Conversion failed!" << std::endl;
        return 2;
    }
    
    std::cout << "Conversion completed successfully." << std::endl;
    return 0;

    // ===== Для конвертации .root -> .mcDst.root ======
    // if (argc != 3) {
    //     std::cerr << "Usage: " << argv[0] << " <input.root> <output.mcDst.root>" << std::endl;
    //     return 1;
    // }

    // ConvertRootToMcDst(argv[1], argv[2]);

    // return 0;
}