#define _CRT_SECURE_NO_WARNINGS
#include"jospeh.h"

int main()
{
	Ring* ring = NULL;
	ring = from_reader();
	Person * outsequence=NULL;
	reset(ring, 3, 3);
	/*next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);*/
	printf("finish\n");
	free_jospeh(ring);
	system("pause");
	return EXIT_SUCCESS;
}