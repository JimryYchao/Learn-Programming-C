## C 输入与输出（Input/output）：stdio.h

`stdio.h` 提供了通用的文件操作支持，并提供了具有窄字符输入和输出功能的函数。宽字符的对应输入输出函数定义在 `wchar.h` 头文件中。

---
### Types

#### FILE

```c
typedef _iobuf FILE
```

- `FILE` 是一种对象类型，能够记录控制流所需的所有信息，包括起文件位置指示器，指向其相关缓冲区的指针，记录是否发生读写错误的错误指示器，以及记录是否到达文件末尾的文件结束指示器。

<br> 

#### fpos_t

```c
typedef long long fpos_t;
```

- `fpos_t` 是一个完整的非数组对象类型，能够记录唯一指定文件的位置和多字节剖析状态。


---
### Macros

#### _IO *X* BF （指示 setvbuf 文件缓冲类型）

```c
#define _IOFBF     0x0000       // 全缓冲
#define _IOLBF     0x0040       // 行缓冲
#define _IONBF     0x0004       // 无缓冲
```

- 这些宏可以作为 `setvbuf` 函数的第三个参数：
  - `_IOFBF` 指示 **全缓冲**：只有在缓冲区被填满之后才会进行 I/O 操作。
  - `_IOLBF` 指示 **行缓冲**：只有在输入或者是输出中遇到换行符的时候才会进行 I/O 操作。
  - `_IONBF` 指示 **无缓冲**：标准 I/O 不缓存字符。

<br>

#### BUFSIZ （指示 setbuf 缓冲区大小）

```c
#define BUFSIZ     512
```

- `BUFSIZ` 指示 `setbuf` 函数所用的缓冲区大小。
- 实现应支持行至少包含 254 个字符的文本文件，包括结束换行字符。宏 BUFSIZ 的值至少为 256。

<br>

#### EOF （指示文件结束）

```c
#define EOF    (-1)
```

- `EOF` 展开为一个负值整数常量表达式，由几个函数返回以表示文件结束，即不再有来自流的输入。


<br>

#### FOPEN_MAX （同时打开文件数）

```c
#define FOPEN_MAX    20
```

- `FOPEN_MAX` 表示能同时打开的文件数。`FOPEN_MAX` 的值至少为 8，其中包括三个标准文本流。

<br>

#### FILENAME_MAX （可支持文件名长度）

```c
#define FILENAME_MAX    260
```

- `FILENAME_MAX` 表示保有最长受支持文件名所需的 `char[]` 数组大小，或是没有文件名长度限制时，建议用于容纳文件名字符串的数组的大小。
- 文件名字符串的内容受制于其他系统特定的约束，因此，不能保证所有长度为 `FILENAME_MAX` 的字符串都能成功打开。

<br>

#### L_tmpnam、L_tmpnam_s （指示 tmpnam 可支持临时文件名长度）

```c
#define L_tmpnam   260 // _MAX_PATH

#define L_tmpnam_s  L_tmpnam
```

- `L_tmpnam` 表示可以容纳由 `tmpnam` 函数生成的临时文件名字符串的长度。`L_tmpnam_s` 为线程安全版本。

<br>

#### SEEK_XXX （指示 fseek 文件寻位标志）

```c
#define SEEK_SET    0           // 指示从文件首开始寻位
#define SEEK_CUR    1           // 指示从文件当前位置开始寻位
#define SEEK_END    2           // 指示从文件尾开始寻位
```

- `SEEK_XXX` 这些宏可以作为函数 `fseek` 的第三个参数用于指示文件寻位的起始起点。

<br>

#### TMP_NAX、TMP_MAX_S （指示 tmpnam 生成的最大独有文件数）

```c
#define TMP_MAX         _CRT_INT_MAX  // int32_max
#define TMP_MAX_S       TMP_MAX
```

- `TMP_MAX` 指示函数 `tmpnam` 能生成的具有唯一性的文件名的最大数目。

<br>

#### stdxxx （定义系统标准流）

```c
#define stdin       // 标准输入
#define stdout      // 标准输出
#define stderr      // 标准错误
```

- 这些宏是 “指向 `FILE` 的指针” 类型，展开为 `FILE *` 类型表达式，分别表示：
  - `stdin` 与 *标准输入流* 关联，用于读取约定的输入。程序启动时，该流为完全缓冲当且仅当能确定流不引用交互式设备。
  - `stdout` 与 *标准输出流* 关联，用于写入约定的输出。程序启动时，该流为完全缓冲当且仅当能确定流不引用交互式设备。
  - `stderr` 与 *标准错误流* 关联，用于写入诊断输出。程序启动时，该流不为完全缓冲。

- UNIX 约定 `stdin` 与 `stdout` 若与终端关联则为行缓冲，`stderr` 为无缓冲。

---
### Stream（流）

* 流（stream）是输入与输出设备的抽象，无论是从终端或磁带机等物理设备输入和输出，还是从结构化存储设备支持的文件输入和输出，都映射为逻辑数据流，用来统一各种的输入与输出概念。有两种概念的映射：文本流和二进制流。

- **文本流** 是由行组成的有序字符序列，每行由零个或多个字符加上一个结束的换行字符组成。最后一行是否需要结束换行符是实现定义的。可能必须在输入与输出时添加、修改或删除字符，以符合 OS 中的文本表示（例如 WindowOS 上的 C 流在输出时将 `\n` 转换为 `\r\n`，而输入时将 `\r\n` 转换为 `\n`）。因此，流中的字符与外部表示中的字符之间不需要一一对应。

* 若需要保证从文本流读入的数据和先前写入该流的数据相等，必须满足：
  - 数据仅由打印字符和控制字符（`\t`，`\n`）组成；
  - 没有空格字符紧接在换行字符之前（` \n`）；
  - 最后一个字符是换行符 `n`。

- **二进制流** 是一个有序的字符序列，可以透明地记录内部数据。在相同的实现下，从二进制流读入的数据应该与早先写进该流的数据比较相等。这样的流可以在流的末尾附加上不确定数目的实现定义的空字符。

* 每个流都有一个方向。在流与外部文件关联后，在对其执行任何操作之前，流没有方向。一旦将宽字符输入输出函数应用于没有方向的流，该流就成为宽方向流。一旦将字节输入输出函数应用于没有方向的流，该流就会成为面向字节的流。只有调用 `freopen` 或 `fwide` 函数才能改变流的方向。

- 字节 I/O 函数不能应用于面向宽的流，宽字符 I/O 函数不能应用于面向字节的流。其余的流操作不影响流的方向，也不受流方向的影响，除了：
  - 二进制宽定向流具有文本流和二进制流的文件定位限制；
  - 面向宽的流，在成功调用文件定位函数（在文件结束之前留下文件位置指示符）之后，宽字符输出函数可以覆盖部分多字节字符；之后任何超出写入字节的文件内容都是不确定的。

* 每个面向宽的流都有一个关联的 `mbstate_t` 对象，该对象存储流的当前解析状态。对 `fgetpos` 的成功调用将这个 `mbstate_t` 对象的值的表示形式存储为 `fpos_t` 对象值的一部分。稍后使用相同存储的 `fpos_t` 值成功调用 `fsetpos` 将恢复相关的 `mbstate_t` 对象的值以及在受控流中的位置。

- 每个流都有一个相关的锁，用于防止多个执行线程访问流时的数据竞争，并限制多个线程执行的流操作的交错。一次只有一个线程可以持有这个锁。锁是可重入的：一个线程可以在给定时间多次持有锁。所有读、写、定位或查询流位置的函数在访问流之前都会锁定流。当访问完成时，它们释放与流关联的锁。

---
### FILE（文件）

- 流通过打开文件与外部文件（可能是物理设备）相关联，这可能涉及创建一个新文件。如果有必要，创建一个现有文件会导致其先前的内容被丢弃。如果一个文件可以支持定位请求（比如磁盘文件，而不是终端），那么与流关联的文件位置指示器定位在文件的开始（字符号为 0），除非文件以追加模式打开，在这种情况下，文件位置指示器最初定位在文件的开始还是结束是由实现定义的。文件位置指示器由随后的读、写和定位请求等维持，以保证指示器在文件中的有序前进。

* 二进制文件不会被截断，除非在相关函数操作中定义。对文本流的写入是否会导致相关文件在该点之后被截断是由实现定义的。

- 当流未被缓冲时，字符将从源端或目标端尽快出现。否则，字符可能会作为一个块积累并传输到主机环境或从主机环境传输出去。当一个流被完全缓冲时，在缓冲区被填满时，这些字符将作为一个块传输到主机环境或从主机环境传输出去。当流被行缓冲时，在遇到新行字符时，这些字符将作为块传输到主机环境或从主机环境传输出去。此外，在缓冲区被填满时、或者是在未缓冲的流上请求输入时、或者在需要从主机环境传输字符的行缓冲流上请求输入时，字符将作为块传输到主机环境中。对这些特性的支持是实现定义的，并且可能会受 `setbuf` 和 `setvbuf` 函数的影响。

