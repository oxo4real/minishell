/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:24:30 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/25 18:26:17 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_node(char *s, int *i, t_exec *x)
{
	t_token	tk;
	t_node	*new;

	tk = match_tk(&s[*i]);
	if (!is_cmd(&s[*i]))
		new = nodenew(tk, NULL);
	else
		new = handle_cmd(s, i, x);
	if (!new)
		return (1);
	nodeadd_back(&x->head, new);
	return (0);
}

static bool	handle_sep(char *s, int *i, t_exec *x)
{
	t_token	tk;

	tk = match_tk(&s[*i]);
	if (handle_node(s, i, x))
		return (1);
	*i += 1 + (tk == AND || tk == OR);
	while (is_space(s[*i]))
		(*i)++;
	if (!s[*i] || (!is_cmd(&s[*i]) && match_tk(&s[*i]) != LPR))
	{
		if (next_token(&s[*i]) == END)
			print_syntax_error("unexpected end of file");
		else
			print_unexpected(match_tk_str(next_token(&s[*i])));
		return (x->status = 258, 1);
	}
	return (0);
}

bool	tokenizer(char *s, t_exec *x)
{
	t_token	tk;
	int		i;
	int		par;

	i = 0;
	par = -1;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		tk = match_tk(&s[i]);
		if (tk == AND || tk == OR || tk == PIPE)
		{
			if (handle_sep(s, &i, x))
				return (1);
		}
		else if (tk == RPR || tk == LPR)
		{
			if (handle_par(s, &i, &par, x))
				return (1);
		}
		else if (handle_node(s, &i, x))
			return (1);
	}
	return (0);
}
