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
static void atoi_test(void);
static void list_test(void);
static void simd_memchr_test(void);

static void misc_test(void);
static void isspace_test(void);
static void memchr_test(void);

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
	else if (ac >= 2 && !strcmp(av[1], "misc"))
		status = 4;
	else
		status = 3;

	if (status == 1 || status == 3)
		mandatory_test();
	if (status == 2 || status == 3)
		bonus_test();
	if (status == 4)
		misc_test();

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
	atoi_test();
	press_anykey();
	
	list_test();
	press_anykey();

	simd_memchr_test();
	press_anykey();
}

static void misc_test(void)
{
	isspace_test();
	press_anykey();

	memchr_test();
	press_anykey();
}

/*/////////////////////
//	INTERNAL TESTS   //
*//////////////////////

static void isspace_test(void)
{
	printf(GREEN "\tISSPACE TESTS!\n");

	printf("testing backslashes char = %d %d %d\n",
		 ft_isspace('\r'), ft_isspace('\t'), ft_isspace('\n'));

	printf("testing lower/upper char = %d %d %d\n",
		 ft_isspace(0), ft_isspace(23), ft_isspace(30));

	printf("testing space char = %d\n", ft_isspace(' '));

	printf("\n" END);
}

static void memchr_test(void)
{
	printf(YELLOW "\tMEMCHR TESTS!\n");

	char *s1  = "apple honey crusty apple cake";
	char *s2  = "honey";
	char *s3  = "apple";
	char *s4  = "not my chair";	// don't sit on cakes
	char *ptr = NULL;

	ptr = ft_memchr(s1, 'h', 15);
	printf("ptr=%p, finding 'h' in [%s]=%s\n", ptr, s1, ptr);

	ptr = ft_memchr(s1, 'c', 15);
	printf("ptr=%p, finding 'c' in [%s]=%s\n", ptr, s1, ptr);

	ptr = ft_memchr(s3, 'h', 15);
	printf("ptr=%p, finding 'h' in [%s]=%s\n", ptr, s3, ptr);

	// ptr = ft_memchr(s3, 'z', 300);
	// printf("ptr=%p, finding 'z' in [%s]=%s\n", ptr, s4, ptr);

	ptr = ft_memchr(s3, 'z', 0);
	printf("ptr=%p, finding 'z' in [%s]=%s\n", ptr, s4, ptr);

	printf("\n" END);
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
	char str6[] = "Hello";
	int mine = 0, real = 0;
	
	mine = ft_strcmp(str1, str6);
	real = strcmp(str1, str6);
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
	printf(B_YELLOW "\tSTRDUP TESTS!\n");

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

static void atoi_test(void)
{
	printf(CYAN "\tATOI BASE TESTS!\n");

	int ret = 42;

	// numbers to convert
	char *s1  		= "123";
	char *s2  		= "042";
	char *s3  		= "202";
	char *s4  		= "  \t    +202hello";
	char *s5  		= "-202U";
	char *s6		= "   +U123";
	char *s7		= "  U+123";
	char *s8		= "876";
	char *s9		= "FF";
	char *s10		= "2147483647";
	char *s11		= "-2147483648";

	// base
	char *dec 		= "0123456789";
	char *ced 		= "9876543210";
	char *hexl 		= "0123456789abcdef";
	char *hexu 		= "0123456789ABCDEF";

	// error
	char *sdup		= "001";
	char *s_wspace	= "0 2";
	char *s_sign	= "+12";

	printf("\nBase argument tests:\n");
	ret = ft_atoi_base(s1, sdup);
	printf("a=[%s], base=[%s], \ti=[%d]\n", s1, sdup, ret);

	ret = ft_atoi_base(s1, s_wspace);
	printf("a=[%s], base=[%s], \ti=[%d]\n", s1, s_wspace, ret);

	ret = ft_atoi_base(s1, s_sign);
	printf("a=[%s], base=[%s], \ti=[%d]\n", s1, s_sign, ret);


	printf("\nConversion tests:\n");
	ret = ft_atoi_base(s1, dec);
	printf("a=[%s], base=[%s], i=[%d]\n", s1, dec, ret);

	ret = ft_atoi_base(s2, dec);
	printf("a=[%s], base=[%s], i=[%d]\n", s2, dec, ret);

	ret = ft_atoi_base(s3, dec);
	printf("a=[%s], base=[%s], i=[%d]\n", s3, dec, ret);

	ret = ft_atoi_base(s5, dec);
	printf("a=[%s], base=[%s], i=[%d]\n", s5, dec, ret);

	ret = ft_atoi_base(s6, dec);
	printf("a=[%s], base=[%s], i=[%d]\n", s6, dec, ret);

	ret = ft_atoi_base(s7, dec);
	printf("a=[%s], base=[%s], i=[%d]\n", s7, dec, ret);

	printf("\nMisc tests:\n");
	ret = ft_atoi_base(s4, dec);
	printf("a=[%s], base=[%s], i=[%d]\n", s4, dec, ret);

	ret = ft_atoi_base(s1, ced);
	printf("a=[%s], base=[%s], i=[%d]\n", s1, ced, ret);

	ret = ft_atoi_base(s8, ced);
	printf("a=[%s], base=[%s], i=[%d]\n", s8, ced, ret);

	ret = ft_atoi_base(s9, hexu);
	printf("a=[%s], base=[%s], i=[%d]\n", s9, hexu, ret);

	ret = ft_atoi_base(s10, dec);
	printf("a=[%s], base=[%s], i=[%d]\n", s10, dec, ret);

	ret = ft_atoi_base(s11, dec);
	printf("a=[%s], base=[%s], i=[%d]\n", s11, dec, ret);

	printf("\n" END);
}

/*
	Tests list functions together
*/
static void list_test(void)
{
	printf(BLINK_YELLOW "\tLIST TESTS!\n" END);

	t_list a, b, *c = NULL, *temp1 = NULL, *temp2 = NULL, *head = &a;
	char *s1 = "apple";
	char *s2 = "badger";
	char *s3 = "cocorico";
	// char *s4 = "test";
	// char *s4 = "Test";
	char *s4 = "bagel";
	a.data = s1;	a.next = &b;
	b.data = s2;	b.next = NULL;

	/*
		Push front
	*/
	printf(B_WHITE "base head=%p, data=%s\n", &head, (char *)head->data);
	printf("\n");
	ft_list_push_front(&head, s3);
	temp1 = head;
	ft_list_push_front(&head, s4);
	temp2 = head;
	printf(YELLOW "ft_list_push_front with %s & %s as data:\n", s3, s4);
	printf("\t   head=%15p, data=%10s, next=%15p\n", head, (char *)head->data, head->next);
	c = head->next;
	while (c)
	{
		printf("\tcurrent=%15p, data=%10s, next=%15p\n", c, (char *)c->data, c->next);
		c = c->next;
	}
	printf("\n");

	/*
		Size
	*/
	printf(CYAN "List has %d elements (ft_list_size)\n", ft_list_size(head));
	printf("Starting from %s list, there's %d element\n", (char *)b.data, ft_list_size(&b));
	printf("Sending an empty list (NULL), size = %d\n", ft_list_size(c));
	printf("\n");

	/*
		Sorting
	*/
	ft_list_sort(&head, ft_strcmp);
	// ft_list_sort(&head, strcmp);
	printf(GREEN "List after sorting: size=%d\n", ft_list_size(head));
	c = head;
	printf("head ptr=%15p\n", c);
	while (c)
	{
		printf("\tptr=%15p, data=%10s, next=%15p\n", c, (char *)c->data, c->next);
		c = c->next;
	}

	free(temp1);
	free(temp2);

	printf("\n" END);
	press_anykey();
	printf(BLINK_YELLOW "\tLIST TESTS! (cont)\n" END);

	/*
		Remove if
	*/
	char *data[6];
	data[0] = ft_calloc(2, sizeof(char));	data[0][0] = 'a';
	data[1] = ft_calloc(2, sizeof(char));	data[1][0] = 'b';
	data[2] = ft_calloc(2, sizeof(char));	data[2][0] = 'c';
	data[3] = ft_calloc(2, sizeof(char));	data[3][0] = 'd';
	data[4] = ft_calloc(2, sizeof(char));	data[4][0] = 'e';
	data[5] = ft_calloc(2, sizeof(char));	data[5][0] = 'z';
	c = malloc(sizeof(t_list));
	c->data = data[0];
	c->next = NULL;
	head = c;
	ft_list_push_front(&head, data[1]);
	ft_list_push_front(&head, data[2]);
	ft_list_push_front(&head, data[3]);
	ft_list_push_front(&head, data[4]);

	// LIST
	c = head;
	printf(B_WHITE "head ptr=%15p (new list)\n", c);
	while (c)
	{
		printf("\tptr=%15p, data=%10s, next=%15p\n", c, (char *)c->data, c->next);
		c = c->next;
	} printf("\n");

	// SORTED LIST
	ft_list_sort(&head, ft_strcmp);
	c = head;
	printf(B_WHITE "head ptr=%15p (after sorting)\n", c);
	while (c)
	{
		printf("\tptr=%15p, data=%10s, next=%15p\n", c, (char *)c->data, c->next);
		c = c->next;
	} printf("\n");

	// REMOVE
	ft_list_remove_if(&head, "c", ft_strcmp, free);
	ft_list_remove_if(&head, "e", strcmp, free);
	c = head;
	printf(B_WHITE "head ptr=%15p (after removing 'c' AND 'e')\n", c);
	while (c)
	{
		printf("\tptr=%15p, data=%10s, next=%15p\n", c, (char *)c->data, c->next);
		c = c->next;
	} printf("\n");

	// REMOVE HEAD
	ft_list_push_front(&head, data[5]);
	ft_list_remove_if(&head, "z", strcmp, free);
	c = head;
	printf(B_WHITE "head ptr=%15p (after adding and removing 'z')\n", c);
	while (c)
	{
		printf("\tptr=%15p, data=%10s, next=%15p\n", c, (char *)c->data, c->next);
		c = c->next;
	} printf("\n");

	// DON'T REMOVE
	ft_list_remove_if(&head, "y", strcmp, free);
	c = head;
	printf(B_WHITE "head ptr=%15p (after removing 'y')\n", c);
	while (c)
	{
		printf("\tptr=%15p, data=%10s, next=%15p\n", c, (char *)c->data, c->next);
		c = c->next;
	}

	// removing everything to free all
	ft_list_remove_if(&head, "a", strcmp, free);
	ft_list_remove_if(&head, "b", strcmp, free);
	ft_list_remove_if(&head, "c", strcmp, free);
	ft_list_remove_if(&head, "d", strcmp, free);
	ft_list_remove_if(&head, "e", strcmp, free);

	printf("\n" END);
}

static void simd_memchr_test(void)
{
	printf(GREEN "\tSIMD MEMCHR TESTS!\n");

	char *s1  = "apple honey crusty apple cake";
	char *s2  = "honey";
	char *s3  = "apple";
	char *s4  = "not my chair";	// don't sit on cakes
	char *ptr = NULL;

	ptr = ft_simd_memchr(s1, 'h', 15);
	printf("ptr=%p, finding 'h' in [%s]=%s\n", ptr, s1, ptr);

	ptr = ft_simd_memchr(s1, 'c', 15);
	printf("ptr=%p, finding 'c' in [%s]=%s\n", ptr, s1, ptr);

	ptr = ft_simd_memchr(s3, 'h', 15);
	printf("ptr=%p, finding 'h' in [%s]=%s\n", ptr, s3, ptr);

	// ptr = ft_simd_memchr(s3, 'z', 300);
	// printf("ptr=%p, finding 'z' in [%s]=%s\n", ptr, s4, ptr);

	ptr = ft_simd_memchr(s3, 'z', 0);
	printf("ptr=%p, finding 'z' in [%s]=%s\n", ptr, s4, ptr);

	printf("\n" END);
}
