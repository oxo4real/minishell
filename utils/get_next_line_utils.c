/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:51:36 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/26 10:07:08 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	len1 = ft_strlen2(s1);
	len2 = ft_strlen2(s2);
	new = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, len1);
	ft_memcpy(new + len1, s2, len2);
	new[len1 + len2] = '\0';
	return (new);
}

int	check_for(char *buff, char c)
{
	int	i;

	i = 0;
	while (buff && buff[i])
	{
		if (buff[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlen2(const char *s)
{
	size_t	len;

	len = 0;
	while (s && ((const unsigned char *)s)[len] != '\0')
		len++;
	return (len);
}
