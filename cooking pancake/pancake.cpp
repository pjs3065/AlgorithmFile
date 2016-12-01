#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define D_MAX 100
#define MAX 31

int pancake_number = 0; // �� �ɟ��� ��
int current_point = 0; // ���� ���� ��ġ
int spatula = 0 ; // �ִ�� ã���� ������ ��ġ
int flip_number = 0; // flip�� ��

int diameter[MAX] = {0,}; // ���ɟ� �߶� ���� ������
char pancake[D_MAX] = {0,}; // �Է¹��� ���� ���ڿ�
int flip[D_MAX] = {0,}; // flip ������

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

	if(input() == -1) // �Է¹ޱ�
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

	while(current_point != pancake_number) // ���� ��ġ�� ������ ���ɟ�� ������ ����
	{
		if(current_point == 0)
		{
			flips(); // ����� �־��� �迭�� �������ֱ�
		}

		max(); // �ִ� �����ϱ�

		if(spatula == current_point) // �������� �� �Ʒ����� ��� ���� ��ġ�� �̵�
		{
			current_point++;
		}

		else // �ƴϸ� ������
			flips();
	}

	for(i = pancake_number; i > 0; i--)  // ������ũ ������ ���� ���
	{
		printf("%d ",diameter[i]);
	}

	printf(")\n");

	printf("(");
	for(i = 0; i < flip_number; i++) // ������ ��ȣ ���
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
	char *temp = ""; // �ӽ÷� �ڸ� ���ڿ�

	printf("Type pancake: ");
	gets(pancake); // ���ɟ� �Է¹ް�

	temp = strtok(pancake," ");
	while(temp != NULL)	// �Է¹��� ���ɟ��� �߶� ���� �迭 �ȿ� �ֱ�
	{
		pancake_number++;
		diameter[pancake_number] = atoi(temp);  // 1,2,3,4,5 -> 1���� ����
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
	int max_diameter = -1; // �ִ� ��

	if(current_point == 0)
	{
		current_point = 1;
	}

	for(int i = current_point; i <= pancake_number; i++) // �ִ밪 ���ϱ�
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
