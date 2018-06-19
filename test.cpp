#include "inject++/lib/include/libInject/hooks/macro_approach.h"

#include <stdio.h>


int ma_ct_main(void) MA_INJECT
{
	printf("compile time execution");
	return 1;
}

int main(int argc, const char **argv)
{
	printf("Hello world!: %d", 7);
	return 1;
}
