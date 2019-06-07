#include <assert.h>
#include <ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

// Declaration of functions implemented in this C program 
void interactiveMode();
int fileMode();
char* file_ext(const char *string);

// Defines a constant value for the maximum number of characters in the textfile
#define MAXCHAR 1000

// Main function 
int main()
{
	int result;			// integer variable for fileMode() return 
	char userInput[10]; // user input array of characters (string) initialized with size 50
	char continueKey[10];	// a character array for user input to determine the continuity of the program

	// Display name and class in a header formatted
	printf("**************************************\n");
	printf("REVERSED ALPHABET CIPHER\n");
	printf("ST2411 Assignment 1 Done by: \n");
	printf("**************************************\n");

	while (1) {
		printf("\nSelect 'i' for interactive mode or 'f' for file mode=> ");
		gets(userInput);

		if (strcmp(userInput, "i") == 0 || strcmp(userInput, "I") == 0) {
			do {
				interactiveMode();
				while (1) {
					printf("\nDo you want to encode/decode more text? y/n=> ");	// Asks if the user wants another cipher of texts
					gets(continueKey);
					// INPUT VALIDATIONS
					if (strcmp(continueKey, "y") == 0 || strcmp(continueKey, "Y") == 0) {
						break;
					}
					else if (strcmp(continueKey, "n") == 0 || strcmp(continueKey, "N") == 0){
						break;
					}
					else {
						printf("Invalid input! Please enter either \"y\" or \"n\" ONLY.\n");
						continue;
					}
				}	
				
			} while (strcmp(continueKey, "y") == 0 || strcmp(continueKey, "Y") == 0);	// Compares string to determine the continuity of the while loop 

			break;
		}
		// INPUT VALIDATIONS
		else if (strcmp(userInput, "f") == 0 || strcmp(userInput, "F") == 0) {
			result = fileMode();	// If user selects "f", runs the fileMode() function 
									// fileMode() returns an integer either 1 or 0 (refer to the function implemention)

			// if result is 1, encoding + writing to another file is successful
			if (result == 1) {
				printf("\nYour file has been encoded/decoded!\n");
				break;
			}
			// if result is 0, failed operation
			else {
				printf("\nEncoding/Decoding failed!\n");
			}
		}
		else {	//Invalid input from the user (anything else other than "i" and "f"
			printf("Invalid input! Please enter either \"i\" or \"f\" ONLY.\n");
			continue;
		}
	}
	printf("\nThank you for using this program!\n");	
}

char* file_ext(const char *string){
	assert(string != NULL);
	char *ext = strrchr(string, '.');

	if (ext == NULL)
		return (char*)string + strlen(string);

	for (char *iter = ext + 1; *iter != '\0'; iter++) {
		if (!isalnum((unsigned char)*iter))
			return (char*)string + strlen(string);
	}

	return ext;
}

// File Mode function implementation 
int fileMode() {
	FILE *file;
	FILE *outputFile;
	char str[MAXCHAR];	//contains original characters before cipher
	char inputFileName[MAXCHAR];
	char outputFileName[MAXCHAR];
	int i = 0;

	//INPUT FILE
	printf("Enter input file=> ");
	gets(inputFileName);
	char* filename_i = inputFileName;
	file = fopen(filename_i, "r");		//opens the output file and set as 'file', with "r", allow READ ONLY (cannot modify the content in the input txt)
	if (file == NULL || strcmp(".txt", file_ext(inputFileName)) != 0 ) {		// When the filename as indicated by 'filename_i' does not exist
		printf("ERROR: Could not open file %s", filename_i);
		return 0;	//return 0 in the main function (result = 0) FAILED
	}

	//OUTPUT FILE
	printf("Enter output file=> ");
	gets(outputFileName);
	char* filename_o = outputFileName;	//output file
	outputFile = fopen(filename_o, "w");	//opens the output file and set as 'outputFile', with "w", allowing writable file
	if (outputFile == NULL || strcmp(".txt", file_ext(outputFileName)) != 0) {	// When the filename as indicated by 'filename_o' does not exist
		printf("ERROR: Could not open file %s", filename_o);
		return 0;	//return 0 in the main function (result = 0) FAILED
	}

	// Cipher happens here
	while (fgets(str, MAXCHAR, file) != NULL) {	// a while loop to checks for each line of characters (line by line)
		// the line of characters is stored as in the array str[]
		int i = 0;	// counting index for the current array of characters
		while (str[i] != '\0')	// to check if it has reached the end of the line
		{
			// checks if the current character is within acceptable range of characters to allow cipher to take place
			// if the current character is a-z or A-Z, satisfies the condition 
			if (!((str[i] >= 0 && str[i]<65) || (str[i]>90 && str[i]<97) || (str[i]>122 && str[i] <= 127)))
			{
				if (str[i] >= 'A'&&str[i] <= 'Z')	// check if it is capital letter
					fprintf(outputFile, "%c", 'Z' + 'A' - str[i]);
				if (str[i] >= 'a'&&str[i] <= 'z')	// check if it is a small letter
					fprintf(outputFile, "%c", 'z' + 'a' - str[i]);
			}
			// if the current character is a-z or A-Z, it remains as it is
			if (((str[i] >= 0 && str[i]<65) || (str[i]>90 && str[i]<97) || (str[i]>122 && str[i] <= 127)))
			{
				fprintf(outputFile, "%c", str[i]);
			}
			i++;	// increment counting index to move on to the next character in the array str[]
		}

	}

	fclose(file);	// closes and saves input file
	fclose(outputFile);	// closes and saves output file

	return 1;	// //return 0 in the main function (result = 1) SUCCESS
}

// Interactive Mode function implementation 
void interactiveMode() {
	int i;
	char str[MAXCHAR];
	printf("\nInput text you want to encode/decode: ");
	gets(str);	// stores the texts input by user as array of characters str[]
	printf("Encoded/decoded text is: ");	
	
	
	i = 0;
	// Cipher happens here
	while (str[i] != '\0')	// a while loop to checks for each line of characters (line by line)
	{
		// checks if the current character is within acceptable range of characters to allow cipher to take place
		// if the current character is a-z or A-Z, satisfies the condition
		if (!((str[i] >= 0 && str[i]<65) || (str[i]>90 && str[i]<97) || (str[i]>122 && str[i] <= 127)))
		{
			if (str[i] >= 'A'&&str[i] <= 'Z')	// check if it is capital letter
				printf("%c", 'Z' + 'A' - str[i]);
			if (str[i] >= 'a'&&str[i] <= 'z')	// check if it is a small letter
				printf("%c", 'z' + 'a' - str[i]);
		}
		// if the current character is a-z or A-Z, it remains as it is
		if (((str[i] >= 0 && str[i]<65) || (str[i]>90 && str[i]<97) || (str[i]>122 && str[i] <= 127)))
		{
			printf("%c", str[i]);
		}

		i++;	// increment counting index to move on to the next character in the array str[]
	}
	printf("\n\n");
	
	
}


