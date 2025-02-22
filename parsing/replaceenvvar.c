/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replaceenvvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 07:56:13 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 20:30:30 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	skipquote(int *i, char *str);
static void	replace(char **str, char *dollar, t_env *env_lst);
static char	*findenvvar(char *dollar, size_t i, t_env *env_lst);

void	replaceenvar(t_env *env_lst, char **str)
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
			replace(str, &((*str)[i]), env_lst);
	}
}

static void	skipquote(int *i, char *str)
{
	char	quote;

	quote = str[(*i)--];
	while ((*i) > -1 && str[*i] != quote)
		(*i)--;
}

static void	replace(char **str, char *dollar, t_env *env_lst)
{
	size_t	i;
	char	*rendu;
	char	*sep;

	i = 1;
	if (!ft_isalnum(dollar[i]) && dollar[i] != '_')
		return ;
	(*dollar) = '\0';
	if (!ft_isdigit(dollar[i]))
	{
		while (dollar[i] && (ft_isalnum(dollar[i]) || dollar[i] == '_'))
			i++;
	}
	else
		i++;
	sep = findenvvar(&dollar[1], i - 1, env_lst);
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

static char	*findenvvar(char *dollar, size_t i, t_env *env_lst)
{
	while (env_lst)
	{
		if (ft_strlen(env_lst->key) == i && ft_strncmp(env_lst->key, dollar,
				i) == 0)
			return (ft_strdup(env_lst->value));
		env_lst = env_lst->next;
	}
	return (NULL);
}
