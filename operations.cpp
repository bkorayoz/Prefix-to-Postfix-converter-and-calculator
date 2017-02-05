/*	@Author
	Student Name: Bulent Koray OZ
	Student ID: 150130281
	Date: 24.12.2016
*/
#include "structs.h"

using namespace std;

void queue::enqueue(long data) {
	
	QUEUETYPE* newnode = new QUEUETYPE;
	newnode->data = data;
	newnode->next = NULL;

	if (front == NULL && back == NULL) { 
		
		front = newnode;
		back = newnode;
	}
	else {
		
		back->next = newnode;
		back = newnode;
	}
};

long queue::dequeue(void) {

	QUEUETYPE* temp;
	long data = front->data;
	temp = front;
	front = front->next;
	delete temp;
	return data;

};

long queue::read_back(void) {

	long data = back->data;
	return data;

}

void queue::close(void) {

	QUEUETYPE* temp;
	temp = front;
	while (front) {
		temp = front;
		front = front->next;
		delete temp;
	}
}

bool queue::isempty(void) {

	return (front == NULL);
}

void stack::push(char* operation, long data) {

	STACKTYPE* newnode = new STACKTYPE;
	strcpy(newnode->operation, operation);
	if (strcmp(operation, "*") == 0) {

		newnode->operationl = data;
	}
	newnode->next = head;
	head = newnode;
};

long stack::topl() {

	return head->operationl;
};

char* stack::topc(void) {

	STACKTYPE* traverse = head;
	char temp[OPERAND_LENGHT];
	::clean(temp, OPERAND_LENGHT);
	if (traverse == NULL) temp[0] = '?'; // stack bos ise flag ( ? ) donduruyor 
	else strcpy(temp, traverse->operation);
	return temp;
}

char* stack::pop(void) {

	STACKTYPE* traverse = head;
	char temp[OPERAND_LENGHT];
	if (traverse == NULL) return NULL;
	else {
		strcpy(temp, traverse->operation);
		head = head->next;
		delete traverse->operation;
		delete traverse;
		return temp;
	}
};

bool stack::isempty() {

	if (head == NULL)
		return true;
	return false;
};

void stack::close(void) {

	STACKTYPE* traverse;
	while (head)
	{
		traverse = head;
		head = head->next;
		delete traverse;
	}
};

char* operations::seperate(char* expression, int* index) {
	char operation[OPERAND_LENGHT];
	clean(operation, OPERAND_LENGHT);
	int lenght = 0;
	for (; lenght < OPERAND_LENGHT; lenght++) {
		if (expression[*index] == ' ' || expression[*index] == '\0') break;
		operation[lenght] = expression[*index];
		(*index)++;
	}
	return operation;
};

bool operations::open_file(void) {

	fileptr = fopen(filename, "r");
	if (!fileptr) {

		cout << "The file could not be opened. The name you entered might be wrong." << endl << endl;
		return false;
	}
	return true;
};

bool operations::read_file(char* expression) {

	if (feof(fileptr)) {
		fclose(fileptr);
		return true;
	}
	fgets(expression, MAXCHAR, fileptr);
	for (int i = 0; i < MAXCHAR; i++) {

		if (expression[i] == '\n') { // fgets fonksiyonunun expression stringine ekledigi '\n' karakterini siliyor.
			expression[i] = '\0';
		}
	}
	return false;
};

bool operations::isalldigit(char* expression) {
	int i = 0;
	if (expression[i] == '-')  i++; // eksi isaretli ise - isaretini de kabul et.
	for (; i < strlen(expression); i++) {

		if (!(isdigit(expression[i]))) return false;
	}
	return true;
}