/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlsttoenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:45:47 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 20:18:26 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**envlsttoenv(t_env *env_lst)
{
	int		i;
	int		len;
	char	**rendu;

	if (!env_lst)
		return (NULL);
	len = envlstlen(env_lst);
	rendu = malloc(sizeof(char *) * (len + 1));
	if (!rendu)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (env_lst->value)
		{
			rendu[i] = ft_strjoin(env_lst->key, env_lst->value, "=");
			if (!rendu[i])
				return (freestrarr(&rendu), NULL);
			i++;
		}
		env_lst = env_lst->next;
	}
	rendu[i] = NULL;
	return (rendu);
}

int	envlstlen(t_env *env_lst)
{
	int	rendu;

	rendu = 0;
	while (env_lst)
	{
		if (env_lst->value)
			rendu++;
		env_lst = env_lst->next;
	}
	return (rendu);
}
