#pragma once

#define __STDC_VERSION_STDDEF_H__       202311L

typedef /* implementation */        ptrdiff_t;
typedef /* implementation */        size_t;
typedef typeof(nullptr)             nullptr_t
typedef /* 由实现定义 */            max_align_t;
typedef  wchar_t                    wchar_t
#define NULL            ((void*)0)

#define offsetof(type, member_designator)
#define unreachable()