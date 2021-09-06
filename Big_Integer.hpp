// Big_Interger_for_cpp
// author: ruz

// To Do List //
// 1.	동적 unsigned int 배열 이용, 2^k 진법 수로 저장
//		배열의 i번 원소는 2^k^i 항의 계수
//		k는 실험적으로 결정 (FFT 오차)
// 2.	곱 연산 시 제곱 크기인 __uint128_t 변수를 사용
//		곱 연산은 FFT 알고리즘 적용 -> NTT+CRT?
// 3.	음수 처리, 나눗셈 모듈러 연산
// 4.	비트 연산 처리
// 5.	스트림 입출력 오버로딩
// 6.	캐스팅 연산
// 7.	비교 연산
// 8.	기본 자료형과의 호환성

#ifndef BIG_INTEGER
#define BIG_INTEGER

#include <string>
#include <iostream>

using value_t = unsigned long long;

constexpr char		BASE_K	= 30;
constexpr value_t	BASE	= 1 << BASE_K;

class Bigint
{
public:
	Bigint();
	Bigint(long long);
	Bigint(unsigned long long);
	Bigint(const Bigint&);
	Bigint(Bigint&&);
	Bigint(const char *);
	Bigint(const std::string&);
	template <typename Tp> Bigint(const Tp&);
	template <typename Tp> Bigint(Tp&&);
	~Bigint();
	
	const bool operator<(Bigint&&) const;
	const bool operator>(Bigint&&) const;
	const bool operator<=(Bigint&&) const;
	const bool operator>=(Bigint&&) const;
	const bool operator==(Bigint&&) const;
	const bool operator!=(Bigint&&) const;
	template <typename Tp> const bool operator<(Tp&& __x) const;
	template <typename Tp> const bool operator>(Tp&& __x) const;
	template <typename Tp> const bool operator<=(Tp&& __x) const;
	template <typename Tp> const bool operator>=(Tp&& __x) const;
	template <typename Tp> const bool operator==(Tp&& __x) const;
	template <typename Tp> const bool operator!=(Tp&& __x) const;
	
	const Bigint operator=(Bigint&&);
	const Bigint operator-() const {
		Bigint ret = *this;
		ret._negative ^= 1;
		return ret;
	}
	const Bigint operator+(const Bigint&) const
	{
		Bigint result = *this;
		return result;
	}
	
private:
	value_t	*a;
	size_t	_capa;
	size_t	_size;
	bool	_negative;
	
	void copy(value_t *, value_t *, size_t);
	void alloc(size_t);
	void realloc(size_t);
	void normalize();
};

#endif