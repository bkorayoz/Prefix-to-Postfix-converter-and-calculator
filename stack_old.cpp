#include "structs.h"

using namespace std;

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
	strcpy(temp, traverse->operation);
	return temp;
}

char* stack::pop(void) {
	
	STACKTYPE* traverse = head;
	char temp[OPERAND_LENGHT];
	strcpy(temp, traverse->operation);
	head = head->next;
	delete traverse->operation;
	delete traverse;
	return temp;
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
