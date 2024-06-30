## C 泛型数学：tgmath.h


`tgmath.h` 包含了 `math.h` 和 `complex.h`，并定义了一些便利宏，这些宏会根据参数的类型决定要调用哪些数学函数。若参数的类型与所选函数的参数类型不兼容，则行为未定义。

以下定义的泛型宏与 `math.h` 和 `complex.h` 中的函数呈现多对一映射关系。泛型宏调用一个相应的函数，该函数的类型由特定参数的实参类型确定。

`math.h`  一些用于十进制浮点类型的函数没有无后缀的对应项。例如在这些带有 `d64` 后缀的函数中，有些函数有一个或多个类型为 `_Decimal64` 的参数。对于每个这样的函数，除了 `decodedecd64`、`encodedecd64`、`decodebind64` 和 `encodebind64` 之外，都有一个对应的类型泛型宏。函数简介中实类型为_Decimal64的形参是泛型形参。

如果泛型宏的泛型参数的实参使得一个参数具有标准浮点类型，而另一个参数具有十进制浮点类型，则行为未定义。

>---
### Macro-Functions

对于 `<math.h>` 中的每个无后缀函数，如果 `<complex.h>` 中有一个同名的函数，但 c 前缀除外，相应的类型泛型宏（对于两个函数）与 `<math.h>` 中的函数具有相同的名称。`fab` 和 `cab` 对应的类型泛型宏是 `fab` 。

对于所有拥有实数及复数对应的函数，存在泛型宏：
  - 实数函数：`XXXf` 对应 `float`，`XXX` 对应 `double`，`XXXl` 对应 `long double`；
  - 复数函数：`cXXXf` 对应 `float _complex`，`cXXX` 对应 `double _complex`，`cXXXl` 对应 `long double _complex`。

| math.h  | complex.h | Macro   |
| :------ | :-------- | :------ |
| `acos`  | `cacos`   | `acos`  |
| `asin`  | `casin`   | `asin`  |
| `atan`  | `catan`   | `atan`  |
| `acosh` | `cacosh`  | `acosh` |
| `asinh` | `casinh`  | `asinh` |
| `atanh` | `catanh`  | `atanh` |
| `cos`   | `ccos`    | `cos`   |
| `sin`   | `csin`    | `sin`   |
| `tan`   | `ctan`    | `tan`   |
| `cosh`  | `ccosh`   | `cosh`  |
| `sinh`  | `csinh`   | `sinh`  |
| `tanh`  | `ctanh`   | `tanh`  |
| `exp`   | `cexp`    | `exp`   |
| `log`   | `clog`    | `log`   |
| `pow`   | `cpow`    | `pow`   |
| `sqrt`  | `csqrt`   | `sqrt`  |
| `fabs`  | `cabs`    | `fabs`  |


以 `sin` 为例进行定义，根据泛型参数的类型，自动选择相应的函数调用。

```c
#include <stdio.h>
#include <tgmath.h>

#define __CPLX(z,R,C) _Generic((z),\
	float:        R##f,		\
	long double:  R##l,     \
	_Fcomplex:    C##f,	    \
	_Dcomplex:    C,		\
    _Lcomplex:    C##l,     \
    default:      R		    \
)(z)

#define sin(x)  __CPLX(x, sin, csin)

int main(void)
{
	double rt = sin(1);
	printf("sin(1) = %.6f", rt);
}
```

对于 `<math.h>` 中每个无后缀函数，在 `<complex.h>` 中没有 c 前缀的对应函数（将结果舍入为较窄的类型的函数、`modf` 和 `canonicalize` 除外），相应的类型泛型宏与函数同名。这些类型泛型宏是：

| line-1      | line-2             | line-3    | line-4       | line-5      |
| :---------- | :----------------- | :-------- | :----------- | :---------- |
| `acospi`    | `exp2`             | `fmod`    | `log2`       | `rootn`     |
| `asinpi`    | `expm1`            | `frexp`   | `logb`       | `roundeven` |
| `atan2pi`   | `fdim`             | `fromfpx` | `logp1`      | `round`     |
| `atan2`     | `floor`            | `fromfp`  | `lrint`      | `rsqrt`     |
| `atanpi`    | `fmax`             | `hypot`   | `lround`     | `scalbln`   |
| `cbrt`      | `fmaximum`         | `ilogb`   | `nearbyint`  | `scalbn`    |
| `ceil`      | `fmaximum_mag`     | `ldexp`   | `nextafter`  | `sinpi`     |
| `compoundn` | `fmaximum_num`     | `lgamma`  | `nextdown`   | `tanpi`     |
| `copysign`  | `fmaximum_mag_num` | `llogb`   | `nexttoward` | `tgamma`    |
| `cospi`     | `fma`              | `llrint`  | `nextup`     | `trunc`     |
| `erfc`      | `fmin`             | `llround` | `pown`       | `ufromfpx`  |
| `erf`       | `fminimum`         | `log10p1` | `powr`       | `ufromfp`   |
| `exp10m1`   | `fminimum_mag`     | `log10`   | `remainder`  |
| `exp10`     | `fminimum_num`     | `log1p`   | `remquo`     |
| `exp2m1`    | `fminimum_mag_num` | `log2p1`  | `rint`       |

如果泛型参数的所有参数都是实数，则使用宏会调用实函数（提供 `<math.h>` 定义确定类型的函数）；否则，宏的使用是未定义的。



对于 `<complex.h>` 中每个不带后缀的函数，如果它们不是 `<math.h>` 中函数的 c 前缀对应项，则相应的类型泛型宏与该函数同名。这些类型泛型宏是 `carg`、`cimag`、`conj`、`cproj`、`creal`。将宏与标准浮点型或复数类型的任何参数一起使用都会调用复数函数。将宏与十进制浮点型参数一起使用则未定义。

```c
#define creal(z)         // 复数的实部
#define cimag(z)         // 复数的虚部
#define carg(z)          // 复数的相角
#define conj(z)          // 复数的复数共轭
#define cproj(z)         // 黎曼球面上的投影
```

将结果舍入为较窄类型的函数具有类型泛型宏，其名称是通过省略函数名称中的任何后缀来获取的。所有参数都是实数。如果宏前缀为 `f` 或 `d`，则使用十进制浮点类型的参数行为未定义。如果宏前缀是 `d32` 或 `d64` ，则使用标准浮点类型的参数行为未定义。

| 后缀 `d` | 后缀 `f` | 后缀 `d32` | 后缀`d64` |
| :------- | :------- | :--------- | :-------- |
| `fadd`   | `dadd`   | `d32add`   | `d64add`  |
| `fsub`   | `dsub`   | `d32sub`   | `d64sub`  |
| `fmul`   | `dmul`   | `d32mul`   | `d64mul`  |
| `fdiv`   | `ddiv`   | `d32div`   | `d64div`  |
| `ffma`   | `dfma`   | `d32fma`   | `d64fma`  |
| `fsqrt`  | `dsqrt`  | `d32sqrt`  | `d64sqrt` |

对于 `math.h` 定义的量子函数和量子指数函数则有以下类型泛型宏。将宏与标准浮点型或复数类型的参数一起使用，或者仅将宏与整数类型参数一起使用时，行为未定义。

| <math.h> function | type-generic macro |
| :---------------- | :----------------- |
| `quantized`*N*    | `quantize`         |
| `samequantumd`*N* | `samequantum`      |
| `quantumd`*N*     | `quantum`          |
| `llquantexpd`*N*  | `llquantexp`       |

---