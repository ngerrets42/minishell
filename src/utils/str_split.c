/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_split.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 17:45:39 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/30 14:21:36 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "n_string.h"

static char	*_alloc_word(const char *str, const char *delims)
{
	size_t	i;
	size_t	len;
	char	*r;

	len = 0;
	while (str[len] && !n_strhaschar(delims, str[len]))
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (i < len)
	{
		r[i] = str[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

static void	_fill(char **arr, const char *str, const char *delims, size_t words)
{
	size_t	i;

	i = 0;
	while (i < words)
	{
		str = n_str_next_word(str, delims);
		arr[i] = _alloc_word(str, delims);
		if (!arr[i])
		{
			arr[i] = NULL;
			n_strarr_free(arr);
			arr = NULL;
			return ;
		}
		while (*str && !n_strhaschar(delims, *str))
			str++;
		i++;
	}
	arr[i] = NULL;
}

//	Unless malloc fails, this'll always return a NULL-terminated array
char	**n_split(const char *str, const char *delims)
{
	char	**arr;
	size_t	words;

	words = n_str_count_words(str, delims);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	if (words == 0)
	{
		*arr = NULL;
		return (arr);
	}
	_fill(arr, str, delims, words);
	return (arr);
}

char	**n_strarr_dup(char **arr)
{
	char	**arr_cpy;
	char	**p;

	arr_cpy = n_zalloc((n_strarr_size(arr) + 1) * sizeof(char *));
	if (!arr_cpy)
		return (NULL);
	p = arr_cpy;
	while (*arr)
	{
		*p = n_memdup(*arr, sizeof(char) * (n_strlen(*arr) + 1));
		if (!*p)
		{
			n_strarr_free(arr_cpy);
			return (NULL);
		}
		p++;
		arr++;
	}
	return (arr_cpy);
}
