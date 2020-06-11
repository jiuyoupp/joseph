#define _CRT_SECURE_NO_WARNINGS
#include"jospeh.h"

int main()
{
	Ring* ring = NULL;
	const char* path = "D:\\Ccode\\jospeh\\peopledata.txt";
	ring = create_jospeh(path);
	Person * outsequence=NULL;
	reset(ring, 3, 3);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	//next(ring);
	//next(ring);
	//next(ring);
	//next(ring);
	printf("finish\n");
	clear_jospeh(ring);
	system("pause");
	return EXIT_SUCCESS;
}