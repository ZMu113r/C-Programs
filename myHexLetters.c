/* COP 3502
   Lab 04
   Author: Zach Muller

   This program converts Upper case letters to lower case
   letters by bit manipulation
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char toLower(char myLetter);
int toBinary(int n);
void print(int binaryNo, char upperLetters, char lowerLetters);

int main(void) {

	int upperLetterInDec = 17;
	int binaryNo;
	char *upperLetters = (char *)malloc(sizeof(char));
	char *lowerLetters = (char *)malloc(sizeof(char));

	//Print headers
	printf("\tUPPER\t\t\t\tlower\t\n");
	printf(" binary Hex Dec -\t\tbinary Hex Dec  -\n");

	int i;
	for(i = 0; i < 26; i++) {
		//Fill char array with upper case letters
		upperLetters[i] = upperLetterInDec + '0';
		
		//Next letter
		upperLetterInDec++;

		//Convert upper to lower
		lowerLetters[i] = toLower(upperLetters[i]);

		//Convert to binary
		binaryNo = toBinary(lowerLetters[i] - '0' + 16);

		//Display conversions
		print(binaryNo, upperLetters[i], lowerLetters[i]);
	}

	return 0;
}

char toLower(char myLetter) {
	return myLetter | 32;
}

int toBinary(int n) {

	int binaryNo = 0;
	int i = 1;
	int remainder;
	
	while(n != 0)
	{	
		remainder = n % 2;
		n /= 2;
		binaryNo = binaryNo + (remainder * i);
		i *= 10;
	}
	return binaryNo;
}

void print(int binaryNo, char upperLetters, char lowerLetters) {
	if(lowerLetters == 'a' || lowerLetters == 'b' || lowerLetters == 'c') {
		printf(" %d %x %d  %c\t\t%d %x %d   %c\n", binaryNo, upperLetters, upperLetters, upperLetters, binaryNo, lowerLetters, lowerLetters, lowerLetters);
		return;
	}
	printf(" %d %x %d  %c\t\t%d %x %d  %c\n", binaryNo, upperLetters, upperLetters, upperLetters, binaryNo, lowerLetters, lowerLetters, lowerLetters);
	
}