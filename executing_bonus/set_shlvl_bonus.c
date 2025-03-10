/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:31:48 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:10:49 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"

static int	isvalid(t_env *shlvl);
static int	set_av1(char **av, t_env *shlvl);
static void	the_one_case(t_env *shelvl, char **av);

void	set_shlvl(t_env **env_lst, t_exec *x)
{
	t_env	*shlvl;
	char	*av[3];

	shlvl = (*env_lst);
	while (shlvl && ft_strcmp(shlvl->key, "SHLVL"))
		shlvl = shlvl->next;
	if (!set_av1(av, shlvl))
		return ;
	av[2] = NULL;
	_export(av, env_lst, x);
	free(av[1]);
}

static int	set_av1(char **av, t_env *shlvl)
{
	int		shelvl_value;
	char	*tmp;

	if (!shlvl || !isvalid(shlvl) || ft_atoi(shlvl->value) > 999)
		the_one_case(shlvl, av);
	else if (shlvl)
	{
		shelvl_value = ft_atoi(shlvl->value);
		if (shelvl_value == 999)
			av[1] = ft_strdup("SHLVL=");
		else if (shelvl_value < 0)
			av[1] = ft_strdup("SHLVL=0");
		else
		{
			tmp = ft_itoa(shelvl_value + 1);
			if (!tmp)
				return (0);
			av[1] = ft_strjoin("SHLVL", tmp, "=");
			free(tmp);
		}
	}
	if (!av[1])
		return (0);
	return (1);
}

static int	isvalid(t_env *shlvl)
{
	int	i;

	if (!shlvl || !shlvl->value)
		return (0);
	i = 0;
	while (shlvl->value[i] == ' ')
		i++;
	if (shlvl->value[i] == '-' || shlvl->value[i] == '+')
		i++;
	if (!ft_isdigit(shlvl->value[i]))
		return (0);
	while (ft_isdigit(shlvl->value[i]))
		i++;
	while (shlvl->value[i] == ' ')
		i++;
	if (shlvl->value[i] != '\0')
		return (0);
	return (1);
}

static void	the_one_case(t_env *shelvl, char **av)
{
	av[1] = ft_strdup("SHLVL=1");
	if (shelvl && ft_atoi(shelvl->value) > 999)
	{
		ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
		ft_putnbr_fd(ft_atoi(shelvl->value) + 1, STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
	}
}
