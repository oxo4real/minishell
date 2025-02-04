/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:19:06 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/04 20:41:50 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		ft_atoi(char *str);
void	print_error2(char *shell_name, char *command,
		char *details, char *description);
int		ft_islong(char *s);

static int	count_args(char **av);
static int	is_valid(char *s);

void	exit_(char **av)
{
	printf("exit\n");
	if (count_args(av) == 1)
		exit(0);
	else if (count_args(av) > 2)
		return (print_error2("minishell", "exit", NULL, "too many arguments"));
	if (!is_valid(av[1]))
	{
		print_error2("minishell", "exit", av[1], "numeric argument required");
		exit(255);
	}
	exit(ft_atoi(av[1]));
}

static int	count_args(char **av)
{
	int	count;

	count = 0;
	while(av[count])
		count++;
	return (count);
}

static int	is_valid(char *s)
{
	char *tmp;

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
