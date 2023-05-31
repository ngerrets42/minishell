/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 13:35:14 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 14:12:24 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

bool	is_redirect(const t_token *token)
{
	return (token->type == TK_REDIRECT_HEREDOC
		|| token->type == TK_REDIRECT_INPUT
		|| token->type == TK_REDIRECT_APPEND
		|| token->type == TK_REDIRECT_OUTPUT);
}

t_file	*command_file_create(char *fname, t_token_type type)
{
	t_file	*f;

	f = n_protect(n_zalloc(sizeof(t_file)));
	f->fname = fname;
	if (type == TK_REDIRECT_APPEND)
		f->fmode = OUT_APPEND;
	else if (type == TK_REDIRECT_OUTPUT)
		f->fmode = OUT_TRUNC;
	else if (type == TK_REDIRECT_INPUT)
		f->fmode = IN_FILE;
	else if (type == TK_REDIRECT_HEREDOC)
		f->fmode = IN_HEREDOC;
	return (f);
}

bool	command_handle_redirect(t_command *command, t_llist **token_list)
{
	t_token	*token;
	t_token	*next;

	token = (t_token *)(*token_list)->content;
	*token_list = (*token_list)->next;
	next = (t_token *)(*token_list)->content;
	if (next->type != TK_ARG && next->type != TK_ARG_STR_DQ
		&& next->type != TK_ARG_STR_DQ)
	{
		perr("minishell: syntax error\n", NULL, NULL);
		return (false);
	}
	if (is_redirect(token))
		llist_add_back(&command->file_list, llist_new(
				command_file_create(next->str, token->type)));
	return (true);
}

void	command_handle_arg(t_command *command, t_llist **token_list)
{
	t_token	*token;

	token = (t_token *)(*token_list)->content;
	add_str_to_arr(&command->argv, token->str);
}

t_llist	*commands_parse(t_llist	*tokens)
{
	t_llist		*command_list;
	t_token		*token;
	t_command	*command;

	command_list = NULL;
	while (tokens)
	{
		command = command_new();
		llist_add_back(&command_list, llist_new(command));
		token = (t_token *)tokens->content;
		while (token->type != TK_PIPE && token->type != TK_END)
		{
			if (is_redirect(token))
			{
				if (!command_handle_redirect(command, &tokens))
					return (command_free_and_return(command_list));
			}
			else
				command_handle_arg(command, &tokens);
			tokens = tokens->next;
			token = (t_token *)tokens->content;
		}
		tokens = tokens->next;
	}
	return (command_list);
}
