#include <sys/time.h>
#include <stdlib.h>

long get_random_integer( long min, long max )
{
	time_t t;
	static int i = 0;
	srand(time(&t) + i++);
	return rand() % ( max - min + 1 ) + min;
}
