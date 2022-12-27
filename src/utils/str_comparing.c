/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_comparing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:14:18 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/28 17:08:24 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/n_string.h"

int	n_strcmp(const char *str1, const char *str2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = n_strlen(str1);
	len2 = n_strlen(str2);
	if (len1 == 0 || len2 == 0)
		return (len2 - len1);
	i = 0;
	while (i < len1 && i < len2)
	{
		if ((unsigned char)str1[i] - (unsigned char)str2[i] != 0)
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

//	TODO: decide if this is usefull or not
int	n_strequals(const char *str1, const char *str2)
{
	if (n_strcmp(str1, str2) == 0)
		return (1);
	return (0);
}

//	Find and return a pointer to the first found instance of c (or NULL)
char	*n_strhaschar(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

char	*n_strfind(const char *str, const char *sub)
{
	size_t	i;
	size_t	j;
	size_t	sublen;

	sublen = n_strlen(sub);
	if (!str || !sub || n_strlen(str) <= sublen || sublen == 0)
		return (NULL);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (sub[j] && str[i + j] && str[i + j] == sub[j])
			j++;
		if (j == n_strlen(sub))
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

//	returns a ptr to the next word found (next char thats not in delims)
char	*n_str_next_word(const char *str, const char *delims)
{
	while (*str != '\0' && n_strhaschar(delims, *str))
		str++;
	return ((char *)str);
}
