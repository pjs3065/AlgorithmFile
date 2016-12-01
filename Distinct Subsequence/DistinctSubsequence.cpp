//Made in 201232342 Jaeseong Park (16/09/22) AM 12 : 33 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	char sequence[10000]={0,}; // ���� ����
	char sub_sequence[100] = {0,}; // ã�� �κ�����

	int **LCS; // LCS
	int row, row_length;
	int col, col_length;	

	printf("Sequence : ");
	scanf("%s",sequence);

	printf("sub_sequence : ");
	scanf("%s",sub_sequence);

	row_length = strlen(sequence);
	col_length = strlen(sub_sequence);

	//LCS ���̺� ����(row�� 10000���� Ŭ �� ����)
	LCS =(int**)malloc(sizeof(int*)*row_length);
	for(row = 0; row<row_length; row++)
	{
		LCS[row] = (int*)malloc(sizeof(int)*col_length);
	}

	// ù��° �ܾ� �񱳸� �ؼ� �ʱ�ȭ ������ ���ش�.
	if(sequence[0] == sub_sequence[0])
		LCS[0][0] = 1;
	else
		LCS[0][0] = 0;

	// ù��° �÷��� ù���� �ٺ��� ������ �ٱ��� ���ؼ� ���� �־��ش�.
	for(row = 1; row < row_length; row++) 
	{
		LCS[row][0] = LCS[row - 1][0]; // ���� �ִ� ���� �״�� ������
		if(sequence[row] == sub_sequence[0]) // �ٵ� ���࿡ sub_sequence�� �Է��ߴ� �� ù ���ڿ� ���� ���� ù��° ��¥�� ���ٸ� 
		{
			LCS[row][0]++; // 1�� �����ش�.
		}
	}

	// �ι�° �÷����� ������ �÷������� ù��° �ٺ��� ������ �ٱ��� ���ؼ� ������ ���� ���� �밢���� ���� ���Ѵ�.
	for(col = 1; col < col_length; col++)
	{
		LCS[col - 1][col] = 0;
		for(row = col; row < row_length; row++)
		{
			LCS[row][col] = LCS[row - 1][col];
			if(sequence[row] == sub_sequence[col])
			{
				LCS[row][col] = LCS[row][col] + LCS[row - 1][col - 1];
			}
		}
	}
	//������ ���
	printf("The number of sub_sequences : %d\n",LCS[row_length - 1][col_length - 1]);
}