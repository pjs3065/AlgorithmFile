#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define D_MAX 100
#define MAX 31

int pancake_number = 0; // 펜 케잌의 수
int current_point = 0; // 현재 시작 위치
int spatula = 0 ; // 최대수 찾은후 뒤집기 위치
int flip_number = 0; // flip의 수

int diameter[MAX] = {0,}; // 팬케잌 잘라서 넣을 지름들
char pancake[D_MAX] = {0,}; // 입력받을 지름 문자열
int flip[D_MAX] = {0,}; // flip 모음집

int input();
void max();
void flips();

/*
<description : main>
purpose : Stack of the delicious pancakes with the task. sort the stack by size such that each pancake is smaller 
		  than all the pancakes below it. 
input : None.
output : None.
*/
void main()
{
	int i = 1;

	if(input() == -1) // 입력받기
	{ 
		printf(" diameter error(1 ~ 10)!!!!\n");
		exit(0);
	}

	while(diameter[i] != NULL)
	{
		printf("%d ",diameter[i]);
		i++;
	}
	printf("( ");

	while(current_point != pancake_number) // 현재 위치와 마지막 팬케잌과 만나면 종료
	{
		if(current_point == 0)
		{
			flips(); // 뒤집어서 넣어진 배열을 뒤집어주기
		}

		max(); // 최대 값구하기

		if(spatula == current_point) // 뒤집개가 맨 아래있을 경우 다음 위치로 이동
		{
			current_point++;
		}

		else // 아니면 뒤집기
			flips();
	}

	for(i = pancake_number; i > 0; i--)  // 팬케이크 위에서 부터 출력
	{
		printf("%d ",diameter[i]);
	}

	printf(")\n");

	printf("(");
	for(i = 0; i < flip_number; i++) // 뒤집개 번호 출력
	{
		printf("%d ",flip[i]);
	}
	printf("0)\n");
}


/*
<description : input>
purpose : Type diameters of pancakes(1~10), then they are stored to diameter array. Typed String token by (" ").
input : None.
output : If typed diameter is less 1 or more 10 ,than return -1 . Else return 0.
*/
int input()
{
	char *temp = ""; // 임시로 자를 문자열

	printf("Type pancake: ");
	gets(pancake); // 팬케잌 입력받고

	temp = strtok(pancake," ");
	while(temp != NULL)	// 입력받은 펜케잌을 잘라서 지름 배열 안에 넣기
	{
		pancake_number++;
		diameter[pancake_number] = atoi(temp);  // 1,2,3,4,5 -> 1부터 시작
		if(diameter[pancake_number] < 1 || diameter[pancake_number] > 10)
		{
			return -1;
		}

		temp = strtok(NULL," ");	
	}
	return 0;
}


/*
<description : max>
purpose : Find largest pancake.    
input : None
output : None
*/
void max()
{
	int max_diameter = -1; // 최대 수

	if(current_point == 0)
	{
		current_point = 1;
	}

	for(int i = current_point; i <= pancake_number; i++) // 최대값 구하기
	{
		if(max_diameter <= diameter[i])
		{
			max_diameter = diameter[i];
			spatula = i;
		}
	}
}


/*
<description : flips>
purpose : At Correct position(spatula position), Flips pancake. (each pancake is smaller than all the pancakes below it).    
input : None
output : None
*/
void flips()
{
	int temp;
	int count = 0;

	if(spatula == 0)
	{
		spatula = 1;
	}

	if(spatula == pancake_number)
	{
		spatula = current_point;
		current_point++;
	}

	if(current_point != 0)
	{
		flip[flip_number] = spatula;
		flip_number++;
	}

	for(int i = spatula; i < (pancake_number + spatula + 1) / 2; i++)
	{
		temp = diameter[i];
		diameter[i] = diameter[pancake_number-count];
		diameter[pancake_number-count] = temp;
		count++;
	}
}
