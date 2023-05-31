/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_str.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 11:52:41 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/28 15:10:14 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "expander.h"

//	get quote type
static t_token_type	gq(char c)
{
	if (c == '\"')
		return (TK_ARG_STR_DQ);
	if (c == '\'')
		return (TK_ARG_STR_SQ);
	return (TK_ARG);
}

//	Cheap way to shorten get_token_str function
static t_token_type	add_str(char ***arr, char *pend, char **str, t_token_type r)
{
	add_str_to_arr(arr, cpy_word(*str, pend));
	*str = pend + 1;
	return (r);
}

static int	expand_last(char **arr, char **env)
{
	char	**ptr;

	ptr = arr;
	while (*ptr)
		ptr++;
	ptr--;
	expand_argument(ptr, env);
	return (1);
}

#define END_CHARS " \t\r\n\v\f<>|"

t_token_type	exp_and_str(char ***arr, char ***env, t_token_type r)
{
	expand_last(*arr, *env);
	return (r);
}

char	*token_get_str(char **str, t_token_type q, char ***env)
{
	char	**arr;
	char	*pend;

	pend = *str - 1;
	arr = NULL;
	while (pend++)
	{
		if (*pend == '\0' || (q == TK_ARG && n_strhaschar(END_CHARS, *pend)))
		{
			q = add_str(&arr, pend, str, q);
			*str -= expand_last(arr, *env);
			break ;
		}
		if (q == TK_ARG && (*pend == '\"' || *pend == '\''))
			q = exp_and_str(&arr, env, add_str(&arr, pend, str, gq(*pend)));
		else if ((q == TK_ARG_STR_DQ || q == TK_ARG_STR_SQ) && (gq(*pend) == q))
		{
			if (add_str(&arr, pend, str, q) != TK_ARG_STR_SQ)
				expand_last(arr, *env);
			q = TK_ARG;
		}
	}
	pend = n_protect(n_strarr_join(arr));
	n_strarr_free(arr);
	return (pend);
}
