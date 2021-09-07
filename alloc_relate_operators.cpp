#include "Big_Integer.hpp"

Bigint& Bigint::operator=(__int128_t __x)
{
	_assign(__x);
	return *this;
}

Bigint& Bigint::operator=(const char *__s)
{
	_assign(__s);
	return *this;
}

Bigint& Bigint::operator=(const std::string& __s)
{
	_assign(__s.c_str());
	return *this;
}

Bigint& Bigint::operator=(const Bigint& __x)
{

	return *this;
}

bool Bigint::operator==(const Bigint& __rhs) const
{
	if (_size != __rhs._size || _negative != __rhs._negative)
		return 0;
	for (int i = 0; i < _size; ++i)
		if (_data[i] != __rhs._data[i])
			return 0;
	return 1;
}

bool Bigint::operator<(const Bigint& __rhs) const
{
	if (_negative != __rhs._negative)
		return _negative;
	if (_negative)
		return -__rhs < -*this;
	if (_size != __rhs._size)
		return _size < __rhs._size;
	for (int i = _size - 1; i >= 0; --i)
		if (_data[i] != __rhs._data[i])
			return _data[i] < __rhs._data[i];
	return 0;
}