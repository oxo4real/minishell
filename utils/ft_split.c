/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:38:27 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/22 19:54:24 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_strl(char const *str, int c)
{
	size_t	len;

	len = 0;
	while (str[len] && ((unsigned char *)str)[len] != c)
		len++;
	return (len);
}

static char	*ft_copy_str(char const **str, int c)
{
	char	*clone;
	size_t	len;

	len = ft_strl(*str, c);
	clone = (char *)malloc(sizeof(char) * (len + 1));
	if (!clone)
		return (NULL);
	ft_memcpy(clone, *str, len);
	clone[len] = '\0';
	*str += len;
	return (clone);
}

static size_t	count_words(char const *str, int c)
{
	int		i;
	size_t	count;
	int		is_word;

	count = 0;
	i = 0;
	is_word = 0;
	while (str[i])
	{
		if (((unsigned char *)str)[i] == c)
			is_word = 0;
		else if (!is_word)
		{
			is_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	free_all(char **ptr, int pos)
{
	size_t	i;

	if (ptr[pos])
		return (0);
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	if (ptr)
		free(ptr);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	len;
	int		j;

	if (!s)
		return (NULL);
	len = count_words(s, c);
	new = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	j = 0;
	new[len] = 0;
	while (*s)
	{
		if (*((unsigned char const *)s) != c)
		{
			new[j] = ft_copy_str(&s, c);
			if (free_all(new, j))
				return (NULL);
			j++;
		}
		else
			s++;
	}
	return (new);
}
