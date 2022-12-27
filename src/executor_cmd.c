/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_cmd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 12:52:30 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/13 11:58:10 by ngerrets      ########   odam.nl         */
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

static bool	run_builtin(int io[2], t_command *cmd, char ***env, size_t amount)
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
		if (amount > 1)
			exit(pid);
		dup2(saved_stdout, STDOUT_FILENO);
	}
	else
		do_parent(io);
	return (true);
}

bool	run_command(int io[4], t_command *cmd, char ***env, size_t amount)
{
	int			pid;	

	if (!cmd->argv || !cmd->argv[0])
		return (true);
	if (builtin_get(cmd->argv[0]))
		return (run_builtin(io, cmd, env, amount));
	command_expand(cmd, *env);
	if (!n_strfind(cmd->argv[0], "/") || access(cmd->argv[0], F_OK | X_OK) != 0)
	{
		perr("minishell: command not found: ", cmd->argv[0], "\n");
		return (!exit_status_set(EXIT_STATUS_CMD_NOT_FOUND));
	}
	pid = fork();
	if (pid < 0)
		n_protect(NULL);
	else if (pid == 0)
	{
		do_child(io, cmd, env);
	}
	else
		do_parent(io);
	return (true);
}
