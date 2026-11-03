// read test!!test read //
#include "header.h"

// Static sector
static void mandatory_test(void);
static void strlen_test(void);
static void strcpy_test(void);
static void strcmp_test(void);
static void write_test(void);
static void read_test(void);
static void strdup_test(void);
static void calloc_test(void);

static void bonus_test(void);
static void list_test(void);

static void press_anykey(void)
{
	printf("--- Press any key to continue ---\n");
	char *line = NULL;
    size_t len = 0;
	getline(&line, &len, stdin);
    free(line);
}

/*
	Big wall of tests inbound
*/

int main(int ac, char **av)
{
	char status = 0;

	if (ac >= 2 && !strcmp(av[1], "mandatory"))
		status = 1;
	else if (ac >= 2 && !strcmp(av[1], "bonus"))
		status = 2;
	else
		status = 3;

	if (status == 1 || status == 3)
		mandatory_test();
	if (status == 2 || status == 3)
		bonus_test();
	ft_exit(42);
	return (0);
}


static void mandatory_test(void)
{
	strlen_test();
	press_anykey();
	
	strcpy_test();
	press_anykey();
	
	strcmp_test();
	press_anykey();

	write_test();
	press_anykey();
	
	read_test();
	press_anykey();

	strdup_test();
	press_anykey();

	calloc_test();
	press_anykey();
}

static void bonus_test(void)
{
	list_test();
}

/*/////////////////////
//	MANDATORY TESTS  //
*//////////////////////

