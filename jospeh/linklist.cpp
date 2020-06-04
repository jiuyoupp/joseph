#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFERASIBLE -1
#define OVERFLOW -2

typedef int Status;   /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType; /* ElemType���͸���ʵ������������������Ϊint */

typedef struct Person
{
	char *name;
	int age;
}Person;

typedef struct Node
{
	Person person;
	int length;
	struct Node* next;
}Node, * Ring;

int ListLength(Ring L);

Status ListEmpty(Ring L);
void ClearList(Ring L);
int LocateElem(Ring L, ElemType e);
Status GetElem(Ring L, int pos, ElemType* e);

Status ListInsert(Ring L, int pos, ElemType e);
void ListTraverse(Ring L);

#define N 1024
//���ļ��ļ�
//��ȡ�ļ�����
//�����ļ���������ָ��
//
int GetFileLin(FILE* file)
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

void GetFile(FILE* file, char** pArr, int lin)
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

void FileShow(char** pArr, int len)
{
	for (int i = 0; i < len; ++i)
	{
		printf("%s", pArr[i]);
	}
}
int CharToInt(char* str)
{
	int i = 0;
	while (*str!='\n')
	{
		if (i==0)
		{
			i+=(int)(*str-'0');
			str++;
		}
		else 
		{
			i = i * 10+(int)((*str) - '0');
			str++;
		}
	}
	return i;

}
Person** GetData(char** pArr, int len)
{
	Person** reader = (Person**)malloc(sizeof(Person*) * len);
	
	int age = 0;
	for (int i = 0; i < len; ++i)
	{

		char* token;
		reader[i] =(Person *) malloc(sizeof(Person));
		reader[i]->name = (char*)malloc(sizeof(char) * 12 + 1);
		token = strtok(*(pArr+i), " ");
		strcpy(reader[i]->name, token);
		token = strtok(NULL, "\0");
		age = CharToInt(token);
		reader[i]->age = age;
		//reader[i]->age = *(token) -'0';
	/*	printf("%s\n", reader[i]->name);
		printf("%d\n",age);*/
	}
	return reader;
}
Person** Reader()
{
	FILE* file = fopen("D:\\Ccode\\jospeh\\peopledata.txt", "r");
	if (file == NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return NULL;
	}
	//ͳ���ļ�����

	int lin = GetFileLin(file);
	//����ָ������ֱ�ָ������
	char** pArr = (char**)malloc(sizeof(char*) * lin);
	memset(pArr, 0, lin);
	GetFile(file, pArr, lin);
	Person** reader;
	reader = GetData(pArr,lin);
	//FileShow(pArr, lin);
	printf("%d", lin);
	fclose(file);
	return reader;
}



// Lָ��β���
Ring InitList()
{
	int i;
	Ring L = (Ring)malloc(sizeof(Node));
	if (!L) // �洢����ʧ��
	{
		exit(OVERFLOW);
	}
	L->next = L; // ָ����Ϊ��
	L->length = 0;
	return L;

}

