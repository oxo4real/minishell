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
static void	removemainqotes(char **str);

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
		//return (removemainqotes()); // TODO: code this function
		return ;
	if ((*i) > 0)
		(*str)[*i] = '\0';
	else
	 	(*str)[0] = '\0';
	rendu = ft_strjoin((*str), tmp + 1, sep);
	//free(sep);
	free(*str);
	(*str) = rendu;
}
