//Made in parkjaeseong. 2016.10.13
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char city_name[100][100]; // city이름을 입력받는 공간

int city_number; // city의 갯수
int train_number; // train의 수
int depart; // 출발 시간

int start; // 시작 하는 위치
int end; // 끝나는 위치

int schedule_number[1000]; //train당 가지고 있는 멈추는 곳의 수
int train[1000][100][2]; // train이 가지고 있는 train시간과 내리는 위치 구간
int min_time[100][2]; // 최소시간을 저장하기 위한 공간 
int check[100]; // train check 확인용 공간

int city_location(char *name); // city의 위치를 알아내는 함수
int input(void); // 입력하는 함수
void scheduler(void); // 다익스트라를 이용해서 도착시간을 빠르게 출발시간을 느리게 짜주는 함수


int main(void)
{
	int i;
	int s; // 몇번 프로그램을 반복하는 입력하는 변수
	scanf("%d",&s); // 몇번 프로그램을 반복할 것인가?
	for(i = 0;i < s; i++) // 1입력시 1번 반복
	{
		if(input() == -1)// 입력하는 함수 ( 출발지가 같을 경우 프로그램 종료 )
			exit(0);
		scheduler(); // 스케쥴 짜주는 함수 (depart 와 arrival)

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

	char name[100]; // 도시의 이름을 입력받을 것이다.
	scanf("%d",&city_number); // 도시의 갯수를 입력한다.

	// 도시 만큼 city_name안에 저장한다. 
	for(i = 0; i < city_number; i++)
		scanf("%s",city_name[i]);

	//train의 갯수를 입력한다. 
	scanf("%d",&train_number);

	// train의 갯수만큼 반복한다.
	for(i = 0; i < train_number; i++)
	{
		//train이 가지는 schedule의 갯수를 입력받는다.
		scanf("%d",&schedule_number[i]);

		//train이 가지는 schedule의 갯수만큼 train이 가지는 시간과 도시 이름을 입력받는다. (ex : 0949 seoul)
		for(j = 0; j < schedule_number[i]; j++)
		{
			//train의 시간과 train의 멈추는 구간을 저장
			scanf("%d %s", &train[i][j][0], name);
			train[i][j][1] = city_location(name);

		}
	}

	//출발시간 입력
	scanf("%d",&depart);
	//출발 장소 입력
	scanf("%s",name);
	start=city_location(name);
	//도착 위치 입력
	scanf("%s",name);
	end=city_location(name);

	if(start == end)
		return -1;
	return 0;
}

// 입력한 이름의 location을 return 해주는 함수
int city_location(char *name)
{
	int i;

	// city의 갯수 만큼 확인한다. 지금 찾고자 하는 위치가 어디인지
	for(i = 0; i < city_number; i++)
	{
		// 만약 찾았으면 그 위치 i를 return
		if(strcmp(name,city_name[i])==0)
			return i;

	}
	// 못찾았으면 못찾았다는 -1값 return
	return -1;
}

// schedule을 계산해주는 함수
void scheduler(void)

{
	int i;
	int j;
	int k;
	int l;
	int now;

	// 지역의 갯수 만큼 0번째와 1번째 를 10000과 -1로 초기화 해준다.
	for(i = 0; i < train_number; i++)
	{
		min_time[i][0] = 10000;
		min_time[i][1] = -1;
		check[i] = 0;
	}

	// min_time을 시작하는 타임의 0번째 0800으로 넣어준다.
	min_time[start][0]=depart;

	for(i = 0; i < train_number; i++)
	{
		now = -1;

		for(j = 0; j < train_number; j++)
		{

			// 기차를 check를 했었나 확인
			if(check[j])
				continue;

			// 현재 now가 -1이거나,  현재 min_time이 다른 것보다 크면
			if(now == -1 || min_time[now][0] > min_time[j][0])
				now = j; // 현재 0
		}

		// 출발시간을 10000을 입력시 종료한다.
		if(min_time[now][0] == 10000)
			break;

		check[now] = -1; // 확인한후 -1로 만들어준다.

		for(j = 0; j < train_number; j++)
		{
			for(k = 0; k < schedule_number[j]-1; k++)
			{
				if(train[j][k][1] == now && min_time[now][0] <= train[j][k][0]) // 이게 출발지와 같고, 현재 최소시간으로 저장되어 있는 것과 비교해서 비교하는 기차가 출발시간이 더 느리다면
				{
				// l값에 현재 스케줄 에서 +1을 해준후
					l = k + 1;

					// 다음 스케줄을 비교해서 train값이 더 작으면 다음 최소시간을 넣어준다.
					if(min_time[train[j][l][1]][0] > train[j][l][0])
						min_time[train[j][l][1]][0] = train[j][l][0];
				}
			}
		}
	}

	// 시작이 끝과 같으면 끄내기
	if(check[end] == 0)
		return;

// 끝에서 시작까지의 시간을 구한다 (반대로 접근)
	// 위에 사용한 코드와 같은 설명이기에 설명 생략

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
