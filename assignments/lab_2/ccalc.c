#include "stdio.h"
#include "stdbool.h"

#define SIZE 100

//Globals
private;
	char Operator;
	int Count;
	int Operands[SIZE];
	int validInput;

//Functions
void runStart();
int runCalc();
bool checkOp();
bool checkCount();
bool checkOperands(int iteration);
void promptOp();
void promptCount();
void promptOperands();
void clearInput();

int main() {
	runStart();
	return 0;
}

void runStart()
{
	do {
		promptOp();
		if (Operator == 'q')
			break;
		promptCount();
		promptOperands();
		runCalc();
	} while (Operator != 'q');
}

int runCalc()
{
	int final = 0;

	switch (Operator)
	{
	case '+':
		for (int i = 0; i < Count; i++)
			final += Operands[i];
		break;
	case '-':
		final = Operands[0];
		for (int i = 1; i < Count; i++)
			final -= Operands[i];
		break;
	case '*':
		final = Operands[0];
		for (int i = 1; i < Count; i++)
			final *= Operands[i];
		break;
	case '/':
		final = Operands[0];
		for (int i = 1; i < Count; i++)
			final /= Operands[i];
		break;
	}

	printf("\nComputing: ");
	for (int i = 0; i < Count; i++) {
		if (i != 0)
		{
			printf(" %c ", Operator);  // print operator between numbers
		}
		printf("%d", Operands[i]);
	}
	printf(" = %d\n\n", final);
}

bool checkOp()
{
	return (Operator == '+' || Operator == '-' || Operator == '*' || Operator == '/' || Operator == 'q');
}

bool checkCount()
{
	return (Count > 1 && validInput == 1);
}

bool checkOperands(int iteration)
{
	if (Operator == '/' && iteration != 0 && Operands[iteration] == 0 && validInput != 0)
	{
		printf("Please enter a non-zero integer for division\n");
		return false;
	}
	if(validInput == 0)
	{
		printf("Please enter an integer\n");
		return false;
	}
	return true;
}

void promptOp()
{
	while(true)
	{
		printf("Enter Operation: ");
		scanf(" %c", &Operator, 1);
		if (checkOp())
			break;
		printf("Please enter a valid operation\n");
		clearInput();
	}
}

void promptCount()
{
	while (true)
	{
		printf("Enter number of integers: ");
		validInput = scanf(" %d", &Count);
		if (checkCount())
			break;
		printf("Please enter an integer greater than 1\n");
		clearInput();
	}
}

void promptOperands()
{
	for(int i = 0; i < Count; i++)
	{
		while (true)
		{
			printf("Enter integer %d: ", i+1);
			validInput = scanf(" %d", &Operands[i]);
			if (checkOperands(i))
			{
				break;
			}
			clearInput();
		}
	}
}

void clearInput()
{
	char buffer;
	do {
		buffer = getchar();
	} while (buffer != '\n' && buffer != EOF);
}

