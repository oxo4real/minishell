/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:50:53 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/23 19:51:14 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

t_gb	g_gb;

void	print_unexpected(char *msg)
{
	printf("%s: %s `%s'\n", SH_NAME, UNEXPECTED_TK, msg);
}

void	print_syntax_error(char *msg)
{
	printf("%s: %s: %s\n", SH_NAME, SYNTAX_ERR, msg);
}

void	ll(void)
{
	system("leaks -q minishell");
}

char	*get_line(void)
{
	int		fd;
	char	*prompt;
	char	*line;

	prompt = "";
	if (isatty(STDIN_FILENO))
		prompt = BOLD_RED SH_NAME " > " RESET;
	fd = dup(1);
	dup2(2, 1);
	line = readline(prompt);
	dup2(fd, 1);
	close(fd);
	return (line);
}

int	main(int ac, char *av[], char *env[])
{
	char	*line;
	t_exec	x;
	int		fd;

	fd = dup(STDIN_FILENO);
	g_gb.ex_code = 0;
	((void)ac, (void)av);
	x.lst = envtoenvlst(env);
	while (1337)
	{
		line = get_line();
		if (!line)
		{
			rl_clear_history();
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		executor(parser(line), &x);
		dup2(fd, 1);
	}
	envlstclear(&x.lst);
	ll();
	return (0);
}
