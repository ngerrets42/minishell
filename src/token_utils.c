/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 17:35:37 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 14:17:12 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

//	For debugging purposes
const char	*token_as_text(t_token_type type)
{
	static const char	*str[] = {
	[TK_NONE] = "",
	[TK_PIPE] = "|",
	[TK_REDIRECT_HEREDOC] = "<<",
	[TK_REDIRECT_APPEND] = ">>",
	[TK_REDIRECT_OUTPUT] = ">",
	[TK_REDIRECT_INPUT] = "<",
	[TK_ARG] = "",
	[TK_ARG_STR_SQ] = "'",
	[TK_ARG_STR_DQ] = "\"",
	[TK_VAR] = "$",
	[TK_END] = ""
	};

	return (str[type]);
}

t_token_type	get_token_type(char **str)
{
	size_t					i;
	static const t_token	token_map[] = {
	{TK_PIPE, "|"}, {TK_REDIRECT_HEREDOC, "<<"},
	{TK_REDIRECT_APPEND, ">>"}, {TK_REDIRECT_OUTPUT, ">"},
	{TK_REDIRECT_INPUT, "<"}, {TK_ARG_STR_SQ, "\'"},
	{TK_ARG_STR_DQ, "\""}, {TK_NONE, NULL}
	};

	if (**str == '\0')
		return (TK_END);
	i = 0;
	while (token_map[i].type != TK_NONE)
	{
		if (n_strlen(*str) >= n_strlen(token_map[i].str)
			&& n_strcmp(*str, token_map[i].str) == 0)
		{
			(*str) += n_strlen(token_map[i].str);
			return (token_map[i].type);
		}
		i++;
	}
	return (TK_ARG);
}

bool	token_is_redirect(t_token_type type)
{
	return (type == TK_REDIRECT_APPEND
		|| type == TK_REDIRECT_HEREDOC
		|| type == TK_REDIRECT_INPUT
		|| type == TK_REDIRECT_OUTPUT);
}

void	token_print(const t_token *token)
{
	if (token->str)
		printf(">\t[%s]: {%s}\n", token_as_text(token->type), token->str);
	else
		printf(">\t[%s]\n", token_as_text(token->type));
}

void	token_free(t_token *token)
{
	free(token->str);
	free(token);
}
