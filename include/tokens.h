/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 11:35:04 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 14:20:08 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "core.h"

typedef enum e_token_type
{
	TK_NONE = 0,
	TK_PIPE,
	TK_REDIRECT_HEREDOC,
	TK_REDIRECT_APPEND,
	TK_REDIRECT_OUTPUT,
	TK_REDIRECT_INPUT,
	TK_ARG,
	TK_ARG_STR_SQ,
	TK_ARG_STR_DQ,
	TK_VAR,
	TK_END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
}	t_token;

//	tokenizer.c
t_llist			*tokenize(char *str, char ***env);
bool			tokens_good(t_llist *token_list, t_token **btoken);

//	token_utils.c
const char		*token_as_text(t_token_type type);
bool			token_is_redirect(t_token_type type);
void			token_print(const t_token *token);
void			token_free(t_token *token);
t_token_type	get_token_type(char **str);

//	token_str.c
char			*token_get_str(char **str, t_token_type type, char ***env);

#endif // TOKENS_H
