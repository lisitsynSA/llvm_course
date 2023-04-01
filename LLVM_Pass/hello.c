#include <stdio.h>

void func(int x) {
	if (x) {
		printf("Hello, world!\n");
	} else {
		printf("Hell, world!\n");
	}
}

int main()
{
	func(1);
	return 0;
}
