## C Term

|term|description|
|:--|:--|
**access**|执行时操作，读取或修改对象的值。如果仅表示这两个操作数之一，则使用 *read* 或 *modify*。修改包括存储的新值与前一个值相同的情况。未计算的表达式不访问对象。|
**alignment**|对齐，要求特定类型的对象和位于存储边界上，其地址是字节地址的特定倍数。
**argument**| 实参，在函数调用表达式中以括号为界的逗号分隔列表中的表达式，或在类似函数的宏调用中以逗号分隔的列表中以括号为界的预处理标记序列。
**arithmetically negate**|算术否定，产生给定数字的负数。对于浮点数，这会更改符号；对于整数，这相当于从零中减去。
**behavior**|行为，外观或动作。
  **implementation-defined behavior**|实现定义的行为，每个实现都记录了如何做出选择。
  **locale-specific behavior**|特定于区域设置的行为，取决于每个实现记录的国家、文化、或语言的当地惯例的行为。
  **undefined behavior**|未定义行为。使用了不可移植或错误的程序结构或错误的数据，本文档对此没有要求的行为。
  **unspecified behavior**|未指定行为。由于使用未指定的值而产生的行为，或本文档提供两种或多种可能性的其他行为，并且不施加任何情况下选择的进一步要求。
**bit**|位，执行环境中的数据存储单位足够大，以容纳可以具有两个值（0 或 1）之一的对象。
**byte**|字节，数据存储的可寻址单元足够大，可以容纳执行环境的基本字符集的任何成员。可以唯一地表示对象的每个字节的地址。字节由连续的位序列组成，其数量是实现定义的，最低有效位称为低位，最高有效位称为高位。
**low-order bit**|低阶位，字节内的最低有效位。
**high-order bit**|高阶位，字节内的最高有效位。
**character**|用于组织、控制或表示数据的一组元素的成员。
  **character**|单字节字符，适合字节的 C 位表示形式。
  **multibyte character**|多字节字符，一个或多个字节的序列，表示源环境或执行环境的扩展字符集的成员。扩展字符集是基本字符集的超集。
  **wide character**|宽字符，值可由 `wchar_t` 类型的对象表示，能够表示当前区域设置中的任何字符。
**constraint**|约束，句法或语义上的限制，通过这些限制来解释语言元素的阐述。
**correctly rounded result**|正确舍入的结果，以最接近结果格式表示，该格式在值上最接近，受当前舍入模式的约束，结果将被赋予无限范围和精度。
**diagnostic message**|诊断消息，属于实现消息输出的实现定义的子集的消息。
**implementation**|实现。特定程序集，在特定转换环境中以特定控制选项运行，用于执行特定执行环境中的程序翻译并支持在特定执行环境中执行功能。
**implementation limit**|实现限制，实现对程序施加的限制。
**memory location**|内存位置，标量类型的对象，或具有非零宽度的相邻位域的最大序列。两个执行线程可以更新和访问单独的内存位置，而不会相互干扰。位域和相邻的非位域成员位于不同的内存位置。这同样适用于两个位域，如果一个在嵌套结构声明中声明而另一个不是，或者如果两者由零长度位域声明分隔，或者如果它们由非位字段成员声明分隔。如果在它们之间声明的所有成员也是（非零长度）位域，则在同一结构中同时更新两个非原子位字段是不安全的，无论这些中间位域的大小如何。
**object**|对象，执行环境中的数据存储区域，其内容可以表示值。引用时，对象可以解释为具有特定类型。
**parameter**|形式参数，声明为函数声明或定义的一部分的对象，该声明或定义在进入函数时获取值，或者从逗号分隔列表中获取标识符，该标识符由类似函数的宏定义中紧跟在宏名称后面的括号限定。
**recommended practice**|建议的做法，强烈建议的规范，因为它符合标准的意图，但对于某些实现来说，这可能是不切实际的。
**runtime-constraint**|运行时约束，调用库函数时对程序的要求。
**value**|值，当被解释为具有特定类型时，对象内容的精确含义。
  **implementation-defined value**|实现定义值，每个实现都记录了如何做出选择。
  **indeterminate representation**|不确定表示，表示未指定值或非值表示形式的对象表示形式。
  **unspecified value**|未指定值，相关类型的有效值，其中语言规范在任何实例中选择哪个值没有要求。
  **non-value representation**|非值表示，不表示对象类型的值的对象表示形式。
  **perform a trap**|执行陷阱，中断程序的执行，以便不执行进一步的操作。
**⌈$x$⌉**|$x$ 的上限，大于或等于 $x$ 的最小整数。
**⌊$x$⌋**|$x$ 的下限，小于或等于 $x$ 的最大整数。
**wraparound**|一个值对 $2^N$ 取模的过程，其中 $N$ 是结果类型的宽度。

---