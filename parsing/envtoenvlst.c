/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoenvlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:38:54 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/06 10:10:34 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

char		**split_var(char *var);
void		envlstclear(t_env **env_lst);

static int	expandenvlst(t_env **env_lst, char	**splited);

t_env	*envtoenvlst(char **env)
{
	int		i;
	char	**splited;
	t_env	*env_lst;

	env_lst = NULL;
	i = 0;
	while (env[i])
	{
		splited = split_var(env[i]);
		if (!splited)
			return (envlstclear(&env_lst), NULL);
		if (!expandenvlst(&env_lst, splited))
			return (free(splited[0]), free(splited[1]), free(splited),
				envlstclear(&env_lst), NULL);
		free(splited);
		i++;
	}
	return (env_lst);
}

static int	expandenvlst(t_env **env_lst, char	**splited)
{
	t_env	*new;
	t_env	*head;

	if (!env_lst || !splited)
		return (0);
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = splited[0];
	new->value = splited[1];
	new->next = NULL;
	if (!(*env_lst))
		(*env_lst) = new;
	else
	{
		head = (*env_lst);
		while (head->next)
			head = head->next;
		head->next = new;
	}
	return (1);
}
