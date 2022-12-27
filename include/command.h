/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 13:33:56 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 14:29:08 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "core.h"
# include "tokens.h"
# include "fcntl.h"

// typedef enum e_outmode
// {
// 	OUT_APPEND,
// 	OUT_TRUNC
// }	t_outmode;

// typedef enum e_inmode
// {
// 	IN_FILE,
// 	IN_HEREDOC
// }	t_inmode;

typedef enum e_fmode
{
	OUT_APPEND = 0,
	OUT_TRUNC,
	IN_FILE,
	IN_HEREDOC
}	t_fmode;

typedef struct s_file
{
	char	*fname;
	t_fmode	fmode;
}	t_file;

//	file_list is the list of file-names that need to be created
//	output is the fname of the file that needs to be written to
//	input is the fname of the file that needs to be read from
//	argv is the string array of arguments (with idx 0 being the cmd name)
//	outmode is the enumerator for the way to output into the file
//	inmode is the enumerator for the way to input (from file or heredoc)
typedef struct s_command
{
	t_llist		*file_list;
	char		**argv;
}	t_command;

t_llist		*commands_parse(t_llist	*tokens);

//	command_utils.c
void		command_free(t_command *command);
void		command_free_file(t_file *file);
void		*command_free_and_return(t_llist *command_list);

//	command_printing.c
void		command_print(const t_command *command);
t_command	*command_new(void);

//	command_expand.c
void		command_expand(t_command *command, char **env);

#endif
