/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:19:06 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/05 10:55:19 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int		ft_atoi(char *str);
void	print_error2(char *shell_name, char *command,
		char *details, char *description);
int		ft_islong(char *s);
void	ft_putstr_fd(char const *s, int fd);

static int	count_args(char **av);
static int	is_valid(char *s);

void	exit_(char **av, bool print)
{
	if (print)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (count_args(av) == 1)
		exit(0);
	else if (!is_valid(av[1]))
	{
		print_error2("minishell", "exit", av[1], "numeric argument required");
		exit(255);
	}
	else if (count_args(av) > 2)
		return (print_error2("minishell", "exit", NULL, "too many arguments"));
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
