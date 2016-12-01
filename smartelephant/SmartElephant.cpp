//made 2016.09.17 3:54pm park jae seong
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ELEPHANT  // 코끼리 정보
{
	int no;
	int weight;
	int iq;
}ELEPHANT;

ELEPHANT elep[1001]; // 코끼리 입력할 수 있는 배열

int *sequence; // 최대 길이를 저장해 놓는 공간
int *navigate; // 길을 안내해주는 저장 공간
int *result; // 결과 값 코끼리 넘버 저장 공간

int len = 0; // 코끼리의 배열의 길이 (1부터 시작)

void input();
void sort();
void swap(int j);
void table();
int max_sequence();
void print(int count);

/*
<description : main>
purpose : Analyze a collection of elephants and place as large a subset of elephants as possible 
		into a sequence whose weights are increasing but IQ’s are decreasing.  
input : None.
output : None.
*/
void main()
{
	int count = 0;
	
	input();				//코끼리를 배열에 넣어준다.
	sort();					// 코기리 몸무게 오름차순으로 정렬한다.
	table();				// table 표시
	count = max_sequence();	// 최대 길이 구하기
	print(count);			//코끼리 넘버와 길이 출력
}

/*
<description : input>
purpose : Input your elephants 's information(Weight, iq).
input : None.
output : None.
*/
void input()
{
	int weight;
	int iq;
	int no = 0;

	while(scanf("%d %d",&weight,&iq) != NULL)
	{
		if(weight == 0 || iq == 0)
			break;
		elep[++len].no = ++no;
		elep[len].weight = weight;
		elep[len].iq = iq;
	}
}

/*
<description : sort>
purpose : Elephant's weight are arranged in ascending order.   
input : None.
output : None.
*/
void sort()
{
	for(int i = 1; i <= len; i++)
	{
		for(int j = 1; j <= len-1; j++)
		{
			if(elep[j].weight > elep[j + 1].weight)
				swap(j);
		}
	}
}

/*
<description : swap>
purpose : Swap your elephants.  
input : None.
output : None.
*/
void swap(int j)
{
	ELEPHANT temp;

	temp = elep[j];
	elep[j] = elep[j + 1];
	elep[j + 1] = temp; 
}

/*
<description : table>
purpose : Store colletion of elephants 's max length in sequence[i] and store next root in navigate[i].  
input : None.
output : None.
*/
void table()
{
	int i, j;

	sequence = (int*)malloc(sizeof(int) * len);
	navigate = (int*)malloc(sizeof(int) * len);

	for(i = 1; i <= len; i++)
	{
		sequence[i] = 1; // 모든 최소 치는 1
		navigate[i] = 0; // 0부터 시작하기에 -1로 초기화
	}

	for(i = 1; i <= len; i++)
	{
		for(j = 1; j < i; j++)
		{
			if(elep[i].iq < elep[j].iq && elep[i].weight != elep[j].weight)
			{
				if(sequence[i] < sequence[j] + 1)
				{
					sequence[i] = sequence[j] +1;
					navigate[i] = j;
				}
			}
		}
	}
}

/*
<description : max_sequence>
purpose : Find max length, Store elephant's number in result sequence from maximum length till first root.  
input : None.
output : length count.
*/
int max_sequence()
{
	int i;
	int length = 0;
	int root = 0;
	int count = 0; // length의 길이

	// length 최대치 찾기
	for(i = 1; i <= len; i++)
	{
		if(length < sequence[i])
		{
			length = sequence[i];
			root = i;
		}
	}

	// 최대 긴 시퀀스의 마지막 코끼리 부터 navigate을 따라 가서 코끼리의 번호를 저장한다.
	result = (int*)malloc(sizeof(int)*(length + 1));

	while(root != 0)
	{
		result[length--] = elep[root].no;
		root = navigate[root];
		count++;
	}
	return count;
}

/*
<description : print>
purpose : Print max length collection of elephants's number.   
input : length count.
output : None.
*/
void print(int count)
{
	printf("--------------------\n");
	printf("  Max length = %d\n", count);
	printf("--------------------\n");
	for(int i = 1; i <= count; i++)
	{
		printf("\t%d\n",result[i]);
	}
	printf("--------------------\n");
}