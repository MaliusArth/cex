/* #include "clang/Tooling/Tooling.h"

TEST(runToolOnCode, CanSyntaxCheckCode) {
  // runToolOnCode returns whether the action was correctly run over the
  // given code.
  EXPECT_TRUE(runToolOnCode(new clang::SyntaxOnlyAction, "class X {};"));
} */

#include "test.h"

#include <libCEX/hooks/macro_approach.h>

// #include "malius/log/Logger.hpp"
// #include "malius/core/lang.hpp"

#include <cstdio>

int fib(int n)
{
    if (n<2) return n;
    return fib(n-1) + fib(n-2);
}

void printFib(int n)
{
	int x = n;
	for(size_t i = 11; i != 0; i--)
	{
		x = fib(x);
		std::printf("%d", x);
	}
}

// int factorial(int n)
// {
// 	//TODO
// }

//problem: cross-compiler compatibility
// int ma_ct_main(void) MA_INJECT // clang/gcc
// MA_INJECT int ma_ct_main(void) // msvc
// this results in a cross-platform solution that would look like this:
//MA_INJECT_BEGIN int ma_ct_main(void) MA_INJECT_END
// __attribute__((annotate("cex_run")))
// MA_ATTRIBUTE(cex_run)
int cex_main(void) CEX_RUN
{
	std::printf("compile time execution");
	printFib(2);
	return 1;
}


void cex_main(int);

void cex_main(int)
{

}

void cex_main(float);
void cex_main(float);

void cex_main(float)
{

}



void cex_main(char const *);


void cex_main(char const *)
{

}


MA_ANNOTATE(dont_run)
MA_ANNOTATE(seriously_dont)
MA_ANNOTATE(cex_run)
void should_find_too(int)
{
	std::printf("should find too");

}

// benefit is that it looks the same on all compilers
// #pragma run
int ma_ct_main2(void)
{
	std::printf("compile time execution");
	printFib(2);
	return 1;
}


int main(int argc, const char **argv)
{
	std::printf("Hello world!: %d\n", 7);
	std::printf("Fib: ");
	printFib(2);
	std::printf("\n");

	//cex func
	// cex_main();

	return 1;
}
