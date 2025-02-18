/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacewildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:12 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/18 17:45:44 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2, char const *sep);

static void	replacewildcard(char **str, char *tmp, int *i);
static void	removemainqotes(char *str);
static void	replace(char *str, int *j);

void	replacewildcards(char **str)
{
	int	i;

	if (!str || !(*str))
		return ;
	i = ft_strlen((*str));
	while (i-- > 0)
	{
		if ((*str)[i] != '\x07')
			replacewildcard(str,&((*str)[i]), &i);
	}
}

static void	replacewildcard(char **str, char *tmp, int *i)
{
	char	*sep;
	char	*rendu;

	while ((*i) > -1 && (*str)[*i] != '\x07')
		(*i)--;
	//sep = getsortedwildcard(&wildcard[*i + 1]); // TODO: code this function make it return null if there is no * outside quotes
	sep = "hello";
	if (!sep)
		return (removemainqotes(&(*str)[(*i) + 1]));
	if ((*i) > 0)
		(*str)[*i] = '\0';
	else
	 	(*str)[0] = '\0';
	rendu = ft_strjoin((*str), tmp + 1, sep);
	//free(sep);
	free(*str);
	(*str) = rendu;
}

void removemainqotes(char *str)
{
	int	j;

	if (!str)
		return ;
	j = 0;
	replace(str, &j);
	while (str[j] && str[j] != '\x07')
		str[j++] = '\x07';
}

static void	replace(char *str, int *j)
{
	int	i;
	int	in_sq;
	int	in_dq;
	
	i = 0;
	in_dq = 0;
	in_sq = 0;
	while (str[i] && str[i] != '\x07') 
	{
		if (str[i] != '\'' && str[i] != '"'
			|| str[i] == '\'' && in_dq
			|| str[i] == '"' && in_sq)
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
