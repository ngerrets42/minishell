/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_heredoc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 11:14:31 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 14:24:51 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "signals.h"
#include "expander.h"

static char	*heredoc_get_fname(void)
{
	char	*arr[3];
	char	*fname;
	int		i;

	arr[0] = HEREDOC_FILE_NAME;
	arr[2] = NULL;
	fname = n_memdup(HEREDOC_FILE_NAME"0",
			sizeof(char) * (n_strlen(HEREDOC_FILE_NAME"0") + 1));
	i = 0;
	while (access(fname, F_OK) == 0 && i < HEREDOC_MAX_N)
	{
		i++;
		arr[1] = n_protect(ft_itoa(i));
		fname = n_protect(n_strarr_join(arr));
		free(arr[1]);
	}
	if (i == HEREDOC_MAX_N)
	{
		perr("minishell: heredoc: can't create temp-file\n", NULL, NULL);
		exit(EXIT_FAILURE);
	}
	return (fname);
}

static void	on_sigint(int c)
{
	(void)c;
	exit(EXIT_FAILURE);
}

static void	heredoc_child(const char *fname, const char *term, char **env)
{
	char	*str;
	int		fd;

	signal(SIGINT, on_sigint);
	signal(SIGQUIT, NULL);
	fd = open(fname, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	n_protect((void *)(size_t)(fd > 2));
	while (true)
	{
		str = readline(HEREDOC_PROMPT);
		if (str)
			expand_argument(&str, env);
		if (!str || (n_strcmp(str, term) == 0
				&& n_strlen(str) == n_strlen(term)))
			break ;
		if (write(fd, str, n_strlen(str) * sizeof(char)) < 0
			|| write(fd, "\n", sizeof(char)) < 0)
		{
			perror("minishell");
			unlink(fname);
			exit(EXIT_FAILURE);
		}
	}
	close(fd);
	exit(EXIT_SUCCESS);
}

/*
**	fork() a child process
**	open() a temp file for write
**	write() the expanded here doc to it. The contents depends on the iteration.
**	close() it
**	open() it again read-only
**	unlink(), so it will be deleted after it's closed
**	dup2(4, 0) the  fd so that the new process has the temp file as stdin
**
**	open("/tmp/sh-thd-865008962", O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600)
*/
int	executor_open_heredoc(const char *terminator, char **env)
{
	char	*fname;
	int		fd;
	int		pid;

	pid = fork();
	if (pid < 0)
		n_protect(NULL);
	fname = heredoc_get_fname();
	if (pid == 0)
		heredoc_child(fname, terminator, env);
	waitpid(pid, &fd, 0);
	if (WEXITSTATUS(fd) != 0)
	{
		free(fname);
		return (-1);
	}
	fd = open(fname, O_RDONLY);
	if (fd < 2 || unlink(fname) != 0)
		n_protect(NULL);
	free(fname);
	return (fd);
}
