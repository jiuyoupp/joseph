#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Person
{
	char* name;
	int age;
}Person;

typedef struct Ring 
{
	Person **person;
	int length;
	int step;
	int location;
	int id;

}Ring;

#define N 1024
#define MAXLENGTH 150
#define NAMELENRGTH 12

Ring* init_ring(Ring* ring);
int get_file_line(FILE* file);
void get_file(FILE* file, char** pArr, int lin);
void file_show(char** pArr, int len);
int char_to_int(char* str);
Person** get_data(char** pArr, int len);
Person** reader();
struct Ring* create_jospeh(Person** reader);
Ring* from_reader();
void append(Person person, Ring* ring);
bool is_empty(Ring* ring);
void show_ring(Ring* ring);
void pop(Ring* ring, int pos);
void next(Ring* ring);
void reset(Ring* ring, int location, int step);

int get_file_line(FILE* file)
{
	if (NULL == file)
	{
		return -1;
	}

	char buf[N] = { 0 };
	int lin = 0;
	//fgets 按行读取 ，成功读取字符串，读到文件末尾或出错NULL
	while (fgets(buf, N, file) != NULL)
	{
		++lin;
	}
	//将光标移动到文件开始 否则下次读取该文件时会从文件末尾开始读

	fseek(file, 0, SEEK_SET);
	return lin;
}

void get_file(FILE* file, char** pArr, int lin)
{
	if (NULL == file)
	{
		return;
	}

	if (NULL == pArr)
	{
		return;
	}

	if (lin <= 0)
	{
		return;
	}
	// 创建缓冲区
	char buf[N] = { 0 };
	int index = 0;

	while (fgets(buf, N, file) != NULL)
	{
		//清空buf memset(buf, 0, 1024);
		int lindate = strlen(buf) + 1;
		//给当前行分配内存
		char* plindate = (char*)malloc(sizeof(char) * lindate);
		//将行数据拷贝到空间中
		strcpy(plindate, buf);
		pArr[index++] = plindate;
		memset(buf, 0, N);
	}
}

void file_show(char** pArr, int len)
{
	for (int i = 0; i < len; ++i)
	{
		printf("%s", pArr[i]);
	}
}

int char_to_int(char* str)
{
	int i = 0;
	while (*str != '\n')
	{
		if (i == 0)
		{
			i += (int)(*str - '0');
			str++;
		}
		else
		{
			i = i * 10 + (int)((*str) - '0');
			str++;
		}
	}
	return i;

}
Person** get_data(char** pArr, int len)
{
	Person** reader = (Person**)malloc(sizeof(Person*) * len);

	int age = 0;
	for (int i = 0; i < len; ++i)
	{

		char* token;
		reader[i] = (Person*)malloc(sizeof(Person));
		reader[i]->name = (char*)malloc(sizeof(char) *  NAMELENRGTH +1 );
		token = strtok(*(pArr + i), " ");
		strcpy(reader[i]->name, token);
		token = strtok(NULL, "\0");
		age = char_to_int(token);
		reader[i]->age = age;

	}
	return reader;
}
Person** reader()
{
	FILE* file = fopen("D:\\Ccode\\jospeh\\peopledata.txt", "r");
	if (file == NULL)
	{
		printf("文件打开失败！");
		return NULL;
	}
	//统计文件行数

	int lin = get_file_line(file);
	//开辟指针数组分别指向数据
	char** pArr = (char**)malloc(sizeof(char*) * lin);
	memset(pArr, 0, lin);
	get_file(file, pArr, lin);
	Person** reader;
	reader = get_data(pArr, lin);
	//file_show(pArr, lin);
	fclose(file);
	return reader;
}

struct Ring* create_jospeh(Person** reader)
{
	struct Person** temp = malloc(sizeof(struct Person*) * MAXLENGTH);
	struct Ring *ring= (struct Ring*)malloc(sizeof(struct Ring));
	ring->person = temp;
	ring->length = 0;

	for (int i = 0; i < 10; ++i)
	{
		temp[i] = malloc(sizeof(struct Person));
		temp[i]->name = malloc(sizeof(char) * 12);
		memset(temp[i]->name, 0, 12);
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

bool is_empty(Ring* ring)
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

void show_ring(Ring* ring)
{
	for (int i = 0; i < ring->length; i++)
	{
		printf("%s", ring->person[i]->name);
		printf("%s", ring->person[i]->age);
	}
}

void pop(Ring* ring, int pos)
{
	printf("%s", ring->person[pos]->name);

	if (ring->length == pos)
	{
		free(ring->person[pos - 1]->name);
		ring->person[pos - 1]->name = NULL;
		free(ring->person[pos - 1]);
		ring->person[pos - 1] = NULL;
		ring->length--;
	}

	if (ring->length > pos)
	{
		for (int i = pos; i < ring->length - 1; i++)
		{
			strcpy(ring->person[i]->name, ring->person[i + 1]->name);
			ring->person[i]->age = ring->person[i + 1]->age;
		}
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
	int id = (ring->id+(location - 1)) % size;
	ring->id += step - 1;
	pop(ring, id);

}

void reset(Ring* ring,int location,int step)
{

	ring->location = location;
	ring->step = step;
	ring->id = location - 1;
}


Ring* init_ring(Ring* ring)
{
	ring->person = NULL;
	ring->length = 0;
	ring->location = 0;
	ring->step = 0;
	ring->id = 0;
}

int main()
{
	Ring* ring = NULL;
	ring=from_reader();
	reset(ring, 3, 3);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	next(ring);
	system("pause");
	return EXIT_SUCCESS;
}

