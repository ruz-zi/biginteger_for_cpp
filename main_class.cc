// 동적 unsigned int 배열 이용, 2^31 진법 수로 저장
// 배열의 i번 원소는 2^31^i 항의 계수
// 곱 연산 시 제곱 크기인 long long 변수를 사용
// 곱 연산은 FFT 알고리즘 적용
// 음수 처리, 나눗셈 모듈러 연산
// 비트 연산 처리
// 스트림 입출력 오버로딩
// 캐스팅 연산
// 비교 연산

#ifndef TEST
#define TEST

#include <bits/stdc++.h>
using namespace std;

#endif

class Bigint
{
private:
	const unsigned base = 1 << 31;
	unsigned *a; // a[i] = 2^31^i 계수
	unsigned c;	 // a배열 용량
	unsigned n;	 // a배열 길이
	bool g;		 // 음수 여부 ( 1/0 )

public:
	Bigint()
	{
		c = 4;
		a = new unsigned[c];
		n = 1;
		g = 0;
	}
	Bigint(const Bigint &ref)
	{
		c = ref.c;
		n = ref.g;
		a = new unsigned[c];
		for (int i = 0; i < n; ++i)
			*(a + i) = *(ref.a + i);
		g = ref.g;
	}
	Bigint(int x) : Bigint()
	{
		if (x == 1 << 31)
		{
			g = 1;
			a[1] = 1;
		}
		else
		{
			if (x < 0)
			{
				g = 1;
				x = -x;
			}
			a[0] = x;
		}
	}
	Bigint(long long x) : Bigint()
	{
		if (x == 1LL << 63)
		{
			g = 1;
			a[2] = 1;
		}
		else
		{
			if (x < 0)
			{
				g = 1;
				x = -x;
			}
			a[1] = x >> 31;
			a[0] = x & base - 1;
		}
	}
	Bigint(const std::string &s) : Bigint()
	{
		long long x = 0;
		for (int i = s.size() - 1; i >= 0; --i)
		{
			x = x * 10 + (s[i] & 15);
			if (x >= base)
			{
				a[n++] = x & base - 1;
				x >>= 31;
			}
		}
	};