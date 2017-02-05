/*	@Author
	Student Name: Bulent Koray OZ
	Student ID: 150130281
	Date: 24.12.2016
*/

#ifndef STRUCTS_H
#define STRUCTS_H
#define MAXCHAR 50
#define OPERAND_LENGHT 9
#define FILENAME_LENGHT 30

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <string>
#include <cctype>

enum MODE  { CONSOLE, BATCH };

typedef struct node_queue {

	long data;
	node_queue* next;
} QUEUETYPE;

typedef struct node_stack {

	char* operation = new char[8];
	long operationl;
	//OPERATOR_TYPE type; // stack e atilan opertaor un tipini tutar.
	node_stack* next;
} STACKTYPE;

struct stack {

	STACKTYPE* head = NULL;
	void push(char*, long);
	char* pop(void);
	long topl(void);
	char* topc(void);
	bool isempty();
	void close(void);
};

struct queue { 

	QUEUETYPE* front = NULL;
	QUEUETYPE* back = NULL;
	int counter = 0;
	long dequeue(void);
	void enqueue(long);
	void print(void);
	bool isempty(void);
	void close(void);
	long read_back(void);
};

struct operations {

	FILE* fileptr;
	bool syntax_error = false;
	char* filename = new char [FILENAME_LENGHT];
	bool open_file(void);
	bool read_file(char*);
	char* seperate(char*, int*);
	bool isalldigit(char* expression);
};

bool scan(char*);
void solution(char*);
void clean(char*, int);
void convert(char*);

#endif // !STRUCTS_H

