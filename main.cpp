/*	@Author
	Student Name: Bulent Koray OZ
	Student ID: 150130281
	Date: 24.12.2016
*/

#include "structs.h"

using namespace std;
queue answers;
operations islem;
MODE mode;
int main(int argc, char* argv[]) {
	system("color 0A");
	if (argv[1] == NULL) {
		mode = CONSOLE;
	}
	else { 
		mode = BATCH;
		char temp[30];
		strcpy(temp, argv[1]);
		strcpy(islem.filename,temp);
		islem.open_file();
		if (!(islem.fileptr)) mode = CONSOLE;
	}
	if(mode == CONSOLE) cout << "Initializing the interpreter..." << endl << endl;
	
	while (true) {
		char* expression = new char[MAXCHAR];
		clean(expression, MAXCHAR); //expression stringinin icini NULL character ile dolduruyor
		if (mode == CONSOLE && scan(expression)) break; // exit ?
		if (mode == BATCH && islem.read_file(expression)) break;
		convert(expression); // icerde degistir. ve ekrana yazdir.
		solution(expression); // store the answer to queue and print it on the console
		if (islem.syntax_error) cout << "Syntax error." << endl << endl;
		if (mode == BATCH && islem.syntax_error) break; // dosyadan okurken syntax error ile karsilasilirsa program sonlandirilir.
		islem.syntax_error = false;
	}
	if (mode == CONSOLE) cout << "Terminating the interpreter..." << endl;
	cout << endl << "Answer queue: ";
	if (answers.counter == 0) { // hic islem yapilmadan kapatiliyorsa uyari yapiyor.
		cout << endl << "There is not any answer to show in the answer queue!!!" << endl;
	}
	else {
		long int result = answers.dequeue();

		if (result == LONG_MAX) cout << "inf" ;
		else if (result == LONG_MIN) cout << "-inf" ;
		else cout << result;
		
		while (!(answers.isempty())) {
			result = answers.dequeue();
			if (result == LONG_MAX) cout << " -> " << "inf";
			else if (result == LONG_MIN) cout << " -> " << "-inf";
			else cout << " -> " << result;
		}
	}
	cout << endl << endl;
	answers.close();
	system("pause");
	return EXIT_SUCCESS;
};

bool scan(char* expression) {

	cout << ">> ";
	cin.getline(expression, MAXCHAR);
	for (int i = 0; (int)expression[i] != 0; i++) {
		expression[i] = tolower(expression[i]);
	}
	cout << endl << endl;
	if (strncmp("exit", expression, 4) == 0 || strncmp("EXIT", expression, 4) == 0) return true;
	else return false;
};

void clean(char* expression, int lenght) { //expression stringinin icini NULL character ile dolduruyor
	
	for (int i = 0; i < lenght; i++) {
		expression[i] = (char) 0;
	}
};

