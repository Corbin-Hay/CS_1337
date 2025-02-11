#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"

#define SIZE 100
#define TARGET_LENGTH 8 

//Globals
private;
char operator;
int count;
char operands[SIZE][SIZE];
int validInput;
long intermediateDecimal[SIZE];
int BinaryOperands[SIZE];

//Functions
void runStart();
void runCalc();
bool checkOp();
bool checkCount();
bool checkOperands(int iteration);
void promptOp();
void promptCount();
void promptOperands();
void hexToBinary(int iteration);
void printBinary(int num);
void printOutput(int final);
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
		if (operator == 'q')
			//quit on q
			break;
		promptCount();
		promptOperands();
		runCalc();
	} while (operator != 'q');
}

void runCalc()
{
	int final = BinaryOperands[0];
	//calculate
	switch (operator)
	{
	case '|':
		for (int i = 1; i < count; i++)
			final |= BinaryOperands[i];
		break;
	case '&':
		for (int i = 1; i < count; i++)
			final &= BinaryOperands[i];
		break;
	case '^':
		for (int i = 1; i < count; i++)
			final ^= BinaryOperands[i];
		break;
	}
	printOutput(final);
}

bool checkOp()
{
	//check for valid operators
	return (operator == '|' || operator == '&' || operator == '^' || operator == 'q');
}

bool checkCount()
{
	//check valid count
	return (count > 1 && validInput == 1);
}

bool checkOperands(int iteration)
{
	//check for more than 8 characters in string
	if (strlen(operands[iteration]) > TARGET_LENGTH)
	{
		printf("Please enter an 8-digit hexadecimal integer\n");
		return false;
	}
	//put in zeros to fill most signifigant bits if needed
	else if (strlen(operands[iteration]) != TARGET_LENGTH)
	{
		int numZeros = TARGET_LENGTH - strlen(operands[iteration]); //calculate number of zeros
		char temp[TARGET_LENGTH + 1]; //create temp array to prepend zeros (+1 to include null terminator)
		for (int i = 0; i < numZeros; i++)
			temp[i] = '0';
		strcpy(&temp[numZeros], operands[iteration]); //copy original string into temp, after zeros
		temp[TARGET_LENGTH] = '\0'; //add null terminator
		strcpy(operands[iteration], temp); //copy temp back to original
	}
	//check for valid inputs
	for (int i = 0; operands[iteration][i] != '\0'; i++)
	{
		if (!((operands[iteration][i] >= '0' && operands[iteration][i] <= '9') || (operands[iteration][i] >= 'A' && operands[iteration][i] <= 'F') || (operands[iteration][i] >= 'a' && operands[iteration][i] <= 'f')))
		{
			printf("Please enter an 8-digit hexadecimal integer\n");
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
		scanf(" %c", &operator);
		clearInput();
		if (checkOp())
			break;
		printf("Please enter | , &, ^, or q\n");
	}
}

void promptCount()
{
	//loop until valid count is inputted
	while (true)
	{
		printf("Enter number of integers: ");
		validInput = scanf(" %d", &count);
		clearInput();
		if (checkCount())
			break;
		printf("Please enter an integer greater than 1\n");
	}
}

void promptOperands()
{
	//nested loop to get 'count' valid operands
	for (int i = 0; i < count; i++)
	{
		while (true)
		{
			printf("Enter integer %d: ", i + 1);
			scanf(" %s", operands[i]);
			if (checkOperands(i))
			{
				hexToBinary(i);
				break;
			}
			clearInput();
		}
	}
}

void hexToBinary(int iteration)
{
	//converts input hex string into binary representation
	BinaryOperands[iteration] = strtol(operands[iteration], NULL, 16);
}

void printBinary(int num)
{
	for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
		printf("%d", (num >> i) & 1); //shift to current bit and isolate it for printing either 0 or 1
		// space every 8 bits
		if (i % 8 == 0) {
			printf(" ");
		}
	}
	printf("\n");
}

void printOutput(int final)
{
	printf("\nHexadecimal Operation:\n");
	for (int i = 0; i <= count; i++)
	{
		if (i == 0)
		{
			printf("%7c", ' ');
			printf("%s\n", operands[i]);
		}
		else if (i == count)
		{
			printf("%6c ", '=');
			printf("%08X\n", final);
		}
		else
		{
			printf("%6c ", operator);
			printf("%s\n", operands[i]);
		}
	}
	printf("\nBinary Operation:\n");
	for (int i = 0; i <= count; i++)
	{
		if (i == 0)
		{
			printf("%7c", ' ');
			printBinary(BinaryOperands[i]);
		}
		else if (i == count)
		{
			printf("%6c ", '=');
			printBinary(final);
			printf("\n");
		}
		else
		{
			printf("%6c ", operator);
			printBinary(BinaryOperands[i]);
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
