/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 10:33:21 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 14:28:34 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	command_free_file(t_file *file)
{
	free(file->fname);
	free(file);
}

void	command_free(t_command *command)
{
	if (command->argv)
		n_strarr_free(command->argv);
	llist_clear(&command->file_list, (t_contentf)command_free_file);
	free(command);
}

t_command	*command_new(void)
{
	return (n_protect(n_zalloc(sizeof(t_command))));
}

void	*command_free_and_return(t_llist *command_list)
{
	llist_clear(&command_list, (t_contentf)command_free);
	return (NULL);
}
