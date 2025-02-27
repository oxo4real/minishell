/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacewildcards_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:45:12 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:11:17 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static void	replacewildcard(char **str, char *tmp, int *i);

void	replacewildcards(char **str)
{
	int	i;

	if (!str || !(*str))
		return ;
	i = ft_strlen((*str));
	while (i-- > 0)
	{
		if ((*str)[i] != SEP)
			replacewildcard(str, &((*str)[i]), &i);
	}
}

static void	replacewildcard(char **str, char *tmp, int *i)
{
	char	*sep;
	char	*rendu;

	while ((*i) > -1 && (*str)[*i] != SEP)
		(*i)--;
	sep = getsortedwildcard(&(*str)[(*i) + 1]);
	if (!sep)
		return ;
	if ((*i) > 0)
		(*str)[*i] = '\0';
	else
		(*str)[0] = '\0';
	rendu = ft_strjoin((*str), tmp + 1, sep);
	free(sep);
	if (!rendu)
		return ;
	free(*str);
	(*str) = rendu;
}
