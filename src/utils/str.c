/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 14:02:25 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/12/07 14:18:54 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char	*cpy_word(char *pstart, char *pend)
{
	size_t	size;
	char	*word;

	size = (size_t)pend - (size_t)pstart;
	word = n_protect(n_zalloc(size + 1 * sizeof(char)));
	n_memcpy(word, pstart, size);
	return (word);
}

//	***argv is a reference to the arguments (string array)
void	add_str_to_arr(char ***argv, char *str)
{
	size_t			argsize;

	if (!*argv)
	{
		*argv = n_protect(n_zalloc(sizeof(char *) * 2));
		(*argv)[0] = str;
		(*argv)[1] = NULL;
		return ;
	}
	argsize = n_strarr_size((*argv));
	(*argv) = n_protect(
			n_realloc((*argv),
				(argsize + 1) * sizeof(char *),
				(argsize + 2) * sizeof(char *)));
	(*argv)[argsize] = str;
	(*argv)[argsize + 1] = NULL;
}

int	perr(const char *str1, const char *str2, const char *str3)
{
	ssize_t	r;

	r = 0;
	if (str1)
		r += write(STDERR_FILENO, str1, n_strlen(str1) * sizeof(char));
	if (str2)
		r += write(STDERR_FILENO, str2, n_strlen(str2) * sizeof(char));
	if (str3)
		r += write(STDERR_FILENO, str3, n_strlen(str3) * sizeof(char));
	return ((int)r);
}
