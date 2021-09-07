#include "Big_Integer.hpp"

static void _copy_n(value_t *__dst, value_t *__src, size_t __n)
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
	value_t carry = 0;
	register value_t *_ptr = _data;
	do {
		*_ptr += carry;
		if (*_ptr < 0)
		{
			carry = -(-*_ptr + BASE_M >> BASE_K);
			*_ptr = (*_ptr & BASE_M) + BASE & BASE_M;
		}
		else if (!(*_ptr < BASE))
		{
			carry = *_ptr >> BASE_K;
			*_ptr = *_ptr & BASE_M;
		}
	} while (carry > 0 && ++_ptr != _data + _size);
	
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
	_alloc(2);
	if (*__s == '+' || *__s == '-')
		_negative = *__s++ == '-';
	while (*__s)
	{
		*this *= 10;
		*this += *__s++ & 15;
	}
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

int Bigint::_comp_abs(const Bigint& __x) const
{
	if (_size != __x._size) return (int)_size - (int)__x._size;
	size_t _i = _size;
	while (_i-- > 0)
		if (*(_data + _i) != *(__x._data + _i))
			return *(_data + _i) - *(__x._data + _i);
	return 0;
}