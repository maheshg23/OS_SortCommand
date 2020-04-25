#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
	char *str = "Hello world";
	write(1, str, strlen(str));
	exit();
}