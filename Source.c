#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"string.h"

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

int add_student(struct student *std, char* file_name);
int remove_student(struct student *std, char* file_name, int rmv_ID);


/*Global variables*/
int total_student = 0;

//void check_score(int abc)
//{};

int add_student(struct student *std, char* file_name)
{
	static unsigned int current_ID = 1;
	char name = NULL;
	char data[100];
	FILE *fPtr = fopen(file_name, "a");
	fprintf(fPtr, "%d %d %d %d\n", current_ID, std->Math_grade, std->Physics_grade, std->English_grade);
	fclose(fPtr);
	total_student++;
	current_ID++;
	return 0;
}

int remove_student(struct student *std, char* file_name, int rmv_ID)
{
	
	int i;
	FILE *fPtr1 = fopen("tmp.txt", "a");// temporary file ;
	FILE *fPtr = fopen(file_name, "r"); // original file;

	student_typedef* passingStudents = malloc((sizeof(std) * total_student));

	int passingCount = 0;
	for (int i = 0; i < total_student; i++) {
		int id, math_score, phy_score, eng_score;
		fscanf(fPtr, "%d %d %d %d", &id, &math_score, &phy_score, &eng_score);

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
	rename("tmp.txt", file_name);

	/**/
	//for (i = 0; i < line; i++)
	//{
	//	fscanf(fPtr, "id:%d\teng:%f\tphys:%f\tmath:%f\n", &std->id, &std->English_grade, &std->Physics_grade, &std->Math_grade);
	//	if (id != std->id)
	//	{
	//		sprintf(data, "id:%d\teng:%f\tphys:%f\tmath:%f\n", std->id, std->English_grade, std->Physics_grade, std->Math_grade);
	//		//write to temporary file
	//		fputs(data, fPtr1);
	//	}
	//	else {
	//		/*Not print the line have same id with input id*/
	//	}
	//}
	//fclose(fPtr);
	//fclose(fPtr1);
	//remove(file_name);          // remove the original file
	//rename("tmp.txt", file_name);
	//system("cls");
	//printf("remove line %d successfully!\n", id);
	return 0;
}
int main(void)
{
	char* file_name = "test1.txt";
	int rmv_ID = 2;
	int error = 0;
	struct student* pSt = (struct student*)malloc(sizeof(struct student));
	pSt->English_grade = 7;
	pSt->Math_grade = 3;
	pSt->Physics_grade = 6;
	error = add_student(pSt, file_name);
	error = add_student(pSt, file_name);
	error = add_student(pSt, file_name);
	error = add_student(pSt, file_name);	
	error = add_student(pSt, file_name);
	error = add_student(pSt, file_name);
	error = remove_student(pSt, file_name, rmv_ID);
}






