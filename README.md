_last update: 21-09-08-03:50 GMT+9_

# Big_Interger_class_for_C++

## 소개

동적 signed long 배열 이용,  
~~2^k 진법 수로 저장 배열의 i번 원소는 2^k^i 항의 계수~~  
입출력 편의를 위해 1ek 진법 수로 저장,  
k는 실험적으로 결정 (FFT 오차)  k->7  

## To Do List

1. 덧셈 ✅
2. 뺄셈 ✅
3. 곱셈 FFT (-> NTT+CRT?) ✅
4. 나눗셈 빠른 나눗셈 알고리즘 ❌
5. 비트연산 ❌
6. 캐스팅 연산 ❌
7. 입출력 오버로딩 ✅
8. 비교 연산 ✅
9. 할당 연산 ✅
10. 기본 자료형과의 호환성 ✅

## 구현된 기능

### 생성/초기화

```cpp
Bigint a; //메모리가 할당되지 않은 상태
Bigint b = 123;
Bigint c = "123";
Bigint d = std::string("123");
Bigint e = b;
```

### 입출력

#### 표준 입출력

```cpp
Bigint a;

std::cin >> a;
std::cout << a;
```

#### 파일 입출력

```cpp
fstream in, out;
Bigint b;

in.open("input_file", fstream::in);
out.open("output_file", fstream::out);

in >> b;
out << b;
```

### 대입 연산

```cpp
Bigint a, b;

a = 123;
a = "123";
b = a;
```

### 비교 연산

```cpp
Bigint a = 123, b = "123";
Bigint c = 100;

std::cout << std::fixed << std::boolalpha;

std::cout << (a == b); // true
std::cout << (a != b); // false
std::cout << (a <  c); // false
std::cout << (a <= c); // false
std::cout << (a >  c); // true
std::cout << (a >= c); // false
```

## 참고 문헌, 출처

[secmem/cubelover - 빠른 다항식 나눗셈](http://www.secmem.org/blog/2019/04/10/polynomial-division/)
