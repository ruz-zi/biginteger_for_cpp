#include "Big_Integer.hpp"

using cd = std::complex<double>;
const double PI = std::acos(-1);

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
static void _fft(cd *__a, size_t __n, bool inv) {
	for (int i = 1, j = 0, k; i < __n; ++i) {
		for (k = __n >> 1; j & k; k >>= 1) j ^= k;
		j ^= k;
		if (i < j) std::swap(__a[i], __a[j]);
	}
	for (int k = 2; k <= __n; k <<= 1) {
		double ang = 2 * PI / k * (inv ? -1 : 1);
		cd wl(cos(ang), sin(ang));
		for (int i = 0; i < __n; i += k) {
			cd w(1);
			for (int j = 0; j < k / 2; ++j, w *= wl) {
				cd u = __a[i + j], v = __a[i + j + k / 2] * w;
				__a[i + j] = u + v;
				__a[i + j + k / 2] = u - v;
			}
		}
	}
	if (inv) {
		cd *_ptr = __a + __n;
		while (_ptr-- != __a)
			*_ptr /= __n;
	}
}

Bigint Bigint::operator-() const
{
	Bigint _res;
	_res._assign(*this);
	_res._sign ^= 1;
	return _res;
}

Bigint& Bigint::operator+=(__int128_t __x)
{
	if (_sign == (__x < 0))
		*_data += _sign ? -__x : __x;
	else
	{
		if (__x < 0)
			__x = -__x;
		if (_size > 1 || *_data > __x)
			*_data -= __x;
		else
		{
			*_data = __x - *_data;
			_sign ^= 1;
		}
	}
	_normalize();
	return *this;
}

Bigint& Bigint::operator-=(__int128_t __x)
{
	if (_sign != (__x < 0))
		*_data += _sign ? __x : -__x;
	else
	{
		if (__x < 0)
			__x = -__x;
		if (_size > 1 || *_data > __x)
			*_data -= __x;
		else
		{
			*_data = __x - *_data;
			_sign ^= 1;
		}
	}
	_normalize();
	return *this;
}

Bigint& Bigint::operator*=(__int128_t __x)
{
	_sign = *this == 0 || __x == 0 ? 0 : _sign ^ (__x < 0);
	value_t *_ptr = _data + _size;
	while (_ptr-- != _data)
		*_ptr *= __x;
	_normalize();
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
	if (_sign == __x._sign)
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
	if (_sign != __x._sign)
		_add(_data, __x._data, std::min(_size, __x._size));
	else if (_comp_abs(__x) > 0)
		_sub(_data, __x._data, std::min(_size, __x._size));
	else
		_assign(Bigint(__x) -= *this);
	_normalize();
	return *this;
}

Bigint& Bigint::operator*=(const Bigint& __x)
{
	register size_t _i;
	size_t _n = 2;
	while (_n < _size + __x._size + 1) _n <<= 1;
	cd *_fa = new cd[_n];
	cd *_fb = new cd[_n];
	for (_i = 0; _i < _size; ++_i)
		_fa[_i] = _data[_i];
	for (_i = 0; _i < __x._size; ++_i)
		_fb[_i] = __x._data[_i];
	_fft(_fa, _n, 0);
	_fft(_fb, _n, 0);
	for (_i = 0; _i < _n; ++_i)
		_fa[_i] *= _fb[_i];
	_fft(_fa, _n, 1);
	
	_size = _n;
	_capa = _n;
	delete[] _data;
	_data = new value_t[_n];
	for (_i = 0; _i < _n; ++_i)
		_data[_i] = (value_t)std::round(_fa[_i].real());
	while (_size > 1 && !_data[_size - 1])
		if (--_size == _capa >> 2)
			_realloc(_capa >> 1);
	_normalize();
	_sign = (*this == 0 ? 0 : _sign ^ __x._sign);
	delete[] _fa;
	delete[] _fb;
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