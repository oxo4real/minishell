/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_yard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:11:52 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/19 18:00:11 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Removes and returns the first node from a linked list of AST nodes.
 *
 * This function extracts the first node from the list,
	updating the head pointer.
 * If the extracted node is of type STR,
	its child and next pointers are set to NULL
 * to ensure proper cleanup.
 *
 * @param head A pointer to the head of the linked list of AST nodes.
 * @return A pointer to the popped node, or NULL if the list is empty.
 */
t_node	*pop_node(t_node **head)
{
	t_node	*poped;

	poped = NULL;
	if (!*head)
		return (NULL);
	poped = *head;
	*head = poped->next;
	if (poped->type == STR)
	{
		poped->r_child = NULL;
		poped->next = NULL;
		poped->l_child = NULL;
	}
	return (poped);
}

void	move_and_convrt(t_node **polished, t_node **op)
{
	t_node	*tmp2;
	t_node	*popped1;
	t_node	*popped2;

	if (!*polished || !*op)
		return ;
	while ((*op) && (*op)->type != LPR)
	{
		tmp2 = (*op)->next;
		popped1 = pop_node(polished);
		popped2 = pop_node(polished);
		(*op)->r_child = popped1;
		(*op)->l_child = popped2;
		nodeadd_front(polished, (*op));
		(*op) = tmp2;
	}
	if ((*op) && (*op)->type == LPR)
	{
		tmp2 = (*op)->next;
		free_node((*op));
		(*op) = tmp2;
	}
}

static void	shunting_yard_helper(t_node *head, t_node **polished, t_node **op)
{
	if (head->type == RPR)
	{
		move_and_convrt(polished, op);
		free_node(head);
	}
	else if (!*op || tk_prec((*op)->type) < tk_prec(head->type))
		nodeadd_front(op, head);
	else
	{
		if (head->type == AND || head->type == OR)
			move_and_convrt(polished, op);
		nodeadd_front(op, head);
	}
}

/**
 * @brief Converts a linked list of nodes into an Abstract Syntax Tree (AST)
 *			using the Shunting Yard algorithm.
 *
 * This function processes a list of nodes representing shell
 * commands and operators,
 * building an AST by applying the **Shunting Yard algorithm**.
 * It ensures correct precedence
 * handling for logical and redirection operators.
 *
 * @param head The head of the tokenized command list.
 * @return A pointer to the root node of the generated AST.
 */

t_node	*shunting_yard(t_node *head)
{
	t_node	*op;
	t_node	*polished;
	t_node	*tmp;

	op = NULL;
	polished = NULL;
	while (head)
	{
		tmp = head->next;
		if (head->type == STR)
			nodeadd_front(&polished, head);
		else
			shunting_yard_helper(head, &polished, &op);
		head = tmp;
	}
	move_and_convrt(&polished, &op);
	return (polished);
}
