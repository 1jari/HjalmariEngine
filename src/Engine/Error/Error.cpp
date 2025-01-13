#include "./Error.h"

namespace Hjalmari7 {

    Error_t CreateError_f(  std::string msg,
                            Gravity_e gravity) {
        return Error_t{msg, gravity};
    }
}
