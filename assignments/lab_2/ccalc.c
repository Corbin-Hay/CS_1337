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
	//run in order
	do {
		promptOp();
		if (Operator == 'q')
			//quit on q
			break;
		promptCount();
		promptOperands();
		runCalc();
	} while (Operator != 'q');
}

int runCalc()
{
	int final = 0;
	//calculate
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

	//display computation
	printf("\nComputing: ");
	for (int i = 0; i < Count; i++) {
		if (i != 0)
		{
			printf(" %c ", Operator);
		}
		printf("%d", Operands[i]);
	}
	printf(" = %d\n\n", final);
}

bool checkOp()
{
	//check for valid operators
	return (Operator == '+' || Operator == '-' || Operator == '*' || Operator == '/' || Operator == 'q');
}

bool checkCount()
{
	//check valid count
	return (Count > 1 && validInput == 1);
}

bool checkOperands(int iteration)
{
	//check for divide by zero error
	if (Operator == '/' && iteration != 0 && Operands[iteration] == 0 && validInput != 0)
	{
		printf("Please enter a non-zero integer for division\n");
		return false;
	}
	//check for invalid input
	if (validInput == 0)
	{
		printf("Please enter an integer\n");
		return false;
	}
	//check for invalid inputs after "valid input"
	if (validInput == 1)
	{
		int c = getchar();
		if (c != '\n' && c != EOF)\
		{
			printf("Please enter an integer\n");
			return false;
		}
	}
	//else
	return true;
}

void promptOp()
{
//loop until valid operator is inputted
	while (true)
	{
		printf("Enter Operation: ");
		scanf(" %c", &Operator, 1);
		clearInput();
		if (checkOp())
			break;
		printf("Please enter a valid operation\n");
	}
}

void promptCount()
{
	//loop until valid count is inputted
	while (true)
	{
		printf("Enter number of integers: ");
		validInput = scanf(" %d", &Count);
		clearInput();
		if (checkCount())
			break;
		printf("Please enter an integer greater than 1\n");
	}
}

void promptOperands()
{
	//nested loop to get 'count' valid operands
	for (int i = 0; i < Count; i++)
	{
		while (true)
		{
			printf("Enter integer %d: ", i + 1);
			validInput = scanf("%d", &Operands[i]);
			if (checkOperands(i))
			{
				break;
			}
			clearInput();
		}
	}
}

//function to clear input buffer
void clearInput()
{
	char buffer;
	do {
		buffer = getchar();
	} while (buffer != '\n' && buffer != EOF);
}