* 可以通过关闭文件来解除文件与控制流的关联。输出流在与文件解除关联之前被刷新（任何未写入的缓冲区内容都被传输到主机环境）。在相关文件关闭后（包括标准文本流），指向 `FILE` 对象的指针的值是不确定的。零长度文件（输出流没有在其上写入任何字符）是否实际存在是实现定义的。

- 该文件可能随后由相同或另一个程序执行重新打开，并回收或修改其内容（如果它可以在开始时重新定位）。如果 `main` 函数返回到它的原始调用者，或者是 `exit` 函数被调用，那么所有打开的文件将在程序终止前关闭（因此所有输出流将被刷新）。其他终止程序的途径不需要正确关闭所有文件，例如调用 `abort` 函数。

* 用于控制流的 `FILE` 对象的地址可能是重要的；`FILE` 对象的副本不需要代替原始对象。

- 在程序启动时，三个文本流是预定义的，不需要显式打开：标准输入（用于读取常规输入）、标准输出（用于写入常规输出）和标准错误（用于写入诊断输出）。在最初打开时，标准错误流没有被完全缓冲；标准输入和标准输出流当且仅当可以确定该流不引用交互式设备时被完全缓冲。 

* 打开其他（非临时）文件的函数需要一个文件名，它是一个字符串。组成有效文件名的规则是由实现定义的。同一文件是否可以同时打开多次也是由实现定义的。

- 虽然文本和二进制宽面向流在概念上都是宽字符序列，但与宽面向流相关的外部文件是多字节字符序列，概括如下：文件中的多字节编码可能包含嵌入的空字节（与程序内部使用的有效多字节编码不同），文件也不必以初始移位状态开始或结束。此外，用于多字节字符的编码可能因文件而异。这种编码的性质和选择都是由实现定义的。

* 宽字符输入函数从流中读取多字节字符，并将其转换为宽字符，就像连续调用 `fgetwc` 函数一样。每次转换都像调用 `mbrtowc` 函数一样发生，转换状态由流自己的 `mbstate_t` 对象描述。字节输入函数从流中读取字符，就像连续调用 `fgetc` 函数一样。

- 宽字符输出函数将宽字符转换为多字节字符，并将其写入流，就像连续调用 `fputwc` 函数一样。每次转换都像调用 `wcrtomb` 函数一样发生，转换状态由流自己的 `mbstate_t` 对象描述。字节输出函数将字符写入流，就像连续调用 `fputc` 函数一样。

* 在某些情况下，一些字节输入输出函数还执行多字节字符和宽字符之间的转换。这些转换也像调用 `mbrtowc` 和 `wcrtomb` 函数一样发生。

- 如果提供给底层 `mbrtowc` 函数的字符序列没有形成有效的（通用的）多字节字符，或者传递给底层 `wcrtomb` 的代码值不对应于有效的（通用的）多字节字符，则会发生编码错误。当且仅当编码错误发生时，宽字符输入输出函数和字节输入输出函数将宏 `EILSEQ` 的值存储在 `errno` 中。

---
### Functions：文件操作（Operations on files）

#### remove （删除文件）

```c
int remove(const char *filename);
```

- `remove` 函数的作用是删除 `filename` 所指向的字符串标识的文件，并使此 `filename` 访问失效。之后使用该名称打开该文件将失败，除非重新创建该文件。
- 若文件为当前进程或另一个进程打开，则函数的行为是实现定义的（例如，POSIX 系统解链接文件名，到最后一个运行的进程关闭该文件为止，即使这是最后一个到文件的硬链接也不回收文件系统空间；而 Windows 不允许删除该文件）。

- `remove` 文件成功时返回 0，操作失败时为非零值。

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    FILE* fp = fopen("file1.txt", "w"); // 创建文件
    if (!fp) { perror("file1.txt"); return 1; }
    puts("Created file1.txt");
    fclose(fp);

    int rc = remove("file1.txt");
    if (rc) { perror("remove"); return 1; }
    puts("Removed file1.txt");

    fp = fopen("file1.txt", "r"); // 错误：文件不存在
    if (!fp) perror("Opening removed file failed");

    rc = remove("file1.txt"); // 错误：文件不存在
    if (rc) perror("Double-remove failed");
}
/*
Created file1.txt
Removed file1.txt
Opening removed file failed: No such file or directory
Double-remove failed: No such file or directory
*/
```

<br>

#### rename （重命名文件）

```c
int rename(const char *old, const char *new);
```

- `rename` 用于更改文件的文件名，用 `new` 替换掉 `old`，若 `new` 存在则行为是实现定义的。函数在重命名成功时返回 0，操作失败时返回非零值。失败的原因可能是文件是打开的，或是不存在，或是新名称不合法。

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	//------------可选注释----------
	int rc = remove("to.txt");			
	if (rc) { perror("remove"); }
	//-----------------------------

	FILE* fp = fopen("from.txt", "w"); // 创建文件 "from.txt"
	if (!fp) { perror("from.txt"); return 1; }
	fprintf(fp, "hello world"); // 写入到 "from.txt"
	fclose(fp);

	rc = rename("from.txt", "to.txt");      // 重命名
	if (rc) { perror("rename"); return 1; }

	fp = fopen("to.txt", "r");
	if (!fp) { perror("to.txt"); return 1; }
	char buf[70];
	printf("%s\n", fgets(buf, sizeof buf, fp)); // 从 "to.txt" 读取
	fclose(fp);
}
```

<br>

#### tmpfile、tmpfile_s （创建临时文件）

> `tmpfile`

```c
FILE * tmpfile(void);
```

- `tmpfile` 函数创建并打开一个临时二进制文件，该文件不同于任何其他现有文件，在关闭或程序终止时将自动删除该文件。如果程序异常终止，是否删除打开的临时文件是由实现定义的。打开的文件以 `"wb+"` 模式进行更新。该文件的名称保证在文件系统中唯一。
- 可以在程序的生存期内创建并打开最多 `TMP_MAX` 个临时文件，但这个限制可能与 `tmpnam` 共享，并可能由 `FOPEN_MAX` 所进一步限制。
- `tmpfile` 返回一个指向它所创建的文件流的指针。文件不能创建时，将返回一个空指针。


> `tmpfile_s`

```c
errno_t tmpfile_s(FILE** _Stream);
```

* `tmpfile_s` 功能和 `tmpfile` 相同，可以在程序的生存期内同时创建并打开最多 `TMP_MAX_S` 个文件，此极限可能与 `tmpnam_s` 共享。若 `_Stream` 为空指针将会调用当前安装的制约处理函数。创建的文件指针将保存在 `_Stream` 所指的对象中，操作成功时将返回 `(errno_t)0`，否则返回非零值。

```c
#include <stdio.h>

int main(void)
{
    FILE* stream;
    char tempstring[] = "String to be written";
    int  i;
    errno_t err;

    // Create temporary files.
    for (i = 0; i <= 520; i++)
    {
        err = tmpfile_s(&stream);
        if (err)
            perror("Could not open new temporary file\n");
        else
            printf("Temporary file %d was created\n", i);
    }
    // Remove temporary files.
    printf("%d temporary files deleted\n", _rmtmp());
}
```

<br>

#### tmpnam、tmpnam_s （返回唯一的文件名）

> `tmpnam`

```c
char *tmpnam(char *buffer);
```

- `tmpnam` 生成一个独有的合法文件名，其字符长度不超过 `L_tmpnam`。此函数可以生成最多 `TMP_MAX` 不同的字符串，但是它们中的一部分可能正在文件系统中使用，因此函数不适合作为返回值。
- `buffer` 是指向足以保有至少有 `L_tmpnam` 字节的字符数组的指针，并将以数组为结果缓冲区，若传递空指针，则返回指向内部静态缓冲区的指针。

- 使用 `tmpnam` 函数生成的字符串创建的文件是临时的，因为它们的名称不会与实现的常规命名规则生成的名称冲突。当这些文件的使用结束时，在程序终止之前，仍然需要使用 `remove` 函数来删除它们。

> `tmpnam_s`

```c
errno_t tmpnam_s(char *buffer_s, rsize_t maxsize);
```

* `tmpnam_s` 是在运行时发生错误时可以调用当前安装的约束处理函数，可以最多创建 `TMP_MAX_S` 个长度不超过 `L_tmpnam_s` 的文件名。运行时检查下列错误：
  - `buffer_s` 是空指针；
  - `maxsize` 超过 `rsize_t` 的范围；
  - `maxsize` 小于生成文件名字符串的长度。  

* `buffer_s` 是指向足以保有至少 `L_tmpnam_s` 字节的字符数组的指针，并以该数组为结果缓冲区。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0

#include <stdio.h>
#include <string.h>

