/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:44:22 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:42:18 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

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
