#include <stdio.h>
#include <stdlib.h>
/* best random source on UNIX-like systems. */
int urandom() {
#ifdef __unix__
	int var;
	FILE *fd = fopen("/dev/urandom", "r");
	fread(&var, sizeof(int), 1, fd);
	fclose(fd);
	return var;
#else
	return 4;
#endif
}
