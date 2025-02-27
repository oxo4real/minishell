/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:44:11 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:12:06 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2, char const *sep)
{
	int		size;
	size_t	i;
	size_t	j;
	char	*rendu;

	if (!s1 || !s2 || !sep)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(sep) + 1;
	rendu = (char *)malloc(size);
	if (!rendu)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_strlen(s1))
		rendu[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(sep))
		rendu[i++] = sep[j++];
	j = 0;
	while (j < ft_strlen(s2))
		rendu[i++] = s2[j++];
	rendu[i] = 0;
	return (rendu);
}
