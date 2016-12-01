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

	//파이 n의 가장 작은 prime odd number를 구한다. (e)
	//euclide_algorithm 사용

	//e 구하기
	e = 3;
	while (euclide(e,temp_n)!=1)
		e = e + 2;

	//d 구하기
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

	//repeated squaring algorithm 사용
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

	// 2미만의 숫자는 소수가 아니다.
	if (n < 2)
	{
		return -1;
	}

	// 2를 제외한 나머지 숫자는 2로 나누어 떨어지게 되면 짝수이다.
	if (n != 2 && n % 2==0)
	{
		return -1;
	}


	//fermat test 의 (n-1) = 2의 k승 * q의 k와 q를 찾아야한다.

	q = n - 1;
	k = 0;
	
	// k와 q를 찾는다.
	while (q % 2 == 0)
	{
		q = q / 2;
		k = k + 1;
	}

	for (i = 0; i < k; i++)
	{
		//랜덤의 1 에서 n-1까지의 숫자를 선택을 하고
		a = rand() % (n - 1) + 1;
		temp = q;

		//overflow 방지를 위해서 repeated_squaring을 사용
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
