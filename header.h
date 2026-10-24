#pragma once

/*
	Header to make it cleaner

	Plenty of defines used to test and format the results
*/

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


#define MSG 	"Billy la truande"
#define LOREM 	"Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since 1966, when designers at Letraset and James Mosley, the librarian at St Bride Printing Library in London, took a 1914 Cicero translation and scrambled it to make dummy text for Letraset's Body Type sheets. It has survived not only many decades, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised thanks to these sheets and more recently with desktop publishing software like Aldus PageMaker and Microsoft Word including versions of Lorem Ipsum."

#define B_WHITE					"\e[1;37m"
#define WHITE					"\e[0;97m"
#define B_RED					"\e[1;31m"
#define RED						"\e[0;31m"
#define BLUE					"\e[0;96m"
#define GREEN					"\e[0;92m"
#define YELLOW					"\e[0;93m"
#define BLINK_YELLOW			"\e[5;93m"
#define PURPLE					"\e[0;35m"
#define CYAN					"\e[0;36m"
#define GRAY					"\e[0;37m"

#define END						"\e[0m"

/*
	Mandatory part
*/
extern size_t ft_strlen(const char *s);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);

/*
	Bonus part
*/

/*
	Misc part because why not
*/
extern void ft_exit(int status);
