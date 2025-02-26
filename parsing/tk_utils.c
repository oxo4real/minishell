/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:06:52 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/26 20:51:45 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	next_token(char *s)
{
	while (*s && is_space(*s))
		s++;
	if (!*s)
		return (END);
	return (match_tk(s));
}

void	toggle_q(char c, char *q)
{
	if (c == '"' || c == '\'')
	{
		if (c == *q)
			*q = -1;
		else if (*q == -1)
			*q = c;
	}
}

int	tk_prec(t_token type)
{
	if (type == OR || type == AND)
		return (42);
	else if (type == PIPE)
		return (1337);
	return (0);
}

bool	check_begining(char *s, t_exec *x)
{
	t_token	tk;

	if (!*s)
		return (1);
	tk = match_tk(&s[0]);
	if (tk == AND || tk == OR || tk == RPR || tk == PIPE)
	{
		print_unexpected(match_tk_str(tk));
		x->status = 258;
		return (1);
	}
	return (0);
}

char	*strdup_to(const char *str, size_t size)
{
	char	*copy;
	size_t	i;

	copy = (char *)ft_calloc((size + 1), sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < size)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
