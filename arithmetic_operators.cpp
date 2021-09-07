#include "Big_Integer.hpp"

static void _add(value_t *__a, value_t *__b, size_t __n)
{
	while (__n-- > 0)
		*__a++ += *__b++;
}
static void _sub(value_t *__a, value_t *__b, size_t __n)
{
	while (__n-- > 0)
		*__a++ -= *__b++;
}

Bigint Bigint::operator-() const
{
	Bigint _res;
	_res._assign(*this);
	_res._negative ^= 1;
	return _res;
}

Bigint& Bigint::operator+=(__int128_t __x)
{
	if (_negative == (__x < 0))
		*_data += _negative ? -__x : __x;
	else
	{
		if (__x < 0)
			__x = -__x;
		if (_size > 1 || *_data > __x)
			*_data -= __x;
		else
		{
			*_data = __x - *_data;
			_negative ^= 1;
		}
	}
	_normalize();
	return *this;
}

Bigint& Bigint::operator-=(__int128_t __x)
{
	return *this;
}
Bigint& Bigint::operator*=(__int128_t __x)
{
	return *this;
}
Bigint& Bigint::operator/=(__int128_t __x)
{
	return *this;
}
Bigint& Bigint::operator%=(__int128_t __x)
{
	return *this;
}
Bigint& Bigint::operator&=(__int128_t __x)
{
	return *this;	
}
Bigint& Bigint::operator|=(__int128_t __x)
{
	return *this;
}
Bigint& Bigint::operator^=(__int128_t __x)
{
	return *this;
}
Bigint& Bigint::operator+=(const Bigint& __x)
{
	if (_negative == __x._negative)
		_add(_data, __x._data, std::min(_size, __x._size));
	else if (_comp_abs(__x) > 0)
		_sub(_data, __x._data, std::min(_size, __x._size));
	else
		_assign(Bigint(__x) += *this);
	_normalize();
	return *this;
}
Bigint& Bigint::operator-=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator*=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator/=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator&=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator|=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator^=(const Bigint& __x)
{
	return *this;
}

Bigint Bigint::operator+(const Bigint& __rhs) const
{
	return Bigint(*this) += __rhs;
}
Bigint Bigint::operator-(const Bigint& __rhs) const
{
	return Bigint(*this) -= __rhs;
}
Bigint Bigint::operator*(const Bigint& __rhs) const
{
	return Bigint(*this) *= __rhs;
}
Bigint Bigint::operator/(const Bigint& __rhs) const
{
	return Bigint(*this) /= __rhs;
}
Bigint Bigint::operator%(const Bigint& __rhs) const
{
	return Bigint(*this) /= __rhs;
}
Bigint Bigint::operator&(const Bigint& __rhs) const
{
	return Bigint(*this) &= __rhs;
}
Bigint Bigint::operator|(const Bigint& __rhs) const
{
	return Bigint(*this) |= __rhs;
}
Bigint Bigint::operator^(const Bigint& __rhs) const
{
	return Bigint(*this) ^= __rhs;
}