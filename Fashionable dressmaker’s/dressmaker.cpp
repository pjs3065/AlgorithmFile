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

	// job은 1 ~ 1000
	if(job <= 0 || job > 1000)
		exit(0);

	// dynamic 할당
	input = (order*)malloc(sizeof(order)*(job + 1));
	cost_table = (double**)malloc(sizeof(double*)*(job + 1));

	//input ( 시간이 1000을 넘으면 안된다 )
	for(i = 1; i <= job; i++)
	{
		printf("Input %dth (due,cost) : ",i);
		scanf("%lf %lf",&(input+i)->due,&(input+i)->cost);

		if((input+i)->due <= 0 || (input+i)->due > 1000)
		exit(0);

		//아직 만들지 않음
		(input+i)->made = 0;
		total_time = total_time + (input+i)->due;
	}

	// 2차원 배열포인터
	make_order = (int*)malloc(sizeof(int)*(total_time + 1));
	for(i=1; i<=job; i++)
	{
		cost_table[i] = (double*)malloc(sizeof(double)*(total_time + 1));
	}

	// cost table 만들기 (현재 아이템의 시간이 지나지 않았다면 하루당 cost양이 증가 만약 시간이 지났다면 패널티 원값이 증가)
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
	
	// cost table 출력
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

	//비교해서 만들 순서 정하기(현재 시간에서 cost의 최대 값을 구하고 item을 선정 그리고 그 item의 시간 만큼 시간이 흐른후 item 선정)
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

	// 만들 순서 출력 합니다.
	printf("\n <make order>\n");
	for(i = 1; i <= item; i++)
	{
		printf("%d ",*(make_order + i));
	}
	printf("\n");
	
}