#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/* MACRO DEFINE */
#define CREATE	1  
#define ADD		2
#define REMOVE	3
#define MAX		4
#define MIN		5
#define TOTAL	6
#define EXIT	7
#define M_01 1     //Error: File is existed.
#define M_02 2     //Error: A file name cannot contain any of the special character.
#define M_03 3     //Error: ID doesn’t exist.
#define M_04 4     //Error: The score is not valid, please try again with score [0...10].  
#define M_05 5     //Create file successfully.
#define M_06 6 
#define M_07 7 
#define M_08 8 
#define M_09 9 
#define M_10 10    //Error: Command Incorrect! Please check the Introduction Notice and try again.
#define M_11 11    //Error: Name of file you have input is null. Please input your filename according to the File naming rules.
#define M_12 12    //Error: File is not existed.
#define M_13 13    //Error: Syntax error.
#define M_14 14    //Error: The ID is not valid

/* INITIALIZE */
struct student
{
	int id;
	unsigned int Math_score;
	unsigned int Physic_score;
	unsigned int English_score;
	char name;
};

typedef struct
{
	int Math_grade;
	int Physics_grade;
	int English_grade;
	int id;
	char name;
}student_typedef;

/*Global variables*/
bool error;
int total_student = 0;

/* Subroutine */
/*Description: Calculation average score*/
/*=================================================START FUNCTION===============================================*/
double Cal_average(int math, int physics, int english) {
	return ((double)math + (double)physics + (double)english) / 3;
}
/*================================================END OF FUNCTION===============================================*/

/* Subroutine */
/*Description: create a new txt file*/
/*=================================================START FUNCTION===============================================*/
int create_function(char file_name[50], int *flag_error)
{
	FILE* file_create = fopen(file_name, "w");
	return *flag_error = M_05;
	//printf("\nCreate sussusfully!\n\n");
	fclose(file_create);
}
/*================================================END OF FUNCTION===============================================*/

/* Subroutine */
/*Description: add a new student with the score into the txt file*/
/*=================================================START FUNCTION===============================================*/
int add_function(struct student* std, char* file_name)
{
	static unsigned int current_ID = 1;
	char name = NULL;
	char data[100];
	FILE* fPtr = fopen(file_name, "a");
	fprintf(fPtr, "%d %d %d %d\n", current_ID, std->Math_score, std->Physic_score, std->English_score);
	fclose(fPtr);
	total_student++;
	current_ID++;
	return 0;
}
/*================================================END OF FUNCTION===============================================*/

/* Subroutine */
/*Description: remove the student with ID from the txt file*/
/*=================================================START FUNCTION===============================================*/
void remove_function(struct student* std, char* file_name, int rmv_ID)
{
	int i;
	FILE* fPtr1 = fopen("tmp.txt", "a");// temporary file ;
	FILE* fPtr = fopen(file_name, "r"); // original file;

	student_typedef* passingStudents = malloc((sizeof(std) * total_student));

	int passingCount = 0;
	for (int i = 0; i < total_student; i++) {
		int id, math_score, phy_score, eng_score;
		error = fscanf(fPtr, "%d %d %d %d", &id, &math_score, &phy_score, &eng_score);

		//check for id that need remove;
		if (rmv_ID != id) {
			passingStudents[passingCount].id = id;
			passingStudents[passingCount].Math_grade = math_score;
			passingStudents[passingCount].Physics_grade = phy_score;
			passingStudents[passingCount].English_grade = eng_score;
			passingCount++;
		}
	}
	if (passingCount != total_student) {
		total_student = passingCount;
		//printf("Rmv complete");
	}

	//fprintf(fPtr1, "%i\n", passingCount);
	for (int i = 0; i < passingCount; i++)
		fprintf(fPtr1, "%d %d %d %d\n", passingStudents[i].id, passingStudents[i].Math_grade, passingStudents[i].Physics_grade, passingStudents[i].English_grade);

	fclose(fPtr1);
	fclose(fPtr);

	remove(file_name);
	error = rename("tmp.txt", file_name);

	return 0;
}
/*================================================END OF FUNCTION===============================================*/

