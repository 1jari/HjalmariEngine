#ifndef _ERROR_H
#define _ERROR_H

#include <string>
#include <iostream>

#define ERROR_OK Hjalmari7::CreateError_f("", Hjalmari7::ERROR_GRAVITY_MOON)

namespace Hjalmari7 {
    enum Gravity_e {
        ERROR_GRAVITY_MOON      = 1,    // Pass
        ERROR_GRAVITY_MARS      = 3,    // Warning
        ERROR_GRAVITY_JUPITER   = 24    // FATAL!
    };

    struct Error_t {
        std::string msg;
        Gravity_e   gravity;
    };

    Error_t CreateError_f(std::string msg, Gravity_e gravity);
}

#endif //_ERROR_H
