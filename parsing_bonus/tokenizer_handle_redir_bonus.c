/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handle_redir_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:48:24 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:11:17 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static void	clear_traces(char *s, size_t i, char q)
{
	i = 0;
	while (s[i])
	{
		toggle_q(s[i], &q);
		if (q != -1)
		{
			s[i] = ' ';
			i++;
			continue ;
		}
		if (s[i] == ' ' || match_tk(&s[i]) != STR)
			break ;
		s[i] = ' ';
		i++;
	}
}

static char	*aloc_fname(char *s, size_t i, char q)
{
	char	*new;

	while (s[i])
	{
		toggle_q(s[i], &q);
		if (q != -1)
		{
			i++;
			continue ;
		}
		if (s[i] == ' ' || match_tk(&s[i]) != STR)
			break ;
		i++;
	}
	new = strdup_to(s, i);
	if (!new)
		return (NULL);
	clear_traces(s, i, q);
	return (new);
}

static char	*take_filename(char *s)
{
	char	*new;
	size_t	i;
	char	q;

	q = -1;
	i = 0;
	while (is_space(*s))
		s++;
	new = aloc_fname(s, i, q);
	if (!new)
		return (NULL);
	return (new);
}

static bool	handle_redir(t_node *node, char *s, int *i)
{
	t_token	tk;
	t_redir	*new_redir;
	char	*fname;

	tk = match_tk(&s[*i]);
	if (tk == APPEND || tk == HEREDOC)
	{
		s[*i] = ' ';
		(*i)++;
	}
	s[*i] = ' ';
	(*i)++;
	fname = take_filename(&s[*i]);
	if (!fname)
		return (1);
	new_redir = redirnew(tk, fname);
	if (!new_redir)
		return (free(fname), 1);
	rediradd_back(&node->redir, new_redir);
	return (0);
}

bool	look_for_redir(t_node *node)
{
	int		i;
	char	q;
	char	*s;

	s = node->cmd;
	i = 0;
	q = -1;
	while (s[i])
	{
		toggle_q(s[i], &q);
		if (q == -1 && is_redir(&s[i]))
		{
			if (handle_redir(node, s, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
