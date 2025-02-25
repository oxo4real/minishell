/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handle_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:44:45 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/25 12:33:10 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	check_syntax_redir_helper(char *s, int *i)
{
	t_token	tk;

	tk = match_tk(&s[*i]);
	if (tk == APPEND || tk == HEREDOC)
		(*i)++;
	(*i)++;
	if (next_token(&s[*i]) != STR)
	{
		if (next_token(&s[*i]) == END)
			print_unexpected("newline");
		else
			print_unexpected(match_tk_str(next_token(&s[*i])));
		return (1);
	}
	return (0);
}

static bool	check_syntax_redir(char *s, int i, int k)
{
	char	q;

	q = -1;
	while (s[i] && i < k)
	{
		toggle_q(s[i], &q);
		if (q == -1 && is_redir(&s[i]))
		{
			if (check_syntax_redir_helper(s, &i))
				return (1);
		}
		else
			i++;
	}
	if (q != -1)
	{
		printf(SH_NAME ": unexpected EOF while looking for matching `%c'\n", q);
		return (1);
	}
	return (0);
}

static void	traverse_cmd(char *s, int *i, int *k, int *j)
{
	char	q;

	q = -1;
	*k = 0;
	*j = 0;
	while (s[*i + *k] && (is_cmd(&s[*i + *k]) || q != -1))
	{
		toggle_q(s[*i + *k], &q);
		if (is_space(s[*i + *k]))
			(*j)++;
		else
			*j = 0;
		(*k)++;
	}
}

static void	polish_cmd(t_node *node)
{
	int	i;

	i = 0;
	while (node->cmd[i])
	{
		if (!is_space(node->cmd[i]))
			return ;
		i++;
	}
	free(node->cmd);
	node->cmd = NULL;
}

t_node	*handle_cmd(char *s, int *i, t_exec *x)
{
	int		j;
	int		k;
	char	*cmd;
	t_node	*new;

	traverse_cmd(s, i, &k, &j);
	if (next_token(&s[*i + k]) == LPR)
	{
		print_unexpected(match_tk_str(LPR));
		return (x->status = 258, NULL);
	}
	if (check_syntax_redir(s, *i, *i + k))
		return (x->status = 258, NULL);
	cmd = strdup_to(&s[*i], (size_t)k - (size_t)j);
	if (!cmd)
		return (NULL);
	new = nodenew(STR, cmd);
	if (!new)
		return (free(cmd), NULL);
	if (look_for_redir(new))
		return (free(cmd), free(new), NULL);
	polish_cmd(new);
	*i += k;
	return (new);
}
