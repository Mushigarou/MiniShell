/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:51:45 by faksouss          #+#    #+#             */
/*   Updated: 2023/05/03 17:24:59 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <ttyent.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <math.h>
# include <termios.h>
# include <termcap.h>
# include <errno.h>
# include <stddef.h>
# include <signal.h>

# define WHITE "\001\e[0m\002"
# define RED "\001\e[31;1m\002"
# define YELLOW "\001\e[33;1;3m\002"
# define GREEN "\001\e[32;3;1m\002"
# define BLUE "\001\e[34;3;1m\002"

typedef struct s_list
{
	char			*pt;
	int				wt;
	int				acs;
	struct s_list	*next;
}	t_list;

typedef struct s_exec
{
	char			**cmd_exec;
	t_list			*redrc;
	int				in;
	int				out;
	int				rdrct_err;
	struct s_exec	*next;
}	t_exec;

typedef struct s_minishell
{
	int		*ext_st;
	char	*line;
	char	*prompt;
	t_exec	*exc;
	int		open_fds[1024];
	int		fd_cnt;
	t_list	*cmd;
	t_list	*env;
}	t_minishell;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *p, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memmove(void *d, const void *s, size_t l);
void	*ft_memcpy(void *d, const void *s, size_t l);
size_t	ft_strlcpy(char	*d, char *s, size_t ds);
size_t	ft_strlcat(char *dest, char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
long	ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strnstr(const char *hs, const char *ndl, size_t l);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t c, size_t s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
t_list	*ft_lstnew(char *wrd, int tp);
t_list	*dup_node(t_list *nd);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);
void	ft_lstiter(t_list *lst, void (*f)(char *));
t_list	*ft_lstmap(t_list *lst, char *(*f)(char *));
int		ft_printf(const char *s, int fd, ...);
int		ft_put_hex(unsigned long n, char frm);
int		tol(long int nb, int base);
int		ft_putun(unsigned int n);
int		ft_put_add(void *p);
int		prnt_frm(va_list arg, char frm, int fd);
void	*deallocate(char **r);
char	*gnl(int fd);

#endif