int main(void)
{
#if _CRT_SECURE_NO_WARNINGS
	char* name1 = tmpnam(NULL);  // 返回静态缓冲区的指针
	printf("temporary file name: %s\n", name1);

	char name2[L_tmpnam];
	if (tmpnam(name2))
		printf("temporary file name: %s\n", name2);
	if (name1)
		remove(name1);
	remove(name2);
#else
	char name3[L_tmpnam_s];
	errno_t err;

	err = tmpnam_s(name3, sizeof name3);
	if (err)
		perror("Could not open new temporary file\n");
	else
		printf("temporary file name: %s\n", name3);

	remove(name3);
#endif
}
```

---
### Functions：文件访问（File access functions）

#### fclose （关闭文件）

```c
int fclose(FILE *stream);
```

- `fclose` 用于刷新 `stream` 指向的流并关闭相关联的文件。流的任何未写入的缓冲数据都被移交给 OS 环境以写入文件；所有未读的缓冲数据被丢弃。无论调用是否成功，流都会与对应的文件解除关联，并且 `setbuf` 或 `setvbuf` 分配的任何缓冲区都将与流解除关联，若是自动分配的缓冲也会被释放。
- 如果 `stream` 成功关闭，函数会返回 0，如果发生任何错误将返回 `EOF`。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE* fp = fopen("test.txt", "wb+");
	if (!fp) perror("File opening failed");
	int c; // 注意：int，非char，要求处理 EOF
	while ((c = fgetc(fp)) != EOF)  // 标准C I/O读取文件循环
		putchar(c);

	if (ferror(fp))
		puts("I/O error when reading");
	else if (feof(fp))
		puts("End of file reached successfully");

	if(!fclose(fp))
        puts("Close file successfully");
	remove("test.txt");
}
```

<br>

#### fflush （同步流到文件）

```c
int fflush(FILE *stream);
```

- `fflush` 函数刷新流 `stream`：如果流是在写入模式（输出流）下打开或是更新模式（输出的更新流）下打开的，并最后一次操作是写入，`fflush` 会将流缓冲区的内容写入基础文件或设备，并且该缓冲区的内容被丢弃。读取模式下或是流没有缓冲区时，调用 `fflush` 没有任何效果。调用后，该流仍保持打开状态。
- `stream` 是空指针时，将对所有输出流与输出的更新流执行此 `fflush` 刷新操作。
- 函数在成功刷新流后返回 0，在指定流无缓冲区或处于打开状态以仅供读取的状态下，也会返回 0；返回 `EOF` 将指示一个错误并设置文件流的错误指示器。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
int* crash_the_program = 0;
int main(void)
{
	FILE* my_file;
	errno_t err = fopen_s(&my_file, "myfile.txt", "w");
	if (my_file && !err)
	{
		printf("Write a number: ");
		int my_number = 0;
		scanf_s("%d", &my_number);
		fprintf(my_file, "User selected %d\n", my_number);

		// 可以输入 0 引发程序崩溃
		// 如果不使用 fflush，在崩溃之前没有数据写入文件，因此数据会丢失。
		if (my_number == 0)
			*crash_the_program = 0;

		// 立即将数据写入文件，而不是进行缓冲
		fflush(my_file);

		// 正常情况下，关闭文件会写入缓冲区，所以不需要使用 fflush
		// 注意：文件在正常终止时自动关闭和刷新。
		fclose(my_file);
	}
}
```

<br>

#### fopen、fopen_s （打开文件）

> `fopen`

```c
FILE *fopen(const char * restrict filename, const char * restrict mode);
```

- `fopen` 打开 `filename` 所指示的文件，并返回指向关联到该文件的流的指针。`mode` 用于确定文件的访问模式。函数在成功打开时返回控制流指针，否则将返回空指针。
* `mode` 的格式字符串中：
  - `"r"` 表示打开文件以读取，`"a"` 表示打开或创建文件以末尾写入，`"w"` 表示打开清空或创建文件并从头写入；
  - 附加二进制访问标签 `"b"` 表示使用二进制模式（默认使用文本模式，仅在 Windows 上生效）。
  - 附加更新模式标签 `"+"` 表示文件打开时可以在相关的流上进行读取和写入。但是如果不调用 `fflush` 或文件定位函数时，输出不能直接跟在输入后面；如果不调用文件定位函数，输入不能直接跟在输出后面。
  - 附加排他模式标签 `"x"` 可以可选地后附到 `"w"` 或 `"w+"` 指定符，表示文件存在或无法创建时，强制函数是失败。
  - 附加默认 `fopen` 许可标签 `"u"` 可以可选地前附到 `"w"` 或 `"a"` 指定符，表示启用默认的 `fopen` 许可。一般使用 `fopen` 时，文件以 `"w"` 或 `"a"` 创建的文件的文件许可是禁止任何其他用户访问它（独占模式）。

- `"r"` 读取模式： 
  - `"r"`：打开文本文件并从头读取（文本模式打开读取）
  - `"rb"`：打开二进制文件并从头读取（二进制模式打开读取）
  - `"r+"`：打开文本文件并从头进行读写更新（文本模式打开读写更新）
  - `"r+b"/"rb+"`：打开二进制文件并从头进行读写更新（二进制模式打开读写更新）

* `"a"` 追加模式：
  - `"a"`：打开或创建文本文件，以便在文件末尾写入（文本模式创建或打开写入）
  - `"ab"`：打开或创建二进制文件，以便在文件末尾写入（二进制模式创建或打开写入）
  - `"a+"`：打开或创建文本文件，以便在文件末尾读写更新（文本模式创建或打开读写更新）
  - `"a+b"\"ab+"`：打开或创建二进制文件，以便在文件末尾读写更新（二进制模式创建或打开读写更新）

- `"w"` 文件访问模式：
  - `"w"`：截断为零长度或创建用于写入的文本文件（文本模式创建或打开写入）
  - `"wb"`：截断为零长度或创建用于写入的二进制文件（二进制模式创建或打开写入）
  - `"w+"`：截断为零长度或创建用于读写更新的文本文件（文本模式创建或打开读写更新）
  - `"w+b"/"wb+"`：截断为零长度或创建用于读写更新的二进制文件（二进制模式创建或打开读写更新）

* `"wx` 文件访问模式： 
  - `"wx"`：创建文本文件以写入，文件存在则失败（文本模式创建写入）
  - `"wbx"`：创建二进制文件以写入，文件存在则失败（二进制模式创建写入）
  - `"w+x"`：创建文本文件以读写更新，文件存在则失败（文本模式创建读写更新）
  - `"w+bx"/"wb+x"`：创建二进制文件以读写更新，文件存在则失败（二进制模式创建读写更新）

> `fopen_s`

```c
errno_t fopen_s(FILE** _Stream, char const* _FileName, char const* _Mode);
```

- `fopen_s` 与 `fopen` 相同，文件打开成功时将控制流指针写入到 `_Stream`，并且在运行时检测下列错误，并调用当前安装的约束处理函数：
  - `_Stream` 或 `_Filename` 或 `_Mode` 是空指针。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
int main(void)
{
	FILE* my_file;
	errno_t err = 1;
#define m_filename  "myfile.txt"

#if _CRT_SECURE_NO_WARNINGS
	if (my_file = fopen(m_filename, "a"))  // 追加写入
		err = 0;
#else
	err = fopen_s(&my_file, m_filename, "a"); // 追加写入
#endif
	if (my_file && !err)
	{
		fprintf(my_file, "Hello world");
		fclose(my_file);
	}
    // 程序结束时会自动 fflush
}
```

<br>

#### freopen、freopen_s （重打开文件）

> `freopen`

```c
FILE *freopen(
    const char * restrict filename,
    const char * restrict mode,
    FILE * restrict stream
);
```

- `freopen` 首先尝试关闭与 `stream` 关联的文件，并忽略任何错误。如果 `filename` 非空，则尝试以 `mode` 模式打开文件（同 `fopen`）并将该文件与 `stream` 所指向的文件流关联。
- 如果 `filename` 为空指针，则函数尝试重新打开 `stream` 关联的文件，并尝试更改为 `mode` 指定的模式，是否允许模式改变则是实现定义的。

> `freopen_s`

```c
errno_t freopen_s(
    FILE *restrict *restrict newstreamptr,
    const char *restrict filename, 
    const char *restrict mode,
    FILE *restrict stream
);
```

- 同 `freopen` 一样，除了以 `fopen_s` 方式处理 `mode`，并将指向文件流的指针写入到 `newstreamptr`，运行时将检查各个指针是否为空的错误，并调用当前安装的约束处理函数。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    puts("stdout is printed to console");
    if (freopen("redir.txt", "w", stdout) == NULL)
    {
       perror("freopen() failed");
       return EXIT_FAILURE;
    }
    puts("stdout is redirected to a file"); // 写入 redir.txt
    fclose(stdout);
}
```

<br>

#### setvbuf、setbuf （设置文件缓冲区）

> `setvbuf`
```c
int setvbuf(FILE * restrict stream, char * restrict buf, int mode, size_t size);
```

- `setvbuf` 用于对 `stream` 设置一定大小的缓冲区。函数在设置成功时返回 0，失败时返回非零。
- 该函数只能在 `stream` 所指向的流与打开的文件关联之后，以及在对该流执行任何其他操作前之前使用。其中 `mode` 决定了 `stream` 将如何被缓冲：
  - `_IOFBF`（全缓冲）：当缓冲区为空时，从流读入数据；或者当缓冲区满时，向流写入数据。
  - `_IOLBF`（行缓冲）：每次从流中读入一行数据；或向流中写入一行数据。
  - `_IONBF`（无缓冲）：直接从流中读入数据或直接从流中写入数据，此时缓冲设置无效。

