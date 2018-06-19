#pragma once

#include <cstdint>

#include "common/preprocessor.hpp"

// Reference: https://blog.molecular-matters.com/2011/08/23/flags-on-steroids/
/// TODO: add possibility of actually setting values    \
TEST THIS PROTOTYPE:
/// #define  MA_DECLARE_FLAGS_GET_VALUE(x,y,...) y
/// #define  MA_PP_FOR_EACH_1(op, count, x, ...) \
/// IF(EQUAL( MA_PP_NUM_VA_ARGS( MA_PP_STRIP_PARENS(x)), 2)\
    ( MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x),  MA_DECLARE_FLAGS_GET_VALUE( MA_PP_STRIP_PARENS(x)))),\
     MA_PP_GLUE(op, ( MA_PP_STRIP_PARENS(x), count)))\
     MA_PP_EAT(__VA_ARGS__)
#define  MA_DECLARE_FLAGS_ENUM(name, n)      name = (1u << n),
#define  MA_DECLARE_FLAGS_BITS(name, n)      uint32_t name : 1;
#define  MA_DECLARE_FLAGS_TO_STRING(name, n) \
case name: return  MA_PP_STRINGIZE(name);

#define  MA_DECLARE_FLAGS(name, ...)    \
struct name     \
{       \
    static const size_t Count =  MA_PP_NUM_VA_ARGS(__VA_ARGS__);     \
    static_assert(Count <= 32 /*sizeof(uint32_t)*8*/, "Too many flags used in  MA_DECLARE_FLAGS. A maximum number of 32 flags is allowed.");     \
    enum Enum       \
    {   \
         MA_PP_FOR_EACH( MA_DECLARE_FLAGS_ENUM, __VA_ARGS__)  \
        /* MA_PP_FOR_EACH_SIMPLE( MA_DECLARE_FLAGS_ENUM, __VA_ARGS__)*/   \
    };  \
    struct Bits     \
    {   \
     MA_PP_FOR_EACH( MA_DECLARE_FLAGS_BITS, __VA_ARGS__)  \
    /* MA_PP_FOR_EACH_SIMPLE( MA_DECLARE_FLAGS_BITS, __VA_ARGS__)*/   \
    };  \
    static const char* ToString(size_t value) \
    {   \
        switch (value)  \
        {   \
             MA_PP_FOR_EACH( MA_DECLARE_FLAGS_TO_STRING, __VA_ARGS__) \
            /* MA_PP_FOR_EACH_SIMPLE( MA_DECLARE_FLAGS_TO_STRING, __VA_ARGS__)*/      \
            default:    \
                 MA_NO_SWITCH_DEFAULT;   \
        }   \
    }   \
};  \
/*inline Flags<name>& operator|=(Flags<name>& lhs, const name::Enum rhs)*/\
inline Flags<name>& operator|=(Flags<name> lhs, const name::Enum rhs)\
{   \
    lhs.Set(rhs);   \
    return lhs;     \
}  \
/* TODO: optimize*/ \
inline Flags<name> operator|(const name::Enum lhs, const name::Enum rhs)\
{   \
    return (Flags<name>(lhs) | Flags<name>(rhs));    \
    /*return Flags<name>(lhs, rhs);*/   \
    /*return (Flags<name>(lhs) |= rhs);*/    \
}   \
/* TODO: optimize*/ \
inline Flags<name> operator|(const name::Enum lhs, const Flags<name>& rhs)  \
{   \
    /* |= returns a reference => out of scope?*/\
    return (Flags<name>(lhs) | rhs);    \
    /*return (Flags<name>(lhs) |= rhs);*/    \
}   \
/* TODO: optimize*/ \
inline Flags<name> operator|(const Flags<name>& lhs, const name::Enum rhs)  \
{   \
/* |= returns a reference => out of scope?*/\
    return (Flags<name>(rhs) | lhs);    \
    /*return (Flags<name>(rhs) |= lhs);*/    \
}

//////////////////////////
//
//struct Mode
//{
//    static const size_t Count = 4;
//    enum Enum
//    {
//        MODE_READ = 1 << 0,
//        MODE_WRITE = 1 << 1,
//        MODE_APPEND = 1 << 2,
//        MODE_RANDOM_ACCESS = 1 << 3
//    };
//    struct Bits
//    {
//        uint32_t MODE_READ : 1;
//        uint32_t MODE_WRITE : 1;
//        uint32_t MODE_APPEND : 1;
//        uint32_t MODE_RANDOM_ACCESS : 1;
//    };
//    static const char* ToString(size_t value)   // Mode::Enum / uint32_t
//    {
//        switch (value)
//        {
//        case MODE_READ:
//            return "MODE_READ";
//        case MODE_WRITE:
//            return "MODE_WRITE";
//        case MODE_APPEND: 
//            return "MODE_APPEND";
//        case MODE_RANDOM_ACCESS: 
//            return "MODE_RANDOM_ACCESS";
//        default:
//             MA_NO_SWITCH_DEFAULT;
//        }
//    }
//};

template <class T>
class Flags
{
    typedef typename T::Enum Enum;
    typedef typename T::Bits Bits;
public:
    typedef char Description[512];

    inline Flags(void)
        : m_flags(0)
    {
    }

    inline explicit Flags(Enum flag)
        : m_flags(flag)
    {
    }

    ////template <typename... Args>
    ////static T* get_instance(Args... args)
    //template <Enum... Enums>
    //inline explicit Flags(Enum flag, Enums... flags)
    //    : m_flags(flag)
    //{
    //    m_flags |= flags;
    //}

    inline void Set(Enum flag)
    {
        m_flags |= flag;
    }

    inline void Remove(Enum flag)
    {
        m_flags &= ~flag;
    }

    inline void Clear(void)
    {
        m_flags = 0;
    }

    inline bool IsSet(Enum flag) const
    {
        return ((m_flags & flag) != 0);
    }

    inline bool IsAnySet(void) const
    {
        return m_flags != 0;
    }

    inline bool AreAllSet(void) const
    {
        // 2 ^ T::Count is the number of possible permutations
        // 2 ^ T::Count - 1 is the value of the highest permutation
        // similar to n-1 being the last index of an n-length array
        return m_flags == 2 ^ T::Count - 1;
    }

    inline Flags &operator|=(const Flags &other)
    {
        m_flags |= other.m_flags;
        return *this;
    }

    inline Flags operator|(const Flags &other) const
    {
        return (Flags(*this) |= other);
        //return (Flags(m_flags) |= *other);
    }

    const char* ToString(Description& description) const
    {
        int offset = 0;
        for (size_t i = 0; i < T::Count; ++i)
        {
            if ((m_flags & (1u << i)) != 0)
            {
                offset += _snprintf_s(description + offset, sizeof(description) - offset, _TRUNCATE, "%s, ", T::ToString(1u << i));
            }
        }
        // remove the trailing comma, if any
        if (offset > 1)
            description[offset - 2] = 0;

        return description;
    }

private:
    inline explicit Flags(uint32_t flags)
        : m_flags(flags)
    {
    }

    union
    {
        uint32_t m_flags;
        Bits m_bits;
    };
};
