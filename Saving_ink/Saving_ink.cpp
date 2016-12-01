//2016.10.8 made in ParkJaeseong(Kruscal's algorithm)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct coordinate
{
	float x; // x��
	float y; // y��
}coordiate;

coordinate *coor;

int i,j;
int u,v; // two vertex
int tem_u, tem_v; // �ӽ÷� ������ vertex
int vertex_number; // vertex�� ��
int edge_number = 1; // ege�� ��

float min_weight; // �ּҰ� weight
float total_weight=0; // �ּҰ����� �� cost
float weight[31][31]; // weight���� ���̺�� ���� 
float set_order[31]; // set�� ��ġ�� ���ؼ� set�� order�� ������

int set_find(int); // set�� �ִ��� ã��
int union_set(int,int); // �� set�� ���� �ʰų�, ��ĥ �� ������ set�� ���� ��ģ��.
float GetDistance(float x1, float y1, float x2, float y2); // �� ��ǥ�� �Ÿ��� ���Ѵ�.

void main()
{
	// ��ǥ�� ���� ���´�.
	printf("\n-----Kruskal's algorithm-----\n");
	printf("\n Enter the number of vertices : ");
	scanf("%d",&vertex_number);

	if(vertex_number < 0 || vertex_number >30)
		exit(0);
	
	// ��ǥ ������ŭ �����Ҵ�
	coor = (coordinate*)malloc(sizeof(coordinate)*(vertex_number+1));

	// ��ǥ �Է��ϱ�
	for(i = 1; i <= vertex_number; i++)
	{
		printf("%dth (x, y) = ",i);
		scanf("%f %f", &(coor + i)->x, &(coor + i)->y);
	}

	// distance weight table �����
	for(i = 1; i <= vertex_number; i++)
	{
		set_order[i] = 0;
		for(j = 1; j <= vertex_number; j++)
		{
			weight[i][j] = GetDistance((coor+i)->x,(coor+i)->y,(coor+j)->x,(coor+j)->y); 
			//weight�� 0�� ��� 999�� �ʱ�ȭ �����ش�.
			if(weight[i][j] == 0)
				weight[i][j] = 999;
		}
	}

	// distance weight table �����ֱ�
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

	// set�� �м�
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
					//�ּ� weight�� ��ǥ�� ���� (�ӽð��� ������ �س�����)
					min_weight = weight[i][j];
					
					u = i;
					tem_u = i;
					
					v = j;
					tem_v = j;
				}
			}
		}

		// set���� ���� �����ϰ� �ִ��� Ȯ���� �Ѵ�.
		u=set_find(u);
		v=set_find(v);

		// Ȯ���� union�� �������� Ȯ��
		if(union_set(u,v))
		{
			printf("%d edge (%d,%d) =%.2f\n",edge_number++,tem_u,tem_v,min_weight);
			total_weight += min_weight;
		}
		//����� ���� weight ���̺����� 999�� �����ش�.
		weight[tem_u][tem_v]=weight[tem_v][tem_u] = 999;
	}
	printf("\n\ minimum weight cost = %.2f\n",total_weight);
}
/* set���� ���� ���� ���� ã�Ƴ� */
int set_find(int i)
{
	while(set_order[i])
		i = set_order[i];
	return i;
}

/* �� set�� �ٸ� set�� ��ĥ �� �ִ��� ���θ� �Ǵ��� ��ģ�� */
int union_set(int i, int j)
{
	if(i != j)
	{
		set_order[j] = i;
		return 1;
	}
	return 0;
}

/* �� ��ǥ���� weight�� ���ϱ� ���� �Լ� */
float GetDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2-x1)*(x2-x1) + (y2-y1) * (y2-y1));
}