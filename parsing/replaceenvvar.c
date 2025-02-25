/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replaceenvvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 07:56:13 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/25 20:40:51 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	skipquote(int *i, char *str);
static void	replace(char **str, char *dollar, t_env *env_lst, t_exec *x);
static char	*findenvvar(char *dollar, size_t i, t_env *env_lst, t_exec *x);

void	replaceenvar(t_env *env_lst, char **str, t_exec *x)
{
	int	i;
	int	in_dq;

	if (!env_lst || !str || !(*str))
		return ;
	i = ft_strlen((*str));
	in_dq = 0;
	while (i-- > 0)
	{
		if ((*str)[i] == '\'' && !in_dq)
			skipquote(&i, (*str));
		else if ((*str)[i] == '"')
		{
			if (!in_dq)
				in_dq = 1;
			else
				in_dq = 0;
		}
		else if ((*str)[i] == '$')
			replace(str, &((*str)[i]), env_lst, x);
	}
}

static void	skipquote(int *i, char *str)
{
	char	quote;

	quote = str[(*i)--];
	while ((*i) > -1 && str[*i] != quote)
		(*i)--;
}

static void	replace(char **str, char *dollar, t_env *env_lst, t_exec *x)
{
	size_t	i;
	char	*rendu;
	char	*sep;

	i = 1;
	if (!ft_isalnum(dollar[i]) && dollar[i] != '_' && dollar[i] != '?')
		return ;
	(*dollar) = '\0';
	if (!ft_isdigit(dollar[i]) && dollar[i] != '?')
	{
		while (dollar[i] && (ft_isalnum(dollar[i]) || dollar[i] == '_'))
			i++;
	}
	else
		i++;
	sep = findenvvar(&dollar[1], i - 1, env_lst, x);
	if (!sep)
		rendu = ft_strjoin((*str), &dollar[i], "");
	else
		rendu = ft_strjoin((*str), &dollar[i], sep);
	free(sep);
	if (!rendu)
		return ;
	free(*str);
	(*str) = rendu;
}

static char	*findenvvar(char *dollar, size_t i, t_env *env_lst, t_exec *x)
{
	if (ft_strncmp("?", dollar, 1) == 0)
		return (ft_itoa(x->status));
	while (env_lst)
	{
		if (ft_strlen(env_lst->key) == i && ft_strncmp(env_lst->key, dollar,
				i) == 0 && env_lst->value)
			return (ft_strdup(env_lst->value));
		env_lst = env_lst->next;
	}
	return (NULL);
}
