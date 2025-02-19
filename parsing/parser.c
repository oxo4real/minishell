/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:15:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/19 18:26:31 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_nodes(t_node *head)
{
	t_redir	*redir;

	while (head)
	{
		if (head->type == STR)
		{
			redir = head->redir;
			printf("CMD:{%s}\n", head->cmd);
			while (redir)
			{
				printf("%s:{%s}\n", match_tk_name(redir->type),
					redir->filename);
				redir = redir->next;
			}
		}
		else
			printf("%s\n", match_tk_str(head->type));
		head = head->next;
	}
}

bool	parser(char *line)
{
	char	*s;
	t_node	*head;

	head = NULL;
	s = ft_strtrim(line, " \t\v\n\f\r");
	free(line);
	if (!s)
		return (1);
	if (check_begining(s))
		return (free(s), 1);
	if (tokenizer(s, &head))
		return (free(s), clear_nodes(&head), 1);
	free(s);
	// print_nodes(head);
	head = shunting_yard(head);
	print_tree(head);
	free_tree(head);
	return (0);
}
