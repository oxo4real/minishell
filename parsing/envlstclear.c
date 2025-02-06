/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:09:34 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/06 10:10:20 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

void	envlstclear(t_env **env_lst)
{
	t_env	*tmp;

	if (!env_lst || !(*env_lst))
		return ;
	while ((*env_lst))
	{
		free((*env_lst)->key);
		free((*env_lst)->value);
		tmp = (*env_lst);
		(*env_lst) = (*env_lst)->next;
		free(tmp);
	}
	(*env_lst) = NULL;
}
