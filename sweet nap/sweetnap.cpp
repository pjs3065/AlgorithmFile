#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct time
{
	int start_h; // 시작 시간
	int start_m; // 시작 분

	int end_h; // 끝 시간
	int end_m; // 끝 분

	char schedule[255]; // 스케쥴 내용
}Time;

Time *sch; // 스케쥴 받아줄 포인터

typedef struct nap
{
	int nstart_h; //낮잠 시작시간
	int nstart_m; // 낮잠 시작 분
	int nap_time; // 낮잠 총 시간
}Nap;

Nap *s_nap;

void input(int size);
void time_token(char* s_time, char* e_time, int i);
int check(int size);
void sort(int size);
void swap(int j);
void naptime(int size);
void print();

/*
<description : main>
purpose : Type number of your schedules(0~99), then Write a program to help your longest nap with the task.  
input : None
output : None
*/
void main(void)
{
	int size;

	printf("<Input the number of the schedules(0~99)> \n");           //input 갯수 입력
	scanf("%d",&size);

	if(size>=100)
	{
		printf("Number Error\n");
		exit(0);
	}

	sch = (Time*)malloc(sizeof(Time) * size); // 갯수 만큼 스케쥴 동적할당
	s_nap = (Nap*)malloc(sizeof(Nap)); // Nap 동적할당

	input(size); //스케줄과 시간을 입력 받는 함수

	if(check(size) == -1)
	{
		printf("Input Error\n");
		exit(0);
	}

	sort(size);
	naptime(size);
	print();

	free(sch);
	free(s_nap);
}


/*
<description : input>
purpose : Input your schedules, (:) separate your input schedule times and store integer about start time and end time into Time structure.  
input : The number of your schedule.
output : None
*/
void input(int size)
{
	int i;

	char s_time[6]; // "10:00"
	char e_time[6]; // "11:00"
	char schedule[255]; // "play computer game"

	printf("<%d schedules>\n",size);

	for(i = 0; i<size; i++)  // 갯수 만큼 시간과 스케줄 입력 받기 및 structure input
	{
		scanf("%s",s_time);
		scanf("%s",e_time);
		time_token(s_time, e_time, i);
		gets((sch+i)->schedule);

		//printf("%d %d %s",(sch+i)->start_h, (sch+i)->start_m, (sch+i)->schecule);
	}
}

/*
<description : time_token>
purpose : (:) Separate your input schedule times and store integer about start time and end time into Time structure.  
input : Start time and end time about your schedule , schedule order.
output : None
*/
void time_token(char *s_time, char *e_time, int i)
{
	char* token; // : token time

	token = strtok(s_time,":");   
	(sch+i)->start_h = atoi(token); // start h -> 11
	token = strtok(NULL,":");
	(sch+i)->start_m = atoi(token); // start m -> 0

	token = strtok(e_time,":");   
	(sch+i)->end_h = atoi(token); // end h -> 12
	token = strtok(NULL,":");
	(sch+i)->end_m = atoi(token); // end m -> 0
}

/*
<description : check>
purpose : Constraints about input time.(10:00 ~ 18:00)   
input : The number of your schedule
output : If all condition is incorrect than return -1 , else retur 0.
*/
int check(int size)
{
	int i;
	int count;

	for(i = 0; i<size; i++)
	{
		count = 0;
		// 10:00 ~ 18:00 제한
		if((sch+i)->start_h >= 10 && (sch+i)->start_h <= 18 && (sch+i)->start_m >= 0 && (sch+i)->start_m < 60 &&
			(sch+i)->end_h >= 10 && (sch+i)->end_h <= 18 && (sch+i)->end_m >= 0 && (sch+i)->end_m < 60)
			count++;
		{			// 같은 시간 방지
			if((sch+i)->start_h != (sch+i)->end_h || (sch+i)->start_m != (sch+i)->end_m)
				count++;
			{			// 시작시간이 끝시간 보다 크는 상황 방지
				if((sch+i)->start_h < (sch+i)->end_h)
					count++;

				else if((sch+i)->start_h == (sch+i)->end_h)
				{
					if((sch+i)->start_m < (sch+i)->end_m)
						count++;
				}
			}
		}
		if(count != 3)
			return -1;
	}
	return 0;
}

/*
<description : sort>
purpose : Schedule times are arranged in ascending order.   
input : The number of your schedule.
output : None.
*/
void sort(int size)
{
	Time sort;
	int i,j;

	for(i = 0 ; i<size; i++)
	{
		for(j = 0 ; j<size-1; j++)
		{
			if((sch+j)->start_h > (sch+j+1)->start_h) // 시간 기준 정렬
				swap(j);

			else if((sch+j)->start_h == (sch+j+1)->start_h) // 시간이 같을 경우 분을 정렬
			{
				if((sch+j)->start_m > (sch+j+1)->start_m)
					swap(j);
			}
		}
	}
}

/*
<description : swap>
purpose : Schedule times are swapped in ascending order.
input : Schedule order
output : None.
*/
void swap(int j)
{
	Time sort;

	sort = *(sch+j);
	*(sch+j) = *(sch+j+1);
	*(sch+j+1) = sort;
}

/*
<description : naptime>
purpose : Find longest nap time. front time(10:00 ~ firtst schedule time) behind time(last schdeult time ~ 18:00)
input : Schedule order.
output : none.
*/
void naptime(int size)
{
	int i;

	int total1;
	int total2;

	int front;
	int behind;

	
	// schedule이 없을 경우
	if(size == 0)
	{
		s_nap->nstart_h = 10;
		s_nap->nstart_m = 0;
		s_nap->nap_time = 480;
	}

	else
	{
		front = ((sch->start_h) * 60 + (sch->start_m)) - 600;
		behind = 1080 - (((sch+size-1)->end_h * 60) + (sch+size-1)->end_m);

		// 10:00와 첫시간 최대값 초기화 할당
		s_nap->nstart_h = 10;
		s_nap->nstart_m = 0;
		s_nap->nap_time = front;


		// 스케쥴 사이 시간 구해서 최대값 찾아서 비교 후 할당

		for(i = 0; i<size-1; i++)
		{
			total1 = ((sch+i+1)->start_h * 60) + (sch+i+1)->start_m;
			total2 = ((sch+i)->end_h * 60) + (sch+i)->end_m;

			if((total1 - total2) > s_nap->nap_time)
			{
				s_nap->nstart_h = (sch+i)->end_h;
				s_nap->nstart_m = (sch+i)->end_m;
				s_nap->nap_time = total1 - total2;
			}
		}

		// 18:00와 비교 낮잠시간이 같을 경우 먼저 나온게 우선
		if(s_nap->nap_time < behind)
		{
			s_nap->nstart_h = (sch+size-1)->end_h;
			s_nap->nstart_m = (sch+size-1)->end_m;
			s_nap->nap_time = behind;
		}
	}
}

/*
<description : print>
purpose : Print the longest nap starts and last and total time about you be albe to take a nap 
input : Schedule order.
output : none.
*/
void print()
{
	int hours;
	int minutes;

	hours = s_nap->nap_time / 60;
	minutes = s_nap->nap_time % 60;

	printf("Day #1: the longest nap starts at %d:",s_nap->nstart_h);

	if(s_nap->nstart_m <10)
		printf("0%d and will last for ",s_nap->nstart_m);
	else
		printf("%d and will last for ",s_nap->nstart_m);

	if(hours > 0)
		printf("%d hours and %d minutes\n",hours,minutes);
	else
		printf("%d minutes\n",minutes);
}