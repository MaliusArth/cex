#pragma once

#ifdef  MA_EXPORTS
#   define  MA_API __declspec(dllexport)
#else
#   define  MA_API __declspec(dllimport)
#endif
