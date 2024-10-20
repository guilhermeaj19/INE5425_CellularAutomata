#include <ostream>
namespace Color {
    enum Code {
        EMPTY  = 49,
        SAND   = 43,
        WALL   = 44
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}