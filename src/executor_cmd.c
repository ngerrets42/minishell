/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 12:52:30 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 15:19:44 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
**	Performs the steps that the parent process is supposed to do. RIGHTly
**	thats only to close the input and output descriptors (of the pipes).
*/
static void	do_parent(int io[4])
{
	if (io[P_READ] != STDIN_FILENO)
		close(io[P_READ]);
	if (io[P_WRITE] != STDOUT_FILENO)
		close(io[P_WRITE]);
	close(io[3]);
	signal(SIGINT, SIG_IGN);
}

/*
**	dup2 but throws an error if something went wrong and closes the relevant
**	descriptors.
*/
static void	duptwo(int fd1, int fd2)
{
	if (fd1 == fd2)
		return ;
	if (dup2(fd1, fd2) < 0)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	if (fd1 != STDIN_FILENO && fd1 != STDOUT_FILENO)
		close(fd1);
	if (fd2 != STDIN_FILENO && fd2 != STDOUT_FILENO)
		close(fd2);
}

/*
**	Perform the steps that the child process is supposed to do.
**	This includes duplicating the STDIN/OUT to/from the pipes, getting the path
**	to the binary of the command and replacing itself with a process of the
**	binary.
*/
static void	do_child(int io[4], t_command *command, char ***env)
{
	if (io[2] > 2)
		close(io[2]);
	if (io[3] >= 0)
		close(io[3]);
	duptwo(io[P_READ], STDIN_FILENO);
	duptwo(io[P_WRITE], STDOUT_FILENO);
	if (execve(command->argv[0], command->argv, *env) < 0)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

static int	run_builtin(int io[4], t_command *cmd, char ***env, size_t amount)
{
	int			pid;
	t_builtin_f	*func;
	int			saved_stdout;

	pid = 0;
	if (amount > 1)
		pid = fork();
	if (pid < 0)
		n_protect(NULL);
	else if (pid == 0)
	{
		saved_stdout = dup(STDOUT_FILENO);
		duptwo(io[P_READ], STDIN_FILENO);
		duptwo(io[P_WRITE], STDOUT_FILENO);
		func = builtin_get(cmd->argv[0]);
		pid = (*func)(n_strarr_size(cmd->argv), cmd->argv, env);
		executor_handle_exit(func, pid, amount);
		if (amount > 1)
			exit(pid);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	else
		do_parent(io);
	return (pid);
}

int	run_command(int io[4], t_command *cmd, char ***env, size_t amount)
{
	int	pid;

	if (!cmd->argv || !cmd->argv[0])
		return (-1);
	if (builtin_get(cmd->argv[0]))
		return (run_builtin(io, cmd, env, amount));
	command_expand(cmd, *env);
	if (!n_strfind(cmd->argv[0], "/") || access(cmd->argv[0], F_OK) != 0
		|| n_strlen(cmd->argv[0]) <= 0)
		return (-1 + 0 * exit_status_set(EXIT_STATUS_CMD_NOT_FOUND)
			+ 0 * perr("minishell: ", cmd->argv[0], ": command not found\n"));
	else if (access(cmd->argv[0], X_OK) != 0)
		return (-1 + 0 * exit_status_set(EXIT_STATUS_NO_PERMISSION)
			+ 0 * perr("minishell: ", cmd->argv[0], ": Permission denied\n"));
	pid = fork();
	if (pid < 0)
		n_protect(NULL);
	else if (pid == 0)
		do_child(io, cmd, env);
	else
		do_parent(io);
	return (pid);
}