Status ListEmpty(Ring L)
{ // ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
	if (L->next != L) // �ǿ�
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

Status FromReader(Ring L, Person** reader,int lin)
{

	for (int i = 0; i < lin; ++i)
	{
		if (L->next->length == 0)
		{

			L->person.name = (char*)malloc(sizeof(char) * 12 + 1);
			strcpy(L->person.name, reader[i]->name); // ����L��
			L->person.age = reader[i]->age;
			L->next->length++;
		}

		else
		{
			Ring s;
			Ring head = L->next;
			s = (Ring)malloc(sizeof(Node)); // �����½��
			s->person.name = (char*)malloc(sizeof(char) * 12 + 1);
			s->person.age = reader[i]->age;
			strcpy(s->person.name, reader[i]->name); // ����L��
			//s->person = q; �ṹ�����ж��ڴ治��ʹ�ø÷��������ͷ��ڴ�ʱ���ܳ���
			s->next = head;
			L->next = s;
			L = s;
			L->next->length++;
		}
	}
	return OK;

}
Status Append(Ring L, Person q)
{
	if (L->length == 0)
	{

		L->person.name =(char*) malloc(sizeof(char) * 12+1);
		strcpy(L->person.name, q.name); // ����L��
		L->person.age = q.age;
		L->length++;
	}

	else
	{
		Ring s;
		Ring head = L->next;
		s = (Ring)malloc(sizeof(Node)); // �����½��
		s->person.name = (char*)malloc(sizeof(char) * 12 + 1);
		s->person.age = q.age;
		strcpy(s->person.name, q.name); // ����L��
		//s->person = q; �ṹ�����ж��ڴ治��ʹ�ø÷��������ͷ��ڴ�ʱ���ܳ���
		s->next = head;
		L->next = s;
		L = s;
		//ͷָ�뱣��������
		L->next->length++;
	}
	return OK;

}

int ListLength(Ring L)
{// ��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ���
	return L->next->length;
}

bool IsEmpty(Ring L)
{
	if (L->next->length)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Status ListDelete(Ring L, int pos, Person *qq)
{
	Ring p = L->next; // pָ��ͷ���
	Ring q = NULL;
	Ring s = NULL;
	int j = 0;
	if (pos <= 0 || pos > ListLength(L)) // ��i��Ԫ�ز�����
	{
		return ERROR;
	}
	while (j < pos - 1) // Ѱ�ҵ�i-1�����
	{
		p = p->next;
		j++;
	}
	q = p->next; // qָ���ɾ�����
	qq->age = q->person.age;
	qq->name = (char*)malloc(sizeof(char) * 12 + 1);
	qq->name = q->person.name;
	p->next = q->next;
	printf("name%s,age%d",qq->name,qq->age);
	if (L == q) // ɾ�����Ǳ�βԪ��
	{
		L = p;
	}
	free(q); // �ͷŴ�ɾ�����
	q = NULL;
	L->next->length--;
	return OK;

}


Person* NextPerson(Ring L,int step,int location)
{
	if (IsEmpty(L) != false)
	{
		printf("��Ϊ��");
	}
	int size = L->next->length;
	int id = (location - 1) % size;
	id = (id + (step - 1)) % size;
	Person* outperson=NULL;
	ListDelete(L, id, outperson);
	return outperson;


}
void FreeSpace(Ring L)
{

	if (NULL == L)
	{
		return;
	}
	Ring p = L->next;
	Ring q = NULL;
	while(p!= L)
	{

		if (p->person.name != NULL)
		{
			printf("Name���ڴ汻�ͷ�!\n");
			free(p->person.name);
			p->person.name = NULL;
		}
		q = p->next;
		free(p);
		p = NULL;
		p = q;

	}
	printf("���һ���ڴ汻�ͷ�");
	free(L);
	L = NULL;
}
int main(void)
{
	
	Ring jospeh=NULL;
	//Ring pp = NULL;
	//P1.age = 13;
	//P2.age = 19;
	//P1.name = (char*)malloc(sizeof(char) * 12);
	//strcpy(P1.name,"sddsa" );
	//P2.name = (char*)malloc(sizeof(char) * 12);
	//strcpy(P2.name, "dkkk");

	//printf("2222\n");
	//Append(jospeh, P1);
	//Append(jospeh, P2);
	////��һ��ָ��û�д�ű���ֵ
	////��һ��βָ��
	//printf("%d\n", jospeh->person.age);
	//printf("%s\n", jospeh->person.name);
	////�ڶ���βָ��
	//printf("%d\n", jospeh->next->person.age);
	//printf("%s\n", jospeh->next->person.name);
	/*char nan;
	int age;
	Person qq;
	
	NextPerson(jospeh, 2, 3);
	NextPerson(jospeh, 2, 3);*/
	//Person qq ;
	//ListDelete(jospeh, 1,&qq);
	//printf("%s", qq.name);
	jospeh = InitList();
	Person** sss;
	sss=Reader();
	FromReader(jospeh,sss,10);
	
	NextPerson(jospeh, 2, 3);
	NextPerson(jospeh, 2, 3);
	NextPerson(jospeh, 2, 3);
	NextPerson(jospeh, 2, 3);
	FreeSpace(jospeh);

	system("pause");
	return EXIT_SUCCESS;
}