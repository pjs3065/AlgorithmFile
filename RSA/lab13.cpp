//2016.11.13 made in parkjaeseong (RSA algorithm)

#include <stdio.h>
#include <stdlib.h>

int miller(long long n); // miller robin algorithm
long long repeated(long long a, long long b, long long n); //repeated_squaring algorithm
long long mulrepeated(long long a, long long b, long long n); //repeated_squaring algorithm
long long euclide(long long a, long long b); // euclid algorithm

void main()
{
	long long p, q, message;
	long long n, temp_n;
	long long e, d;
	long long cipertext, decrypted;

	int i = 1;

	//input p
	printf("Enter the odd integer P :");
	scanf("%lld", &p);

	//prime check
	if(miller(p) == -1)
	{
		printf("p is not prime number!!\n");
		exit(0);
	}

	//input q
	printf("Enter the odd integer Q :");
	scanf("%lld", &q);

	//prime check
	if(miller(q) == -1)
	{
		printf("q is not prime number!!\n");
		exit(0);
	}

	// input message
	printf("Enter the message: ");
	scanf("%lld", &message);

	n = p * q;
	temp_n = (p-1)*(q-1);

	//���� n�� ���� ���� prime odd number�� ���Ѵ�. (e)
	//euclide_algorithm ���

	//e ���ϱ�
	e = 3;
	while (euclide(e,temp_n)!=1)
		e = e + 2;

	//d ���ϱ�
	while(1)
	{
		if ((temp_n * i + 1) % e == 0)
		{
			d = (temp_n * i + 1) / e;
			break;
		}
		i++;
	}

	//output

	printf("e: %lld\n", e);
	printf("d: %lld\n", d);

	//repeated squaring algorithm ���
	cipertext = repeated(message, e, n);
	printf("cypher text: %lld\n", cipertext);

	decrypted = repeated(cipertext, d, n);
	printf("original Message : %lld\n", decrypted);
}

int miller(long long n)
{
	long long q, temp;
	long long a, mod;
	int i, k;

	// 2�̸��� ���ڴ� �Ҽ��� �ƴϴ�.
	if (n < 2)
	{
		return -1;
	}

	// 2�� ������ ������ ���ڴ� 2�� ������ �������� �Ǹ� ¦���̴�.
	if (n != 2 && n % 2==0)
	{
		return -1;
	}


	//fermat test �� (n-1) = 2�� k�� * q�� k�� q�� ã�ƾ��Ѵ�.

	q = n - 1;
	k = 0;
	
	// k�� q�� ã�´�.
	while (q % 2 == 0)
	{
		q = q / 2;
		k = k + 1;
	}

	for (i = 0; i < k; i++)
	{
		//������ 1 ���� n-1������ ���ڸ� ������ �ϰ�
		a = rand() % (n - 1) + 1;
		temp = q;

		//overflow ������ ���ؼ� repeated_squaring�� ���
		mod = repeated(a, q, n);

		//fermat and miller rabin
		while (temp != n - 1 && mod != 1 && mod != n - 1)
		{
			mod = mulrepeated(mod, mod, n);
			temp *= 2;
		}

		//Carmichael number
		if (mod != n - 1 && temp % 2 == 0)
			return -1;
	}
	return 0;
}

long long repeated(long long a, long long b, long long n)
{
	long long x = 1;
	long long y = a;
	while (b > 0)
	{
		if (b % 2 == 1)
			x = (x * y) % n;
		y = (y * y) % n;
		b = b / 2;
	}
	return x % n;
}

long long mulrepeated(long long a, long long b, long long n)
{
	long long x = 0;
	long long y = a % n;
	while (b > 0)
	{
		if (b % 2 == 1)
		{    
			x = (x + y) % n;
		}
		y = (y * 2) % n;
		b /= 2;
	}
	return x % n;
}

long long euclide(long long a, long long b)
{
	if (a == 0)
		return b;

	else if (b == 0)
		return a;

	else if (a > b)
		return euclide(a % b, b);

	else if (a < b)
		return euclide(a, b % a);
}
