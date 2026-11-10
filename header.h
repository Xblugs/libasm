#pragma once

/*
	Header to make it cleaner

	Plenty of defines used to test and format the results
*/

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MSG 			"Billy la truande"
#define LOREM 			"Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since 1966, when designers at Letraset and James Mosley, the librarian at St Bride Printing Library in London, took a 1914 Cicero translation and scrambled it to make dummy text for Letraset's Body Type sheets. It has survived not only many decades, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised thanks to these sheets and more recently with desktop publishing software like Aldus PageMaker and Microsoft Word including versions of Lorem Ipsum."

#define B_WHITE			"\e[1;37m"
#define WHITE			"\e[0;97m"
#define B_RED			"\e[1;31m"
#define RED				"\e[0;31m"
#define BLUE			"\e[0;96m"
#define GREEN			"\e[0;92m"
#define YELLOW			"\e[0;93m"
#define BLINK_YELLOW	"\e[5;93m"
#define PURPLE			"\e[0;35m"
#define CYAN			"\e[0;36m"
#define GRAY			"\e[0;37m"

#define END				"\e[0m"

/*
	On schoo computer (x64):
	Size of bool: 1
	Size of _Bool: 1
	Size of short: 2
	Size of int: 4
	Size of long: 8
	Size of long long: 8
	Size of size_t: 8
	Size of void*: 8
	Size of float: 4
	Size of double: 8
	pid_t: 4
	uid_t: 4
	gid_t: 4
	t_list: 16
	t_list->data: 8
	t_list->next: 8
*/

// used for some bonus functions
typedef struct s_list		// 16 bytes
{
	void *data;				// 8 bytes
	struct s_list *next;	// 8 bytes
} t_list;

/*
	Mandatory part
*/
extern void *ft_calloc(size_t nmemb, size_t size);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern int ft_strcmp(const char *s1, const char *s2);
extern char *ft_strcpy(char *dest, const char *src);
extern char *ft_strdup(const char *s);
extern size_t ft_strlen(const char *s);
extern ssize_t ft_write(int fd, const void *buf, size_t count);

/*
	Bonus part
*/
extern int ft_atoi_base(char *str, char *base);
extern void ft_list_push_front(t_list **begin_list, void *data);
extern unsigned int ft_list_size(t_list *begin_list);
extern void ft_list_sort(t_list **begin_list, int (*cmp)());
//	(*cmp)(list_ptr->data, list_other_ptr->data);

extern void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
//	(*cmp)(list_ptr->data, data_ref);
//	(*free_fct)(list_ptr->data);

extern void *ft_simd_memchr(const void *s, int c, size_t n);

/*
	Misc part because why not
*/
// used internally by ft_atoi_base to make it more readable
extern void	*ft_memchr(const void *s, int c, size_t n);

extern void ft_exit(int status);
