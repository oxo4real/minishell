/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handle_par.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:40:31 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/25 12:57:38 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	checker_par_helper(char *s, int *i)
{
	char	q;

	q = -1;
	while (s[*i])
	{
		toggle_q(s[*i], &q);
		if (q == -1 && s[*i] == ')')
			break ;
		(*i)++;
	}
	if (!s[*i])
	{
		print_syntax_error("unclosed parentheses");
		return (1);
	}
	return (0);
}

static bool	check_par(char *s, int i, int *par)
{
	if (s[i] == ')' && *par != -1 && i <= *par)
		return (0);
	else if (s[i] == ')')
	{
		print_unexpected(match_tk_str(RPR));
		return (1);
	}
	if (*par != -1)
		i = *par;
	i++;
	if (checker_par_helper(s, &i))
		return (1);
	*par = i;
	return (0);
}

int	handle_par(char *s, int *i, int *par, t_exec *x)
{
	t_token	tk;
	t_token	ntk;

	tk = match_tk(&s[*i]);
	ntk = next_token(&s[*i + 1]);
	if (tk == RPR && (ntk != RPR && ntk != AND && ntk != OR && ntk != PIPE
			&& ntk != END))
	{
		print_unexpected(match_tk_str(tk));
		return (x->status = 258, 1);
	}
	if (check_par(s, *i, par))
		return (x->status = 258, 1);
	if (handle_node(s, i, x))
		return (1);
	(*i)++;
	while (is_space(s[*i]))
		(*i)++;
	if ((!s[*i] || !is_cmd(&s[*i])) && tk != RPR && match_tk(&s[*i]) != LPR)
	{
		print_unexpected(match_tk_str(match_tk(&s[*i])));
		return (x->status = 258, 1);
	}
	return (0);
}
