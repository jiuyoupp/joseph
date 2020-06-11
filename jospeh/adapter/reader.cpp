#define _CRT_SECURE_NO_WARNINGS
#include"reader.h"

int get_file_line(FILE* file)
{
	if (NULL == file)
	{
		return -1;
	}

	char buf[N] = { 0 };
	int lin = 0;
	//fgets ���ж�ȡ ���ɹ���ȡ�ַ����������ļ�ĩβ�����NULL
	while (fgets(buf, N, file) != NULL)
	{
		++lin;
	}
	//������ƶ����ļ���ʼ �����´ζ�ȡ���ļ�ʱ����ļ�ĩβ��ʼ��

	fseek(file, 0, SEEK_SET);
	return lin;
}

void get_file(FILE* file, char** parr, int lin)
{
	// ����������
	char buf[N] = { 0 };
	int index = 0;
	int lindata = 0;
	//����ǰ�з����ڴ�

	if (NULL == file)
	{
		return;
	}

	if (NULL == parr)
	{
		return;
	}

	if (lin <= 0)
	{
		return;
	}

	while (fgets(buf, N, file) != NULL)
	{
		lindata = strlen(buf) + 1;
		//����ǰ�з����ڴ�
		parr[index] = (char*)malloc(sizeof(char) * lindata);
		//�������ݿ������ռ���
		strcpy(parr[index], buf);
		index++;
		memset(buf, 0, N);
		lindata = 0;
	}
}

void char_to_int(char* str, int* age)
{
	int i = 0;
	char strage[6];
	while (*str != '\n')
	{

		strage[i] = *str;
		i++;
		str++;
	}
	sscanf(strage, "%d", age);
}

Person** data_to_reader(char** parr, int len)
{
	if (NULL == parr)
	{
		return NULL;
	}

	Person** reader = (Person**)malloc(sizeof(Person*) * len);

	int age = 0;
	for (int i = 0; i < len; ++i)
	{

		char* token;
		reader[i] = (Person*)malloc(sizeof(Person));
		reader[i]->name = (char*)malloc(sizeof(char) * NAMELENRGTH );
		token = strtok(*(parr + i), " ");
		strcpy(reader[i]->name, token);
		token = strtok(NULL, "\0");
		char_to_int(token, &age);
		reader[i]->age = age;

	}

	return reader;
}

Person** reader(int* length,const char* path)
{
	FILE* file = fopen(path, "r");

	if (NULL == file )
	{
		printf("�ļ���ʧ�ܣ�");
		return NULL;
	}

	int lin = get_file_line(file);
	char** parr = (char**)malloc(sizeof(char*) * lin);
	memset(parr, 0, lin);
	get_file(file, parr, lin);
	Person** reader = NULL;
	reader = data_to_reader(parr, lin);
	fclose(file);
	*length = lin;
	free_file_space(parr, lin);
	return reader;
}

void free_file_space(char ** parr,int lin)
{

	if (NULL == parr)
	{
		return;
	}

	for (int i = 0; i < lin; ++i)
	{

		if (parr[i] != NULL)
		{
			free(parr[i]);
			parr[i] = NULL;
		}
	}

	free(parr);
	parr = NULL;
}

void free_reader(Person** people,int lin)
{
	if (NULL == people)
	{
		return;
	}

	for (int i = 0; i < lin; ++i)
	{
		if (people[i] == NULL)
		{
			continue;
		}

		if (people[i]->name != NULL)
		{
			printf("Name:%s���ڴ汻�ͷ�!\n", people[i]->name);
			free(people[i]->name);
			people[i]->name = NULL;
		}
		free(people[i]);
		people[i] = NULL;
	}

	free(people);
	people = NULL;
}