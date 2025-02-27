/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_types_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:56:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:11:17 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

bool	is_cmd(char *s)
{
	t_token	tk;

	tk = match_tk(s);
	return (tk == STR || tk == APPEND || tk == OUT || tk == HEREDOC
		|| tk == IN);
}

bool	is_redir(char *s)
{
	t_token	tk;

	tk = match_tk(s);
	return (tk == IN || tk == OUT || tk == HEREDOC || tk == APPEND);
}

bool	is_valid_filename_end(char *s, char q)
{
	t_token	tk;

	tk = next_token(s);
	if (q != ' ' && *s != q)
		return (true);
	else if (q == ' ' && tk == STR && (*s != '\'' && *s != '"') && *s != ' ')
		return (true);
	return (false);
}

bool	is_space(char c)
{
	return (c == ' ' || (unsigned)c - '\t' < 5);
}
