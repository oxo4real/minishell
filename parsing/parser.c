/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:15:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/23 14:44:57 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

t_node	*pop(t_node **head)
{
	t_node	*poped;

	poped = NULL;
	if (!*head)
		return (NULL);
	poped = *head;
	*head = poped->next;
	poped->next = NULL;
	return (poped);
}

void	print_tree_preorder(t_node *head)
{
	t_node	*stack;
	t_node	*curr;

	stack = NULL;
	curr = head;
	if (!curr)
		return ;
	nodeadd_front(&stack, curr);
	while (stack)
	{
		curr = pop(&stack);
		if (curr->type == STR)
			printf("%s\n", curr->cmd);
		else
			printf("%s\n", match_tk_name(curr->type));
		if (curr->r_child)
			nodeadd_front(&stack, curr->r_child);
		if (curr->l_child)
			nodeadd_front(&stack, curr->l_child);
	}
}

t_node	*parser(char *line)
{
	char	*s;
	t_node	*head;

	head = NULL;
	s = ft_strtrim(line, " \t\v\n\f\r");
	free(line);
	if (!s)
		return (NULL);
	if (check_begining(s))
		return (free(s), NULL);
	if (tokenizer(s, &head))
		return (free(s), clear_nodes(&head), NULL);
	free(s);
	// print_nodes(head);
	// clear_nodes(&head);
	// return (NULL);
	return (shunting_yard(head));
}
