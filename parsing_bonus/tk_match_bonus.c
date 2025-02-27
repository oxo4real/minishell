/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_match_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:36:23 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:11:17 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

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
	else if (*s == '|' && *(s + 1) == '|')
		return (OR);
	else if (*s == '&' && *(s + 1) == '&')
		return (AND);
	else if (*s == '|')
		return (PIPE);
	else if (*s == '(')
		return (LPR);
	else if (*s == ')')
		return (RPR);
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
	else if (type == OR)
		return ("||");
	else if (type == AND)
		return ("&&");
	else if (type == PIPE)
		return ("|");
	else if (type == LPR)
		return ("(");
	else if (type == RPR)
		return (")");
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
	else if (type == OR)
		return ("OR");
	else if (type == AND)
		return ("AND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == LPR)
		return ("LPR");
	else if (type == RPR)
		return ("RPR");
	return ("STR");
}
