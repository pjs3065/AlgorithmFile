//Made in parkjaeseong. 2016.10.13
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char city_name[100][100]; // city�̸��� �Է¹޴� ����

int city_number; // city�� ����
int train_number; // train�� ��
int depart; // ��� �ð�

int start; // ���� �ϴ� ��ġ
int end; // ������ ��ġ

int schedule_number[1000]; //train�� ������ �ִ� ���ߴ� ���� ��
int train[1000][100][2]; // train�� ������ �ִ� train�ð��� ������ ��ġ ����
int min_time[100][2]; // �ּҽð��� �����ϱ� ���� ���� 
int check[100]; // train check Ȯ�ο� ����

int city_location(char *name); // city�� ��ġ�� �˾Ƴ��� �Լ�
int input(void); // �Է��ϴ� �Լ�
void scheduler(void); // ���ͽ�Ʈ�� �̿��ؼ� �����ð��� ������ ��߽ð��� ������ ¥�ִ� �Լ�


int main(void)
{
	int i;
	int s; // ��� ���α׷��� �ݺ��ϴ� �Է��ϴ� ����
	scanf("%d",&s); // ��� ���α׷��� �ݺ��� ���ΰ�?
	for(i = 0;i < s; i++) // 1�Է½� 1�� �ݺ�
	{
		if(input() == -1)// �Է��ϴ� �Լ� ( ������� ���� ��� ���α׷� ���� )
			exit(0);
		scheduler(); // ������ ¥�ִ� �Լ� (depart �� arrival)

		if(check[end])
		{
			printf("----------------------\n");
			printf("Departure : %04d %s\n",min_time[start][1],city_name[start]);
			printf("Arrival : %4d %s\n",min_time[end][0],city_name[end]);
		}
		else
			printf("No!! Connection");
		printf("\n");
	}
}

int input(void)
{
	int i;
	int j;

	char name[100]; // ������ �̸��� �Է¹��� ���̴�.
	scanf("%d",&city_number); // ������ ������ �Է��Ѵ�.

	// ���� ��ŭ city_name�ȿ� �����Ѵ�. 
	for(i = 0; i < city_number; i++)
		scanf("%s",city_name[i]);

	//train�� ������ �Է��Ѵ�. 
	scanf("%d",&train_number);

	// train�� ������ŭ �ݺ��Ѵ�.
	for(i = 0; i < train_number; i++)
	{
		//train�� ������ schedule�� ������ �Է¹޴´�.
		scanf("%d",&schedule_number[i]);

		//train�� ������ schedule�� ������ŭ train�� ������ �ð��� ���� �̸��� �Է¹޴´�. (ex : 0949 seoul)
		for(j = 0; j < schedule_number[i]; j++)
		{
			//train�� �ð��� train�� ���ߴ� ������ ����
			scanf("%d %s", &train[i][j][0], name);
			train[i][j][1] = city_location(name);

		}
	}

	//��߽ð� �Է�
	scanf("%d",&depart);
	//��� ��� �Է�
	scanf("%s",name);
	start=city_location(name);
	//���� ��ġ �Է�
	scanf("%s",name);
	end=city_location(name);

	if(start == end)
		return -1;
	return 0;
}

// �Է��� �̸��� location�� return ���ִ� �Լ�
int city_location(char *name)
{
	int i;

	// city�� ���� ��ŭ Ȯ���Ѵ�. ���� ã���� �ϴ� ��ġ�� �������
	for(i = 0; i < city_number; i++)
	{
		// ���� ã������ �� ��ġ i�� return
		if(strcmp(name,city_name[i])==0)
			return i;

	}
	// ��ã������ ��ã�Ҵٴ� -1�� return
	return -1;
}

// schedule�� ������ִ� �Լ�
void scheduler(void)

{
	int i;
	int j;
	int k;
	int l;
	int now;

	// ������ ���� ��ŭ 0��°�� 1��° �� 10000�� -1�� �ʱ�ȭ ���ش�.
	for(i = 0; i < train_number; i++)
	{
		min_time[i][0] = 10000;
		min_time[i][1] = -1;
		check[i] = 0;
	}

	// min_time�� �����ϴ� Ÿ���� 0��° 0800���� �־��ش�.
	min_time[start][0]=depart;

	for(i = 0; i < train_number; i++)
	{
		now = -1;

		for(j = 0; j < train_number; j++)
		{

			// ������ check�� �߾��� Ȯ��
			if(check[j])
				continue;

			// ���� now�� -1�̰ų�,  ���� min_time�� �ٸ� �ͺ��� ũ��
			if(now == -1 || min_time[now][0] > min_time[j][0])
				now = j; // ���� 0
		}

		// ��߽ð��� 10000�� �Է½� �����Ѵ�.
		if(min_time[now][0] == 10000)
			break;

		check[now] = -1; // Ȯ������ -1�� ������ش�.

		for(j = 0; j < train_number; j++)
		{
			for(k = 0; k < schedule_number[j]-1; k++)
			{
				if(train[j][k][1] == now && min_time[now][0] <= train[j][k][0]) // �̰� ������� ����, ���� �ּҽð����� ����Ǿ� �ִ� �Ͱ� ���ؼ� ���ϴ� ������ ��߽ð��� �� �����ٸ�
				{
				// l���� ���� ������ ���� +1�� ������
					l = k + 1;

					// ���� �������� ���ؼ� train���� �� ������ ���� �ּҽð��� �־��ش�.
					if(min_time[train[j][l][1]][0] > train[j][l][0])
						min_time[train[j][l][1]][0] = train[j][l][0];
				}
			}
		}
	}

	// ������ ���� ������ ������
	if(check[end] == 0)
		return;

// ������ ���۱����� �ð��� ���Ѵ� (�ݴ�� ����)
	// ���� ����� �ڵ�� ���� �����̱⿡ ���� ����

	for(i = 0; i < city_number; i++)
		check[i] = 0;

	min_time[end][1] = min_time[end][0];

	for(i = 0; i < city_number; i++)
	{
		now = -1;
		for(j = 0; j < city_number; j++)
		{
			if(check[j])
				continue;

			if(now == -1 || min_time[now][1] < min_time[j][1])
				now = j;
		}

		check[now] = 1;
		
		for(j = 0; j < train_number; j++)
		{
			for(k = 1;k < schedule_number[j]; k++)
			{
				if(train[j][k][1] == now && min_time[now][1] >= train[j][k][0])
				{
					l = k-1;
					if(min_time[train[j][l][1]][1] < train[j][l][0])
						min_time[train[j][l][1]][1] = train[j][l][0];
				}
			}
		}

	}
}
