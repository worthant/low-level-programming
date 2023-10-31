#include <stdio.h>
#include <inttypes.h>
#define print_var(x) printf(#x " is %" PRIu64 "\n", x )
// #define print_var(x) printf(#x " is %d", x )
#define const 203847

int main(){
	uint64_t num = 304567293572643520;
	print_var(num);
	print_var(293856);
	print_var(const);

	return 0;
}