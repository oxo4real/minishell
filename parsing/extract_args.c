/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:44:22 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/22 20:49:02 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	count_args(char *s)
{
	size_t	count;
	bool	is_word;
	char	q;

	is_word = 0;
	q = -1;
	count = 0;
	while (*s)
	{
		toggle_q(*s, &q);
		if (is_space(*s) && q == -1)
			is_word = 0;
		else if (!is_word)
		{
			count++;
			is_word = 1;
		}
		s++;
	}
	return (count);
}

size_t	arg_len(char *s)
{
	size_t	count;
	char	q;

	q = -1;
	count = 0;
	while (*s && (!is_space(*s) || q != -1))
	{
		if (((*s == '\'' || *s == '"') && q == -1) || (*s == '\'' && q == *s)
			|| (*s == '"' && q == *s))
		{
			if (q == -1)
				q = *s;
			else if (q == *s)
				q = -1;
		}
		else
			count++;
		s++;
	}
	return (count);
}

char	*polish_arg(char *s)
{
	char	*new;
	char	q;
	int		k;

	k = 0;
	q = -1;
	new = ft_calloc(arg_len(s) + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (*s && (!is_space(*s) || q != -1))
	{
		if (((*s == '\'' || *s == '"') && q == -1) || (*s == '\'' && q == *s)
			|| (*s == '"' && q == *s))
		{
			if (q == -1)
				q = *s;
			else if (q == *s)
				q = -1;
		}
		else
			new[k++] = *s;
		s++;
	}
	return (new);
}

char	**extract_args(char *s)
{
	char	**new;
	int		k;
	char	q;
	bool	is_word;

	is_word = 0;
	q = -1;
	k = 0;
	new = ft_calloc(count_args(s) + 1, sizeof(char *));
	while (*s && new)
	{
		toggle_q(*s, &q);
		if (is_space(*s) && q == -1)
			is_word = 0;
		else if (!is_word)
		{
			new[k] = polish_arg(s);
			if (!new[k])
				return (freestrarr(&new), NULL);
			k++;
			is_word = 1;
		}
		s++;
	}
	return (new);
}
