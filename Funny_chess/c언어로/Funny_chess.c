#include<stdio.h>
#include<math.h>
#include<float.h>
 
// x축과 y축을 나타낼 point구조체
typedef struct POINT
{
    int x;
    int y;
}POINT;
 
// 총 갯수를 새주는 total 변수 (전역변수)

double total = 0.0;

// 함수
void BackTracking(int b_position[], int dep, int n, int k);
int IsSolution(int b_position[], int dep, int n, int k);
void MakeCandidate(int b_position[], int dep, int n, int k, int candidate[], int *candidateCnt);

int IsDiagonal(int x1, int y1, int x2, int y2); 
POINT Getposition(int arr[], int n);
float Getgradient(int x1, int y1, int x2, int y2);

void main()
{
	int n, k;
	int i;
	int b_position[10];

    while(1)
    {
		//input
       
		//initiailize
		for(i= 0; i<10; i++)
			b_position[i] = 0;

        scanf_s("%d %d", &n, &k);
        
		//n은 1부터 10까지
		if(n == 0 || n > 10)
            break;
 
		//k는 1부터 10까지
        if(k == 0 || k > n)
            break;
 
		//판이 1 x 1이면 한개가 출력
        if(n == 1)
        {
            printf("1\n");
            continue;
        }
 
		//k가 1이면 n x n 만큼놓을 수 있음
        if(k == 1)
        {
            printf("%d\n",n*n);
            continue;
        }
 
		//n x n 만큼 확인
        for(i = 0; i < n * n; i++)
        {
            b_position[0] = i;
			//백트레싱 실행
            BackTracking(b_position, 0, n, k);
        }

		//output
		printf("%.0lf\n",total);
		total = 0;
    }
}

// 타일에서 배열순번값으로 해당 좌표를 계산한다 
POINT Getposition(int arr[], int n)
{
    POINT temp;
    temp.x = (arr[0] % n) + 1;
    temp.y = (arr[0] / n) + 1;
 
    return temp;
}
 
// 두 좌표점의 기울기를 계산한다
float Getgradient(int x1, int y1, int x2, int y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    return dx / dy;
}
 
// 두 좌표점이 대각선에 위치하는지 확인한다s
int IsDiagonal(int x1, int y1, int x2, int y2)
{
	float gradient;

    if(x1 == x2 || y1 == y2)
        return 0;
 
    gradient = Getgradient(x1, y1, x2, y2);

    if(gradient < 0)
        gradient *= -1;
    
    if(gradient < 1 - FLT_EPSILON || 1 + FLT_EPSILON < gradient)
        return 0;
 
    return 1;
}
 
// 백트래킹 알고리즘 - 풀이확인 함수
int IsSolution(int b_position[], int dep, int n, int k)
{
	int i,j;
	POINT l;
	POINT r;

    // 마지막 깊이까지 오지 않았으면 무조건 0이다.
    if(dep != k - 1)
        return 0;
 
    // 현재 설정된 각 비숍의 위치가 대각선에 위치하면 0이다.
    for(i = 0; i < k; i++)
    {
       l = Getposition(&b_position[i], n);
 
        for(j = 0; j < k; j++)
        {
            if(i == j)
                continue;
 
            r = Getposition(&b_position[j], n);

            if(IsDiagonal(l.x, l.y, r.x, r.y))
                return 0;
        }
    }
    
    return 1;
}
 
// 백트래킹 알고리즘 - 후보자 구축함수
void MakeCandidate(int b_position[], int dep, int n,  int k, int candidate[], int *candidateCnt)
{
	int targetPos[100] = {0,};
	int i, j;
	int alreadyPos;

    // 깊이값이 비숍의 개수보다 크면 확장할 수 없다
    if(dep > k - 1)
        return;
 
    // 현재 깊이 이전의 비숍이 놓아진 위치를 확인한다
    
    for(i = 0; i < dep; i++)
    {
        alreadyPos = b_position[i];
        targetPos[alreadyPos] = 1;
    }
 
    for(i = 0; i < n * n; i++)
    {
        // 놓아지지 않았고...
        if(targetPos[i] == 1)
            continue;
 
        // 마지막 놓은 비숍 이상의 순서라면...
        // -- 모든 순열을 추가하면 중복된 형태가 나온다(비숍을 넘버링하지 않는다)
        if(i > b_position[dep - 1])
            continue;
 
        // 후보군으로 추가한다
        candidate[(*candidateCnt)++] = i;
    }
 
}
 
// 백트래킹 알고리즘
void BackTracking(int b_position[], int dep,int n, int k)
{
	int candidate[100] = {0,};
    int candidateCnt = 0;
	int i;

    if(IsSolution(b_position, dep, n, k))
    {
        total++;
        return;
    }
 
    // 깊이 확장, 후보군 탐색
    dep++;
    MakeCandidate(b_position, dep, n, k, candidate, &candidateCnt);
 
    // 탐색한 후보군만큼 추적
    for(i = 0; i < candidateCnt; i++)
    {
        b_position[dep] = candidate[i];
        BackTracking(b_position, dep, n, k);
    }
}
