#include "Big_Integer.hpp"

Bigint::Bigint()
{
	alloc(2);
}

Bigint::Bigint(unsigned long long __x)
{
	alloc(2);
	*a = __x;
	normalize();
}

Bigint::Bigint(long long __x)
{
	alloc(2);
	if (__x < 0)
	{
		_negative = 1;
		*a = 1ULL + ~__x;
	}
	else
	{
		*a = __x;
	}
	normalize();
}

Bigint::Bigint(const Bigint &__x)
{
	_size = __x._size;
	_capa = __x._capa;
	_negative = __x._negative;
	a = new value_t[_capa];
	copy(a, __x.a, _size);
}

Bigint::Bigint(const char *__s)
{
	// 추가 예정
}

Bigint::Bigint(const std::string &__s) : Bigint(__s.c_str()) {}

template <typename Tp>
Bigint::Bigint(const Tp &__x) : Bigint((long long)__x) {}

template <typename Tp>
Bigint::Bigint(Tp &&__x) : Bigint((long long)__x) {}

Bigint::~Bigint() { delete[] a; }