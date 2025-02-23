/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:58:42 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/23 10:35:57 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_flag(const char *s);

void	echo(char **av)
{
	int	newline;
	int	i;

	if (!av)
		return ;
	if (write(1, NULL, 0) < 0)
		return (print_error("minishell", "echo", "write error"),
			exit(EXIT_FAILURE));
	newline = 1;
	i = 1;
	while (av[i] && is_flag(av[i]))
	{
		newline = 0;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		printf("\n");
	// exit(EXIT_SUCCESS);
}

static int	is_flag(const char *s)
{
	if (*s != '-')
		return (0);
	s++;
	while (*s && *s != ' ')
	{
		if (*s != 'n')
			return (0);
		s++;
	}
	return (1);
}
