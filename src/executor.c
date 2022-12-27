/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 17:11:03 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/27 10:35:57 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "command.h"
#include "builtins.h"

#include <readline/readline.h>

static void	reset_pipe(int pipe[2])
{
	pipe[P_READ] = -1;
	pipe[P_WRITE] = -1;
}

static void	reset_io(int io[4])
{
	io[0] = -1;
	io[1] = -1;
	io[2] = -1;
	io[3] = -1;
}

static void	wait_and_set_status(void)
{
	int			status;

	while (wait(&status) > 0)
	{
		status = WEXITSTATUS(status);
		exit_status_set(status);
	}
}

void	execute(t_llist *cmd_list, size_t list_size, char ***env)
{
	int			pipes[2][2];
	int			io[4];

	reset_pipe(pipes[LEFT]);
	while (cmd_list)
	{
		reset_pipe(pipes[RIGHT]);
		reset_io(io);
		if (cmd_list->next != NULL)
			pipe(pipes[RIGHT]);
		if (executor_io(io, cmd_list->content, pipes, *env))
		{
			if (io[P_READ] < 0)
				io[P_READ] = STDIN_FILENO;
			if (cmd_list->next == NULL && io[P_WRITE] < 0)
				io[P_WRITE] = STDOUT_FILENO;
			io[2] = pipes[RIGHT][P_READ];
			if (!run_command(io, cmd_list->content, env, list_size))
				break ;
			pipes[LEFT][P_READ] = pipes[RIGHT][P_READ];
			pipes[LEFT][P_WRITE] = pipes[RIGHT][P_WRITE];
		}
		cmd_list = cmd_list->next;
	}
	wait_and_set_status();
}