* `size` 的大小一般为 2 的倍数、页面大小的倍数。多数情况下，行缓冲仅对终端输入流可用。
* 若 `buf` 为空指针，则重新设定内部缓冲区的大小为 `size`；若 `buf` 不是空指针，则指示流使用始于 `buf` 大小为 `size` 的用户提供缓冲区。必须在 `buf` 生存期结束之前调用 `fclose` 关闭流。常见的错误是设置 `stdin` 或 `stdout` 的缓冲区为生存期在程序终止前就结束的数组：
* 在成功调用 `setvbuf` 之后，其他任何使用 `buf` 数组的行为都是未定义的。

```c
int main(void){
    char buf[BUFSIZ];
    setbuf(stdin, buf)
}
```

> `setbuf`

```c
void setbuf(FILE * restrict stream, char * restrict buf);
```

- `setbuf` 设置用于流操作的内部缓冲区，其长度应该为 `BUFSIZ` 个字符。`stream` 表示要设置缓冲区的文件流，`buf` 表示指向文件流所用的缓冲区的指针（若 `buf` 为空时，表示关闭缓冲，`setbuf` 可用于禁用要求立即输出的流的缓冲）。
- 若 `buf` 非空，等价于 `setvbuf(stream, buf, _IOFBF, BUFSIZ)`。
- 若 `buf` 为空，等价于 `setvbuf(stream, NULL, _IONBF, 0)`。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>

int main(void)
{
	setbuf(stdout, NULL);  // 设置标准输出流为无缓冲，输出流将立即出现在 stdout
	puts("IONBF stdout...");

	char buf[32];
	char scan[BUFSIZ];
	setvbuf(stdout, buf, _IOFBF, sizeof buf); // 设置标准输出流为全缓冲
	puts("IOFBF stdout...");
	if (scanf(" %s", scan)) {
		printf("input: %s\n", scan);
		fflush(stdout);
	}
	fclose(stdout);
}
```

---
### Functions：格式化输入与输出（Formatted input/output functions）

#### printf、fprintf、sprintf、snprintf （格式化输出）

```c
// 写入到 stdout
int printf(char const* const format, ...);                        
 // 写入到 _Stream
int fprintf(
    FILE* const stream, 
    char const* const format, ...); 
// 写入到 _Buffer
int sprintf(                        
    char* const str,
    char const* const format, ...); 
// 写入到 _Buffer，并且最多写入 _BufferCount-1 个字符
int snprintf(           
    char* const str, 
    size_t const size, 
    char const* const format, ...);
```

- `fprintf` 将输出写入到 `stream` 流中；`printf` 将输出写入到 `stdout`；`sprintf` 将输出写入到 `str` 字符串中；`snprintf` 最多写入 `size - 1` 个字符到 `str` 字符串中并以空终止符结尾。函数输出成功时返回输出的字符数目，发生错误时将返回负值。

- `format` 格式字符串由普通多字节和若干的转换说明构成，每个转换说明由 `%` 加格式标志构成。如果没有足够的格式参数，行为是未定义的；而转换说明被耗尽时，参数仍存在时也会计算多余的参数，并且会被忽略。

> *`format`* *中的转换说明规范*：

- 每个格式规范由字符 `%` 表示，在 % 之后，可以出现：
  - 修改转换规范的零个或多个标志（任何顺序）；
  - **可选的最小字符宽度**。转换值的字符少于字符宽度时用空格填充，字符宽度采用星号或者非负十进制整数的形式；
  - **可选的精度**。即给出 `d`、`i`、`o`、`u`、`x`、`X` 转换要出现的最小位数，`a`、`A`、`e`、`E`、`f`、`F` 转换要出现在小数点后的位数，`g`、`G` 转换的最大有效位数，`s` 转换要写入的最大字节数。其中精度采用句点 `.` 后跟星号或可选的非负十进制整数（只指定句点表示精度为 0）。如果精度与其他的转换说明符一起出现则行为未定义；
  - **可选的长度修饰符**，用于指定实参的大小；
  - **指定要应用的转换类型的转换说明符**。

* 字符的精度或宽度，都可以用 `*` 表示。此时需要提供一个 `int` 参数提供对应的数值，此时会插入一个宽度或精度参数到该转换说明符对应格式参数的位置之前。宽度提供负数表示左对齐的字符宽度；精度提供负数则精度将被忽略。

```c
printf("%*d", -5, 10);   // - 表示左对齐, 5 指定 %*d 的字符宽度至少为 5, 10 对应 "%d"
```

> *标志字符（flags）*：

- `-`：要求转换后的结果在字段内左对齐（未指定时右对齐），如 `"%-d"`、`"%-.2f"`、`"%-10s"`；
- `+`：数值转换结果显示符号字符，未指定时数值时仅在负值时显示符号，如 `"%+lu"`；
- ` `：空格，表示带符号转换不产生字符时，在结果前加一个空格（同时出现空格和 `+`，则忽略空格），如 `% d`；
- `#`：结果转换为替代模式。对于 `%#o` 转换，以强制结果的第一个数字为 0（`"%#o",9` = `"011"`，`"%#o",0` = `0`）；对于 `%#x` （或 `"&#X"`） 转换，非零结果带有 `"0x"` （或 `"0X"`） 前缀；对于 `a`，`A`，`e`，`E`，`f`、`F`、`g`、`G` 转换，转换浮点数的结果总是包含一个小数点符号（即使后面没有数字）。对于其他转换则行为未定义；
- `0`：对于 `d`、`i`、`o`、`u`、`x`、`X`、`a`、`A`、`e`、`E`、`f`、`F`、`g`、`G` 转换，使用前导零（在任何符号或基数指示之后）用于填充字符宽度，而不是用空格填充（除非是 NaN 或无穷大）。同时出现 `-` 和 `0` 则忽略前导零。对于 `d`、`i`、`o`、`u`、`x`、`X` 指定精度时，忽略前导零。对于其他的转换则行为未定义。

> *长度修饰符（length modifier）*：

- `hh`：指定 `d`、`i`、`o`、`u`、`x`、`X` 转换说明符适用于 `signed char` 或 `unsigned char` 参数并将其值转换为 `signed char` 或 `unsigned char`；对于 `hhn` 则应用 `signed char` 类型的指针参数。 
- `h`：指定 `d`、`i`、`o`、`u`、`x`、`X` 转换说明符适用于 `signed short` 或 `unsigned short` 参数；对于 `hn` 则应用 `signed short` 类型的指针参数。 
- `l`：指定 `d`、`i`、`o`、`u`、`x`、`X` 转换说明符适用于 `signed long` 或 `unsigned long` 参数；对于 `ln` 则应用 `signed long` 类型的指针参数；`lc` 则应用 `wint_t` 参数；`ls` 应用 `wchar_t` 类型的指针参数；对于浮点数的转换说明符则没有效果。
- `ll`：指定 `d`、`i`、`o`、`u`、`x`、`X` 转换说明符适用于 `signed long long` 或 `unsigned long long` 参数`；对于 `lln` 则应用 `signed long long` 类型的指针参数。 
- `j`：指定 `d`、`i`、`o`、`u`、`x`、`X` 转换说明符适用于 `intmax_t` 或 `uintmax_t` 参数；对于 `jn` 则应用 `intmax_t` 类型的指针参数。 
- `z`：指定 `d`、`i`、`o`、`u`、`x`、`X` 转换说明符适用于 `size_t` 或相应的有符号整数参数；对于 `zn` 则应用 `size_t` 类型的指针参数。 
- `t`：指定 `d`、`i`、`o`、`u`、`x`、`X` 转换说明符适用于 `ptrdiff_t` 或相应的无符号整数参数；对于 `zn` 则应用 `ptrdiff_t` 类型的指针参数。 
- `L`：指定 `a`、`A`、`e`、`E`、`f`、`F`、`g` 或 `G` 转换说明符应用 `long double` 类型参数。

> *转换说明符*

- `d`、`i`：`int` 参数转换成有符号十进制整数 *[-]dddd*。`%.*d` 精度指定要显示的最小位数，如果转换的位数不足则以前导 0 进行扩展（默认精度为 1，转换精度为 0 的零值 `%.d, 0` 结果是没有字符）。
- `o`、`u`、`x`、`X`：`unsigned int` 参数分别转换为 *dddd* 的无符号八进制 `o`、无符号十进制 `u`、无符号十六进制 `x` 或 `X`。精度指定要显示的最小位数，不足位数则以前导 0 填充。
- `f`、`F`：表示浮点数的 `double` 转换为十进制 *[-]ddd.ddd*。精度指定要显示的小数位数，未指定默认精度为 6，舍入方式是四舍五入。若精度为 0 且未指定 `#` 标志，则不显示小数点字符。对于无穷大，则显示 `[-]inf` 或 `[-]infinity`；NaN 则显示为 `[-]nan` 或 `[-]nan(n-char-sequence)` 则是实现定义的。`F` 则分别显示为 `INF`、`INFINITY`、`NAN`。
- `e`、`E`：表示浮点数的 `double` 转换为十进制 *[-]d.ddd±dd*。精度指定要显示的小数位数，未指定默认精度为 6，舍入方式为四舍五入。若精度为 0 且未指定 `#` 标志，则不显示小数点字符。`E` 则表示 `e[±dd]` 替换为 `E[±dd]`。指数总是至少包含两位数字，位数不足用零补齐。
- `g`、`G`：表示浮点数的 `double` 根据值和精度自动转换为 `e` 或 `f` 的样式。指定 $P$ 表示为精度，若精度未指定时 $P$ 为 6，精度为 0 时 $P$ 为 1。若带 `E` 的转换会有指数 $X$：若 $P$ > $X$ >= -4，转换为 `f` 的样式及精度 $P$ - 1 - $E$；否则为 `e` 风格及精度 $P$ - 1。
- `a`、`A`：表示浮点数的 `double` 转换为十六进制 P 计数法下的 *[-]0xh.hhhp±d*。精度指定要显示的小数位数，若精度为 0 且未指定 `#` 标志，则不显示小数点字符。若参数是正规化的浮点值，则首位数非 0。若值为 0，则指数为 0。指数总是至少包含一位数字。
- `c`：没有长度修饰符 `l` 则转换 `int` 参数为 `unsigned char`，并写入结果字符。若使用 `l` 修饰，则 `wint_t` 参数就像由一个没有精度的 `%ls` 转换规范和一个指向 `wchar_t[2]` 双元素数组的初始元素的参数进行转换，第一个元素包含指向 `lc` 转换规范的 `wint_t` 参数，第二个元素包含一个空宽字符。
- `s`：没有长度修饰符 `l` 则实参是指向字符类型数组的指针，数组中的字符写到空终止符 `\0`。精度指定写入字符的最大数目。未指定精度或精度大于数组的大小，则数组必须包含空终止符。若使用了长度修饰符 `l` 则参数必须是指向 `wchar_t` 数组。
- `p`：实参是指向 `void` 的指针。指针的值以实现定义的方式转换为一系列打印字符。
- `n`：实参应该是一个指向有符号整数的指针 `int *`，该指针表示调用 `fprintf` 到目前为止写入输出流的字符数。该转换符不会转换任何类型，但是会占用一个格式参数（必须是 `int *`），并且会将当前位置的字符数结果被写入到参数中。规范不可包含任何标志，宽度，精度。
- `%`：`%%` 打印一个 `"%"` 百分号。没有参数被转换。

