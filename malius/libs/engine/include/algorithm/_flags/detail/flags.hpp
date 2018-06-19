

#ifdef  MA_CONFIG_STRONGLY_TYPED_ENUMS

#include <cstdint>

enum class Mode : std::int8_t
{
    READ = 1 << 0,          // 0b0001   //binary literals C++14
    WRITE = 1 << 1,         // 0b0010
    APPEND = 1 << 2,        // 0b0100
    RANDOM_ACCESS = 1 << 3  // 0b1000   // 0b0000'1000 <- digit separators
};

#include <type_traits>

using T = std::underlying_type<Mode>::type;

template<class T>
using underlying_type_t = typename std::underlying_type<T>::type;

inline Mode operator | (Mode lhs, Mode rhs)
{
    return static_cast<Mode>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

inline Mode& operator |= (Mode& lhs, Mode rhs)
{
    lhs = static_cast<Mode>(static_cast<T>(lhs) | static_cast<T>(rhs));
    return lhs;
}

auto test = Mode::type;

int mode = Mode::READ | Mode::WRITE | Mode::RANDOM_ACCESS;

const bool isReadMode = ((mode & MODE_READ) != 0);

#endif