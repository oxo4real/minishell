/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:58:42 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:10:49 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"

static int	is_flag(const char *s);

void	echo(char **av, t_exec *x)
{
	int	newline;
	int	i;

	if (write(1, NULL, 0) < 0)
	{
		x->status = 1;
		return (print_error("minishell", "echo", "write error"));
	}
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
		ft_putchar_fd('\n', 1);
	x->status = 0;
}

static int	is_flag(const char *s)
{
	if (*s != '-')
		return (0);
	s++;
	if (*s != 'n')
		return (0);
	while (*s && *s != ' ')
	{
		if (*s != 'n')
			return (0);
		s++;
	}
	return (1);
}
