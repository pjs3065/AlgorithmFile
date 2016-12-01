//made 2016.09.17 3:54pm park jae seong
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ELEPHANT  // �ڳ��� ����
{
	int no;
	int weight;
	int iq;
}ELEPHANT;

ELEPHANT elep[1001]; // �ڳ��� �Է��� �� �ִ� �迭

int *sequence; // �ִ� ���̸� ������ ���� ����
int *navigate; // ���� �ȳ����ִ� ���� ����
int *result; // ��� �� �ڳ��� �ѹ� ���� ����

int len = 0; // �ڳ����� �迭�� ���� (1���� ����)

void input();
void sort();
void swap(int j);
void table();
int max_sequence();
void print(int count);

/*
<description : main>
purpose : Analyze a collection of elephants and place as large a subset of elephants as possible 
		into a sequence whose weights are increasing but IQ��s are decreasing.  
input : None.
output : None.
*/
void main()
{
	int count = 0;
	
	input();				//�ڳ����� �迭�� �־��ش�.
	sort();					// �ڱ⸮ ������ ������������ �����Ѵ�.
	table();				// table ǥ��
	count = max_sequence();	// �ִ� ���� ���ϱ�
	print(count);			//�ڳ��� �ѹ��� ���� ���
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
		sequence[i] = 1; // ��� �ּ� ġ�� 1
		navigate[i] = 0; // 0���� �����ϱ⿡ -1�� �ʱ�ȭ
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
	int count = 0; // length�� ����

	// length �ִ�ġ ã��
	for(i = 1; i <= len; i++)
	{
		if(length < sequence[i])
		{
			length = sequence[i];
			root = i;
		}
	}

	// �ִ� �� �������� ������ �ڳ��� ���� navigate�� ���� ���� �ڳ����� ��ȣ�� �����Ѵ�.
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