* 对于 `e`、`E`、`f`、`F`、`g` 和 `G` 转换，有效十进制位数的数量最多是 `DECIMAL_DIG`，那么结果应该是正确的四舍五入。如果有效十进制位数的数量多于 `DECIMAL_DIG`，但是源值可以用 `DECIMAL_DIG` 数字精确地表示，那么结果应该是带末尾零的精确表示。

> *格式转换案例*

```c
#include <stdio.h>
 
int main(void)
{
    printf("%s", "Strings:\n");
    const char s[] = "Hello";
    printf("\t.%10s.\n\t.%-10s.\n\t.%*s.\n", s, s, 10, s);
 
    printf("Characters:\t%c %%\n", 65);
 
    printf("%s", "Integers\n");
    printf("Decimal:\t%i %d %.6i %i %.0i %+i %u\n", 1, 2, 3, 0, 0, 4, -1);
    printf("Hexadecimal:\t%x %x %X %#x\n", 5, 10, 10, 6);
    printf("Octal:\t%o %#o %#o\n", 10, 10, 4);
 
    printf("%s", "Floating point\n");
    printf("Rounding:\t%f %.0f %.32f\n", 1.5, 1.5, 1.3);
    printf("Padding:\t%05.2f %.2f %5.2f\n", 1.5, 1.5, 1.5);
    printf("Scientific:\t%E %e\n", 1.5, 1.5);
    printf("Hexadecimal:\t%a %A\n", 1.5, 1.5);
}
/*
Strings:
    .     Hello.
    .Hello     .
    .     Hello.
Characters:     A %
Integers
Decimal:        1 2 000003 0  +4 4294967295
Hexadecimal:    5 a A 0x6
Octal:          12 012 04
Floating point
Rounding:       1.500000 2 1.30000000000000004440892098500626
Padding:        01.50 1.50  1.50
Scientific:     1.500000E+00 1.500000e+00
Hexadecimal:    0x1.8p+0 0X1.8P+0
*/
```

> `printf_s`、`fprintf_s`、`sprintf_s`、`snprintf_s`

```c
// 写入到 stdout
int printf_s(char const* const format, ...);                        
 // 写入到 _Stream
int fprintf_s(
    FILE* const stream, 
    char const* const format, ...); 
// 写入到 _Buffer
int sprintf_s(                        
    char* const str,
    size_t const size, 
    char const* const format, ...); 
// 写入到 _Buffer，并且最多写入 _BufferCount-1 个字符
int snprintf_s(           
    char* const str, 
    size_t const size, 
    char const* const format, ...);
```

- 这些 `xxxx_s` 函数同对应的 `xxxx` 函数，运行时将检测下列错误，并调用当前安装的约束处理函数：
  - `format` 中存在转换说明符 `%n`；
  - `%s` 对应的参数是空指针；
  - `format` 或 `str` 是空指针；
  - `size` 为 0 或超出 `size_t` 的范围；
  - 在任何一个字符串及字符转换说明符中出现编码错误；
  - 对于 `sprintf_s` 中存储于 `str` 的字符串超过 `size` 的大小。

<br> 

#### vprintf、vfprintf、vsprintf、vsnprintf （使用可变参数列表的格式化输出）

```c
// vxxxx
int vprintf(char const* const format, va_list vlist);                        
int vfprintf(FILE* const stream, char const* const format, va_list vlist); 
int vsprintf(char* const str, char const* const format, va_list vlist); 
int vsnprintf(char* const str, size_t const size, char const* const format, va_list vlist);

// vxxxx_s
int vprintf_s(char const* const format, va_list vlist);                        
int vfprintf_s(FILE* const stream, char const* const format, va_list vlist); 
int vsprintf_s(char* const str, size_t const size, char const* const format, va_list vlist); 
int vsnprintf_s(char* const str, size_t const size, char const* const format, va_list vlist);
```

- `vxxxx` 与对应 `xxxx` 输出函数不同的是，格式参数列表从 `va_list` 的位置加载数据。

```c
// MSVC
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#define DEBUG_BUFSIZ 2048
char buf[DEBUG_BUFSIZ];

void debug_log(const char* fmt, ...)
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	char time_buf[100];
	size_t rc = strftime(time_buf, sizeof time_buf, "%D %T", gmtime(&ts.tv_sec));
	snprintf(time_buf + rc, sizeof time_buf - rc, ".%06ld UTC", ts.tv_nsec / 1000);

	va_list args1;
	va_start(args1, fmt);
	va_list args2;
	va_copy(args2, args1);
	size_t bufsize = vsnprintf(NULL, 0, fmt, args1) + 1;  // vsnprintf
	va_end(args1);
	vsnprintf(buf, bufsize, fmt, args2);
	va_end(args2);

	printf("%s [debug]: %s\n", time_buf, buf);
}

int main(void)
{
	debug_log("Logging, %d, %d, %d", 1, 2, 3);
}
// 09/23/23 18:44:31.402615 UTC [debug]: Logging, 1, 2, 3
```

<br>

#### scanf、fscanf、sscanf （格式化输入）

```c
// 从 stdin 读取
int scanf(char const* const format, ...);        
// 从 stream 读取                   
int fscanf(FILE* const stream, char const* const format, ...); 
// 从 str 读取
int sscanf(char const* const str, char const* const format, ...); 
```

- `scanf` 从 `stdin` 读取数据；`fscanf` 从文件流 `stream` 中读取数据；`sscanf` 从空终止的字符串 `str` 中读取数据。函数返回赋值成功的次数，若第一次转换完成之前发生输入失败，函数返回 `EOF`。

- `format` 指定可接受的输入序列以及如何将它们转换为赋值，并使用后续对应参数作为指向对象的指针来接收转换后的输入。没有足够的格式参数则行为是未定义的。多余的参数仍会计算但是会被忽略。


> *format 中的转换说明规范：*

- 格式字符串由下列内容组成：
  - **非空白多字节字符**，除了 `%`：每个格式字符串中的这种字符处理来自输入流的准确同一字符，或若它与流的下个字符比较不相等则导致函数失败。
  - **空白符**：任何格式字符串中的单个空白符处理所有来自输入的可用连续空白符（符合 `isspace` 规定）。格式字符串中 `"\n"`、`" "`、`"\t\t"` 或其他空白无区别。
  - **转换规范**：转换规范由字符 `%` 表示，在 `%` 之后，依次出现以下内容：
    - 可选的赋值抑制字符 `*`；
    - 可选的大于零的十进制整数，指定最大字符宽度（如不提供宽度，`%s`、`%[` 可能会导致缓冲区溢出）；
    - 可选的长度修饰符，指定接收对象的类型大小；
    - 指定要应用的转换类型的转换说明符。

