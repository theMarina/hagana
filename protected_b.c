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
int canary_val = 0;
int get_canary_val() {
	if (!canary_val)
		canary_val = urandom();
	return canary_val;
}
#include <stdio.h>
void main ()
{
int canary0 = get_canary_val();
	int k = 0;
int canary1 = get_canary_val();
int canary2 = get_canary_val();
	double aa;
int canary3 = get_canary_val();
if (canary0 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary1 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary2 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary3 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }

if (canary0 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary1 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary2 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary3 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
	while(2 != 3)
	{
if (canary0 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary1 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary2 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary3 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
		k = 5;
if (canary0 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary1 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary2 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary3 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
		k = 8;
if (canary0 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary1 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary2 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary3 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
	}
if (canary0 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary1 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary2 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary3 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }

if (canary0 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary1 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary2 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary3 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
	printf("cool");
if (canary0 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary1 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary2 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
if (canary3 != get_canary_val()) {printf("Alert! Buffer Overflow detected."); exit(1); }
}
