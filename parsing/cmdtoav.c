/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtoav.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:59:26 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/25 19:54:01 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	removemainqotes(char *str);
static void	replace(char *str, int *j);

char	**cmdtoav(char **cmd, t_env *env_lst, t_exec *x)
{
	char	**av;
	int		i;

	replaceenvar(env_lst, cmd, x);
	sptobel(*cmd);
	replacewildcards(cmd);
	av = ft_split(*cmd, SEP);
	if (!av)
		return (NULL);
	i = 0;
	while (av[i])
		removemainqotes(av[i++]);
	return (av);
}

static void	removemainqotes(char *str)
{
	int	j;

	if (!str)
		return ;
	j = 0;
	replace(str, &j);
	while (str[j])
		str[j++] = '\0';
}

static void	replace(char *str, int *j)
{
	int	i;
	int	in_sq;
	int	in_dq;

	i = 0;
	in_dq = 0;
	in_sq = 0;
	while (str[i] && str[i] != SEP)
	{
		if ((str[i] != '\'' && str[i] != '"') || (str[i] == '\'' && in_dq)
			|| (str[i] == '"' && in_sq))
			str[(*j)++] = str[i];
		if (str[i] == '\'' && !in_sq && !in_dq)
			in_sq = 1;
		else if (str[i] == '\'' && in_sq)
			in_sq = 0;
		if (str[i] == '"' && !in_dq && !in_sq)
			in_dq = 1;
		else if (str[i] == '"' && in_dq)
			in_dq = 0;
		i++;
	}
}
