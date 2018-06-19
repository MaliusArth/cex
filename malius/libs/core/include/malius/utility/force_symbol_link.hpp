#pragma once

#ifdef _MSC_VER
//TODO: #ifdef MA_COMPILER_MVC
#include <malius/core/lang.hpp>
#include <malius/preprocessor/cat.hpp>

/// Sounds like some of the .cpp files belong to a statically linked library, which is linked to the main executable. In this case, the linker will only pull in .obj files if that object file contains any symbol the linker needs for generating the executable. As soon as the linker has found all symbols necessary for creating a valid executable, it won�t look at any other remaining .obj files (if any).
/// 
/// This is just a byproduct of the(crappy) C++ compile / link mechanism.The only thing you can do against it is to force the linker to link certain.obj files by requiring symbols from the corresponding.cpp file.Those symbols could either be your config values, or some dummy variable which you force to be linked by e.g.setting its value.
/// 
/// As an example, something like the following will work :
/// 
/// At the top of some.cpp file you absolutely want to be linked in, you do :
//    char forceLinkageDummy = 0;
/// 
/// And in some file used by the main application(e.g.in main() itself), you could do:
/// 
//extern char forceLinkageDummy;
//forceLinkageDummy = 0;
/// 
/// There are other, platform - specific tricks you can use, like the following :
#define MA_FORCE_SYMBOL_LINK(symbolName) MA_PRAGMA(comment(linker, MA_PP_CAT("/include:", symbolName)))

/// Using the macro above, you can force the linker to include a certain symbol(using MSVC, at least). It needs to find this symbol somewhere, and if it does, it will link in the corresponding.obj file. Note that even using this trick it might be hard to link in certain files across (static) library boundaries.
#define MA_FORCE_SYMBOL_LINK_EXCLUDED(symbolName) /* This is not needed. */ /*char symbolName = 0;*/

#else
#include <malius/core/lang.hpp>

// Reference: http://stackoverflow.com/questions/599035/force-visual-studio-to-link-all-symbols-in-a-lib-file
// This is placed at the top of a file from which you know it will be linked.
#define MA_FORCE_SYMBOL_LINK(symbolName) \
	/* MA_MULTILINE_MACRO_BEGIN */ \
	void force_symbol_link_function_##symbolName(void) \
	{ \
		extern char force_symbol_link_##symbolName; \
		force_symbol_link_##symbolName = 0; \
	}
	// MA_MULTILINE_MACRO_END

// This is placed in the source file of functions that are being excluded.
#define MA_FORCE_SYMBOL_LINK_EXCLUDED(symbolName) \
	/* MA_MULTILINE_MACRO_BEGIN */ \
	char force_symbol_link_##symbolName = 0
	// MA_MULTILINE_MACRO_END
#endif


MA_FORCE_SYMBOL_LINK("force_linkage_utility")
