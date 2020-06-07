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
	// ����������
	char buf[N] = { 0 };
	int index = 0;

	while (fgets(buf, N, file) != NULL)
	{
		//���buf memset(buf, 0, 1024);
		int lindate = strlen(buf) + 1;
		//����ǰ�з����ڴ�
		char* plindate = (char*)malloc(sizeof(char) * lindate);
		//�������ݿ������ռ���
		strcpy(plindate, buf);
		pArr[index++] = plindate;
		memset(buf, 0, N);
	}
}

void file_show(const char** pArr, int len)
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
		reader[i]->name = (char*)malloc(sizeof(char) * NAMELENRGTH + 1);
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
		printf("�ļ���ʧ�ܣ�");
		return NULL;
	}
	//ͳ���ļ�����

	int lin = get_file_line(file);
	//����ָ������ֱ�ָ������
	char** pArr = (char**)malloc(sizeof(char*) * lin);
	memset(pArr, 0, lin);
	get_file(file, pArr, lin);
	Person** reader;
	reader = get_data(pArr, lin);
	//file_show(pArr, lin);
	fclose(file);
	return reader;
}