/* Subroutine */
/*Description: get the ID of the student who has the highest average score and display that score*/
/*=================================================START FUNCTION===============================================*/
void max_function(struct student* std, char* file_name)
{
	/*local var*/
	double arr_average_value[1000];
	double max_value = 0;
	int count = 0;

	/*call Read_all_file_function*/
	FILE* fPtr = fopen(file_name, "r"); // original file;

	student_typedef* gettingStudents = malloc((sizeof(std) * total_student));

	for (int i = 0; i < total_student; i++) {
		int id, math_score, phy_score, eng_score;

		fscanf(fPtr, "%d %d %d %d", &id, &math_score, &phy_score, &eng_score);

		gettingStudents[i].id = id;
		gettingStudents[i].Math_grade = math_score;
		gettingStudents[i].Physics_grade = phy_score;
		gettingStudents[i].English_grade = eng_score;

		/*Calculation average value for each student*/
		arr_average_value[i] = Cal_average(math_score, phy_score, eng_score);

		/*check for new max value*/
		if (max_value < arr_average_value[i]) {
			max_value = arr_average_value[i];
		}
	}

	/*Print all id that have the same max average*/
	printf("Max average score is %1.2f\n", max_value);
	for (int i = 0; i < total_student; i++) {
		if (arr_average_value[i] == max_value) {
			printf("Id = %d\n", gettingStudents[i].id);
		}
	}
}
/*================================================END OF FUNCTION===============================================*/

/* Subroutine */
/*Description: get the ID of the student who has the lowest average score and display that score*/
/*=================================================START FUNCTION===============================================*/
void min_function(struct student* std, char* file_name)
{
	/*local var*/
	double arr_average_value[1000];
	double min_value = 10;
	int count = 0;

	/*call Read_all_file_function*/
	FILE* fPtr = fopen(file_name, "r"); // original file;

	student_typedef* gettingStudents = malloc((sizeof(std) * total_student));

	for (int i = 0; i < total_student; i++) {
		int id, math_score, phy_score, eng_score;

		error = fscanf(fPtr, "%d %d %d %d", &id, &math_score, &phy_score, &eng_score);

		gettingStudents[i].id = id;
		gettingStudents[i].Math_grade = math_score;
		gettingStudents[i].Physics_grade = phy_score;
		gettingStudents[i].English_grade = eng_score;

		/*Calculation average value for each student*/
		arr_average_value[i] = Cal_average(math_score, phy_score, eng_score);

		/*check for new max value*/
		if (min_value > arr_average_value[i]) {
			min_value = arr_average_value[i];
		}
	}

	/*Print all id that have the same max average*/
	printf("Min average score is %1.2f\n", min_value);
	for (int i = 0; i < total_student; i++) {
		if (arr_average_value[i] == min_value) {
			printf("ID = %d\n", gettingStudents[i].id);
		}
	}
}
/*================================================END OF FUNCTION===============================================*/

/* Subroutine */
/*Description: display the total number of students existing in the database file*/
/*=================================================START FUNCTION===============================================*/
void total_function()
{
	printf("Total number of student: %d\n", total_student);
}
/*================================================END OF FUNCTION===============================================*/

/* Subroutine */
/*Description: call funtion to exit the program*/
/*=================================================START FUNCTION===============================================*/
int exit_function(int *Mode_exit)
{
	char Continue[5];
	printf("If you want to continue, please select:        (y/Y).\n");
	printf("If you want to exit, please select:     (n/N).\n");
	printf("Your choice is: ");
	error = scanf("%s", Continue);
	if ((Continue[0] == 'y') | (Continue[0] == 'Y'))
	{
		*Mode_exit = 1;
	}
	else if ((Continue[0] == 'n') | (Continue[0] == 'N'))
	{
		*Mode_exit = 0;
		printf("THANK YOU! HAVE A NICE DAY!\n");
	}
	else
	{
		//do nothing;
	}
	return *Mode_exit;
}
/*================================================END OF FUNCTION===============================================*/

/* Subroutine */
/*Description: function to check if file is exist or not */
/*=================================================START FUNCTION===============================================*/
int exists(const char* fname)
{
	FILE* file;
	if ((file = fopen(fname, "r")))
	{
		fclose(file);
		return 1;
	}
	return 0;
}
/*================================================END OF FUNCTION===============================================*/

