#ifndef _JOSPEH_H_
#define _JOSPEH_H_

#include"reader.h"

typedef struct Ring
{
	Person** person;
	int length;
	int step;
	int location;
	int id;

}Ring;

Ring* init_ring(Ring* ring);
struct Ring* create_jospeh(Person** reader);
Ring* from_reader();
void append(Person person, Ring* ring);
bool is_empty(const Ring* ring);
void show_ring(const Ring* ring);
void pop(Ring* ring, int pos);
void next(Ring* ring);
void reset(Ring* ring, int location, int step);

#endif