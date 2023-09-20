/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegrand <tlegrand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:43:09 by tlegrand          #+#    #+#             */
/*   Updated: 2023/09/20 13:24:58 by tlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef SIZE_MAX
#  define SIZE_MAX 18446744073709551615UL
# endif

//	content is a pointer to whatever struct/union/variable you want
//	"node" refer to ptr to a t_list (aka t_list*)
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*	####################	char	####################	*/
//	take a char (int), return 1 if true or else 0
int			ft_isdigit(int c);
//	take a char (int), return 1 if true or else 0
int			ft_isalpha(int c);
//	take a char (int), return 1 if true or else 0
int			ft_isalnum(int c);
//	take a char (int), return 1 if true or else 0
int			ft_isascii(int c);
//	take a char (int), return 1 if true or else 0
int			ft_isprint(int c);
// take a char (int), return 1 if true or else 0
int			ft_isspace(char c);
//	take a char (int), if alpha return uppercasecase
int			ft_toupper(int c);
//	take a char (int),  if alpha return lowercase
int			ft_tolower(int c);
//	take a string and a char, return number of char in string
int			ft_count_char(char *str, char c);
//	take a string and a charset, return number of charset element in string
int			ft_count_charset(char *str, char *charset);

/*	####################	convert	####################	*/
//	take a string, convert it in int, return int or -1/0 in case of overflow 
//	(string format "    +1232fsefs")
int			ft_atoi(const char *str);
//	take a string and a reference base, convert it in int, return int or 0 if 
//	error in base (not protected against overflow)
int			ft_atoi_base(char *str, char *base);
//	take an int, convert it in a string, return char or NULL if malloc failed
char		*ft_itoa(int n);

/*	####################	memory	####################	*/
//	take a number of element and a size of element, allocate memory and set it 
//	to 0, return pointer to memory
void		*ft_calloc(size_t count, size_t size);
//	take a pointer, a value interpreted as an unsigned char, a len, set  
//	memory from ptr to value for len element, return ptr to memory
void		*ft_memset(void *b, int c, size_t len);
//	take a pointer and a len, set memory from ptr to 0
void		ft_bzero(void *s, size_t n);
//	take two pointer and a size, copy size element from src to dst,
//	return ptr to dst (not protected against overlapping)
void		*ft_memcpy(void *dst, const void *src, size_t n);
//	take two pointer and a size, copy size element from src to dst,
//	return ptr to dst (protected against overlapping)
void		*ft_memmove(void *dst, const void *src, size_t n);
//	take a pointer, a value interpreted as an unsigned char, a size,
//	if there is at least one element from ptr == value, 
//	return ptr to this element, otherwise return NULL 
void		*ft_memchr(const void *s, int c, size_t n);
//	take two pointer to compare and a size, 
//	return the first difference between s1 and s2 inside size
//	(element from ptr are interpreted as an unsigned char)
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/*	####################	string	####################	*/
//	take two string and a size, copy from src to dst, size should be enought for
//	src + '\0', return src size
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
//	take two string and a size, copy from src to dst, size should be enought for
//	src + '\0', return src size + dst size or whatever i dont want to remember 
//	this hellish strlcat
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
//	take a string, allocate memory, duplicate it, return ptr to duplicata / NULL
char		*ft_strdup(const char *s1);
//	take a string and a size, allocate memory, duplicate string,
//	return ptr to duplicata / NULL (max size element duplicate)
char		*ft_strndup(char *src, int n);
//	take a string, a starting index and a len, allocate memory,
//	duplicate len element from start index, return ptr to duplicata / NULL
char		*ft_substr(char const *s, unsigned int start, size_t len);
//	take a string, and a end ptr towhere to erase, create string without end,
//	free string and return new string
//	(usefull only if u need to free memory, for short string use bzero insteed)
char		*ft_strerase_end(char *str, char *end);
//	take two string, allocate memory, return a concatenation of s1 and s2
char		*ft_strjoin(char const *s1, char const *s2);
//	take three string, allocate memory, return a concatenation of s1, s2 and s3
char		*ft_strjoin3(char const *s1, char const *s2, char const *s3);
//	take the number of string to concatenate, allocate memory,
//	return a concatenation of all string
char		*ft_multijoin(int n, ...);
//	take two string, allocate memory, free self,
//	return a concatenation of self and toappend
char		*ft_strappend(char *self, char *to_append);
//	take a string and a charset, trim char based on charset at beginning and end
//	allocate memory and return the trimed string 
char		*ft_strtrim(char const *s1, char const *set);
//	take a string and a char, allocate memory, split it based on char and 
//	return a char** NULL terminated
char		**ft_split(char const *s, char c);
//	take a NULL-terminated char**, return number of char* inside
int			ft_path_splitlen(char **split);
//	take a string, a function, create a duplicata of string and apply func to 
//	duplicate string (allocate memory), return duplicata
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
//	take a string, a function, apply func to all char in string
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
//	take a string, return len of string (not protected)
size_t		ft_strlen(const char *s);
//	take a string, return len of string or 0 if str is NULL (protected)
size_t		ft_strlen2(const char *s);
//	take a string and a char, search from start of string
//	return a ptr to first element of string == c, or else NULL
char		*ft_strchr(const char *s, int c);
//	take a string and a char, search from end of string
//	return a ptr to first element of string == c, or else NULL
char		*ft_strrchr(const char *s, int c);
//	take two string, if needle is in haystack return a ptr to haystack or NULL
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
//	take two string to compare, 
//	return the first difference between s1 and s2 inside size element
int			ft_strncmp(const char *s1, const char *s2, size_t n);
//	take a string, return 1 if true or else 1
int			ft_str_isdigit(char *str);
//	take a string, return 1 if true or else 1
int			ft_str_isalnum(char *str);

