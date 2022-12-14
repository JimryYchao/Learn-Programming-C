/*
id: luaconf.h
level: 1
explain: Lua 的通用配置文件，配置中的一些定义可以通过编译器在外部进行更改，搜索
	 “@@” 可以找到所有可配置定义
*/

#ifndef luaconf_h
#define luaconf_h

#include <limits.h>
#include <stddef.h>

/* {============================================================================
### 系统配置：使 Lua 适应(如果需要) 某些特定平台的宏)
*/

/*
@@ LUA_USE_C89：控制非 ISO-C89 特性的使用。如果希望 Lua 避免在 Windows 上
	使用一些 C99 特性或特定于 Windows 的特性，请定义它
*/
// #define LUA_USE_C89  /* 限制 Lua 使用的 C 标准为 ISO-C89 */

/*
@@ 默认情况下，Windows 上的 Lua 使用(某些)特定的 Windows 功能
*/
#if !defined(LUA_USE_C89) && defined(_WIN32) && !defined(_WIN32_WCE)
#define LUA_USE_WINDOWS	 /* 为常规窗口启用goodies */

#endif

#endif