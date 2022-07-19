#include<stdio.h>

#define _0810


#ifdef _0801
FILE* fp = nullptr;
char* field = (char*)"%s\t%s\t%s\t%s\t%s";
char a[9];
char b[7];
char c[9];
char d[10];
char e[8];

int main(void) {
	fopen_s(&fp, "data1.txt", "r");
	if (fp != NULL) {
		while (fscanf_s(fp, field, &a, 9, &b, 7, &c, 9, &d, 10, &e, 8) != EOF) {
			printf(field, a, b, c, d, e);
			putchar('\n');
		}
		fclose(fp);
	}
	else putchar('\a');

	return 0;
}
#endif

#ifdef _0802
void copy(FILE* src, FILE* dst) {
	int ch;
	while ((ch = fgetc(src)) != EOF) {
		fputc(ch, dst);
	}
}

int main(int argc, char * argv[]) {
	FILE* fp = nullptr;

	if (argc < 2) copy(stdin, stdout);
	else {
		while (--argc > 0) {
			fopen_s(&fp, *++argv, "r");
			if (fp == NULL) {
				fprintf(stderr, "ファイル%sがオープンできません。\n", *argv);
				return 1;
			}
			else {
				copy(fp, stdout);
				fclose(fp);
			}
		}
	}

	return 0;
}
#endif

#ifdef _08C1
int main(int argc, char** argv) {
	for (int i = 0; i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}

	return 0;
}
#endif

#ifdef _08C2
int main(int argc, char** argv) {
	int i = 0;
	while (argc-- > 0) {
		printf("argv[%d] = %s\n", i++, *argv++);
	}

	return 0;
}
#endif

#ifdef _08C3
int main(int argc, char** argv) {
	int i = 0;
	while (argc-- > 0) {
		char c = 0;
		printf("argv[%d] = ", i++);
		while (c = *(*argv)++) {
			putchar(c);
		}
		argv++;
		putchar('\n');
	}

	return 0;
}
#endif

#ifdef _0803
struct rec {
	char a[9];
	char b[7];
	char c[9];
	char d[10];
	char e[8];
};

int fgetword(FILE* fp, char* str) {
	int ch = 0;
	while ((ch = fgetc(fp)) != EOF && ch != '\t' && ch != '\n') {
		if (ch != ' ') *str++ = ch;
	}
	return ch;
}

int getrec(FILE* fp, struct rec* dst) {
	if (fgetword(fp, dst->a) == EOF) return EOF;
	if (fgetword(fp, dst->b) == EOF) return EOF;
	if (fgetword(fp, dst->c) == EOF) return EOF;
	if (fgetword(fp, dst->d) == EOF) return EOF;
	if (fgetword(fp, dst->e) == EOF) return EOF;
	return 0;
}

int main(void) {
	FILE* fp = nullptr;
	struct rec dat {};

	fopen_s(&fp, "data2.txt", "r");
	if (fp == NULL) {
		putchar('\a');
		return 1;
	}
	else{
		while (getrec(fp, &dat) == 0) {
			printf("%9s\t%7s\t%9s\t%10s\t%8s\n", dat.a, dat.b, dat.c, dat.d, dat.e);
			dat = { '\0' };
		}
		fclose(fp);
	}

	return 0;
}
#endif

#ifdef _0804
int main(void) {
	int num = 0;

	while (true) {
		printf("整数値を入力せよ : ");
		scanf_s("%d", &num);
		if (num == 9999) break;
		printf("あなたは%dと入力しましたね。\n", num);
	}

	return 0;
}
#endif

#ifdef _0805
#include<stdlib.h>

int main(void) {
	int num = 0;
	char buffer[8]{};

	while (true) {
		printf("整数値を入力せよ : ");
		if (scanf_s("%s", buffer, 8) == EOF) break;
		if ((num = atoi(buffer)) == 9999) break;
		printf("あなたは%dと入力しましたね。\n", num);
	}

	return 0;
}
#endif

#ifdef _0806
#include<ctype.h>

int strtoi(const char* str, int* err) {
	int no = 0;
	int sign = 1;

	while (isspace(*str)) str++;
	switch (*str) {
	case'+': str++; break;
	case'-': str++; sign = -1; break;
	}

	for (; isdigit(*str); str++) no = no * 10 + (*str - '0');
	no *= sign;
	*err = *str ? 1 : 0;

	return no;
}

