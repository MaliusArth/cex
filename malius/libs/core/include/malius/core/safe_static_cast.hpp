#pragma once

// std lib
#include <limits>
#include <type_traits>

// external libs
#include <malius/assert.hpp>

namespace ma
{
    // base template
    template <bool IsFromSigned, bool IsToSigned>
    struct safe_static_cast_helper;

    // template specialization for casting from an unsigned type into an unsigned type
    template <>
    struct safe_static_cast_helper<false, false>
    {
        template <typename TO, typename FROM>
        static inline TO cast(FROM from)
        {
            MA_ASSERT(from >= std::numeric_limits<TO>::min(), "Number to cast exceeds numeric limits.")(from, TO(), std::numeric_limits<TO>::min(), std::numeric_limits<TO>::max());
            MA_ASSERT(from <= std::numeric_limits<TO>::max(), "Number to cast exceeds numeric limits.")(from, TO(), std::numeric_limits<TO>::min(), std::numeric_limits<TO>::max());

            return static_cast<TO>(from);
        }
    };

    // template specialization for casting from an unsigned type into a signed type
    template <>
    struct safe_static_cast_helper<false, true>
    {
        template <typename TO, typename FROM>
        static inline TO cast(FROM from)
        {
            MA_ASSERT(from >= std::numeric_limits<TO>::min(), "Number to cast exceeds numeric limits.")(from, TO(), std::numeric_limits<TO>::min(), std::numeric_limits<TO>::max());
            MA_ASSERT(from <= std::numeric_limits<TO>::max(), "Number to cast exceeds numeric limits.")(from, TO(), std::numeric_limits<TO>::min(), std::numeric_limits<TO>::max());

            return static_cast<TO>(from);
        }
    };

    // template specialization for casting from a signed type into an unsigned type
    template <>
    struct safe_static_cast_helper<true, false>
    {
        template <typename TO, typename FROM>
        static inline TO cast(FROM from)
        {
            // make sure the input is not negative
            MA_ASSERT(from >= 0, "Number to cast exceeds numeric limits.")(from, TO(), std::numeric_limits<TO>::min(), std::numeric_limits<TO>::max());

            // assuring a positive input, we can safely cast it into its unsigned type and check the numeric limits
            typedef typename std::make_unsigned<FROM>::type UnsignedFrom;
            //std::make_unsigned_t<FROM> t;
            MA_ASSERT(static_cast<UnsignedFrom>(from) >= std::numeric_limits<TO>::min(), "Number to cast exceeds numeric limits.")(from, TO(), std::numeric_limits<TO>::min(), std::numeric_limits<TO>::max());
            MA_ASSERT(static_cast<UnsignedFrom>(from) <= std::numeric_limits<TO>::max(), "Number to cast exceeds numeric limits.")(from, TO(), std::numeric_limits<TO>::min(), std::numeric_limits<TO>::max());

            return static_cast<TO>(from);
        }
    };

    // template specialization for casting from a signed type into a signed type
    template <>
    struct safe_static_cast_helper<true, true>
    {
        template <typename TO, typename FROM>
        static inline TO cast(FROM from)
        {
            MA_ASSERT(from >= std::numeric_limits<TO>::min(), "Number to cast exceeds numeric limits.")(from, TO(), std::numeric_limits<TO>::min(), std::numeric_limits<TO>::max());
            MA_ASSERT(from <= std::numeric_limits<TO>::max(), "Number to cast exceeds numeric limits.")(from, TO(), std::numeric_limits<TO>::min(), std::numeric_limits<TO>::max());

            return static_cast<TO>(from);
        }
    };

    // Reference: https://blog.molecular-matters.com/2011/08/12/a-safer-static_cast/
    template <typename TO, typename FROM>
    inline TO safe_static_cast(FROM from)
    {
#if MA_RELEASE
        return static_cast<TO>(from);
#else
        // delegate the call to the proper helper class, depending on the signedness of both types
        // template keyword usage: http://en.cppreference.com/w/cpp/language/dependent_name
        return safe_static_cast_helper<std::numeric_limits<FROM>::is_signed, std::numeric_limits<TO>::is_signed>::template cast<TO>(from);
#endif
    }
}
