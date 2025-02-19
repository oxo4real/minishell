/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:41:29 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/19 13:50:43 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->cmd)
		(free(node->cmd), node->cmd = NULL);
	if (node->redir)
		clear_redir(&node->redir);
	free(node);
}

void	free_tree(t_node *head)
{
	if (!head)
		return ;
	free_tree(head->l_child);
	free_tree(head->r_child);
	free_node(head);
}

/* DELETE */
void	print_tree(t_node *head)
{
	if (!head)
		return ;
	if (head->type == STR)
		printf("%s\n", head->cmd);
	else
		printf("%s\n", match_tk_name(head->type));
	print_tree(head->l_child);
	print_tree(head->r_child);
}
