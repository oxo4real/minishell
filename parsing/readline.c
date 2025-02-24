/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:50:53 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/24 21:44:56 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

int		g_sig = 0;
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

char	*get_line(t_exec *x)
{
	int		fd;
	char	*prompt;
	char	*line;

	if (g_sig == 130)
	{
		g_sig = 0;
		x->status = 130;
		ft_putstr_fd("\n", 2);
	}
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

void	interrupt(int sig)
{
	(void)sig;
	if (g_sig)
	{
		g_sig = 130;
		return ;
	}
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quit(int sig)
{
	(void)sig;
}

int	main(int ac, char *av[], char *env[])
{
	char	*line;
	t_exec	x;
	int		fd;
	int		fd2;

	rl_catch_signals = 0;
	fd = dup(STDOUT_FILENO);
	fd2 = dup(STDIN_FILENO);
	signal(SIGINT, interrupt);
	signal(SIGQUIT, quit);
	((void)ac, (void)av);
	x.lst = envtoenvlst(env);
	set_shlvl(&x.lst);
	while (1337)
	{
		line = get_line(&x);
		if (!line)
		{
			rl_clear_history();
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		executor(parser(line), &x);
		dup2(fd, 1);
		dup2(fd2, 0);
	}
	envlstclear(&x.lst);
	ll();
	return (0);
}
