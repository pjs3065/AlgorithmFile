//Made in 201232342 Jaeseong Park (16/09/22) AM 12 : 33 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	char sequence[10000]={0,}; // 원래 문장
	char sub_sequence[100] = {0,}; // 찾을 부분집합

	int **LCS; // LCS
	int row, row_length;
	int col, col_length;	

	printf("Sequence : ");
	scanf("%s",sequence);

	printf("sub_sequence : ");
	scanf("%s",sub_sequence);

	row_length = strlen(sequence);
	col_length = strlen(sub_sequence);

	//LCS 테이블 생성(row가 10000보다 클 수 없다)
	LCS =(int**)malloc(sizeof(int*)*row_length);
	for(row = 0; row<row_length; row++)
	{
		LCS[row] = (int*)malloc(sizeof(int)*col_length);
	}

	// 첫번째 단어 비교를 해서 초기화 선언을 해준다.
	if(sequence[0] == sub_sequence[0])
		LCS[0][0] = 1;
	else
		LCS[0][0] = 0;

	// 첫번째 컬럼의 첫번재 줄부터 마지막 줄까지 비교해서 값을 넣어준다.
	for(row = 1; row < row_length; row++) 
	{
		LCS[row][0] = LCS[row - 1][0]; // 위에 있는 값이 그대로 내려옴
		if(sequence[row] == sub_sequence[0]) // 근데 만약에 sub_sequence에 입력했던 맨 첫 글자와 현재 줄의 첫번째 글짜가 같다면 
		{
			LCS[row][0]++; // 1씩 더해준다.
		}
	}

	// 두번째 컬럼부터 마지막 컬럼까지의 첫번째 줄부터 마지막 줄까지 비교해서 같으면 위의 값과 대각선의 값을 더한다.
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
	//최종값 출력
	printf("The number of sub_sequences : %d\n",LCS[row_length - 1][col_length - 1]);
}