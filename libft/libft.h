/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamguerreiro <williamguerreiro@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:43:49 by willda-s          #+#    #+#             */
/*   Updated: 2025/05/11 18:27:32 by williamguer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <errno.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int					ft_atoi(const char *str);

void				ft_bzero(void *s, size_t n);

void				*ft_calloc(size_t nmemb, size_t size);

int					ft_isalnum(int c);

int					ft_isalpha(int c);

int					ft_isascii(int c);

int					ft_isdigit(int c);

int					ft_isprint(int c);

void				*ft_memchr(const void *s, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memcpy(void *dest, const void *src, size_t n);

void				*ft_memmove(void *dst, const void *src, size_t len);

void				*ft_memset(void *s, int c, size_t n);

char				*ft_strchr(const char *str, int c);

char				*ft_strdup(const char *str1);

char				*ft_strndup(const char *str, size_t len);

size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t				ft_strlen(const char *str);

size_t				count_word(char const *s, char c);

int					ft_strncmp(const char *s1, const char *s2, size_t length);

char				*ft_strnstr(const char *big, const char *little,
						size_t len);

char				*ft_strrchr(const char *str, int c);

int					ft_tolower(int c);

int					ft_toupper(int c);

char				*ft_substr(char const *s, unsigned int start, size_t len);

char				*ft_strjoin(char const *s1, char const *s2);

char				*ft_strtrim(char const *s1, char const *set);

char				**ft_split(char const *s, char c);

char				*ft_itoa(int n);

char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

void				ft_putchar_fd(char c, int fd);

void				ft_putstr_fd(char *s, int fd);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);

int					ft_lstsize(t_list *lst);

void				ft_lstadd_front(t_list **lst, t_list *new);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

////////////////////////GET_NEXT_LINE///////////////////////////////

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char				*get_next_line(int fd);

char				*ft_strccpy(char *dst, char *src);

size_t				ft_strrlen(const char *str);

char				*ft_strjjoin(char *s1, char const *s2);

int					ft_strcchr(const char *str, int c);

char				*ft_strddup(char *dst, char *src);

////////////////////////FT_PRINTF///////////////////////////////

int					ft_formatspercentage(va_list args, const char format);

int					ft_putstr(char *str);

int					ft_putnbr(int n);

size_t				hexa_nbr(unsigned int n);

void				ft_puthexa(unsigned int n, bool upper_case);

int					prt_hexa(unsigned int n, bool upper_case);

size_t				address_nbr(unsigned long n);

void				ft_putaddress(unsigned long n, bool upper_case);

int					prt_address(unsigned long n, bool upper_case);

int					ft_putchar(int c);

int					ft_printf(const char *str, ...);

int					ft_putnbr_unsigned(unsigned int n);

char				*ft_itoa_unsigned(unsigned int n);

int					ft_strlenint_unsigned(unsigned int n);

#endif
