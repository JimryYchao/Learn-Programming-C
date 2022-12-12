# complex.h 复数运算

---
- [complex.h 复数运算](#complexh-复数运算)
- [1. complex.h 复数运算数学库（Microsoft C）](#1-complexh-复数运算数学库microsoft-c)

---
# 1. complex.h 复数运算数学库（Microsoft C）

- 当实现定义了 ```__STDC_NO_COMPLEX__```，将不会提供 ```complex.h``` 头文件

- 该头文件支持复数类型和虚数类型的数学运算

```c
// 三种复数类型
double _Complex;
float _Complex;
long double _Complex;
// 三种虚数类型
double _Imaginary;
float _Imaginary;
long double _Imaginary;
```