void solution(char* expression) {
	
	stack conversion;
	int i = 0;
	long ans = 0;
	char element[OPERAND_LENGHT];
	bool done = false;
	while (!(done)) {
		
		if (islem.syntax_error) { // syntax error varsa basa doner.
			conversion.close();
			return;
		}
		strcpy(element, islem.seperate(expression, &i));
		
		if (*element == '(') { // sol parantez ise 	
			conversion.push("#", 0);
		}
		else if (*element == ')') { // sag parantez ise
		}
		else if (strcmp(element, "abs") == 0 || strcmp(element, "sqrt") == 0 || strcmp(element, "sub") == 0 ||
			strcmp(element, "div") == 0 || strcmp(element, "exp") == 0 || strcmp(element, "log") == 0 || strcmp(element, "mod") == 0 || strcmp(element, "sum") == 0 ||
			strcmp(element, "product") == 0 || strcmp(element, "min") == 0 || strcmp(element, "max") == 0) { // islem ise

			if (strcmp(element, "abs") == 0) {
				long int operand = 0;
				if (strcmp(conversion.topc(), "*") == 0) {
					
					operand = conversion.topl();
				}
				else {
					char* temp = new char[strlen(conversion.topc())];
					char* temp2 = conversion.topc();
					for (int i = 0; i < temp2[i] != '\0'; i++) {
						temp[i] = temp2[i];
					}
					if (strncmp(temp, "inf", 3) == 0) operand = LONG_MAX;
					else if (strncmp(temp, "-inf", 4) == 0) operand = LONG_MIN;
					else if (strncmp(temp, "ans", 4) == 0) operand = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
					else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
					else operand = atol(temp);
					delete[] temp; // donusum icinolusturulan array silindi.
				}
				conversion.pop();
				ans = abs(operand);
				conversion.push("*", ans);
			}
			else if (strcmp(element, "sqrt") == 0) {
				
				long operand = 0;
				if (strcmp(conversion.topc(), "*") == 0) {
					operand = conversion.topl();
				}
				else {
					char* temp = new char[strlen(conversion.topc())];
					char* temp2 = conversion.topc();
					for (int i = 0; i < strlen(conversion.topc()); i++) {
						temp[i] = temp2[i];
					}
					if (strncmp(temp, "inf",3) == 0) operand = LONG_MAX;
					else if (strncmp(temp, "-inf",4) == 0) operand = LONG_MIN;
					else if (strncmp(temp, "ans",3) == 0) operand = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
					else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
					else operand = atol(temp);
					delete[] temp; // donusum icinolusturulan array silindi.
				}
				conversion.pop();
				if (operand == LONG_MAX) ans = LONG_MAX;
				else if (operand < 0) {islem.syntax_error = true; // operand sifirdan kucuk ise syntax error.
				}
				else ans = floor(sqrtl(operand));
				conversion.push("*", ans);
			}
			else if (strcmp(element, "sub") == 0) {
				
				long operand1 = 0, operand2 = 0;
				if (strcmp(conversion.topc(), "*") == 0) { // 1. operand

					operand1 = conversion.topl();
				}
				else {
					char* temp = new char[strlen(conversion.topc())];
					char* temp2 = conversion.topc();
					for (int i = 0; i < strlen(conversion.topc()); i++) {

						temp[i] = temp2[i];
					}
					if (strncmp(temp, "inf",3) == 0) operand1 = LONG_MAX;
					else if (strncmp(temp, "-inf",4) == 0) operand1 = LONG_MIN;
					else if (strncmp(temp, "ans",3) == 0) operand1 = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
					else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
					else operand1 = atol(temp);
					delete[] temp; // donusum icinolusturulan array silindi.
				}
				conversion.pop();
				if (strcmp(conversion.topc(), "*") == 0) { // 2. operand

					operand2 = conversion.topl();
				}
				else {
					char* temp = new char[strlen(conversion.topc())];
					char* temp2 = conversion.topc();
					for (int i = 0; i < strlen(conversion.topc()); i++) {

						temp[i] = temp2[i];
					}
					if (strncmp(temp, "inf",3) == 0) operand2 = LONG_MAX;
					else if (strncmp(temp, "-inf",4) == 0) operand2 = LONG_MIN;
					else if (strncmp(temp, "ans",4) == 0) operand2 = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
					else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
					else operand2 = atol(temp);
					delete[] temp; // donusum icinolusturulan array silindi.
				}
				conversion.pop();
				if ((operand1 == LONG_MAX || operand1 == LONG_MIN) && (operand2 == LONG_MAX || operand2 == LONG_MIN)) islem.syntax_error = true;
				else if (!(operand1 == LONG_MAX || operand1 == LONG_MIN) && (operand2 == LONG_MAX)) ans = LONG_MAX;
				else if (!(operand1 == LONG_MAX || operand1 == LONG_MIN) && (operand2 == LONG_MIN)) ans = LONG_MIN;
				else if ((operand1 == LONG_MAX) && !(operand2 == LONG_MAX || operand2 == LONG_MIN)) ans = LONG_MIN;
				else if ((operand1 == LONG_MIN) && !(operand2 == LONG_MAX || operand2 == LONG_MIN)) ans = LONG_MAX;
				else{
					ans = operand2 - operand1;
				}
				
				conversion.push("*", ans);
			}
			else if (strcmp(element, "div") == 0) {
				
				long operand1 = 0, operand2 = 0;
				if (strcmp(conversion.topc(), "*") == 0) { // 1. operand

					operand1 = conversion.topl();
				}
				else {
					char* temp = new char[strlen(conversion.topc())];
					char* temp2 = conversion.topc();
					for (int i = 0; i < strlen(conversion.topc()); i++) {

						temp[i] = temp2[i];
					}
					if (strncmp(temp, "inf",3) == 0) operand1 = LONG_MAX;
					else if (strncmp(temp, "-inf",4) == 0) operand1 = LONG_MIN;
					else if (strncmp(temp, "ans",3) == 0) operand1 = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
					else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
					else operand1 = atol(temp);
					delete[] temp; // donusum icin olusturulan array silindi.
				}
				conversion.pop();
				if (strcmp(conversion.topc(), "*") == 0) { // 2. operand

					operand2 = conversion.topl();
				}
				else {
					char* temp = new char[strlen(conversion.topc())];
					char* temp2 = conversion.topc();
					for (int i = 0; i < strlen(conversion.topc()); i++) {

						temp[i] = temp2[i];
					}
					if (strncmp(temp, "inf",3) == 0) operand2 = LONG_MAX;
					else if (strncmp(temp, "-inf",4) == 0) operand2 = LONG_MIN;
					else if (strncmp(temp, "ans",3) == 0) operand2 = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
					else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
					else operand2 = atol(temp);
					delete[] temp; // donusum icinolusturulan array silindi.
				}
				conversion.pop();
				if (operand1 == 0) islem.syntax_error = true;
				else if ((operand1 == LONG_MAX || operand1 == LONG_MIN) && !(operand2 == LONG_MAX || operand2 == LONG_MIN)) ans = 0;
				else if ((operand1 == LONG_MAX || operand1 == LONG_MIN) && (operand2 == LONG_MAX || operand2 == LONG_MIN)) islem.syntax_error = true;
				else if (!(operand1 == LONG_MAX || operand1 == LONG_MIN) && (operand2 == LONG_MIN)) ans = LONG_MIN;
				else if (!(operand1 == LONG_MAX || operand1 == LONG_MIN) && (operand2 == LONG_MAX)) ans = LONG_MAX;
				else { 
					ans = floor(operand2 / operand1); 
				}
				conversion.push("*", ans);
			}
			else if (strcmp(element, "exp") == 0) {
				long operand[2] = {0, 0};
				int operand_number = -1;
				while (strcmp(conversion.topc(), "#") != 0) {
					operand_number++;
					if (strcmp(conversion.topc(), "*") == 0) {

						operand[operand_number] = conversion.topl();
					}
					else {
						char* temp = new char[strlen(conversion.topc())];
						char* temp2 = conversion.topc();
						for (int j = 0; j < strlen(conversion.topc()); j++) {

							temp[j] = temp2[j];
						}
						if (strncmp(temp, "inf",3) == 0) operand[operand_number] = LONG_MAX;
						else if (strncmp(temp, "-inf",4) == 0) operand[operand_number] = LONG_MIN;
						else if (strncmp(temp, "ans",3) == 0) operand[operand_number] = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
						else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
						else operand[operand_number] = atol(temp);
						delete[] temp; // donusum icinolusturulan array silindi.
					}
					conversion.pop();
				}
				if (operand_number == 0) { // kac tane operand var? unary or binary operation.
					if (operand[0] == LONG_MAX) ans = LONG_MAX;
					else if (operand[0] == LONG_MIN) ans = 0;
					else {
						if (expl(operand[0]) >= LONG_MAX) ans = LONG_MAX;
						else ans = expl(operand[0]);
					}
				} else if (operand_number == 1){
					if ((operand[0] == LONG_MAX) && !(operand[1] == LONG_MAX || operand[1] == LONG_MIN)) ans = LONG_MAX;
					else if ((operand[0] == LONG_MIN) && !(operand[1] == LONG_MAX || operand[1] == LONG_MIN)) ans = 0;
					else if (!(operand[0] == LONG_MAX || operand[0] == LONG_MIN) && (operand[1] == LONG_MAX)) ans = LONG_MAX;
					else if (!(operand[0] == LONG_MAX || operand[0] == LONG_MIN) && (operand[1] == LONG_MIN)) {
						if (pow(-1, operand[0]) == 1) ans = LONG_MAX;
						else ans = LONG_MIN;
					}
					else ans = pow(operand[1], operand[0]);
				}				
				conversion.pop();
				ans = floor(ans);
				conversion.push("*", ans);
			}
			else if (strcmp(element, "log") == 0) {
			
				long operand[2] = {0,0};
				int operand_number = -1;
				while (strcmp(conversion.topc(), "#") != 0) {
					operand_number++;
					if (strcmp(conversion.topc(), "*") == 0) {

						operand[operand_number] = conversion.topl();
					}
					else {
						char* temp = new char[strlen(conversion.topc())];
						char* temp2 = conversion.topc();
						for (int j = 0; j < strlen(conversion.topc()); j++) {

							temp[j] = temp2[j];
						}
						if (strncmp(temp, "inf",3) == 0) operand[operand_number] = LONG_MAX;
						else if (strncmp(temp, "-inf",4) == 0) operand[operand_number] = LONG_MIN;
						else if (strncmp(temp, "ans",3) == 0) operand[operand_number] = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
						else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
						else operand[operand_number] = atol(temp);
						delete[] temp; // donusum icinolusturulan array silindi.
					}
					conversion.pop();
				}
				if (operand_number == 0) { // kac tane operand var. unary or binary operation.				
					if (operand[0] == LONG_MAX) ans = LONG_MAX;
					else if (operand[0] <= 0) islem.syntax_error = true;
					else ans = log(operand[0]);
				}
				else if (operand_number == 1) {
					if (operand[0] <= 0 || operand[1] <= 0 || operand[1] == LONG_MAX) islem.syntax_error = true;
					else if (operand[0] == LONG_MAX) ans = LONG_MAX;
					else ans = (log10(operand[0])) / (log10(operand[1]));
				}
				conversion.pop();
				ans = floor(ans);
				conversion.push("*", ans);

			}
			else if (strcmp(element, "mod") == 0) {
			
				long operand[2] = {0,0};
				int operand_number = -1;
				while (strcmp(conversion.topc(), "#") != 0) {
					operand_number++;
					if (strcmp(conversion.topc(), "*") == 0) {

						operand[operand_number] = conversion.topl();
					}
					else {
						char* temp = new char[strlen(conversion.topc())];
						char* temp2 = conversion.topc();
						for (int j = 0; j < strlen(conversion.topc()); j++) {

							temp[j] = temp2[j];
						}
						if (strncmp(temp, "inf",3) == 0) operand[operand_number] = LONG_MAX;
						else if (strncmp(temp, "-inf",4) == 0) operand[operand_number] = LONG_MIN;
						else if (strncmp(temp, "ans",3) == 0) operand[operand_number] = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
						else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
						else operand[operand_number] = atol(temp);
						delete[] temp; // donusum icinolusturulan array silindi.
					}
					conversion.pop();
				}
				if ((operand[0] == LONG_MAX || operand[0] == LONG_MIN) && (operand[1] == LONG_MAX || operand[1] == LONG_MIN)) islem.syntax_error = true; // operamdlardan herhangi biri inf ise syntax error
				if (operand_number == 0) { // kac tane operand var. unary or binary operation.	
					ans = fmodl(operand[0],10);
				}
				else if (operand_number == 1) {
					if (operand[1] == 0) islem.syntax_error = true;
					ans = fmodl(operand[0], operand[1]);
				}
				conversion.pop();
				conversion.push("*", ans);
			}
			else if (strcmp(element, "sum") == 0) {
				long total = 0;
				long operand = 0;
				while (strcmp(conversion.topc(), "#") != 0) {
					if (strcmp(conversion.topc(), "*") == 0) {

						operand = conversion.topl();
					}
					else {
						char* temp = new char[strlen(conversion.topc())];
						char* temp2 = conversion.topc();
						for (int i = 0; i < strlen(conversion.topc()); i++) {

							temp[i] = temp2[i];
						}
						if (strncmp(temp, "inf", 3) == 0) operand = LONG_MAX;
						else if (strncmp(temp, "-inf",4) == 0) operand = LONG_MIN;
						else if (strncmp(temp, "ans", 3) == 0) operand = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
						else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
						else operand = atol(temp);
						delete[] temp; // donusum icinolusturulan array silindi.
					}
					conversion.pop();
					if (operand == LONG_MAX) ans = LONG_MAX;
					else if (operand == LONG_MIN) ans = LONG_MIN;
					else total = total + operand;
				}
				conversion.pop();
				if (!(ans == LONG_MAX || ans == LONG_MIN)) {
					ans = total;
				}
				conversion.push("*", ans);
			}
			else if (strcmp(element, "product") == 0) {
				long product = 1;
				long int operand = 0;
				while (strcmp(conversion.topc(), "#") != 0) {
					if (strcmp(conversion.topc(), "*") == 0) {

						operand = conversion.topl();
					}
					else {
						char* temp = new char[strlen(conversion.topc())];
						char* temp2 = conversion.topc();
						for (int i = 0; i < strlen(conversion.topc()); i++) {
							
							temp[i] = temp2[i];
						}
						if (strncmp(temp, "inf", 3) == 0) operand = LONG_MAX;
						else if (strncmp(temp, "-inf", 4) == 0) operand = LONG_MIN;
						else if (strncmp(temp, "ans", 3) == 0) operand = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
						else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
						else operand = atol(temp);
						delete[] temp; // donusum icinolusturulan array silindi.
					}
					conversion.pop();
					if (operand == LONG_MAX) ans = LONG_MAX;
					else if (operand == LONG_MIN) ans = LONG_MIN;
					else product = product * operand;	
				}
				conversion.pop(); // parantez icin konulan # flag i pop edildi.
				if (!(ans == LONG_MAX || ans == LONG_MIN)) {
					ans = product;
				}
				conversion.push("*", ans);
			}
			else if (strcmp(element, "min") == 0) {
				
				long min = LONG_MAX;
				long operand = 0;
				while (strcmp(conversion.topc(), "#") != 0) {
					if (strcmp(conversion.topc(), "*") == 0) {

						operand = conversion.topl();
					}
					else {
						char* temp = new char[strlen(conversion.topc())];
						char* temp2 = conversion.topc();
						for (int i = 0; i < strlen(conversion.topc()); i++) {

							temp[i] = temp2[i];
						}
						if (strncmp(temp, "inf", 3) == 0) operand = LONG_MAX;
						else if (strncmp(temp, "-inf",4) == 0) operand = LONG_MIN;
						else if (strncmp(temp, "ans", 3) == 0) operand = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
						else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
						else operand = atol(temp);
						delete[] temp; // donusum icinolusturulan array silindi.
					}
					conversion.pop();

					if (min > operand) min = operand;
				}
				conversion.pop();
				ans = min;
				conversion.push("*", ans);
			}
			else if (strcmp(element, "max") == 0) {
			
				long max = LONG_MIN;
				long operand = 0;
				while (strcmp(conversion.topc(), "#") != 0) {
					if (strcmp(conversion.topc(), "*") == 0) {
						operand = conversion.topl();
					}
					else {
						char* temp = new char[strlen(conversion.topc())];
						char* temp2 = conversion.topc();
						for (int i = 0; i < strlen(conversion.topc()); i++) {

							temp[i] = temp2[i];
						}
						if (strncmp(temp, "inf", 3) == 0) operand = LONG_MAX;
						else if (strncmp(temp, "-inf", 4) == 0) operand = LONG_MIN;
						else if (strncmp(temp, "ans", 3) == 0) operand = answers.read_back(); // operand in ans olup olmadigi kontrol ediliyor.
						else if (strncmp(temp, "?", 1) == 0) islem.syntax_error = true;
						else operand = atol(temp);
						delete[] temp; // donusum icinolusturulan array silindi.
					}
					conversion.pop();

					if (operand > max) max = operand;
				}
				conversion.pop();
				ans = max;
				conversion.push("*", ans);
			}		
		}
		else { // sayi ise
			char temp1[OPERAND_LENGHT];
			strcpy(temp1, element);
			conversion.push(temp1, 0);		
		}
		i++;
		if (islem.syntax_error) { // syntax error varsa basa doner.
			conversion.close();
			return;
		}
		if (expression[i] == '\0') { // expression string inin sonuna gelindi.
			conversion.pop();
			if (!(conversion.isempty())) { // en sonda stack bos degil ise syntax error
				islem.syntax_error = true;
				conversion.close();
				return;
			}
			conversion.close();
			done = true;
		}
	}
	answers.enqueue(ans);
	answers.counter++;
	if (mode == CONSOLE) { // console modda calisiliyorsa sonuclari yazdir.
		if (ans == LONG_MAX) cout << "Answer: " << "inf" << endl << endl; // sonuc yazdiriliyor.
		else if (ans == LONG_MIN) cout << "Answer: " << "-inf" << endl << endl; // sonuc yazdiriliyor.
		else cout << "Answer: " << ans << endl << endl; // sonuc yazdiriliyor.
	}
};

