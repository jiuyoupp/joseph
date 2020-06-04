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

typedef int Status;   /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType; /* ElemType类型根据实际情况而定，这里假设为int */

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
//打开文件文件
//获取文件行数
//根据文件行数开辟指针
//
int GetFileLin(FILE* file)
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
		printf("文件打开失败！");
		return NULL;
	}
	//统计文件行数

	int lin = GetFileLin(file);
	//开辟指针数组分别指向数据
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



// L指向尾结点
Ring InitList()
{
	int i;
	Ring L = (Ring)malloc(sizeof(Node));
	if (!L) // 存储分配失败
	{
		exit(OVERFLOW);
	}
	L->next = L; // 指针域为空
	L->length = 0;
	return L;

}

Status ListEmpty(Ring L)
{ // 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
	if (L->next != L) // 非空
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
			strcpy(L->person.name, reader[i]->name); // 插入L中
			L->person.age = reader[i]->age;
			L->next->length++;
		}

		else
		{
			Ring s;
			Ring head = L->next;
			s = (Ring)malloc(sizeof(Node)); // 生成新结点
			s->person.name = (char*)malloc(sizeof(char) * 12 + 1);
			s->person.age = reader[i]->age;
			strcpy(s->person.name, reader[i]->name); // 插入L中
			//s->person = q; 结构体中有堆内存不能使用该方法否则释放内存时可能出错
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
		strcpy(L->person.name, q.name); // 插入L中
		L->person.age = q.age;
		L->length++;
	}

	else
	{
		Ring s;
		Ring head = L->next;
		s = (Ring)malloc(sizeof(Node)); // 生成新结点
		s->person.name = (char*)malloc(sizeof(char) * 12 + 1);
		s->person.age = q.age;
		strcpy(s->person.name, q.name); // 插入L中
		//s->person = q; 结构体中有堆内存不能使用该方法否则释放内存时可能出错
		s->next = head;
		L->next = s;
		L = s;
		//头指针保存链表长度
		L->next->length++;
	}
	return OK;

}

int ListLength(Ring L)
{// 初始条件：线性表L已存在。操作结果：返回L中数据元素个数
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
	Ring p = L->next; // p指向头结点
	Ring q = NULL;
	Ring s = NULL;
	int j = 0;
	if (pos <= 0 || pos > ListLength(L)) // 第i个元素不存在
	{
		return ERROR;
	}
	while (j < pos - 1) // 寻找第i-1个结点
	{
		p = p->next;
		j++;
	}
	q = p->next; // q指向待删除结点
	qq->age = q->person.age;
	qq->name = (char*)malloc(sizeof(char) * 12 + 1);
	qq->name = q->person.name;
	p->next = q->next;
	printf("name%s,age%d",qq->name,qq->age);
	if (L == q) // 删除的是表尾元素
	{
		L = p;
	}
	free(q); // 释放待删除结点
	q = NULL;
	L->next->length--;
	return OK;

}


Person* NextPerson(Ring L,int step,int location)
{
	if (IsEmpty(L) != false)
	{
		printf("环为空");
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
			printf("Name的内存被释放!\n");
			free(p->person.name);
			p->person.name = NULL;
		}
		q = p->next;
		free(p);
		p = NULL;
		p = q;

	}
	printf("最后一个内存被释放");
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
	////第一个指针没有存放变量值
	////第一个尾指针
	//printf("%d\n", jospeh->person.age);
	//printf("%s\n", jospeh->person.name);
	////第二个尾指针
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