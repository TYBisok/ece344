#include "common.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int factorial (int n);
bool isint (char* str);
int
main(int argc, char **argv)
{
	
	if (argc != 2) {
		printf("Huh?\n");
		return 0;
	}
	int num = atoi(argv[1]);
	if (num == 0){
		printf("Huh?\n");
		return 0;
	}
	else if (!isint(argv[1])) {
		printf("Huh?\n");
		return 0;
	}
	else{
		if (num > 12){
			printf("Overflow\n");
		}
		else printf("%d\n",factorial(num));
	return 0;
	}
}

int factorial (int n){
	if (n == 1) return 1;
	else return (n * factorial (n-1) );
}

bool isint (char* str){
	bool isinteger = true;
	for (int i = 0; i < strlen(str); ++i){
		if (!isdigit(str[i])) {
			isinteger = false;
			break;		
		}
	}
	return isinteger;
}
