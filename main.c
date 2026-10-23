#include "header.h"

// Static sector
static void strlen_test(void);

/*
	Big wall of tests inbound
*/

int main(int ac, char **av)
{
	strlen_test();
	return (0);
}

static void strlen_test(void)
{
	printf(YELLOW "STRLEN TESTS!\n");

	int a = ft_strlen(MSG);
	int b = strlen(MSG);
	printf("asm=%03d, mine=%03d \t-- Billy (17)\n", a, b);

	// NULL crashes strlen
	// a = ft_strlen(NULL);
	// b = strlen(NULL);
	// printf("a=%03d, b=%03d \t-- NULL\n", a, b);

	char arr[4] = {'1', '2', '3', 0};
	a = ft_strlen(arr);
	b = strlen(arr);
	printf("asm=%03d, real=%03d \t-- arr {'1', '2', '3', 0}\n", a, b);

	arr[3] = 4;
	a = ft_strlen(arr);
	b = strlen(arr);
	printf("asm=%03d, real=%03d \t-- arr {'1', '2', '3', 4}\n", a, b);

	a = ft_strlen(LOREM);
	b = strlen(LOREM);
	printf("asm=%03d, real=%03d \t-- What is Lorem Ipsum?\n", a, b);

	a = ft_strlen("");
	b = strlen("");
	printf("asm=%03d, real=%03d \t-- empty string\n", a, b);

	printf("\n" END);
}