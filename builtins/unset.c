/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:04:21 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/07 13:30:42 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int			ft_strcmp(const char *s1, const char *s2);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
void		print_error3(char *shell_name, char *command,
				char *details, char *description);

static void	freenode(t_env **node);
static bool	valid_identifier(char *s);

void	unset(char **av, t_env **env_lst)
{
	t_env	*var;
	t_env	*head;
	int		i;

	if (!env_lst || !av)
		return ;
	i = 0;
	while (av[++i])
	{
		var = (*env_lst);
		while (var && ft_strcmp(var->key, av[i]) != 0)
			var = var->next;
		if (var && valid_identifier(av[i]))
		{
			head = (*env_lst);
			while (head != var && head->next != var)
				head = head->next;
			if (head == var)
				(*env_lst) = var->next;
			else
				head->next = var->next;
			freenode(&var);
		}
	}
}

static void	freenode(t_env **node)
{
	if (!node || !(*node))
		return ;
	free((*node)->key);
	free((*node)->value);
	free(*node);
	(*node) = NULL;
}

static bool	valid_identifier(char *s)
{
	char	*str;

	str = s;
	if (!s || ft_isdigit(*s))
		return (print_error3("minishell", "export", str, 
				"not a valid indentifier"), false);
	while ((*s))
	{
		if (!ft_isalnum(*s) || (*s) == '_')
			return (print_error3("minishell", "export", str, 
					"not a valid indentifier"), false);
		s++;
	}
	return (true);
}
