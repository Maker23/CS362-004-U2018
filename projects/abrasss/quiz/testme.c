#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MINSTR 5
#define MAXSTR 5

#define ASCIILOW 32
#define ASCIIHIGH 126 

#define ALPHALOW 97
#define ALPHAHIGH 122 

char String[MAXSTR+1];  // global, so we don't have to involve malloc

char inputChar()
{
	char c;
	c = rand() % (ASCIIHIGH - ASCIILOW + 1) + ASCIILOW; 
	return c;
}
char inputAlpha()
{
	char c;
	c = rand() % (ALPHAHIGH - ALPHALOW + 1) + ALPHALOW;
	return c;
}

char *inputString()
{
	int i;
	int len = rand() % (MAXSTR - MINSTR + 1) + MINSTR;
	// printf ("%d", len); // debug

	for (i = 0; i < len; i++) {
		String[i] = inputAlpha();
	}
	while ( i < MAXSTR + 1){
		String[i++] = '\0';
	}
	
	return &String[0];
}
void testme()
{
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;

	while (1){
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' '&& state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'&& s[2] == 's' && s[3] == 'e'&& s[4] == 't' && s[5] == '\0'&& state == 9)
		{
			printf("error ");
			exit(200);
		}
	}
}
void testchar()
{
	char c;
	int i=0;

	while (i++ < 100) {
		c=inputChar();
		printf("%c\n", c);
	}
}
void teststring()
{
	char *s;
	int i=0;

	while (i++ < 100) {
		s=inputString();
		printf("%s\n", s);
	}
}
int main(int argc, char *argv[]){
	srand(time(NULL));
	testme();
	//testchar();
	//teststring();
	return 0;
}
