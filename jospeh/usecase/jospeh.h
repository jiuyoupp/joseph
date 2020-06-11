#ifndef _JOSPEH_H_
#define _JOSPEH_H_

#include"reader.h"

typedef struct Ring
{
	Person** people;
	Person** temppeople;
	int length;
	int templength;
	int step;
	int location;
	int id;

}Ring;

Person** copy_people(Person** peopledata, int lin);
Ring* init_ring();
struct Ring* from_reader(Person** reader,int lin);
Ring* create_jospeh(const char* path);
void append(Person person, Ring* ring);
bool is_empty(const Ring* ring);
void show_ring(const Ring* ring);
void pop(Ring* ring, int pos);
void next(Ring* ring);
void reset(Ring* ring, int location, int step);
void free_people(Person** people, int lin);
void clear_jospeh(Ring* ring);
#endif