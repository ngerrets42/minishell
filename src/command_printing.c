/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_printing.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 14:28:44 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 14:28:52 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static void	put(const char *str)
{
	printf("{%s}", str);
}

void	file_print(const t_file *file)
{
	printf(">\t\t\t[FILE]:\n");
	if (file->fmode == OUT_APPEND)
		printf(">\t\t\t| FMODE: OUT_APPEND\n");
	else if (file->fmode == OUT_TRUNC)
		printf(">\t\t\t| FMODE: OUT_TRUNCATE\n");
	else if (file->fmode == IN_FILE)
		printf(">\t\t\t| FMODE: IN_FILE\n");
	else if (file->fmode == IN_HEREDOC)
		printf(">\t\t\t| FMODE: IN_HEREDOC\n");
	printf(">\t\t\t| FNAME: {%s}\n", file->fname);
}

void	command_print(const t_command *command)
{
	t_llist	*curr;

	printf(">\t[COMMAND]:\n");
	if (command->argv)
	{
		printf(">\t\tARGV: {");
		n_strarr_exec(command->argv, (t_str_f)put);
		printf("}\n");
	}
	if (command->file_list)
	{
		printf(">\t\tFILES:\n");
		curr = command->file_list;
		while (curr)
		{
			file_print((const t_file *)(curr->content));
			curr = curr->next;
		}
	}
}
