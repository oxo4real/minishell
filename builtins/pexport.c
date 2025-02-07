/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexport.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:49:12 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/07 13:04:07 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	pexport(t_env *env_lst)
{
	while (env_lst)
	{
		printf("declare -x %s", env_lst->key);
		if (env_lst->value)
			printf("=\"%s\"", env_lst->value);
		printf("\n");
		env_lst = env_lst->next;
	}
}