/*Function: main*/
/*Description: main function*/
/*=================================================START FUNCTION===============================================*/
void main()
{
	/*Initialize variables*/

	char file_name[50];
	int mode; //using to call function
	int mode_exit = 1; //using to exit the program
	int error_flag = 0; //using in the case of checking error
						/*Print the intruction for users*/
	char input[100]; // using to store user's input
	char parse[10][10]; // using to store data after parse input
	char output[10][10]; // using to store output data after check valid
						 // Out put will have
						 // output[0] = error flag
						 // output[1] = function/ mode
						 // output[2] = filename.txt
						 // output[3] = math_score
						 // output[4] = physic_score
						 // output[5] = english_score
						 // output[6] = ID if any
	int j, k; // index of parse[][]
	int function = 0; // store function in check valid
	bool check; // flag to check if file is exist or not
	int out_math_score;
	int out_physic_score;
	int out_english_score;
	int rmv_ID;

	struct student* pSt = (struct student*)malloc(sizeof(struct student));

	printf("----------------------------------------------MENU------------------------------------------------------------");
	printf("\n1. Create a new text file -> Syntax: Program - create filename.txt");
	printf("\n2. Add a new student with the score -> Syntax: Program -add filename.txt x y z");
	printf("\n3. Remove a student with ID N from a txt file -> Syntax: Program -remove filename.txt N");
	printf("\n4. Get the ID of the student who has the highest average score -> Syntax: Program -max filename.txt");
	printf("\n5. Get the ID of the student who has the lowest average score -> Syntax: Program -min filename.txt");
	printf("\n6. Display the total number of students existing in the database file -> Syntax: Program -total filename.txt");
	printf("\n7. Exit the program -> Syntax: Program -exit");
	printf("\n----------------------------------------------NOTE------------------------------------------------------------");
	printf("\n      1. A file name can not contain any of the special characters");
	printf("\n      2. When you enter the scores, you have to enter the score from 0 to 10");
	printf("\n      3. You must follow the syntax as above");
	printf("\n--------------------------------------------------------------------------------------------------------------");
	do
	{
		error_flag = 0;
		j = 0; k = 0;
		function = 0;

		// Function to input
		printf("\nEnter your command: ");
		error = scanf("%*[\n]");
		fgets(input, sizeof input, stdin);

		// Parse input, slit by space
		// Arg: Inpput
		// Return parse[][]
		for (int i = 0; i <= strlen(input); i++)
		{
			if (input[i] == ' ' || input[i] == '\0' || input[i] == '\n')
			{
				parse[j][k] = '\0';
				j++;
				k = 0;
			}
			else
			{
				parse[j][k] = input[i];
				k++;
			}
		}

		while (error_flag == 0)
		{
			// Check input for special characters
			for (int a = 0; a < strlen(input); a++)
			{
				if ((input[a] >= 'a' && input[a] <= 'z') || (input[a] >= 'A' && input[a] <= 'Z'))
				{

				}
				else if (input[a] >= '0' && input[a] <= '9')
				{

				}
				else if (input[a] == ' ' || input[a] == '-' || input[a] == '.' || input[a] == '/0' || input[a] == '\n')
				{

				}
				else
				{
					error_flag = M_02;
					break;
				}

			}

			// handle the 1st member of parse, index = 0
			// it's must be "program"
			// if not, return syntax error
			if (strcmp(parse[0], "program") == 0)
			{
				// NOP
			}
			else
			{
				error_flag = M_13;
				break;
			}

			// handle the 2nd member of parse, index = 1
			// it's must be "-<function_name>"
			// if not, return syntax error
			if (strcmp("-create", parse[1]) == 0)
			{
				function = CREATE;
			}
			else if (strcmp("-add", parse[1]) == 0)
			{
				function = ADD;
			}
			else if (strcmp("-remove", parse[1]) == 0)
			{
				function = REMOVE;
			}
			else if (strcmp("-max", parse[1]) == 0)
			{
				function = MAX;
			}
			else if (strcmp("-min", parse[1]) == 0)
			{
				function = MIN;
			}
			else if (strcmp("-total", parse[1]) == 0)
			{
				function = TOTAL;
			}
			else if (strcmp("-exit", parse[1]) == 0)
			{
				function = EXIT;
			}
			else
			{
				error_flag = M_13;
				break;
			}

			// Copy function code to output[1]
			output[1][0] = function + '0'; output[1][1] = '\0';

			// Calculate the length of parse[2] and parse[3] for check file and ID
			int len_file = strlen(parse[2]);
			int leng = strlen(parse[3]);

			// handle the 3rd member of parse, index = 2
			// This function will compare 5 last elements of parse[2]
			// Because the file name end with .txt so 4 last elements are must be ".txt"
			// If not, return filename error
			// AND this will check if the file name is not blank
			// If yes, return filename error
			// After that, it's will copy all the file name to the 3rd members of output[2]
			if (function != EXIT)
			{
				if (parse[2][len_file - 1] == 't' && parse[2][len_file - 2] == 'x' && parse[2][len_file - 3] == 't' && parse[2][len_file - 4] == '.' && parse[2][len_file - 5] != NULL)
				{
					// NOP
				}
				else
				{
					error_flag = M_11;
					break;
				}

				for (int m = 0; m < strlen(parse[2]) + 1; m++)
				{
					output[2][m] = parse[2][m];
					if (m == strlen(parse[2]))
					{
						output[2][m] = NULL;
					}
				}
			}

			// Check if file exist in create function
			// and check if file not exist in orther funtion except exit and create
			if (function == CREATE)
			{
				check = exists(parse[2]);
				if (check == false)
				{
					// NOP
				}
				else
				{
					error_flag = M_01;
					break;
				}
			}
			else if (function == EXIT)
			{

			}
			else
			{
				check = exists(parse[2]);
				if (check == false)
				{
					error_flag = M_12;
				}
				else
				{
					// NOP
				}
			}

			// This function will check the number error of 3 scores.
			if (function == ADD)
			{
				for (int n = 3; n < 6; n++)
				{
					for (int o = 0; o < strlen(parse[n]); o++)
					{
						if (parse[n][o] >= '0' && parse[n][o] <= '9')
						{

						}
						else
						{
							error_flag = M_04;
							break;
						}

						if (parse[n][0] == '1')
						{
							if(parse[n][1] != '0' && parse[n][1] != NULL)
							{
								error_flag = M_04;
								break;
							}
							else if (parse[n][1] == '0')
							{

							}
						}
						else
						{
						
						}
					}
					if (parse[n][0] == '1' && parse[n][1] == '0')
					{
						output[n][0] = '1'; output[n][1] = '0';
					}
					else
					{
						output[n][0] = parse[n][0]; output[n][1] = '\0';
					}
				}
			}
			else
			{
				output[3][0] = NULL;
				output[4][0] = NULL;
				output[5][0] = NULL;
			}

			// This function will check the number error of ID.
			if (function == REMOVE)
			{
				int o;
				for (o = 0; o < strlen(parse[3]); o++)
				{
					if (parse[3][o] >= '0' && parse[3][o] <= '9')
					{
						output[6][o] = parse[3][o];
					}
					else
					{
						error_flag = M_14;
						break;
					}
				}
				 output[6][o] = '\0';
			}
			else
			{
				output[6][0] = NULL;
			}

			break;
		}

		output[0][0] = error_flag + '0'; output[0][1] = '\0';

		

		/* OUTPUT HANDLE */
		error_flag = atoi(output[0]);
		mode = atoi(output[1]);
		strcpy(file_name, output[2]);
		pSt->Math_score = atoi(output[3]);
		pSt->Physic_score = atoi(output[4]);
		pSt->English_score = atoi(output[5]);
		rmv_ID = atoi(output[6]);

		/*PROCESS*/
		
		if (error_flag == 0)
		{
			switch (mode)
			{
			case CREATE:
				//printf("\nEnter your filename: ");
				//scanf("%s", &file_name);
				create_function(file_name, &error_flag);
				break;
			case ADD:
				add_function(pSt, file_name);
				break;
			case REMOVE:
				remove_function(pSt, file_name, rmv_ID);
				break;
			case MAX:
				max_function(pSt, file_name);
				break;
			case MIN:
				min_function(pSt, file_name);
				break;
			case TOTAL:
				total_function();
				break;
			case EXIT:
				exit_function(&mode_exit);
				break;
			default:
				break;
			}
		}
		/**/
		else
		{
			//do nothing;
		}

		/*OUTPUT*/

		if (error_flag != 0)
		{
			switch (error_flag)
			{
			case M_01:
				printf("File name is existed!");
				break;
			case M_02:
				printf("A file name can not contain any of the special characters!");
				break;
			case M_03:
				printf("ID doesn't exist!");
				break;
			case M_04:
				printf("The score is not valid, please try again with the score from 0 to 10!");
				break;
			case M_05:
				printf("Create successfully!");
				break;
			case M_06:
				printf("Update successfully");
				break;
			case M_07:
				printf("Remove successfully!");
				break;
			case M_08:
				printf("The score is not valid, please try again with the score from 0 to 10!");
				break;
			case M_09:
				printf("");
				break;
			case M_10:
				printf("");
				break;
			case M_11:
				printf("Name of file you have input is null. Please input your filename according to the File naming rules!");
				break;
			case M_12:
				printf("File is not existed!");
				break;
			case M_13:
				printf("Syntax error!");
				break;
			case M_14:
				printf("ID is not valid, please try again");
				break;
			default:
				break;
			}
		}
		else
		{
			//do nothing
		}
		
	} while (mode_exit != 0);
	_getch();
	return 0;
}
/*================================================END OF FUNCTION===============================================*/
