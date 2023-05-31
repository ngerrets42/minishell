/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_io.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 12:50:13 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 14:42:00 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	executor_open_infile(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		perr("minishell: ", path, ": No such file or directory\n");
	return (fd);
}

int	executor_open_outfile(const char *path, t_fmode fmode)
{
	int	fd;
	int	flags;

	flags = O_CREAT | O_WRONLY;
	if (fmode == OUT_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(path, flags, S_IRUSR | S_IWUSR);
	if (fd < 0)
		perr("minishell: ", path, ": Permission denied\n");
	return (fd);
}

static int	executor_get_fd(t_file *file, char **env)
{
	if (file->fmode == IN_HEREDOC)
		return (executor_open_heredoc(file->fname, env));
	if (file->fmode == IN_FILE)
		return (executor_open_infile(file->fname));
	if (file->fmode == OUT_APPEND || file->fmode == OUT_TRUNC)
		return (executor_open_outfile(file->fname, file->fmode));
	return (-1);
}

bool	executor_io(int io[4], t_command *cmd, int pipes[2][2], char **env)
{
	t_llist	*curr_list;
	t_file	*curr_file;
	int		fd;

	curr_list = cmd->file_list;
	while (curr_list)
	{
		curr_file = (t_file *)(curr_list->content);
		fd = executor_get_fd(curr_file, env);
		if (fd < 0)
			return (0 * close(io[P_READ] + 0 * close(io[P_WRITE])));
		if (curr_file->fmode == OUT_APPEND || curr_file->fmode == OUT_TRUNC)
			io[P_WRITE] = fd + 0 * (close(io[P_WRITE]));
		else
			io[P_READ] = fd + 0 * (close(io[P_READ])
					+ close(pipes[LEFT][P_READ]));
		curr_list = curr_list->next;
	}
	if (io[P_READ] < 0)
		io[P_READ] = pipes[LEFT][P_READ];
	if (io[P_WRITE] < 0)
		io[P_WRITE] = pipes[RIGHT][P_WRITE];
	else
		io[3] = pipes[RIGHT][P_WRITE];
	return (true);
}
