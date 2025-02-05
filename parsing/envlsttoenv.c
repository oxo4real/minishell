/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlsttoenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:45:47 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/05 14:59:46 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

int		envlstlen(t_env *env_lst);
char	*ft_strjoin(char const *s1, char const *s2, char const *sep);
void	freestrarr(char ***arr);

char	**envlsttoenv(t_env *env_lst)
{
	int		i;
	int		len;
	char	**rendu;

	len = envlstlen(env_lst);
	rendu = malloc(sizeof(char *) * (len + 1));
	if (!rendu)
		return (NULL);
	i = 0;
	while (i < len)
	{
		rendu[i] = ft_strjoin(env_lst->key, env_lst->value, "=");
		if (!rendu[i])
			return (freestrarr(&rendu), NULL);
		env_lst = env_lst->next;
		i++;
	}
	rendu[i] = NULL;
	return (rendu);
}

int	envlstlen(t_env *env_lst)
{
	int	rendu;

	rendu = 0;
	while(env_lst)
	{
		rendu++;
		env_lst = env_lst->next;
	}
	return (rendu);
}
