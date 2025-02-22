/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:08:49 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/22 21:09:31 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	**fetch_paths(void)
{
	char	*line;

	line = getenv("PATH");
	if (line)
	{
		return (ft_split(line, ':'));
	}
	return (ft_split("", ' '));
}

char	*get_path(char *cmd)
{
	char	**paths;
	int		i;
	char	*new;

	i = 0;
	if (access(cmd, X_OK) == 0 || !*cmd)
		return (cmd);
	paths = fetch_paths();
	if (!paths)
		return (NULL, cmd);
	while (paths[i])
	{
		new = ft_strjoin(paths[i], cmd, "/");
		if (!new)
			return (freestrarr(&paths), NULL);
		if (access(new, X_OK) == 0)
			return (freestrarr(&paths), free(cmd), new);
		free(new);
		i++;
	}
	return (freestrarr(&paths), cmd);
}
