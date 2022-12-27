/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_string.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 17:45:45 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/30 14:21:55 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_STRING_H
# define N_STRING_H

# include <stddef.h>
# include <stdlib.h>
# include "n_mem.h"
# include "n_alloc.h"

# define DELIMS_WHITESPACE " \t\r\n\v\f"

//	represents a function that can be executed on a string (or char)
typedef void	(*t_str_f)(char *);

//	str_counting.c
size_t	n_strlen(const char *str);
size_t	n_strlen_p(const char *str);
size_t	n_str_count_words(const char *str, const char *delims);

//	str_comparing.c
char	*n_strhaschar(const char *str, char c);
int		n_strcmp(const char *str1, const char *str2);
int		n_strequals(const char *str1, const char *str2);
char	*n_strfind(const char *str, const char *sub);
char	*n_str_next_word(const char *str, const char *delims);

//	str_split.c
char	**n_split(const char *str, const char *delims);
char	**n_strarr_dup(char **arr);

//	str_array.c
void	n_strarr_exec(char **arr, t_str_f func);
void	n_strarr_free(char **arr);
char	*n_strarr_find(char **arr, const char *str);
size_t	n_strarr_size(char **arr);
char	*n_strarr_join(char **arr);

#endif // N_STRING_H
