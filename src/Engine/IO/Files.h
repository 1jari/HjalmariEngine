#ifndef _FILES_H
#define _FILES_H

#include <iostream>	// std::cout std::cin
#include <fstream>	// std::ifstream
#include <string>	// std::string
#include <sstream>	// std::stringstream

#include "../Error/Error.h"

namespace Hjalmari7 {
    namespace FileSystem {
        std::string ReadFile_f(const std::string& filename) ;
    }
}

#endif //_FILES_H