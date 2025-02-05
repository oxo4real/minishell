/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoenvlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:38:54 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/05 13:49:01 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

static char	**split_var(char *var);
static char	**alloc_rendu(char *var);
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

static char	**split_var(char *var)
{
	char	**rendu;
	int		start;
	int		count;

	count = -1;
	rendu = alloc_rendu(var);
	if (!rendu)
		return (NULL);
	while (var[++count] && var[count] != '=')
		rendu[0][count] = var[count];
	rendu[0][count] = '\0';
	start = count;
	if (var[count])
		start = count + 1;
	count = 0;
	while (var[start + count])
	{
		rendu[1][count] = var[start + count];
		count++;
	}
	rendu[1][count] = '\0';
	return (rendu);
}

static char	**alloc_rendu(char *var)
{
	int		start;
	int		count;
	char	**rendu;

	rendu = malloc(sizeof(char *) * 2);
	if (!rendu)
		return (NULL);
	count = 0;
	while (var[count] && var[count] != '=')
		count++;
	rendu[0] = malloc(sizeof(char) * (count + 1));
	if (!rendu[0])
		return (free(rendu), NULL);
	start = count;
	if (var[count])
		start = count + 1;
	count = 0;
	while (var[start + count])
		count++;
	rendu[1] = malloc(sizeof(char) * (count + 1));
	if (!rendu[1])
		return (free(rendu[0]), free(rendu), NULL);
	return (rendu);
}

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

static int	expandenvlst(t_env **env_lst, char	**splited)
{
	t_env	*new;
	t_env	*head;

	if (!env_lst)
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
