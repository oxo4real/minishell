/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoenvlst_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:38:54 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:11:17 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

t_env	*envtoenvlst(char **env)
{
	int		i;
	char	**splited;
	t_env	*env_lst;

	if (!env)
		return (NULL);
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