* 格式输入函数会依次执行该格式的每个指令。当所有的指令都被执行完，或其中一个指令失败时，函数返回。失败被描述为输入失败（编码错误或输入字符不可用）或匹配失败（不适当的输入）。
* 空白字符不被读取，除非有指令匹配。

> *长度修饰符*：

- `hh`：指定 `d`、`i`、`o`、`u`、`x`、`X` 或 `n` 应用于类型指针指向 `signed char` 或 `unsigned char` 的实参。
- `h`：指定 `d`、`i`、`o`、`u`、`x`、`X` 或 `n` 应用于类型指针指向 `signed short` 或 `unsigned short` 的实参。
- `l`：指定 `d`、`i`、`o`、`u`、`x`、`X` 或 `n` 适用于类型指针指向 `long int` 或 `unsigned long` 的实参；指定 `a`、`A`、`e`、`E`、`f`、`F`、`g` 或 `G` 适用于类型指针指向 `double` 的实参；指定的 `c`、`s` 或 `[` 转换说明符应用于类型指针指向 `wchar_t` 的实参。
- `ll`：指定 `d`、`i`、`o`、`u`、`x`、`X` 或 `n` 应用于类型指针指向 `long long` 或 `unsigned long long` 的实参。
- `j`：指定 `d`、`i`、`o`、`u`、`x`、`X` 或 `n` 应用于类型指针指向 `intmax_t` 或 `uintmax_t` 的实参。
- `z`：指定 `d`、`i`、`o`、`u`、`x`、`X` 或 `n` 应用于类型指针指向 `size_t` 或相应的有符号整数类型的实参。
- `t`：指定 `d`、`i`、`o`、`u`、`x`、`X` 或 `n` 应用于类型指针指向 `ptrdiff_t` 或相应的无符号整数类型。
- `L`：指定的 `a`、`A`、`e`、`E`、`f`、`F`、`g` 或 `G` 应用于类型指针指向 `long double` 的实参。

> *转换说明符*：

- `d`：匹配一个可选的带符号十进制整数，对应的实参是一个指向有符号整数的指针。
- `i`：匹配一个可选的带符号整数，对应的实参是一个指向有符号整数的指针。
- `o`：匹配一个可选的带符号八进制整数，对应的实参是一个指向无符号整数的指针。
- `u`：匹配一个可选的带符号十进制整数，对应的实参是一个指向无符号整数的指针。
- `x`：匹配一个可选的带符号十六进制整数，对应的实参是一个指向无符号整数的指针。
- `a`、`e`、`f`、`g`：匹配可选的带符号浮点数、infinity、NaN。对应的实参是一个指向浮点类型的指针。
- `c`：匹配正好指定字段宽度的字符序列（未指定字段宽度则为 1）。若没有长度修饰符，对应的参数是一个足够容纳字符序列的初始元素 `char` 数组的指针，不会添加空终止符。若存在 `l` 修饰，则输入应该是一个从初始移位状态开始的多字节字符序列，每个多字节字符被转换为宽字符。对应的实参应该是指向 `wchar_t` 数组初始元素的指针，不会添加宽空终止符。
- `s`：匹配非空白字符序列。若没有长度修饰，对应的参数是一个指向足够大的初始元素 `char` 数组的指针，该数组可以容纳序列和一个空终止符（null 字符被自动添加）。若存在 `l` 则输入应该是一个从初始移位状态开始的多字节字符序列，每个多字节被转换为宽字符。对应的实参应该是指向 `wchar_t` 数组初始元素的指针，宽空终止符会被自动添加
- `[`：匹配一个来自集合的字符的非空字符序列。若集合的首字符是 `^`，则匹配所有不在集合中的字符。若集合以 `]` 或 `]^` 开始，则 `]` 字符包含在集合中。`-` 可以指示范围（如 `[0-9]`）。`l` 修饰表示使用宽字符序列和数组。空终止符会被自动添加。
- `p`：匹配定义一个指针的实现定义的字符序列。该序列集应与 `fprinf` 的 `%p` 转换可能产生的序列集相同。对应的实参是指向指向 `void` 的指针的指针（`void **`）。
- `n`：返回已读取的字符数，且不消耗输出。执行 `%n` 指令不会增加 `scanf` 系列函数的赋值次数。
- `%%`：匹配单个字符 `'%'`。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stddef.h>
#include <locale.h>

