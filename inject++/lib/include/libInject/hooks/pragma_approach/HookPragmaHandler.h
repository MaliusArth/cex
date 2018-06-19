#pragma once

// #include <llvm/l>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/Pragma.h>
#include <clang/Lex/Token.h>

namespace ma
{
	class HookPragmaHandler
	{

		public:
		void HandlePragma(clang::Preprocessor &pp,
							clang::PragmaIntroducerKind introducer,
							clang::Token &firstToken);
	};

}
