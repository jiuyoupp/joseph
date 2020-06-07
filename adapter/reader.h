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
void file_show(const char** pArr, int len);
int char_to_int(char* str);
Person** get_data(char** pArr, int len);
Person** reader();

#endif
