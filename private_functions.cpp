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
	_sign = 0;
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
			carry = -((-*_ptr + BASE - 1) / BASE);
			*_ptr = (*_ptr % BASE + BASE) % BASE;
		}
		else if (!(*_ptr < BASE))
		{
			carry = *_ptr / BASE;
			*_ptr = *_ptr % BASE;
		}
		else carry = 0;
	} while (carry != 0 && ++_ptr != _data + _size);
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
		_sign = 1;
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
	value_t _tmp = 0;
	size_t _n = 0, _i, _j;
	
	_sign = *__s == '+' || *__s == '-' ? *__s++ == '-' : 0;
	while (__s[_n]) _n++;
	
	if (_data) delete[] _data;
	_data = new value_t[_capa = _n / BASE_K + 1];
	
	_size = 0;
	for (_i = _n; _i >= BASE_K; _i -= BASE_K)
	{
		for (_j = _i - BASE_K; _j < _i; ++_j)
			_tmp = _tmp * 10 + (__s[_j] & 15);
		_data[_size++] = _tmp;
		_tmp = 0;
	}
	for (_j = 0; _j < _i; ++_j)
		_tmp = _tmp * 10 + (__s[_j] & 15);
	_data[_size++] = _tmp;
	_normalize();
}

void Bigint::_assign(const Bigint& __x)
{
	_size = __x._size;
	_capa = __x._capa;
	_sign = __x._sign;
	
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