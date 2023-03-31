/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:27:39 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 05:45:45 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define DECIMAL "0123456789"
# define HEXA_LOWER "0123456789abcdef"
# define HEXA_UPPER "0123456789ABCDEF"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define FILE_DESCRIPTORS 256

# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_dynamic_string {
	char	*content;
	int		length;
	int		capacity;
}	t_dynamic_string;

// srcs/chars
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

// srcs/clean
void				ft_close(int *fd);
void				ft_free(void **ptr);
void				ft_free_double(void ***ptr);
void				ft_free_triple(void ****ptr);

// srcs/conversion
int					ft_atoi(const char *nptr);
bool				ft_atoi_safe(char *s, int *n);
char				*ft_itoa(int n);
char				*ft_itoa_base(unsigned long n, char *base);

// srcs/dynamic_strings
bool				ft_ds_add_nbr(t_dynamic_string *buffer, int n);
bool				ft_ds_add_nbr_base(
						t_dynamic_string *buffer, unsigned long n, char *base);
bool				ft_ds_append(t_dynamic_string *ds, char c);
bool				ft_ds_extend(t_dynamic_string *s1, char *s2, size_t len2);
bool				ft_ds_extend_free(t_dynamic_string *buffer, char *s);
t_dynamic_string	ft_ds_new(char *s);

// srcs/ft_printf
int					ft_dprintf(int fd, const char *format, ...);
int					ft_printf(const char *format, ...);
char				*ft_sprintf(const char *format, ...);
int					ft_vdprintf(int fd, const char *format, va_list ap);
int					ft_vprintf(const char *format, va_list ap);
char				*ft_vsprintf(const char *format, va_list ap);

// srcs/ft_split
size_t				ft_num_words(char const *s, char const *set);
char				**ft_split_set(char const *s, char const *set);
char				**ft_split(char const *s, char c);

// srcs/get_next_line
char				*get_next_line(int fd);

// srcs/linked_lists
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst,
						void *(*f)(void *), void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				*ft_lst_get(const t_list *lst, size_t idx);
bool				ft_lst_includes(const t_list *lst, void *x);
void				ft_lst_sort(t_list *lst, int (*cmp)(void *, void *));

//srcs/memory
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);

// srcs/output
int					ft_putbase_fd(unsigned long n,
						char *base, size_t base_length, int fd);
int					ft_putchar_fd(char c, int fd);
int					ft_putendl_fd(char *s, int fd);
int					ft_putnbr_fd(int n, int fd);
int					ft_putstr_fd(char *s, int fd);

// src/strings
bool				ft_endswith(const char *str, const char *end);
bool				ft_startswith(const char *str, const char *start);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin3(char const *s1, char const *s2,
						char const *s3);
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_strjoin_arr(char **strs, char *sep, char *end);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strnstr(
						const char *big, const char *little, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);

#endif
