#include<stdio.h>
#include<math.h>
#include<float.h>
 
// x��� y���� ��Ÿ�� point����ü
typedef struct POINT
{
    int x;
    int y;
}POINT;
 
// �� ������ ���ִ� total ���� (��������)

double total = 0.0;

// �Լ�
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
        
		//n�� 1���� 10����
		if(n == 0 || n > 10)
            break;
 
		//k�� 1���� 10����
        if(k == 0 || k > n)
            break;
 
		//���� 1 x 1�̸� �Ѱ��� ���
        if(n == 1)
        {
            printf("1\n");
            continue;
        }
 
		//k�� 1�̸� n x n ��ŭ���� �� ����
        if(k == 1)
        {
            printf("%d\n",n*n);
            continue;
        }
 
		//n x n ��ŭ Ȯ��
        for(i = 0; i < n * n; i++)
        {
            b_position[0] = i;
			//��Ʈ���� ����
            BackTracking(b_position, 0, n, k);
        }

		//output
		printf("%.0lf\n",total);
		total = 0;
    }
}

// Ÿ�Ͽ��� �迭���������� �ش� ��ǥ�� ����Ѵ� 
POINT Getposition(int arr[], int n)
{
    POINT temp;
    temp.x = (arr[0] % n) + 1;
    temp.y = (arr[0] / n) + 1;
 
    return temp;
}
 
// �� ��ǥ���� ���⸦ ����Ѵ�
float Getgradient(int x1, int y1, int x2, int y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    return dx / dy;
}
 
// �� ��ǥ���� �밢���� ��ġ�ϴ��� Ȯ���Ѵ�s
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
 
// ��Ʈ��ŷ �˰��� - Ǯ��Ȯ�� �Լ�
int IsSolution(int b_position[], int dep, int n, int k)
{
	int i,j;
	POINT l;
	POINT r;

    // ������ ���̱��� ���� �ʾ����� ������ 0�̴�.
    if(dep != k - 1)
        return 0;
 
    // ���� ������ �� ����� ��ġ�� �밢���� ��ġ�ϸ� 0�̴�.
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
 
// ��Ʈ��ŷ �˰��� - �ĺ��� �����Լ�
void MakeCandidate(int b_position[], int dep, int n,  int k, int candidate[], int *candidateCnt)
{
	int targetPos[100] = {0,};
	int i, j;
	int alreadyPos;

    // ���̰��� ����� �������� ũ�� Ȯ���� �� ����
    if(dep > k - 1)
        return;
 
    // ���� ���� ������ ����� ������ ��ġ�� Ȯ���Ѵ�
    
    for(i = 0; i < dep; i++)
    {
        alreadyPos = b_position[i];
        targetPos[alreadyPos] = 1;
    }
 
    for(i = 0; i < n * n; i++)
    {
        // �������� �ʾҰ�...
        if(targetPos[i] == 1)
            continue;
 
        // ������ ���� ��� �̻��� �������...
        // -- ��� ������ �߰��ϸ� �ߺ��� ���°� ���´�(����� �ѹ������� �ʴ´�)
        if(i > b_position[dep - 1])
            continue;
 
        // �ĺ������� �߰��Ѵ�
        candidate[(*candidateCnt)++] = i;
    }
 
}
 
// ��Ʈ��ŷ �˰���
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
 
    // ���� Ȯ��, �ĺ��� Ž��
    dep++;
    MakeCandidate(b_position, dep, n, k, candidate, &candidateCnt);
 
    // Ž���� �ĺ�����ŭ ����
    for(i = 0; i < candidateCnt; i++)
    {
        b_position[dep] = candidate[i];
        BackTracking(b_position, dep, n, k);
    }
}
