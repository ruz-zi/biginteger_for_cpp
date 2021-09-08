#ifndef BIG_INTEGER
#define BIG_INTEGER

#include <iostream>
#include <iomanip>
#include <complex>
#include <string>
#include <cmath>
#include <cassert>

typedef signed long long value_t;

constexpr char		BASE_K	= 7;
constexpr value_t	BASE	= 10000000;

class Bigint
{
public:
// constructor & destructor
	Bigint();
	Bigint(__int128_t);
	Bigint(const char *);
	Bigint(const std::string&);
	Bigint(const Bigint&);
	~Bigint();
	
// allocational & relational operators
	Bigint& operator=(__int128_t);
	Bigint& operator=(const char *);
	Bigint& operator=(const std::string&);
	Bigint& operator=(const Bigint&);
	
	bool operator==(const Bigint&) const;
	bool operator!=(const Bigint&) const;
	bool operator< (const Bigint&) const;	
	bool operator> (const Bigint&) const;
	bool operator<=(const Bigint&) const;
	bool operator>=(const Bigint&) const;

// arithmetic operators
	Bigint operator-() const;
	Bigint& operator+=(__int128_t);
	Bigint& operator-=(__int128_t);
	Bigint& operator*=(__int128_t);
	Bigint& operator/=(__int128_t);
	Bigint& operator%=(__int128_t);
	Bigint& operator&=(__int128_t);
	Bigint& operator|=(__int128_t);
	Bigint& operator^=(__int128_t);
	Bigint& operator+=(const Bigint&);
	Bigint& operator-=(const Bigint&);
	Bigint& operator*=(const Bigint&);
	Bigint& operator/=(const Bigint&);
	Bigint& operator%=(const Bigint&);
	Bigint& operator&=(const Bigint&);
	Bigint& operator|=(const Bigint&);
	Bigint& operator^=(const Bigint&);
	Bigint operator+(const Bigint&) const;
	Bigint operator-(const Bigint&) const;
	Bigint operator*(const Bigint&) const;
	Bigint operator/(const Bigint&) const;
	Bigint operator%(const Bigint&) const;
	Bigint operator&(const Bigint&) const;
	Bigint operator|(const Bigint&) const;
	Bigint operator^(const Bigint&) const;
	
// public functions
	std::string to_string() const;
	void swap(Bigint&);
	
private:
	value_t	*_data = nullptr;
	size_t	_capa;
	size_t	_size;
	bool	_sign;
	
// private functions
	void _alloc(size_t);
	void _realloc(size_t);
	void _normalize();
	void _assign(__int128_t);
	void _assign(const char *);
	void _assign(const Bigint&);
	int _comp_abs(const Bigint&) const;
};

template <typename T> bool operator==(const Bigint& __lhs, T __rhs) { return __lhs == Bigint(__rhs); }
template <typename T> bool operator!=(const Bigint& __lhs, T __rhs) { return !(__lhs == Bigint(__rhs)); }
template <typename T> bool operator< (const Bigint& __lhs, T __rhs) { return __lhs < Bigint(__rhs); }
template <typename T> bool operator> (const Bigint& __lhs, T __rhs) { return Bigint(__rhs) < __lhs; }
template <typename T> bool operator<=(const Bigint& __lhs, T __rhs) { return !(Bigint(__rhs) < __lhs); }
template <typename T> bool operator>=(const Bigint& __lhs, T __rhs) { return !(__lhs < Bigint(__rhs)); }
template <typename T> bool operator==(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) == __rhs; }
template <typename T> bool operator!=(T __lhs, const Bigint& __rhs) { return !(Bigint(__lhs) == __rhs); }
template <typename T> bool operator< (T __lhs, const Bigint& __rhs) { return Bigint(__lhs) < __rhs; }
template <typename T> bool operator> (T __lhs, const Bigint& __rhs) { return __rhs < Bigint(__lhs); }
template <typename T> bool operator<=(T __lhs, const Bigint& __rhs) { return !(__rhs < Bigint(__lhs)); }
template <typename T> bool operator>=(T __lhs, const Bigint& __rhs) { return !(Bigint(__lhs) < __rhs); }


template <typename T> Bigint operator+(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) += __lhs; }
template <typename T> Bigint operator-(const Bigint& __lhs, T __rhs) { return Bigint(__lhs) -= Bigint(__rhs); }
template <typename T> Bigint operator*(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) *= __lhs; }
template <typename T> Bigint operator/(const Bigint& __lhs, T __rhs) { return Bigint(__lhs) /= Bigint(__rhs); }
template <typename T> Bigint operator%(const Bigint& __lhs, T __rhs) { return Bigint(__lhs) %= Bigint(__rhs); }
template <typename T> Bigint operator&(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) &= __lhs; }
template <typename T> Bigint operator|(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) |= __lhs; }
template <typename T> Bigint operator^(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) ^= __lhs; }
template <typename T> Bigint operator+(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) += __rhs; }
template <typename T> Bigint operator-(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) -= __rhs; }
template <typename T> Bigint operator*(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) *= __rhs; }
template <typename T> Bigint operator/(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) /= __rhs; }
template <typename T> Bigint operator%(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) %= __rhs; }
template <typename T> Bigint operator&(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) &= __rhs; }
template <typename T> Bigint operator|(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) |= __rhs; }
template <typename T> Bigint operator^(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) ^= __rhs; }

template <typename I> I& operator>>(I& __in, Bigint& __x)
{
	std::string _str;
	__in >> _str;
	__x._assign(_str.c_str());
	return __in;
}
template <typename O> O& operator<<(O& __out, const Bigint& __x)
{
	__out << __x.to_string();
	return __out;
}

#endif