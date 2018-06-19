#include "hooks/pragma_approach/HookPragmaHandler.h"

#include <sstream>

namespace ma
{
	void HookPragmaHandler::HandlePragma(clang::Preprocessor &pp,
											clang::PragmaIntroducerKind introducer,
											clang::Token &firstToken)
	{
		clang::Token token;
		// first slurp the directive content in a string.
		// TODO: dont use stream
		std::ostringstream myAnnotateDirective;
		while(token.isNot(clang::tok::eod))
		{
			pp.Lex(token);
			if(token.isNot(clang::tok::eod))
			{
				myAnnotateDirective << pp.getSpelling(token);
			}
		}

	token.startToken();
	token.setKind(clang::tok::annot_pragma_ma_inject_hook);
	token.setLocation(firstToken.getLocation());
	token.setAnnotationEndLoc(firstToken.getLocation());
	// TODO: there should be something better than this strdup :-/
	token.setAnnotationValue(strdup(myAnnotateDirective.str().c_str()));

	pp.EnterToken(token);
	}
}