int main(void)
{
	int i, j;
	float x, y;
	char str1[10], str2[4];
	wchar_t warr[2];
	setlocale(LC_ALL, "en_US.utf8");

	char input[] = "25 54.32E-1 Thompson 56789 0123 56ß水";
	/* 按下列分析：
	   %d ：整数
	   %f ：浮点值
	   %9s ：最多有 9 个非空白符的字符串
	   %2d ： 2 位的整数（数位 5 和 6 ）
	   %f ：浮点值（数位 7 、 8 、 9）
	   %*d ：不存储于任何位置的整数
	   ' ' ：所有连续空白符
	   %3[0-9] ：至多有 3 个十进制数字的字符串（数位 5 和 6 ）
	   %2lc ：二个宽字符，使用多字节到宽转换  */
	int ret = sscanf(input, "%d%f%9s%2d%f%*d %3[0-9]%2lc",
		&i, &x, str1, &j, &y, str2, warr);

	printf("Converted %d fields:\ni = %d\nx = %f\nstr1 = %s\n"
		"j = %d\ny = %f\nstr2 = %s\n"
		"warr[0] = U+%x warr[1] = U+%x\n",
		ret, i, x, str1, j, y, str2, warr[0], warr[1]);

	int n = sscanf_s(input, "%d%f%s", &i, &x, str1, (unsigned)sizeof(str1));
	// 写 25 到 i ， 5.432 到 x ， 9 个字节 "thompson\0" 到 str1 ，和 3 到 n 。
}
```

> `scanf_s`、`fscanf_s`、`sscanf_s`

```c
// 从 stdin 读取
int scanf(char const* const format, ...);        
// 从 stream 读取                   
int fscanf(FILE* const stream, char const* const format, ...); 
// 从 str 读取
int sscanf(char const* const str, char const* const format, ...); 
```

- `xxxx_s` 与对应的 `xxxx` 相同，除了 `%c`、`%s` 及 `%[` 转换指示符要求二个参数。`%c` 读取单个字符可以设置第二个 size 参数为 1。
- 这些函数在运行时检测下列错误，并调用当前安装的约束处理函数：
  - 任何指针类型的参数是为空指针；
  - `format`、`stream` 或 `str` 为空指针；
  - `%c`、`%s` 或 `%[` 写入的字符数加上空终止字符的长度，超过提供给这些转换指示符的第二个 size_t 参数；
  - 可选，任何其他可检测错误，例如未知转换指示符。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>

int main(void)
{
	char input[] = "hello world, 666";

	char str1[6], str2[6];
	int num;
	
	int n = sscanf_s(input, "%5s%5s,%d", str1, 6, str2, 6, &num);
	printf("scanf_s count [%d] : %s %s, %d\n", n, str2, str1, num);
}
// scanf_s count [3] : world hello, 666
```

<br>

#### vscanf、vfscanf、vsscanf （使用可变参数列表的格式化输入）

```c
// vxxxx
int vscanf(char const* const format, va_list vlist);                        
int vfscanf(FILE* const stream, char const* const format, va_list vlist); 
int vsscanf(char* const str, char const* const format, va_list vlist); 

// vxxxx_s
int vscanf_s(char const* const format, va_list vlist);                        
int vfscanf_s(FILE* const stream, char const* const format, va_list vlist); 
int vssanf_s(char* const str, char const* const format, va_list vlist); 
```

- `vxxxx` 与对应 `xxxx` 输入函数不同的是，格式参数列表从 `va_list` 的位置加载数据。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

bool checked_sscanf(int count, const char* buf, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int rc = vsscanf(buf, fmt, ap);
    va_end(ap);
    return rc == count;
}

int main(void)
{
    int n, m;

    printf("Parsing '1 2'...");
    if (checked_sscanf(2, "1 2", "%d %d", &n, &m))
        puts("success");
    else
        puts("failure");

    printf("Parsing '1 a'...");
    if (checked_sscanf(2, "1 a", "%d %d", &n, &m))
        puts("success");
    else
        puts("failure");
}
/*
Parsing '1 2'...success
Parsing '1 a'...failure
*/
```

---
### Functions：字符输入和输出（Character input/output functions）
#### putc、fputc、putchar （输出字符）

```c
int putc(int c, FILE *stream);      // 输出到 stream
int fputc(int c, FILE *stream);     // 输出到 stream
int putchar(int c);                 // 输出到 stdout
```

- `fputc` 函数将 `c` 转换为 `unsigned char` 并写入到 `stream` 所指向的输出流中。`putc` 等价于 `fputc`，`putc` 可以是采用宏的方式实现，参数可能会被调用多次，因此参数不能有副作用。`putchar` 等价于 `putc(c, stdout)`。
- 三个函数输出成功时返回 `c`，失败时返回 `EOF` 并设置相关输出流上的错误指示器 `ferrer`。

```c
#include <stdio.h>

int main(void)
{
	fputc('C', stdout);
	putc(' ', stdout);
	putchar('C');
}
```

<br>

#### getc、fgetc、getchar （读取字符）

```c
int getc(FILE *stream);             // 输入到 stream
int fgetc(FILE *stream);            // 输入到 stream
int getchar(void);                  // 输入到 stdin
```

- `fgetc` 从给定的输入流中读取下一个字符，并将其作为 `unsigned char` 类型获取并转换为 `int`，转换失败时返回 `EOF`。`getc` 等价于 `fgetc`，`getc` 可以是采用宏的方式实现，参数可能会被调用多次，因此参数不能有副作用。`getchar` 等价于 `getc(stdin)`。
- 三个函数成功时返回字符转换 `int` 的值，失败则返回 `EOF`。若是到达文件尾导致失败则设置相关输入流上的文件尾指示器 `feof`。若是其他错误导致失败则设置相关输入流的错误指示器 `ferror`。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>

int main(void)
{
#define filename "test.txt"
	FILE* f = fopen(filename, "w");
	fputs("hello world", f);
	if (freopen(filename, "r", f)) {
		int c1 = fgetc(f);
		int c2 = getc(f);
		printf("get chars : %c %c", c1, c2);
	}
}
```

<br>

#### puts、fputs （输出字符串）

```C
int fputs(const char * restrict s, FILE * restrict stream);   // 输出字符串到 stream
int puts(const char *s);        // 输出字符串到 stdout
```

- `fputs` 函数将 `s` 指向的字符串写入到 `stream` 所指向的流中。不写入字符串结尾的 null 字符。
- `puts` 函数将 `s` 指向的字符串及追加的换行符写入到 `stdout`。不写入字符串结尾的 null 字符
- 这些函数在输出成功后返回非负数，失败时返回 `EOF` 并设置关联流的错误指示器（`ferror`）。

```c
#include <stdio.h>

int main(void)
{
	fputs("hello ", stdout);
	puts("world");
}
// hello world
```

<br>

#### gets、gets_s、fgets （读取字符串）

```c
// C11 起 gets 被移除
char * gets(char* str);

char * gets_s(char * str, rsize_t size);
char *fgets(char * restrict str, int n, FILE * restrict stream);
```

- `gets` 从 `stdin` 读取字符存储到 `str` 所指向的字符数组，直到发现换行符或文件尾。在读入数组的最后一个字符后立即写入空字符。换行符被舍弃，但不会存储于缓冲区中。
- `gets_s` 从 `stdin` 读取字符直到发现换行符或文件尾，最多写入 `n-1` 个字符到 `str` 指向的字符数组，并始终在末尾写入空终止符（除非 `str` 是空指针）。若发现换行符，将被舍弃并且不会将它计入写入缓冲区的字符数。`gets_s` 在运行时检查错误并调用当前安装的制约处理函数：`n` 为 0 或大于 `RSIZE_MAX`、`str` 是空指针、写入 `n-1` 个字符到缓冲区后仍未遇到换行符或文件尾。
- `fgets` 从 `stream` 读取最多 `n-1` 个字符到 `str` 所指的字符数组中。在换行符（保留）或文件尾之后停止读取字符。在读入数组的最后一个字符之后立即写入空终止符。
- 这些函数在成功读取后返回 `str`，失败时则为空指针。失败的原因是遇到文件尾失败则设置相关流上的文件尾指示器（`feof`），此时返回空指针且不改变 `str` 的内容；若是其他错误则设置相关流上的错误指示器（`ferror`），`str` 上的内容不确定。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE* tmpf = tmpfile();
    fputs("Alan Turing\n", tmpf);
    fputs("John von Neumann\n", tmpf);
    fputs("Alonzo Church\n", tmpf);

    rewind(tmpf);

    char buf[8];
    while (fgets(buf, sizeof buf, tmpf) != NULL)
        printf("\"%s\"\n", buf);

    if (feof(tmpf))
        puts("End of file reached");
}
```

<br>

#### ungetc 

```c
int ungetc(int c, FILE *stream);
```

- 若 `c` 不等于 `EOF`，则将 `c` 转译为 `unsigned char` 并推入到流 stream 关联的缓冲区，方式满足从 `stream` 的后继读取操作将取得该字符。函数不修改与流相关的外部设备。
- 如果 `c` 的值等于宏 `EOF` 的值，则操作失败，输入流保持不变。

* 文件定位函数（`fseek`、`fsetpos`、`rewind`）的成功调用会丢弃流的所有回推字符（弃去 `ungetc` 的效果）。 
- 保证一个字符的推退。如果在同一流上调用 `ungetc` 函数多次而没有在该流上进行中间的读取或文件定位操作，则操作可能会失败。

* 成功调用 `ungetc` 函数将清除流的文件结束指示符。在读取或丢弃所有推入字符后，流的文件位置指示符的值应与字符被推入之前的值相同。
  - 在文本流上对 `ungetc` 的成功调用以未指定方式修改流位置指示器，但保证在以读取操作取得所有回放字符后，流位置指示器等于其在 `ungetc` 之前的值。
  - 在二进制流上对 `ungetc` 的成功调用将流位置指示器减 1（若流位置指示器为零，则行为不确定）。

- 函数在成功时返回 `c`。失败时返回 `EOF`，而给定的流保持不变。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <ctype.h>
#include <stdio.h>

void demo_scanf(const char* fmt, FILE* s) {
    if (*fmt == '%') {
        int c;
        switch (*++fmt) {
        case 'u': while (isspace(c = getc(s))) {} // 跳过空白符
                unsigned int num = 0;
                while (isdigit(c)) {
                    num = num * 10 + c - '0';
                    c = getc(s);
                }
                printf("%%u scanned %u\n", num);
                ungetc(c, s); // 重处理非数字，x 字符回推回 stream
        case 'c': c = getc(s);
            printf("%%c scanned '%c'\n", c);
        }
    }
}

int main(void)
{
    FILE* f = fopen("input.txt", "w+");
    fputs("123x", f);
    rewind(f);
    demo_scanf("%u%c", f);
    fclose(f);
}
/*
%u scanned 123
%c scanned 'x'
*/
```

---
### Functions：直接输入和输出（Direct input/output functions）

#### fread （从文件读取）

```c
size_t fread(void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);
```

- `fread` 函数从 `stream` 中读取最多 `nmemb` 个元素到数组 `ptr` 中。这些元素的大小由 `size` 指定。对于每个对象，调用 `size` 次 `fgetc`，并将结果按照读取的顺序存储在刚好覆盖该对象的 `unsigned char` 数组中。流的文件位置指示器按成功读取的字符数递增。
- 如果发生错误，则流的文件位置指示器的结果值是不确定的。如果读取部分元素，则其值不确定。

- `fread` 函数返回成功读取的元素数，如果遇到读取错误或文件结束，该元素数可能小于 `nmemb`。如果 `size` 或 `nmemb` 为零，则 `fread` 返回零，数组的内容和流的状态保持不变。
- `fread` 不区别文件尾和错误，而调用者必须用 `feof` 和 `ferror` 鉴别出现者为何。

<br>

#### fwrite （写入到文件）

```c
size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);
```

- `fwrite` 函数将最多 `nmemb` 个大小为 `size` 元素写入到 `stream` 关联的流中。对于每个对象，调用 `size` 次 `fputc` 以正好覆盖该对象的 `unsigned char` 数组按顺序读取值并写入到 `stream`。流的文件位置指示器按成功写入的字符数递增。
- 如果发生错误，流的文件位置指示的结果值是不确定的。
- `fwrite` 函数返回成功写入的元素数，只有在遇到写入错误时才会小于 `nmemb`。如果 `size` 或 `nmemb` 为零，`fwrite` 返回零，流的状态保持不变。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <assert.h>

enum { SIZE = 5 };
int main(void)
{
	double a[SIZE] = { 1.,2.,3.,4.,5. };
	double b[SIZE];

	FILE* fp = fopen("test.bin", "wb");		// 必须用二进制模式
	fwrite(a, sizeof * a, SIZE, fp);		// 写 double 的数组
	fp = freopen("test.bin", "rb", fp);
	assert(fp);

	size_t ret_code = fread(b, sizeof * b, SIZE, fp); // 读 double 的数组
	if (ret_code == SIZE) {
		puts("Array read successfully, contents: ");
		for (int n = 0; n < SIZE; ++n) printf("%f ", b[n]);
		putchar('\n');
	}
	else { // error handling
		if (feof(fp))
			printf("Error reading test.bin: unexpected end of file\n");
		else if (ferror(fp))
			perror("Error reading test.bin");
	}
	fclose(fp);
}
/*
Array read successfully, contents: 
1.000000 2.000000 3.000000 4.000000 5.000000
*/ 
```

---
### Functions：文件定位（File positioning functions）

#### ftell （位置指示器的位置）

```c
long int ftell(FILE *stream);
```

- `ftell` 获取流 `stream` 的文件位置指示器：
  - 对于二进制流，函数返回从文件开始的字节数。
  - 对于文本流，它的文件位置指示器包含未指定的信息，且仅若作为 `fseek` 的输入才有意义。

- 函数在成功时返回文件位置指示器，失败则返回 `-1L` 并设置 `errno` 对象为实现定义的正值。
- `ftell` 返回的值可能无法反映以文本模式打开的流的物理字节偏移量，因为文本模式会导致回车换行转换。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
int main(void)
{
	double A[SIZE] = { 1.,2.,3.,4.,5. };
	double Buf[SIZE] = { 0 };
	FILE* fp = fopen("test.bin", "wb");     // 写入数组到文件。
	fwrite(A, sizeof(double), SIZE, fp);
	printf("Current pos : %ld\n", ftell(fp));
	int rt_code = 0;
	if (freopen("test.bin", "rb", fp)) {
		int rt_code = fread(Buf, sizeof(double) * 1L, 1, fp);
		printf("Current pos : %ld\n", ftell(fp));
	}
	return EXIT_SUCCESS;
}
/*
Current pos : 40
Current pos : 8
*/
```

<br>

#### fseek （设置位置指示器的位置）

```c
int fseek(FILE *stream, long int offset, int origin);
```

- `fseek` 函数用于设置文件流 `stream` 的文件位置指示器为 `offset` 所指向的值。`origin` 的值是 `SEEK_SET`、`SEEK_CUR`、`SEEK_END` 之一。函数成功时为 ​0​，否则为非零。

* 对于二进制流，新位置（从文件开始以字符为单位测量）是从通过向 `origin` 指定的位置添加偏移量来获得的：
  - 当 `origin` 为 `SEEK_SET`，则指定的位置是文件的开始。
  - 当 `origin` 为 `SEEK_CUR`，则指定的位置是文件位置指示器的当前值。
  - 当 `origin` 为 `SEEK_END`，则指定的位置是文件的结尾（不要求二进制流支持 `SEEK_END`）。

- 对于文本流，`offset` 要么为零（可用于任何的 `origin` 值），要么为先前在与同一文件关联的流上成功调用 `ftell` 函数所返回的值（且仅可用 `SEEK_SET` 的 `origin`）。

* 若 `stream` 为宽面向，则一同应用对文本和二进制流的限制：
  - `ftell` 的结果作为 `offset` 与 `SEEK_SET` 一同使用；
  - 零值的 `offset` 和 `SEEK_SET` 或 `SEEK_CUR` 而非 `SEEK_END` 一同使用。

- 确定新位置后，对`fseek` 的成功调用将撤销 `ungetc` 的效果并清除文件尾状态。在 `fseek` 调用成功之后，更新流上的下一个操作可能是输入或输出。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
int main(void)
{
	double A[SIZE] = { 1.,2.,3.,4.,5. };
	FILE* fp = fopen("test.bin", "wb");     // 写入数组到文件。
	fwrite(A, sizeof(double), SIZE, fp);
	fclose(fp);

	double B[SIZE];
	fp = fopen("test.bin", "rb");

	// 设置文件位置指示器到第三个浮点值之前。
	if (fseek(fp, sizeof(double) * 2L, SEEK_SET))  // 从文件开头向右偏移
	{
		perror("fseek()");
		exit(EXIT_FAILURE);
	}

	// 读取一个浮点值
	int ret_code = fread(B, sizeof(double), 1, fp);
	printf("read double : %.1f\n", B[0]);
	printf("Current pos : %d\n", ftell(fp));	// 读取当前指示器的位置

	if (fseek(fp, 0, SEEK_SET))		// 指示器设置到开头
	{
		perror("fseek()");
		exit(EXIT_FAILURE);
	}else
	printf("Current pos : %d\n", ftell(fp));

	fclose(fp);
	return EXIT_SUCCESS;
}
```

<br>

#### rewind （指示器置于文件首）

```c
void rewind(FILE *stream);
```

- `rewind` 函数将 `stream` 指向的流的文件位置指示器设置为文件的开头。相当于 `fseek(stream, 0L, SEEK_SET)`。此外，`rewind` 会清除流的错误指示器和文件结束指示器。`rewind` 也会消除 `ungetc` 效果。
- 若要清除键盘缓冲区，请将 `rewind` 与流 `stdin` 一起使用，后者默认与键盘相关联。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
int main(void)
{
	FILE* file = fopen("test.txt", "wb+"); // 读写模式
	char str[] = "Hello world";
	char s_read[BUFSIZ];
	fputs(str, file);
	printf("The file position indicator = %d\n", ftell(file));
	rewind(file);
	if (fscanf(file, "%s", s_read))
	{
		printf("file content : %s\n", s_read);
		printf("The file position indicator = %d\n", ftell(file));
	}
}
```

<br>

#### fgetpos、fsetpos （获取或恢复指示器位置信息）

```c
int fgetpos(FILE * restrict stream, fpos_t * restrict pos);
int fsetpos(FILE *stream, const fpos_t *pos);
```

- `fgetpos` 函数存储文件流 `stream` 的多字节分析状态的当前值（若存在）和文件位置指示器到 `pos` 所指向对象中。存储的值 `pos` 可用于 `fsetpos` 函数参数，表示将 `stream` 流重新定位到调用 `fgetpos` 函数时的位置。
- `fsetpos` 按照 `pos` 所指向的值，设置文件流 `stream` 的文件位置指示器和多字节分析状态（若存在）。调用此函数还会撤销 `ungetc` 的效果，同时也会清除文件尾状态（`feof`）。若读或写出现错误，则设置流的错误指示器（`ferror`）。

* 函数调用成功，则返回零；如果失败，函数返回非零值，并在 `errno` 中存储实现定义的正值。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
#define SIZE 5
	double A[SIZE] = { 1.,2.,3.,4.,5. };
	double B[SIZE];

	FILE* fp = fopen("test.bin", "wb");
	fwrite(A, sizeof(double), SIZE, fp);
	fp = freopen("test.bin", "rb", fp);

	fpos_t pos;
	if (fgetpos(fp, &pos) != 0)      /* 保存当前位置：文件起始 */
	{
		perror("fgetpos()");
		exit(EXIT_FAILURE);
	}
	int ret_code = fread(B, sizeof(double), 1, fp); /* 读取一个浮点值 */
	printf("%.1f\n", B[0]);   /* 打印一个浮点值 */

	if (fsetpos(fp, &pos) != 0 && ferror(fp))   /* 恢复未读取前的文件位置 */
	{
		perror("fsetpos()");
		exit(EXIT_FAILURE);
	}

	ret_code = fread(B, sizeof(double), 1, fp); /* 重读首个浮点值 */
	printf("%.1f\n", B[0]);                   
	fclose(fp);
}
```

---
### Functions：错误处理函数（Error-handling functions）
#### feof （检查文件尾）

```c
int feof(FILE *stream);
```

- `feof` 函数用于检查是否到达给定文件流的结尾。当且仅当为流设置了文件结束指示符时，`feof` 函数返回非零。例如，若最近一次 I/O 是抵达文件最后字节的 `fgetc`，则 `feof` 返回零。下个 `fgetc` 失败并更改流状态为文件尾，然后 `feof` 才返回非零。

<br>

#### ferror （检查文件错误）

```c
int ferror(FILE *stream);
```

- `ferror` 函数测试流所指向的流的错误指示器。返回当且仅当为流设置了错误指示符时，`ferror` 函数返回非零，否则为零。

<br>

#### perror （打印当前错误）

```c
void perror(const char *s);
```

- `perror` 函数用于打印当前存储于系统变量 `errno` 的错误码到 `stderr` 标准错误流中。如果 `s` 不是空字符或空指针，`s` 所指的字符串后随 `": "` 和一个适当的错误消息字符串（若为空则仅打印错误信息字符串），并自动附加一个换行符。错误消息字符串的内容等同于 `strerror(error)` 的结果。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
int main(void)
{
    FILE *f = fopen("non_existent", "r");
    if (f == NULL) perror("fopen() failed");
    else fclose(f);
}
```

<br>

#### clearerr （清除错误）

```c
void clearerr(FILE* stream);
```

- `clearerr` 函数清除由 `stream` 指向的流的文件结束指示器（`feof`）和错误指示符（`ferror`）。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
    FILE* tmpf = tmpfile();
    fputs("abcde\n", tmpf);
    rewind(tmpf);
    int ch;
    while ((ch = fgetc(tmpf)) != EOF)
        printf("%c", ch);
    assert(feof(tmpf)); // 此循环期待以 eof 终止，返回非零
    puts("End of file reached");
    clearerr(tmpf);  // 清除 eof

    if (feof(tmpf)) // 被清除，返回 0
        puts("EOF indicator set");
    else
        puts("EOF indicator cleared\n");
}
/*
abcde
End of file reached
EOF indicator cleared
*/
```

---