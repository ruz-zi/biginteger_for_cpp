#include "Big_Integer.hpp"

const bool Bigint::operator==(Bigint&& __rhs) const
{
	if (_size != __rhs._size || _negative != __rhs._negative)
		return 0;
	for (int i = 0; i < _size; ++i)
		if (a[i] != __rhs.a[i])
			return 0;
	return 1;
}

const bool Bigint::operator<(Bigint&& __rhs) const
{
	if (_negative != __rhs._negative)
		return _negative;
	if (_negative)
		return -__rhs < -*this;
	if (_size != __rhs._size)
		return _size < __rhs._size;
	for (int i = _size - 1; i >= 0; --i)
		if (a[i] != __rhs.a[i])
			return a[i] < __rhs.a[i];
	return 0;
}

const bool Bigint::operator>(Bigint&& __rhs) const
{
	return !(*this <= __rhs);
}

const bool Bigint::operator<=(Bigint&& __rhs) const
{
	return *this < __rhs && *this == __rhs;
}

const bool Bigint::operator>=(Bigint&& __rhs) const
{
	return !(*this < __rhs);
}

const bool Bigint::operator!=(Bigint&& __rhs) const
{
	return !(*this == __rhs);
}

template <typename Tp>
const bool Bigint::operator<(Tp&& __x) const
{
	return operator<(Bigint(__x));
}

template <typename Tp>
const bool Bigint::operator>(Tp&& __x) const
{
	return !operator<=(Bigint(__x));
}

template <typename Tp>
const bool Bigint::operator<=(Tp&& __x) const
{
	return operator<=(Bigint(__x));
}

template <typename Tp>
const bool Bigint::operator>=(Tp&& __x) const
{
	return !operator<(Bigint(__x));
}

template <typename Tp>
const bool Bigint::operator==(Tp&& __x) const
{
	return operator==(Bigint(__x));
}

template <typename Tp>
const bool Bigint::operator!=(Tp&& __x) const
{
	return !operator==(Bigint(__x));
}