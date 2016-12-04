#include <stdio.h>
#include <stdlib.h>

//Function declarations
void fileToArray(char *fileName, int *fileInfoArray);
int getInfoArrayLength(char *fileName);
void cutToChunks(int *fileInfoArray, int length);
void createSumArrays(int *tempArrayBuffer, int *tempArrayLength, int *tempTargetSum, int currentTestCase);
int numSummation(int *tempArrayLength);
void compareSums(int *tempTargetSum, int *sumArrayBuffer, int numSums, int currentTestCase);

int main(int argc, char **argv) {

	//Pointer to name of file
	char *fileName = (char *)malloc(10 * sizeof(char));

	//Get file name from command line
	fileName = argv[1];

	//Variable to hold length of array being read in
	int length = 0;
	//Get array length
	length = getInfoArrayLength(fileName);

	//Make an array size of length of array being read in
	int array[length];
	//Pointer to an integer array
	int *fileInfoArray = (int *)malloc(length * sizeof(int));
	//Assign pointer space in memory size of array to the actual array 
	fileInfoArray = array;
	//Get info from file and put it in array 
	fileToArray(fileName, fileInfoArray);
	
	//Break it up into easier to use pieces
	//Goes further to create an array of sums for each test case chunk
	//Takes each element in array of sums and 
	//compares it to the target sum
	cutToChunks(fileInfoArray, length);

	//Just so the output looks clean...
	printf("\n");

	return 0;
}

//Get the number of elements in file in order to  
//declare an array dynamically with size length 
int getInfoArrayLength(char *fileName) {

	//File pointer
	FILE *file;
	//variable for length of array
	int length = 0;
	//Buffer to temporarily hold read in values
	int buffer;

	//open file for reading
	file = fopen(fileName, "r");

	//Defense
	if(file == NULL) {
		printf("targetsum ERROR: File '%s' not found.\n", fileName);
	}

	//Get length
	while(fscanf(file, "%d", &buffer) != EOF) {
		length++;
	}
	//Bring file pointer back to top of file
	rewind(file);

	//Close file to prevent leakage
	fclose(file);
	return length;
}

//Read info in from file into an array
void fileToArray(char *fileName, int *fileInfoArray) {

	//File pointer
	FILE *file;
	//Buffer to temporarily hold integer values
	int buffer = 0;

	//open up the file to get info
	file = fopen(fileName, "r");

	//Defensive code
	if(file == NULL) {
		printf("targetsum ERROR: File '%s' not found.\n", fileName);
	}

	int i = 0;
	//Get each integer
	while(fscanf(file, "%d", &buffer)!= EOF) {

		//Put it in array
		fileInfoArray[i] = buffer;

		//Move array index
		i++;
	}
	printf("\n");

	//Bring fp back up to top of file for repeated usage
	rewind(file);

	//Dont let the memory leak
	fclose(file);
}

//Takes large array and cuts it into smaller 
//arrays to make more manageable
void cutToChunks(int *fileInfoArray, int length) {

	//Variables to hold smaller arrays
	int numTestCases = 0;
	//Get number of test cases
	numTestCases = fileInfoArray[0];

	//Do this for every test case
	int currentTestCase = 1;
	int currentArray = 1;

	while(currentTestCase <= numTestCases) {
		
		//Buffers for dynamic variables
		int *tempArrayLength = (int *)malloc(sizeof(int));
		int *tempTargetSum = (int *)malloc(sizeof(int));

		//Get array length and target sum for test case
		*tempArrayLength = fileInfoArray[currentArray];
		int *tempArrayBuffer = (int *)malloc((*tempArrayLength) * sizeof(int));
		*tempTargetSum = fileInfoArray[currentArray + 1];

		//Create an array for the test case and put it in a buffer
		int tempArray[*tempArrayLength];
		tempArrayBuffer = tempArray;

		//Fill the temp array 
		int i;
		int j = (currentArray + 2);
		for(i = j; i < (*tempArrayLength + j); i++) {
			tempArray[i - j] =  fileInfoArray[i];
		}

		//create array of sums of every combination
		//of numbers in the tempArray
		createSumArrays(tempArrayBuffer, tempArrayLength, tempTargetSum, currentTestCase);

		//Move to next test case
		currentTestCase++;
		currentArray += *(tempArrayLength) + 2;
	}
}

//Function to dot sum every element in array chunks
void createSumArrays(int *tempArrayBuffer, int *tempArrayLength, int *tempTargetSum, int currentTestCase) {

	//Create array to hold sums for temporary array chunk
	//Variable for size of summation array
	int numSums;
	if(*tempArrayLength == 1) {
		numSums = 1;
	}
	else if(*tempArrayLength > 1) {
		numSums = numSummation(tempArrayLength);
	}
	
	//Create a buffer to hold array and put it there
	int *sumArrayBuffer = (int *)malloc(numSums * sizeof(int));
	//Make an array of size big enough to hold all sums
	int *sumArray = (int *)malloc(numSums * sizeof(int));
	//int sumArray[numSums];
	sumArrayBuffer = sumArray;

	//Counter to represent base number of summation operations
	int iLoop = 0;
	//Counter to represent traversing through array of number being added
	//to base number
	int jLoop = 1;
	int i;
	for(i = 0; i < numSums; i++) {

		if(iLoop < *tempArrayLength) {

			//sum two values and put it in array
			sumArray[i] = tempArrayBuffer[iLoop] + tempArrayBuffer[jLoop];
			//printf("Current: %d\tNext: %d\n", tempArrayBuffer[iLoop], tempArrayBuffer[jLoop]);
			//printf("Sum: %d\n", sumArray[i]);

			//increment "secondary loop"
			jLoop++;

			if(jLoop == *(tempArrayLength)) {
			
				//increment "primary loop"
				iLoop++;
				//Start "secondary loop" over
				jLoop = (iLoop + 1);
			}
		}	
	}

	//See if the target sum is there
	compareSums(tempTargetSum, sumArrayBuffer, numSums, currentTestCase);

	//Reset them for next array chunk
	iLoop = 0;
	jLoop = 1;
}

//Function to calculate number of summations to be done for 
//the temporary array
int numSummation(int *tempArrayLength) {

	//Variable for numSum calculation
	int numSummation = 0;

	int i;
	//(n-1)+(n-2)+...+(n-n)
	for(i = (*tempArrayLength); i > 0; i--) {
		numSummation += (i - 1);
	}

	return numSummation;
}

//Function to compare target sum to each element in the 
//array of sums
void compareSums(int *tempTargetSum, int *sumArrayBuffer, int numSums, int currentTestCase) {

	int i;
	//Loop through all sums
	for(i = 0; i < numSums; i++) {

		//Found it!
		if(sumArrayBuffer[i] == *tempTargetSum) {

			//Exclaim!
			printf("Yes for test case: %d\n", currentTestCase);

			//Stop looking
			i = numSums;
		}

		//Couldn't find it boss
		else if(i == (numSums - 1) && (sumArrayBuffer[i] != *tempTargetSum)) {

			//Better luck next time
			printf("No for test case: %d\n", currentTestCase);
		}
	}
}