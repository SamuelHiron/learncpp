#include <cstddef>
#include <cstdio>
#include <fmt/base.h>

const int numStandards = 7;
const long stdCode[numStandards] = {199711L, 201103L, 201402L, 201703L, 202002L, 202302L, 202612L};
const char* stdName[numStandards] = {"Pre-C++11", "C++11", "C++14", "C++17", "C++20", "C++23", "C++26"};

int getCPPStandard(){
#if defined (_MSVC_LANG)
    return _MSVC_LANG;
#elif defined (_MSC_VER)
    return -1;
#else
    return __cplusplus;
#endif
}

int main(){
    int standard = getCPPStandard();
    if (standard == -1){
        fmt::println(stderr, "Error: Unable to determine your language standard. Sorry");
        return 0;
    }

    for (int i = 0; i < numStandards; i++){
        // If the reported version is one of the finalized standard codes
        // then we know exactly what version the compiler is running
        if(standard == stdCode[i]){
            fmt::println("Your compiler is using {} (language standard code {} L)", stdName[i], standard);
            break;
        }

        // If the reported version is between two finalized standard codes,
        // this must be a preview / experimental support for the next upcoming version.
        if (standard < stdCode[i]) {
            fmt::println("Your compiler is using a preview/pre-release of {} (language standard code {}L) ", stdName[i], standard);
            break;
        }
    }
    return 0;
}