/*	####################	t_list	####################	*/
//	take a ptr to content, allocate memory, return a node created with content
t_list		*ft_lstnew(void *content);
//	take a ptr to a node (start of list) and a node to add in list
//	add new in front of list
void		ft_lstadd_front(t_list **lst, t_list *new);
//	take a ptr to a node (start of list) and a node to add in list
//	add new in last position of list
void		ft_lstadd_back(t_list **lst, t_list *new);
//	take a node of list, return size of list starting from this node
int			ft_lstsize(t_list *lst);
//	take a node of list, return last node in list
t_list		*ft_lstlast(t_list *lst);
//	take a node and a function to delete content, delete content and free node
void		ft_lstdelone(t_list *lst, void (*del)(void *));
//	take a ptr to a node (start of list) and a function to delete content,
//	delete the full list
void		ft_lstclear(t_list **lst, void (*del)(void *));
//	take a node and a function to apply to list, apply func to list;
void		ft_lstiter(t_list *lst, void (*f)(void *));
//	take a node and a function to apply to list, create a duplicated list,
//	apply func to list and return first node of duplicated list
//	(allocate memory)
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*	####################	print	####################	*/
# define LEFT 0b00000001
# define PRECISION 0b00000010
# define ZERO 0b00000100 
# define BLANK 0b00001000 
# define PLUS 0b00010000 
# define ALTERNATE 0b00100000 

# define P_BUFFER_SIZE 256

// 	internal printf buffer
typedef struct s_print_buffer
{
	char	buffer[P_BUFFER_SIZE];
	int		idx;
}	t_print_buffer;

//	take a string and element tp print
//	print string with "%format" substitued by element in order
//	format currently supported : %iudscpxX
//	no flag supported
//	return number of char printed
int			ft_printf(const char *str, ...);

//	take a int and a string as a base, print the number,
//	return number of char printed
int			ft_putnbr_base(long int nbr, char *base);
//	take a file descriptor fd and a char, write char in fd
void		ft_putchar_fd(char c, int fd);
//	take a file descriptor fd and a string, write string in fd
void		ft_putstr_fd(char *s, int fd);
//	take a file descriptor fd and a string, write string with '\n, at end in fd
void		ft_putendl_fd(char *s, int fd);
//	take a file descriptor fd and a number (int), write number in fd
void		ft_putnbr_fd(int n, int fd);
//	take a NULL terminated char **, print it
void		ft_print_tab2d_char(char **tab);
//	take a int** tab and his size, print it
void		ft_print_tab_int(int *tab, int size);

/*	####################	GNL and file	####################	*/
# ifndef MAX_FD
#  define MAX_FD 8
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

//	take a fd, and a pptr, allocate memory and copy a line from fd inside
//	subsequent call with same fd (if not closed between) give the other line
//	can handle multiple call to different fd
//	a line is a string terminated with '\n' or EOF 
//	return 1 if an error occuri
//	if there is nothing else to read, line is set to NULL
int			get_next_line(int fd, char **line);
//	take a pathname to a file, return number of char inside
int			ft_file_size(char *pathname);

/*	####################	free and close	####################	*/
//	take a ptr, free memory if ptr != NULL, return NULL,
//	should be used to free ptr AND assigne it to NULL
void		*ft_free_secure(void *ptr);
//	take a void ** ptr and his size, free all element of ptr
//	if size = 0, assume ptr is NULL terminated, return NULL
//	should be used to free ptr AND assigne it to NULL
void		*ft_free2d(void **arr, int size);
//	take a void *** ptr and his size, free all element of ptr
//	if size3d = 0, assume ptr is NULL terminated, size2d is ignored
//	size2d should be used to indicate size of each sub-element of ptr
//	if size2d[1] == -1, assume all sub-element have size2d[0] size
//	should be used to free ptr AND assigne it to NULL
void		*ft_free3d(void ***arr, int size3d, int *size2d);
//	take a fd, if fd != -1 close it, return -1
//	should be used to close a fd and assigne it to -1
int			ft_close_secure(int fd);
//	take a int[2], if element are != -1, close them, set them to -1
void		ft_close_pipe(int pipefd[2]);

/*	####################	math	####################	*/
// 	return absolute value of a
long int	ft_abs(long int a);
// 	return max(a,b)
int			ft_max(int a, int b);
// 	return min(a,b)
int			ft_min(int a, int b);

/*	####################	debug	####################	*/
// print tab
void		debug_print_tab(int *tab, int n);

#endif