/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit__bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:19:06 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:10:49 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"

static int	count_args(char **av);
static int	is_valid(char *s);

void	exit_(char **av, bool print, t_exec *x)
{
	if (!av)
		return ;
	if (print)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (count_args(av) == 1)
		exit(x->status);
	else if (!is_valid(av[1]))
	{
		print_error2("minishell", "exit", av[1], "numeric argument required");
		exit(255);
	}
	else if (count_args(av) > 2)
	{
		x->status = 1;
		return (print_error2("minishell", "exit", NULL, "too many arguments"));
	}
	exit(ft_atoi(av[1]));
}

static int	count_args(char **av)
{
	int	count;

	count = 0;
	while (av[count])
		count++;
	return (count);
}

static int	is_valid(char *s)
{
	char	*tmp;

	if (!s)
		return (0);
	tmp = s;
	while (*tmp == ' ')
		tmp++;
	if (!(*tmp))
		return (0);
	if (*tmp == '-' || *tmp == '+')
		tmp++;
	while (*tmp <= '9' && *tmp >= '0')
		tmp++;
	if (*tmp && *tmp != ' ')
		return (0);
	while (*tmp == ' ')
		tmp++;
	if (*tmp != '\0')
		return (0);
	return (ft_islong(s));
}
