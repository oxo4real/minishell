/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:04:21 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/06 09:29:30 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

int	ft_strcmp(const char *s1, const char *s2);

void	unset(char **av, t_env **env_lst)
{
	t_env	*var;
	t_env	*head;

	if (!av[1] || !env_lst)
		return ;
	var = (*env_lst);
	while (var && ft_strcmp(var->key, av[1]) != 0)
		var = var->next;
	if (var)
	{
		head = (*env_lst);
		while (head != var && head->next != var)
			head = head->next;
		if (head == var)
			(*env_lst) = var->next;
		else
			head->next = var->next;
	}
}
