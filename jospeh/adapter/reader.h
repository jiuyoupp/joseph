#ifndef _REDER_H_
#define _REDER_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"person.h"

#define N 1024
#define MAXLENGTH 150
#define NAMELENRGTH 12

int get_file_line(FILE* file);
void get_file(FILE* file, char** pArr, int lin);
void char_to_int(char* str,int* age);
Person** data_to_reader(char** pArr, int len);
Person** reader(int* lenth, const char* path);
void free_file_space(char** parr, int lin);
void free_reader(Person** people, int lin);

#endif
