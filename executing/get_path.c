/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:08:49 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/25 18:31:36 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	**fetch_paths(t_env *env_lst)
{
	char	*line;
	char	**tmp;

	line = getenv_("PATH", env_lst);
	if (line)
	{
		tmp = ft_split(line, ':');
		free(line);
		return (tmp);
	}
	return (NULL);
}

bool	is_dir(char *s)
{
	DIR	*dir;

	dir = opendir(s);
	if (dir)
		return (closedir(dir), 1);
	return (0);
}

char	*get_path(char *cmd, t_exec *x)
{
	char	**paths;
	int		i;
	char	*new;

	i = 0;
	if (is_dir(cmd))
		return (x->status = 126, cmd);
	if (!*cmd)
		return (x->status = 127, cmd);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	paths = fetch_paths(x->lst);
	if (!paths)
		return (x->status = 127, cmd);
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
	return (x->status = 127, freestrarr(&paths), cmd);
}