void convert(char* expression) {

	stack conversion;
	char element[OPERAND_LENGHT];
	bool done = false;
	char converted[MAXCHAR];
	int i_org = 0;
	int i_new = 0;
	clean(converted, MAXCHAR);
	while (!done) {

		if (islem.syntax_error) { // syntax error varsa basa doner.
			conversion.close();
			return;
		}
		strcpy (element, islem.seperate(expression, &i_org));

		if (strcmp(element, "abs") == 0 || strcmp(element, "sqrt") == 0 || strcmp(element, "sub") == 0 ||
			strcmp(element, "div") == 0 || strcmp(element, "exp") == 0 || strcmp(element, "log") == 0 || strcmp(element, "mod") == 0 || strcmp(element, "sum") == 0 ||
			strcmp(element, "product") == 0 || strcmp(element, "min") == 0 || strcmp(element, "max") == 0) { // operator ise
			char temp1[OPERAND_LENGHT];
			strcpy(temp1, element);
			conversion.push(temp1, 0);

			
			if (strcmp(temp1, "sum") == 0 || strcmp(temp1, "product") == 0 || strcmp(temp1, "min") == 0 || strcmp(temp1, "max") == 0 ||
				strcmp(temp1, "exp") == 0 || strcmp(temp1, "log") == 0 || strcmp(temp1, "mod") == 0) { // operator polynary veya unary/binary ise
				converted[i_new++] = '(';
				converted[i_new++] = ' ';
			}
		}
		else if (*element == '(') {// sol parantez ise 
		}
		else if (*element == ')') {// sag parantez ise 

			char* temp2 = conversion.pop();
			for (int i = 0; temp2[i] != '\0'; i++) {

				converted[i_new++] = temp2[i];
			}
			converted[i_new++] = ' ';
			if (strcmp(temp2, "sum") == 0 || strcmp(temp2, "product") == 0 || strcmp(temp2, "min") == 0 || strcmp(temp2, "max") == 0 ||
				strcmp(temp2, "exp") == 0 || strcmp(temp2, "log") == 0 || strcmp(temp2, "mod") == 0) { // operator polynary veya unary/binary ise

				converted[i_new++] = ')';
				converted[i_new++] = ' ';
			}
		}
		else { 
			char temp[OPERAND_LENGHT];
			strcpy(temp, element);
			if (islem.isalldigit(temp) || strcmp(temp, "ans") == 0 || strcmp(temp, "inf") == 0 || strcmp(temp, "-inf") == 0) { // integer sayi ve ya static operand ise
			for (int i = 0; temp[i] != '\0'; i++) {

				converted[i_new++] = temp[i];
			}
			converted[i_new++] = ' ';
			}
			else { // hicbiri ise

			islem.syntax_error = true;
			conversion.close();
			return;
			}
		}
		if (expression[i_org] == '\0') { // expression un sonuna gelindiyse butun stack i converted expression a yaz.
			int counter = 0;
			while (!(conversion.isempty())) {

				char* temp2 = conversion.pop();
				for (int i = 0; temp2[i] != '\0'; i++) {

					converted[i_new++] = temp2[i];
				}
				converted[i_new++] = ' ';
				if (strcmp(temp2, "sum") == 0 || strcmp(temp2, "product") == 0 || strcmp(temp2, "min") == 0 || strcmp(temp2, "max") == 0 ||
					strcmp(temp2, "exp") == 0 || strcmp(temp2, "log") == 0 || strcmp(temp2, "mod") == 0) { // operator polynary veya unary/binary ise

					converted[i_new++] = ')';
					converted[i_new++] = ' ';
				}
				counter++;
			}
			done = true;
		}
		i_org++;
	}

	for (int i = 0; i < MAXCHAR; i++) {

		expression[i] = converted[i];
	}
	if (mode == CONSOLE) {
	cout << "Postfix string: ";
	for (int i = 0; (int)expression[i] != 0; i++) { // prints the converted string
		cout << expression[i];
	}
	cout << endl << endl;
	}
	conversion.close();
	return;
};