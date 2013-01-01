#include <stdio.h>

int main() {
	printf("%d\n", gcd(56, 42));
}

int gcd(int a, int b) {
	if (a == 0) {
	return b;
	}
	return gcd(b % a, a);
}

