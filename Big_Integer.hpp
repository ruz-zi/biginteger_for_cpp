#ifndef BIG_INTEGER
#define BIG_INTEGER

#include <string>
#include <iostream>

using value_t = __uint64_t;

constexpr char		BASE_K	= 30;
constexpr value_t	BASE	= 1 << BASE_K;

class Bigint
{
public:
// constructor & destructor
	Bigint()						{}
	Bigint(__int128_t __x)			{ _assign(__x); }
	Bigint(const char *__s)			{ _assign(__s); }
	Bigint(const std::string& __s)	{ _assign(__s.c_str()); }
	Bigint(const Bigint& __x)		{ _assign(__x); }
	~Bigint()						{ delete[] _data; }
	
// allocational & relational operators
	Bigint& operator=(__int128_t);
	Bigint& operator=(const char *);
	Bigint& operator=(const std::string&);
	Bigint& operator=(const Bigint&);
	
	bool operator==(const Bigint&) const;
	bool operator< (const Bigint&) const;	

// arithmetic operators
	const Bigint& operator-() const;
	Bigint& operator+=(const Bigint&);
	Bigint& operator-=(const Bigint&);
	Bigint& operator*=(const Bigint&);
	Bigint& operator/=(const Bigint&);
	Bigint& operator&=(const Bigint&);
	Bigint& operator|=(const Bigint&);
	Bigint& operator^=(const Bigint&);

// public functions
	const std::string& to_string() const;
	
	
private:
	value_t	*_data = nullptr;
	size_t	_capa;
	size_t	_size;
	bool	_negative;
	
// private functions
	void _alloc(size_t);
	void _realloc(size_t);
	void _copy_n(value_t *, value_t *, size_t);
	void _normalize();
	void _assign(__int128_t);
	void _assign(const char *);
	void _assign(const Bigint&);
};

template <typename I> I&	operator>>(I& __in, Bigint& __x)
{
	std::string _str;
	__in >> _str;
	__x._assign(_str.c_str());
	return __in;
}
template <typename O> O&	operator<<(O& __out, const Bigint& __x)
{
	__out << __x.to_string();
	return __out;
}
bool operator!=(const Bigint& __lhs, const Bigint& __rhs) { return !(__lhs == __rhs); }
bool operator> (const Bigint& __lhs, const Bigint& __rhs) { return __rhs < __lhs; }
bool operator<=(const Bigint& __lhs, const Bigint& __rhs) { return !(__rhs < __lhs); }
bool operator>=(const Bigint& __lhs, const Bigint& __rhs) { return !(__lhs < __rhs); }
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

const Bigint& operator+(const Bigint& __lhs, const Bigint& __rhs) { return Bigint(__lhs) += __rhs; }
const Bigint& operator-(const Bigint& __lhs, const Bigint& __rhs) { return Bigint(__lhs) -= __rhs; }
const Bigint& operator*(const Bigint& __lhs, const Bigint& __rhs) { return Bigint(__lhs) *= __rhs; }
const Bigint& operator/(const Bigint& __lhs, const Bigint& __rhs) { return Bigint(__lhs) /= __rhs; }
const Bigint& operator&(const Bigint& __lhs, const Bigint& __rhs) { return Bigint(__lhs) &= __rhs; }
const Bigint& operator|(const Bigint& __lhs, const Bigint& __rhs) { return Bigint(__lhs) |= __rhs; }
const Bigint& operator^(const Bigint& __lhs, const Bigint& __rhs) { return Bigint(__lhs) ^= __rhs; }
template <typename T> const Bigint& operator+(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) += __lhs; }
template <typename T> const Bigint& operator-(const Bigint& __lhs, T __rhs) { return Bigint(__lhs) -= Bigint(__rhs); }
template <typename T> const Bigint& operator*(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) *= __lhs; }
template <typename T> const Bigint& operator/(const Bigint& __lhs, T __rhs) { return Bigint(__lhs) /= Bigint(__rhs); }
template <typename T> const Bigint& operator%(const Bigint& __lhs, T __rhs) { return Bigint(__lhs) %= Bigint(__rhs); }
template <typename T> const Bigint& operator&(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) &= __lhs; }
template <typename T> const Bigint& operator|(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) |= __lhs; }
template <typename T> const Bigint& operator^(const Bigint& __lhs, T __rhs) { return Bigint(__rhs) ^= __lhs; }
template <typename T> const Bigint& operator+(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) += __rhs; }
template <typename T> const Bigint& operator-(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) -= __rhs; }
template <typename T> const Bigint& operator*(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) *= __rhs; }
template <typename T> const Bigint& operator/(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) /= __rhs; }
template <typename T> const Bigint& operator%(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) %= __rhs; }
template <typename T> const Bigint& operator&(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) &= __rhs; }
template <typename T> const Bigint& operator|(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) |= __rhs; }
template <typename T> const Bigint& operator^(T __lhs, const Bigint& __rhs) { return Bigint(__lhs) ^= __rhs; }

#endif