int main(void) {
	int num = 0, err = 0;
	char buffer[64]{};

	while (true) {
		printf("整数値を入力せよ : ");
		scanf_s("%s", buffer, 64);
		num = strtoi(buffer, &err);
		if (err) puts("\a整数値に変換できませんでした。");
		else {
			if (num == 9999) break;
			printf("あなたは%dと入力しましたね。\n", num);
		}
	}

	return 0;
}
#endif

#ifdef _0807
#include<ctype.h>
#include<limits.h>
#include<stdlib.h>

int strtoi(const char* str, int* err) {
	int no = 0;
	int sign = 1;
	div_t int_min = div(INT_MIN, 10);

	int_min.rem *= -1;
	*err = 2;

	while (isspace(*str)) str++;
	switch (*str) {
	case '+': str++; break;
	case '-': str++; sign = -1; break;
	}

	for (; isdigit(*str); str++) {
		if ((no < int_min.quot) ||
			(no == int_min.quot && *str - '0' > int_min.rem)) {
			no = INT_MIN;
			goto OverFlow;
		}
		no = no * 10 - (*str - '0');
	}
	if (sign == 1) {
		if (no < -INT_MAX) {
			no = INT_MAX;
			goto OverFlow;
		}
		no = -no;
	}
	*err = *str ? 1 : 0;
OverFlow:
	return no;
}

int main(void) {
	int num = 0, err = 0;
	char buffer[64]{};

	while (true) {
		printf("整数値を入力せよ : ");
		scanf_s("%s", &buffer, 64);
		num = strtoi(buffer, &err);
		if (err) puts("\a整数値に変換できませんでした。");
		else {
			if (num == 9999) break;
			printf("あなたは%dと入力しましたね。\n", num);
		}
	}

	return 0;
}
#endif

#ifdef _08C4
#include<stdlib.h>

int main(void) {
	int number = 0, denom = 0;
	div_t qr{};

	printf("割られる数 : "); scanf_s("%d", &number);
	printf("割る数 : ");  scanf_s("%d", &denom);

	qr = div(number, denom);
	printf("商は%dで剰余は%dです。\n", qr.quot, qr.rem);

	return 0;
}
#endif

#ifdef _0808
int main(void) {
	int i = 0;
	char ns[20][6]{};

	for (i = 0; i < 20; i++) sprintf_s(ns[i], "No.%02d", i + 1);
	for (i = 0; i < 20; i++) printf("%s\n", ns[i]);

	return 0;
}
#endif

#ifdef _0809
int main(void) {
	int n1 = 0, n2 = 0;
	double x = 0;
	char buf[256]{};

	printf("実数値を入力してください : ");
	scanf_s("%lf", &x);

	printf("少なくとも何桁の文字列に変換しますか : ");
	scanf_s("%d", &n1);

	printf("そのうち小数部は何桁ですか : ");
	scanf_s("%d", &n2);

	sprintf_s(buf, "%*.*f", n1, n2, x);

	printf("変換後の文字列は\"%s\"です。\n", buf);

	return 0;
}
#endif

#ifdef _0810
#include<string.h>

typedef struct {
	int y;
	int m;
	int d;
} Date;

int fgetdate(FILE* fp, Date* d) {
	const char* month[] = {
		"", "Janualy", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "Desember"
	};
	char buf[256]{}, mbuf[256]{};
	d->y = d->m = d->d = 0;

	if (fgets(buf, sizeof(buf), fp) != NULL) {
		if (sscanf_s(buf, "%d/%d/%d", &d->y, &d->m, &d->d) == 3) return 1;
		else if (sscanf_s(buf, "%d-%d-%d", &d->y, &d->m, &d->d) == 3) return 1;
		else if (sscanf_s(buf, "%d%s%d", &d->d, mbuf, 256, &d->y) == 3) {
			for (int i = 1; i <= 12; i++) {
				if (strncmp(month[i], mbuf, 3) == 0) {
					d->m = i;
					return 1;
				}
			}
		}
	}
	return 0;
}

int main(void) {
	Date date{};

	puts("日付を入力してください。");
	while (fgetdate(stdin, &date)) {
		printf("日付 : %d-%d-%d\n\n", date.y, date.m, date.d);
	}

	return 0;
}
#endif