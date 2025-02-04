/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:09:36 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/04 15:31:37 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	print_error(char *shell_name, char *command, char *details);

void	pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
    if (cwd != NULL)
        printf("%s\n", cwd);
    else
        print_error("minishell", "pwd", NULL);
	free(cwd);
}
