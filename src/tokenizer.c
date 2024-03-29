/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 11:44:03 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 14:19:55 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "expander.h"

//	returns next token and increments str past the token
//	str is a REFERENCE to a string
//	returned token is a struct including the token str and the type
static t_token	token_next(char **str, char ***env)
{
	t_token	token;

	token.str = NULL;
	*str = n_str_next_word(*str, DELIMS_WHITESPACE);
	token.type = get_token_type(str);
	if (token.type == TK_NONE)
		return (token);
	if (token.type == TK_ARG
		|| token.type == TK_ARG_STR_DQ
		|| token.type == TK_ARG_STR_SQ
		|| token.type == TK_VAR)
		token.str = token_get_str(str, token.type, env);
	if (token.type == TK_VAR)
		expand_argument(&(token.str), *env);
	return (token);
}

bool	tokens_good(t_llist *token_list, t_token **btoken)
{
	t_llist	*prev;

	*btoken = ((t_token *)token_list->content);
	if ((*btoken)->type == TK_PIPE)
		return (false);
	while (token_list && token_list->next)
	{
		*btoken = ((t_token *)token_list->content);
		if ((*btoken)->type == TK_PIPE
			&& ((t_token *)token_list->next->content)->type == TK_PIPE)
			return (false);
		if (token_is_redirect((*btoken)->type)
			&& token_is_redirect(((t_token *)token_list->next->content)->type))
			return (false);
		prev = token_list;
		token_list = token_list->next;
	}
	*btoken = ((t_token *)prev->content);
	if ((*btoken)->type == TK_PIPE)
		return (false);
	return (true);
}

t_llist	*tokenize(char *str, char ***env)
{
	t_llist	*token_list;
	t_token	*token;

	token_list = NULL;
	while (str)
	{
		token = n_protect(malloc(sizeof(t_token)));
		*token = token_next(&str, env);
		llist_add_back(&token_list, llist_new(token));
		if (token->type == TK_NONE)
		{
			llist_clear(&token_list, (t_contentf)token_free);
			return (NULL);
		}
		if (token->type == TK_END)
			break ;
	}
	return (token_list);
}
