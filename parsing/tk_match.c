/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:36:23 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:33:36 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	match_tk(char *s)
{
	if (!*s)
		return (END);
	else if (*s == '>' && *(s + 1) == '>')
		return (APPEND);
	else if (*s == '<' && *(s + 1) == '<')
		return (HEREDOC);
	else if (*s == '<')
		return (IN);
	else if (*s == '>')
		return (OUT);
	else if (*s == '|')
		return (PIPE);
	return (STR);
}

char	*match_tk_str(t_token type)
{
	if (type == END)
		return ("newline");
	else if (type == APPEND)
		return (">>");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == IN)
		return ("<");
	else if (type == OUT)
		return (">");
	else if (type == PIPE)
		return ("|");
	return ("STR");
}

char	*match_tk_name(t_token type)
{
	if (type == END)
		return ("END");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == IN)
		return ("IN");
	else if (type == OUT)
		return ("OUT");
	else if (type == PIPE)
		return ("PIPE");
	return ("STR");
}
