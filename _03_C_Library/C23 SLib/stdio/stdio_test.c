#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

void test_tmpfile()
{
    FILE *stream;
    char tempstring[] = "String to be written";
    int i;
    errno_t err;

    // Create temporary files.
    for (i = 0; i <= 520; i++)
    {
        err = tmpfile_s(&stream);
        if (err)
            perror("Could not create or open new temporary file\n");
        else
            printf("Temporary file %d was created and opened\n", i);
    }
    // Remove temporary files.
    printf("%d temporary files deleted\n", _rmtmp());
}

void test_tmpnam_s()
{
    char tmpname[L_tmpnam_s];
    if (tmpnam_s(tmpname, sizeof tmpname))
    {
        perror("Could not open new temporary file\n");
        return;
    }
    else
        printf("temporary file tmpname: %s\n", tmpname);

    FILE *fp = fopen(tmpname, "w"); // 创建文件
    if (!fp)
    {
        perror(tmpname);
        return;
    }
    fprintf(fp, "hello world"); // 写入到 "tmp"
    fclose(fp);

    int rc = rename(tmpname, "newName"); // 重命名
    if (rc)
    {
        perror("rename");
        return;
    }

    fp = fopen("newName", "r");
    if (!fp)
    {
        perror("fopen");
        return;
    }
    char buf[70];
    printf("%s\n", fgets(buf, sizeof buf, fp)); // 从 "newName" 读取
    fclose(fp);

    if (remove("newName"))
        perror("remove");
}

void test_fclose()
{
    FILE *fp = fopen("test.txt", "wb+");
    if (!fp)
        perror("File opening failed");
    int c;                         // 注意：int，非char，要求处理 EOF
    while ((c = fgetc(fp)) != EOF) // 标准 C I/O 读取文件循环
        putchar(c);

    if (ferror(fp))
        puts("I/O error when reading");
    else if (feof(fp))
        puts("End of file reached successfully");

    if (!fclose(fp))
        puts("Close file successfully");
    remove("test.txt");
}

void test_fflush()
{
    int *crash_the_program = 0;
    FILE *my_file;
    if (!fopen_s(&my_file, "myfile.txt", "w"))
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
        // 所有文件在正常终止时自动关闭和刷新。
        fclose(my_file);
    }
}

void test_freopen()
{
#define m_filename "myfile.txt"
    FILE *my_file;
    if (!fopen_s(&my_file, m_filename, "a")) // 追加写入
        fprintf(my_file, "Hello world");

    if (!freopen(m_filename, "r", my_file))
    {
        perror("freopen() failed");
        return;
    }
    char buf[70] = {0};
    fread(buf, sizeof(char), 69, my_file);
    printf("%s", buf);
    // 程序结束时会自动 fflush 并关闭
    fclose(my_file);
}

void test_setbuf()
{
    setbuf(stdout, NULL); // 设置标准输出流为无缓冲，输出流将立即出现在 stdout
    puts("IONBF stdout...");

    char buf[32];
    char scan[BUFSIZ];
    setvbuf(stdout, buf, _IOFBF, sizeof buf); // 设置标准输出流为全缓冲
    puts("IOFBF stdout...");
    if (scanf(" %s", scan))
    {
        printf("input: %s\n", scan);
        fflush(stdout);
    }
}

void test_fread_fwrite()
{
#define SIZE 5
    double a[SIZE] = {1., 2., 3., 4., 5.};
    double b[SIZE] = {};

    FILE *fp = fopen("test.bin", "wb"); // 必须用二进制模式
    fwrite(a, sizeof *a, SIZE, fp);     // 写 double 的数组
    if (!freopen("test.bin", "rb", fp))
    {
        perror("freopen");
        return;
    }

    size_t ret_code = fread(b, sizeof *b, SIZE, fp); // 读 double 的数组
    if (ret_code == SIZE)
    {
        puts("Array read successfully, contents: ");
        for (int n = 0; n < SIZE; ++n)
            printf("%f ", b[n]);
        putchar('\n');
    }
    else
    { // error handling
        if (feof(fp))
            printf("Error reading test.bin: unexpected end of file\n");
        else if (ferror(fp))
            perror("Error reading test.bin");
    }
    fclose(fp);
    remove("test.bin");
}

void test_format_printf()
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

int main()
{
    // test_tmpfile();

    // test_tmpnam_s();

    // test_fclose();

    // test_fflush();

    // test_freopen();

    // test_setbuf();

    // test_fread_fwrite();

    // test_format_printf();

}