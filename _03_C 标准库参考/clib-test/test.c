#include <stdio.h>
#include <math.h>

int n;

int main(void)
{
	FILE *f = fopen("test.txt", "a");
	char s[] = " world";
	fwrite(s, 1, sizeof s - 1, f);

	if (freopen("test.txt", "rb", f))
	{
		char buf[BUFSIZ] = {0};
		fread(buf, 1L, BUFSIZ - 1, f);
		printf("%s\n", buf);
	}
	else
		perror("e");
	fclose(f);
}