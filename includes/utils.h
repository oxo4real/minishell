/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:31:28 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/26 11:25:45 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

void	freestrarr(char ***arr);
int		ft_atoi(char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char const *s, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2, char const *sep);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
int		check_for(char *buff, char c);
char	*ft_strjoin2(char *s1, char *s2);
size_t	ft_strlen2(const char *s);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
int		ft_wordcmp(char *w1, char *w2);
char	*generaterandstr(void);
int		ft_islong(char *w);
void	print_error(char *shell_name, char *command, char *details);
void	print_error2(char *shell_name, char *command, char *details,
			char *description);
void	print_error3(char *shell_name, char *command, char *details,
			char *description);
#endif
