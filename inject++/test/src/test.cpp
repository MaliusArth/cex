/* #include "clang/Tooling/Tooling.h"

TEST(runToolOnCode, CanSyntaxCheckCode) {
  // runToolOnCode returns whether the action was correctly run over the
  // given code.
  EXPECT_TRUE(runToolOnCode(new clang::SyntaxOnlyAction, "class X {};"));
} */

#include <libInject/hooks/macro_approach.h>

#include <cstdio>


int ma_ct_main(void) MA_INJECT
{
	std::printf("compile time execution");
	return 1;
}

int main(int argc, const char **argv)
{
	std::printf("Hello world!: %d", 7);
	return 1;
}
