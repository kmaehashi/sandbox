#include <stdio.h>
#include <shadow.h>

int main() {
	struct spwd *dat = getspnam("kenichi");
	printf("his password is %s.\n", dat->sp_pwdp);
	return 0;
}

