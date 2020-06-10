#define _CRT_SECURE_NO_WARNINGS
#include"reader.h"
#include"jospeh.h"

struct Ring* create_jospeh(Person** reader)
{
	Ring* ring=NULL;
	struct Person** temp = (Person**) malloc(sizeof(struct Person*) * MAXLENGTH);
	ring = init_ring();
	ring->person = temp;
	ring->length = 0;

	for (int i = 0; i < 10; ++i)
	{
		temp[i] = (Person *)malloc(sizeof(struct Person));
		temp[i]->name = (char*)malloc(sizeof(char) * NAMELENRGTH);
		memset(temp[i]->name, 0, NAMELENRGTH);
		strcpy(temp[i]->name, reader[i]->name);
		ring->length++;
		temp[i]->age = reader[i]->age;
	}
	return ring;
}

Ring*  from_reader()
{
	Ring* ring;
	Person** readerdata = NULL;
	readerdata = reader();
	ring =create_jospeh(readerdata);
	return ring;
}

void append(Person person, Ring* ring)
{
	int len=ring->length;
	ring->person[len] = (Person*)malloc(sizeof(struct Person));
	ring->person[len]->name =(char*) malloc(sizeof(char) * NAMELENRGTH );
	memset(ring->person[len]->name, 0, NAMELENRGTH);
	strcpy(ring->person[len]->name, person.name);
	ring->person[len]->age = person.age;
	ring->length++;
}

bool is_empty(const Ring* ring)
{
	if (ring->length == 0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void show_ring(const Ring* ring)
{
	for (int i = 0; i < ring->length; i++)
	{
		printf("%s", ring->person[i]->name);
		printf("%d", ring->person[i]->age);
	}
}

void popspace(Ring* ring, int pos)
{


}

void pop(Ring* ring, int pos)
{
	printf("%s\n", ring->person[pos]->name);

	 if (ring->length-1 >= pos)
		{
			for (int i = pos; i < ring->length - 1; i++)
			{
				strcpy(ring->person[i]->name, ring->person[i+1]->name);
				ring->person[i]->age = ring->person[i + 1]->age;
			}
			free(ring->person[ring->length - 1]->name);
			ring->person[ring->length - 1]->name = NULL;
			free(ring->person[ring->length - 1]);
			ring->person[ring->length - 1] = NULL;
			ring->length--;
		}
}

void next(Ring* ring)
{
	int size = ring->length;
	int location = ring->location;
	int step = ring->step;
	ring->id = ((ring->id+(step - 1))) % size;
	pop(ring, ring->id);
	
	

}

void reset(Ring* ring,int location,int step)
{

	ring->location = location;
	ring->step = step;
	ring->id = location - 1;
}


Ring* init_ring()
{
	struct Ring* ring = (Ring*)malloc(sizeof(struct Ring));
	ring->person = NULL;
	ring->length = 0;
	ring->location = 0;
	ring->step = 0;
	ring->id = 0;
	return ring;
}

void free_jospeh(Ring* ring)
{
	int length = ring->length;
	if (NULL == ring)
	{
		return;
	}
	if (ring->person == NULL)
	{
		free(ring);
		ring = NULL;
		return;
	}
	printf("%d\n",ring->length);
	if (ring->person != NULL)
	{
		for (int i = 0; i < length; i++)
		{
			if (ring->person[i] == NULL)
			{
				continue;
			}

			if (ring->person[i]->name != NULL)
			{
				printf("Name:%s的内存被释放!\n", ring->person[i]->name);
				free(ring->person[i]->name);
				ring->person[i]->name = NULL;
			}

			ring->length--;
			free(ring->person[i]);
			ring->person[i] = NULL;
		}
	}

	free(ring);
	ring = NULL;

}

