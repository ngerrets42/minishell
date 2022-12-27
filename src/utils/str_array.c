/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_array.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 17:45:47 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/15 14:03:46 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/n_string.h"

void	n_strarr_exec(char **arr, t_str_f func)
{
	while (*arr)
	{
		func(*arr);
		arr++;
	}
}

void	n_strarr_free(char **arr)
{
	n_strarr_exec(arr, (t_str_f)free);
	free(arr);
}

char	*n_strarr_find(char **arr, const char *str)
{
	while (*arr)
	{
		if (n_strequals(*arr, str))
			return (*arr);
		arr++;
	}
	return (NULL);
}

size_t	n_strarr_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

//	combines all elements into a newly allocated single string
//	NOTE: doesnt destroy array.
//	NOTE: unprotected input
//	NOTE: returns NULL on malloc failure
char	*n_strarr_join(char **arr)
{
	size_t	total_size;
	size_t	i;
	char	*str;

	total_size = 0;
	i = 0;
	while (arr[i])
	{
		total_size += n_strlen(arr[i]);
		i++;
	}
	str = n_zalloc(sizeof(char) * (total_size + 1));
	i = 0;
	total_size = 0;
	while (str && arr[i])
	{
		n_memcpy(&str[total_size], arr[i], n_strlen(arr[i]));
		total_size += n_strlen(arr[i]);
		i++;
	}
	return (str);
}
