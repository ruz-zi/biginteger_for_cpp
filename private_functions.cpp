#include "Big_Integer.hpp"

void Bigint::_copy_n(value_t *__dst, value_t *__src, size_t __n)
{
	while (__n-- > 0)
		*__dst++ = *__src++;
}

void Bigint::_alloc(size_t __n)
{
	if (_data) delete[] _data;
	_data = new value_t[_capa = __n];
	_size = 1;
	_negative = 0;
}

void Bigint::_realloc(size_t __n)
{
	auto _old = _data;
	_data = new value_t[_capa = __n];
	_copy_n(_data, _old, _size);
	delete[] _old;
}

void Bigint::_normalize()
{
	register size_t i;
	value_t carry = 0;
	for (i = 0; i < _size; ++i)
	{
		_data[i] += carry;
		if ((carry = _data[i] >> BASE_K) > 0)
			_data[i] &= BASE - 1;
	}
	if (carry > 0)
	{
		if (_size == _capa)
			_realloc(_capa << 1);
		_data[_size++] = carry;
	}
	while (_size > 1 && !_data[_size - 1])
		if (--_size == _capa >> 2)
			_realloc(_capa >> 1);
}

void Bigint::_assign(__int128_t __x)
{
	_alloc(2);
	if (__x < 0)
	{
		_negative = 1;
		*_data = 1ULL + ~__x;
	}
	else
	{
		*_data = __x;
	}
	_normalize();
}

void Bigint::_assign(const char *__s)
{
	//
}

void Bigint::_assign(const Bigint& __x)
{
	_size = __x._size;
	_capa = __x._capa;
	_negative = __x._negative;
	
	if (_data) delete[] _data;
	_data = new value_t[_capa];
	
	_copy_n(_data, __x._data, _size);
}