static void strlen_test(void)
{
	printf(YELLOW "\tSTRLEN TESTS!\n");

	int a = ft_strlen(MSG);
	int b = strlen(MSG);
	printf("asm=%03d, real=%03d \t-- Billy (17)\n", a, b);

	// NULL crashes both
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

static void strcpy_test(void)
{
	printf(B_WHITE "\tSTRCPY TESTS!\n");

	char dst[30], src[30], *ptr;
	bzero(dst, 30);
	bzero(src, 30);

	strcpy(src, "le chat est dans la boite");
	ptr = ft_strcpy(dst, src);
	printf("src=%s\ndst=%s\n\t-- Basic copy\n\n", src, ptr);

	strcpy(src, &src[8]);
	ptr = ft_strcpy(dst, &dst[8]);
	printf("asm=%s\nreal=%s\n\t-- Overlapping copy\n\n", ptr, src);

	strcpy(src, "le chien dort");
	ptr = ft_strcpy(dst, src);
	printf("asm=%s\nreal=%s\n\t-- NULL terminaison copy\n", ptr, src);

	// any NULL crashes
	// strcpy(NULL, NULL);

	printf("\n" END);
}

static void strcmp_test(void)
{
	printf(CYAN "\tSTRCMP TESTS!\n");

	char str1[] = "Hello";
	char str2[] = "World";
	char str3[] = "ab";
	char str4[] = "abc";
	char str5[] = "";
	int mine = 0, real = 0;
	
	mine = ft_strcmp(str1, str1);
	real = strcmp(str1, str1);
	printf("asm=%d, real=%d\t-- Hello vs Hello\n", mine, real);

	mine = ft_strcmp(str1, str2);
	real = strcmp(str1, str2);
	printf("asm=%d, real=%d\t-- Hello vs World\n", mine, real);

	mine = ft_strcmp(str3, str4);
	real = strcmp(str3, str4);
	printf("asm=%d, real=%d\t-- ab vs abc\n", mine, real);

	mine = ft_strcmp(str4, str3);
	real = strcmp(str4, str3);
	printf("asm=%d, real=%d\t-- abc vs ab\n", mine, real);

	mine = ft_strcmp(str3, str5);
	real = strcmp(str3, str5);
	printf("asm=%d, real=%d\t-- \"ab\" vs \"\"\n", mine, real);

	printf("\n" END);
}
static void write_test(void)
{
	printf(GREEN "\tWRITE TESTS!\n");

	int a = ft_write(STDIN_FILENO, "FT_HELLO\n", 10);
	int b = write(STDIN_FILENO, "   HELLO\n", 10);
	printf("asm=%03d, real=%03d \t-- HELLO\n\n", a, b);

	a = ft_write(STDIN_FILENO, "FT_HELLO\n", 25);
	b = write(STDIN_FILENO, "   HELLO\n", 25);
	printf("asm=%03d, real=%03d \t-- BIG HELLO\n\n", a, b);

	a = ft_write(STDIN_FILENO, "FT_HELLO\n", 0);
	b = write(STDIN_FILENO, "   HELLO\n", 0);
	printf("asm=%03d, real=%03d \t-- Len = 0\n", a, b);

	errno = 42;
	a = ft_write(-1, "FT_HELLO\n", 10);
	printf("asm=%03d errno=%03d \t", a, errno);
	b = write(-1, "   HELLO\n", 10);
	printf("real=%03d errno=%03d\t-- FD = -1\n", a, errno);

	errno = 42;
	a = ft_write(STDIN_FILENO, NULL, 10);
	printf("asm=%03d errno=%03d \t", a, errno);
	b = write(STDIN_FILENO, NULL, 10);
	printf("real=%03d errno=%03d\t-- string = NULL\n", a, errno);

	errno = 42;
	a = ft_write(STDIN_FILENO, "🦜\n", -10);
	printf("asm=%03d errno=%03d \t", a, errno);
	b = write(STDIN_FILENO, "🦜\n", -10);
	printf("real=%03d errno=%03d\t-- negative len\n", a, errno);

	printf("\n" END);
}

static void read_test(void)
{
	printf(BLUE "\tREAD TESTS!\n");

	char res[30];
	int a ,b, fd;
	memset(res, 0xff, sizeof(char));
	// bzero(res, 30);
	res[29] = 0;

	fd = open("./main.c", 0);
	a = ft_read(fd, res, 13);
	b = read(fd, &res[13], 13);
	printf("asm=%03d, real=%03d \t-- Read test\n", a, b);
	close(fd);
	printf("res=[%s]\n", res);

	errno = 42;
	fd = open("./README.md", O_WRONLY);
	a = ft_read(fd, "FT_HELLO\n", 10);
	printf("asm=%03d errno=%03d \t", a, errno);

	errno = 42;
	b = read(fd, "   HELLO\n", 10);
	printf("real=%03d errno=%03d\t-- File open in writing only\n", a, errno);
	close(fd);

	errno = 42;
	a = ft_read(-1, "FT_HELLO\n", 10);
	printf("asm=%03d errno=%03d \t", a, errno);

	errno = 42;
	b = read(-1, "   HELLO\n", 10);
	printf("real=%03d errno=%03d\t-- FD = -1\n", a, errno);

	errno = 42;
	fd = open("./README.md", 0);
	a = ft_read(fd, NULL, 10);
	printf("asm=%03d errno=%03d \t", a, errno);

	errno = 42;
	b = read(fd, NULL, 10);
	printf("real=%03d errno=%03d\t-- buf = NULL\n", a, errno);

	errno = 42;
	a = ft_read(fd, "🦜\n", -10);
	printf("asm=%03d errno=%03d \t", a, errno);

	errno = 42;
	b = read(fd, "🦜\n", -10);
	printf("real=%03d errno=%03d\t-- negative len\n", a, errno);
	close(fd);

	printf("res = [%s]\n", res);
	printf("\n" END);
}

static void strdup_test(void)
{
	printf(B_RED "\tSTRDUP TESTS!\n");

	char src[30] = "Testing grounds!", *ptr1 = NULL, *ptr2 = NULL;

	ptr1 = strdup(src);
	ptr2 = ft_strdup(src);
	// printf("errno=%d\n", errno); // uncomment when testing errno
	printf("strdup=[%s], ft_strdup=[%s]\n", ptr1, ptr2);
	printf("strcmp between copies = [%d], ptr1=%p, ptr2=%p\t-- Dup test\n"
			, strcmp(ptr1, ptr2), ptr1, ptr2);
	printf("real len=%lu, asm len2=%lu\n\n", strlen(ptr1), strlen(ptr2));
	free(ptr1);
	free(ptr2);

	ptr2 = ft_strdup(LOREM);
	printf("longer test, ft_strdup=[%s]\n", ptr2);
	printf("len=%lu\n", strlen(ptr2));
	free(ptr2);

	printf("\n" END);
}

static void calloc_test(void)
{
	printf(PURPLE "\tCALLOC TESTS!\n");

	char *ptr1 = NULL;

	ptr1 = ft_calloc(200, sizeof(char));
	printf("ft_calloc=%s\n\t-- Nothing should be printed after '='\n\n", ptr1);
	free(ptr1);

	errno = 42;
	ptr1 = ft_calloc(__SIZE_MAX__, sizeof(long));
	printf("ft_calloc=%p, errno=%d\n\t-- Should print nil and 12\n", ptr1, errno);
	free(ptr1);

	printf("\n" END);
}

/*/////////////////////
//	BONUS PART TESTS //
*//////////////////////

/*
	Tests ft_list_push_front, ft_list_size
*/
static void list_test(void)
{
	printf(BLINK_YELLOW "\tLIST TESTS!\n" END);

	t_list a, b, *c = NULL, *temp = NULL, *head = &a;
	char s1[10]="apple", s2[10]="badger", s3[10]="cocorico";

	a.data = s1;	a.next = &b;
	b.data = s2;	b.next = NULL;

	printf(B_WHITE "base head=%p, data=%s\n", &head, (char *)head->data);
	ft_list_push_front(&head, s3);
	ft_list_push_front(&head, "TEST");
	printf(YELLOW "ft_list_push_front with %s as data:\n", s3);
	temp = head;
	printf("\t   head=%15p, data=%10s, next=%15p\n", head, (char *)head->data, head->next);
	c = head->next;
	while (c)
	{
		printf("\tcurrent=%15p, data=%10s, next=%15p\n", c, (char *)c->data, c->next);
		c = c->next;
	}

	printf(CYAN "List has %d elements (ft_list_size)\n", ft_list_size(head));
	printf("Starting from %s list, there's %d element\n", (char *)b.data, ft_list_size(&b));
	printf("Sending an empty list (NULL), size = %d\n", ft_list_size(c));

	ft_list_sort(&head, *strcmp);
	printf(GREEN "List after sorting: size=%d\n", ft_list_size(head));
	c = head;
	printf("head ptr=%15p\n", c);
	while (c)
	{
		printf("\tptr=%15p, data=%10s, next=%15p\n", c, (char *)c->data, c->next);
		c = c->next;
	}

	free(temp);
	printf("\n" END);
}