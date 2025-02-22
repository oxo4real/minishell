/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:33:57 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/22 20:18:26 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "parsing.h"

void	echo(char **av);
int		gohome(t_env **env_lst);
void	set_env(t_env **env_lst);
void	_export(char **av, t_env **env_lst);
void	unset(char **av, t_env **env_lst);
void	env_(t_env *env_lst);
void	exit_(char **av, bool print);
void	pexport(t_env *env_lst);
void	pwd(void);

#endif
