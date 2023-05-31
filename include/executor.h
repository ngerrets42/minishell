/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 13:30:53 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 12:59:17 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "core.h"
# include "command.h"
# include "builtins.h"

# include <readline/readline.h>

# define HEREDOC_PROMPT "> "
# define HEREDOC_FILE_NAME "/tmp/sh-thd-"
# define HEREDOC_MAX_N 1024

typedef struct s_process
{
	int	pid;
}	t_process;

enum e_pipe_fd
{
	P_READ = 0,
	P_WRITE
};

enum e_pipe_location
{
	LEFT = 0,
	RIGHT
};

void	execute(t_llist *command_list, size_t list_size, char ***env);
void	executor_handle_exit(t_builtin_f *func, int pid, int amount);

//	executor_heredoc.c
int		executor_open_heredoc(const char *terminator, char **env);

//	executor_io.c
int		executor_open_infile(const char *path);
int		executor_open_outfile(const char *path, t_fmode fmode);
bool	executor_io(int io[3], t_command *cmd, int pipes[2][2], char **env);

//	executor_cmd.c
int		run_command(int io[3], t_command *cmd, char ***env, size_t amount);

#endif	//	EXECUTOR_H
