#include "Big_Integer.hpp"

void Bigint::copy(value_t *__dst, value_t *__src, size_t __n)
{
	while (__n-- > 0)
		*__dst++ = *__src++;
}

void Bigint::alloc(size_t __n)
{
	if (a)
		delete[] a;
	a = new value_t[_capa = __n];
	_size = 1;
	_negative = 0;
}

void Bigint::realloc(size_t __n)
{
	auto _old = a;
	a = new value_t[_capa = __n];
	copy(a, _old, _size);
	delete[] _old;
}

void Bigint::normalize()
{
	register size_t i;
	value_t carry = 0;
	for (i = 0; i < _size; ++i)
	{
		a[i] += carry;
		if ((carry = a[i] >> BASE_K) > 0)
			a[i] &= BASE - 1;
	}
	if (carry > 0)
	{
		if (_size == _capa)
			realloc(_capa << 1);
		a[_size++] = carry;
	}
	while (_size > 1 && !a[_size - 1])
		if (--_size == _capa >> 2)
			realloc(_capa >> 1);
}