/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_expand.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 12:14:17 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 14:50:11 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "expander.h"

void	command_expand(t_command *command, char **env)
{
	char	*path;

	if (n_strlen(command->argv[0]) == 0 || command->argv[0][0] == '/')
		return ;
	path = NULL;
	if (command->argv && !n_strfind(command->argv[0], "/")
		&& command->argv[0][0] != '.')
		path = get_path(command->argv[0], env);
	else if (command->argv)
		path = command->argv[0];
	if (!path || access(path, F_OK | X_OK) != 0)
		return ;
	if (path != command->argv[0])
		free(command->argv[0]);
	command->argv[0] = path;
}
