/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_counting.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 18:22:21 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/14 10:39:36 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/n_string.h"

size_t	n_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

//	Protected version of strlen, returns 0 if str==NULL
size_t	n_strlen_p(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

size_t	n_str_count_words(const char *str, const char *delims)
{
	size_t	words;
	size_t	i;

	if (!str || n_strlen(str) == 0)
		return (0);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && n_strhaschar(delims, str[i]))
			i++;
		if (str[i])
			words++;
		while (str[i] && !n_strhaschar(delims, str[i]))
			i++;
	}
	return (words);
}
