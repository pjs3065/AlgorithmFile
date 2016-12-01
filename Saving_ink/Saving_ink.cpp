//2016.10.8 made in ParkJaeseong(Kruscal's algorithm)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct coordinate
{
	float x; // x축
	float y; // y축
}coordiate;

coordinate *coor;

int i,j;
int u,v; // two vertex
int tem_u, tem_v; // 임시로 저장할 vertex
int vertex_number; // vertex의 수
int edge_number = 1; // ege의 수

float min_weight; // 최소값 weight
float total_weight=0; // 최소값들의 합 cost
float weight[31][31]; // weight들을 테이블로 저장 
float set_order[31]; // set을 합치기 위해서 set의 order을 저장함

int set_find(int); // set이 있는지 찾음
int union_set(int,int); // 두 set이 같지 않거나, 합칠 수 있으면 set을 둘이 합친다.
float GetDistance(float x1, float y1, float x2, float y2); // 두 좌표의 거리를 구한다.

void main()
{
	// 좌표의 수를 적는다.
	printf("\n-----Kruskal's algorithm-----\n");
	printf("\n Enter the number of vertices : ");
	scanf("%d",&vertex_number);

	if(vertex_number < 0 || vertex_number >30)
		exit(0);
	
	// 좌표 갯수만큼 동적할당
	coor = (coordinate*)malloc(sizeof(coordinate)*(vertex_number+1));

	// 좌표 입력하기
	for(i = 1; i <= vertex_number; i++)
	{
		printf("%dth (x, y) = ",i);
		scanf("%f %f", &(coor + i)->x, &(coor + i)->y);
	}

	// distance weight table 만들기
	for(i = 1; i <= vertex_number; i++)
	{
		set_order[i] = 0;
		for(j = 1; j <= vertex_number; j++)
		{
			weight[i][j] = GetDistance((coor+i)->x,(coor+i)->y,(coor+j)->x,(coor+j)->y); 
			//weight이 0일 경우 999로 초기화 시켜준다.
			if(weight[i][j] == 0)
				weight[i][j] = 999;
		}
	}

	// distance weight table 보여주기
	printf("\n\t<The distance weight matrix>\n\n\t");
	
	for(i = 1; i <= vertex_number; i++)
	{
		printf("%d\t",i);
	}

	for(i = 1; i <= vertex_number; i++)
	{
		printf("\n%d\t",i);
		for(j = 1; j <= vertex_number; j++)
		{
			printf("%.2f\t",weight[i][j]);
		}
	}
	printf("\n");

	// set비교 분석
	printf("\nThe edges of min_weight cost Spanning Tree are\n");
	while(edge_number < vertex_number)
	{
		min_weight = 999;
		for(i = 1; i<= vertex_number; i++)
		{
			for(j = 1;j <= vertex_number; j++)
			{
				if(weight[i][j] < min_weight)
				{
					//최소 weight과 좌표를 저장 (임시값도 저장을 해놓은다)
					min_weight = weight[i][j];
					
					u = i;
					tem_u = i;
					
					v = j;
					tem_v = j;
				}
			}
		}

		// set에서 현재 존재하고 있는지 확인을 한다.
		u=set_find(u);
		v=set_find(v);

		// 확인후 union이 가능한지 확인
		if(union_set(u,v))
		{
			printf("%d edge (%d,%d) =%.2f\n",edge_number++,tem_u,tem_v,min_weight);
			total_weight += min_weight;
		}
		//사용한 값은 weight 테이블내에서 999로 없애준다.
		weight[tem_u][tem_v]=weight[tem_v][tem_u] = 999;
	}
	printf("\n\ minimum weight cost = %.2f\n",total_weight);
}
/* set에서 선의 연결 고리를 찾아냄 */
int set_find(int i)
{
	while(set_order[i])
		i = set_order[i];
	return i;
}

/* 이 set이 다른 set과 합칠 수 있는지 여부를 판단후 합친다 */
int union_set(int i, int j)
{
	if(i != j)
	{
		set_order[j] = i;
		return 1;
	}
	return 0;
}

/* 두 좌표간의 weight을 구하기 위한 함수 */
float GetDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2-x1)*(x2-x1) + (y2-y1) * (y2-y1));
}