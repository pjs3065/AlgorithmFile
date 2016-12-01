#include<stdio.h>
#include<stdlib.h>

typedef struct order
{
	double due;
	double cost;
	int made;
}order;

void main()
{
	order *input;
	double **cost_table;
	int *make_order;

	int job;
	int total_time = 0;

	int i,j;
	int item = 0;
	double max_cost;
	int max_index;

	//input jobs
	printf("How many input your order : ");
	scanf("%d", &job);

	// job�� 1 ~ 1000
	if(job <= 0 || job > 1000)
		exit(0);

	// dynamic �Ҵ�
	input = (order*)malloc(sizeof(order)*(job + 1));
	cost_table = (double**)malloc(sizeof(double*)*(job + 1));

	//input ( �ð��� 1000�� ������ �ȵȴ� )
	for(i = 1; i <= job; i++)
	{
		printf("Input %dth (due,cost) : ",i);
		scanf("%lf %lf",&(input+i)->due,&(input+i)->cost);

		if((input+i)->due <= 0 || (input+i)->due > 1000)
		exit(0);

		//���� ������ ����
		(input+i)->made = 0;
		total_time = total_time + (input+i)->due;
	}

	// 2���� �迭������
	make_order = (int*)malloc(sizeof(int)*(total_time + 1));
	for(i=1; i<=job; i++)
	{
		cost_table[i] = (double*)malloc(sizeof(double)*(total_time + 1));
	}

	// cost table ����� (���� �������� �ð��� ������ �ʾҴٸ� �Ϸ�� cost���� ���� ���� �ð��� �����ٸ� �г�Ƽ ������ ����)
	for(i = 1; i <= job; i++)
	{
		cost_table[i][0] = 0;
		for(j = 1; j <= total_time; j++)
		{
			if(j <= (input+i)->due)
				cost_table[i][j] = cost_table[i][j-1] + ((input+i)->cost / (input+i)->due);
			else
				cost_table[i][j] = cost_table[i][j-1] + (input+i)->cost;
		}
	}
	
	// cost table ���
	printf("\n< cost talbe >\n\n");
	printf("\t");

	for(i = 1; i<= total_time; i++)
	{
		printf("<%d>\t",i);
	}
	printf("\n");

	for(i = 1; i <= job; i++)
	{
		printf("<%d>th\t",i);
		for(j = 1; j <= total_time; j++)
		{
			printf("%.1lf\t",cost_table[i][j]);
		}
		printf("\n");
	}

	//���ؼ� ���� ���� ���ϱ�(���� �ð����� cost�� �ִ� ���� ���ϰ� item�� ���� �׸��� �� item�� �ð� ��ŭ �ð��� �帥�� item ����)
	for(j = 1; j <= total_time; j = j + (input + max_index)->due)
	{
		max_cost = 0;
		item++;
		for(i = 1; i <= job; i++)
		{
			if(cost_table[i][j] > max_cost && (input+i)->made != 1)
			{
				max_cost = cost_table[i][j];
				max_index = i;
			}
		}
		*(make_order + item) = max_index;
		(input + max_index)->made = 1;
	}

	// ���� ���� ��� �մϴ�.
	printf("\n <make order>\n");
	for(i = 1; i <= item; i++)
	{
		printf("%d ",*(make_order + i));
	}
	printf("\n");
	
}