/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:24:30 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/19 13:43:29 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_node(t_node **head, char *s, int *i)
{
	t_token	tk;
	t_node	*new;

	tk = match_tk(&s[*i]);
	if (!is_cmd(&s[*i]))
		new = nodenew(tk, NULL);
	else
		new = handle_cmd(s, i);
	if (!new)
		return (1);
	nodeadd_back(head, new);
	return (0);
}

static bool	handle_sep(char *s, int *i, t_node **nodes)
{
	t_token	tk;

	tk = match_tk(&s[*i]);
	if (handle_node(nodes, s, i))
		return (1);
	*i += 1 + (tk == AND || tk == OR);
	while (is_space(s[*i]))
		(*i)++;
	if (!s[*i] || (!is_cmd(&s[*i]) && match_tk(&s[*i]) != LPR))
	{
		print_unexpected(match_tk_str(match_tk(&s[*i])));
		return (1);
	}
	return (0);
}

bool	tokenizer(char *s, t_node **nodes)
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
			if (handle_sep(s, &i, nodes))
				return (1);
		}
		else if (tk == RPR || tk == LPR)
		{
			if (handle_par(s, &i, nodes, &par))
				return (1);
		}
		else if (handle_node(nodes, s, &i))
			return (1);
	}
	return (0);
}
