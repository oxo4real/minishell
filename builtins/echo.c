/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:58:42 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/06 10:53:07 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_flag(const char *s);
void		print_error(char *shell_name, char *command, char *details);

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
		print_error("minishell", "echo", "write error");
		if (av[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	exit(EXIT_SUCCESS);
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
