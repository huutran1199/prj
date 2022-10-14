#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h""
#include <string.h>
#include "conio.h"
#include <stdlib.h>


struct student
{
	int Math_grade;
	int Physics_grade;
	int English_grade;
	int id;
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
/*==============================================================================*/
unsigned int total_student;

/*==============================================================================*/
void max_function(struct student* std, char* file_name);
void min_function(struct student* std, char* file_name);
void total_function();
double Cal_average(int math, int physics, int english);

/*==============================================================================*/


void main() {
	char* file_name = "test1.txt";
	struct student* pSt = (struct student*)malloc(sizeof(struct student));
	total_student = 5;
	min_function(pSt, file_name);
	max_function(pSt, file_name);
	total_function();
	
	_getch();
	system("pause");
}

double Cal_average(int math, int physics, int english) {
	return ((double)math + (double)physics + (double)english) / 3;
}

void max_function(struct student* std, char* file_name) {
	/*local var*/
	double arr_average_value[1000];
	double max_value = 0;
	int count = 0;

	/*call Read_all_file_function*/
	FILE *fPtr = fopen(file_name, "r"); // original file;

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
	printf("Max value is %1.2f\n", max_value);
	for (int i = 0; i < total_student; i++) {
		if (arr_average_value[i] == max_value) {
			printf("%d\n", gettingStudents[i].id);
		}
	}
	/*---------------------------*/
	/*---------------------------*/
}


void min_function(struct student* std, char* file_name) {
	/*local var*/
	double arr_average_value[1000];
	double min_value = 10;
	int count = 0;

	/*call Read_all_file_function*/
	FILE *fPtr = fopen(file_name, "r"); // original file;

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
		if (min_value > arr_average_value[i]) {
			min_value = arr_average_value[i];
		}
	}

	/*Print all id that have the same max average*/
	printf("Min value is %1.2f\n", min_value);
	for (int i = 0; i < total_student; i++) {
		if (arr_average_value[i] == min_value) {
			printf("%d\n", gettingStudents[i].id);
		}
	}
	/*---------------------------*/
	/*---------------------------*/
}

void total_function(void) {
	printf("Total number of student: %d\n", total_student);
}
