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

// L指向尾结点
Ring InitList()
{
	int i;
	Ring L = (Ring)malloc(sizeof(Node));
	if (!L) // 存储分配失败
		exit(OVERFLOW);
	L->next = L; // 指针域为空
	L->length = 0;
	return L;

}


Status ListEmpty(Ring L)
{ // 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
	if (L->next != L) // 非空
		return FALSE;
	else
		return TRUE;
}
Status RingAppend(Ring L, Person q)
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
		L->length++;
	}
	return OK;

}

int ListLength(Ring L)
{// 初始条件：线性表L已存在。操作结果：返回L中数据元素个数
	return L->length;
}

bool IsEmpty(Ring L)
{
	if (L->length)
		return false;
	else
		return true;
}

Status ListDelete(Ring L, int pos, Person *qq)
{
	Ring p = L->next; // p指向头结点
	Ring q = NULL;
	Ring s = NULL;
	int j = 0;
	if (pos <= 0 || pos > ListLength(L)) // 第i个元素不存在
		return ERROR;
	while (j < pos - 1) // 寻找第i-1个结点
	{
		p = p->next;
		j++;
	}
	q = p->next; // q指向待删除结点
	*qq = q->person;
	p->next = q->next;
	if (L == q) // 删除的是表尾元素
		L = p;
	free(q); // 释放待删除结点
	q = NULL;
	L->length--;
	return OK;

}


Person NextPerson(Ring L,int step,int location)
{
	if (IsEmpty(L) != false)
	{
		printf("环为空");
	}
	int size = L->length;
	int id = (location - 1) % size;
	id = (id + (step - 1)) % size;
	Person outperson;
	ListDelete(L, id, &outperson);
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
	Person P1;
	Person P2;
	Ring jospeh=NULL;
	Ring pp = NULL;
	P1.age = 13;
	P2.age = 19;
	P1.name = (char*)malloc(sizeof(char) * 12);
	strcpy(P1.name,"sddsa" );
	P2.name = (char*)malloc(sizeof(char) * 12);
	strcpy(P2.name, "dkkk");
	jospeh = InitList();
	printf("2222\n");
	RingAppend(jospeh, P1);
	RingAppend(jospeh, P2);
	//第一个指针没有存放变量值
	//第一个尾指针
	printf("%d\n", jospeh->person.age);
	printf("%s\n", jospeh->person.name);
	//第二个尾指针
	printf("%d\n", jospeh->next->person.age);
	printf("%s\n", jospeh->next->person.name);
	char nan;
	int age;
	Person qq;
	
	NextPerson(jospeh, 2, 3);
	NextPerson(jospeh, 2, 3);
	//Person qq ;
	//ListDelete(jospeh, 1,&qq);
	//printf("%s", qq.name);
	FreeSpace(jospeh);

	system("pause");
	return EXIT_SUCCESS;
}