/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   llist_mem.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 11:04:56 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/11/14 10:39:05 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/llist.h"

//	allocates a new list element and assigns content to it
t_llist	*llist_new(void *content)
{
	t_llist	*element;

	element = (t_llist *)malloc(sizeof(t_llist));
	if (element == NULL)
		return (NULL);
	element->content = content;
	element->next = NULL;
	return (element);
}

//	frees the content with del_func and then frees the lst pointer
void	llist_del(t_llist *lst, t_contentf del_func)
{
	if (lst != NULL)
	{
		if (del_func)
			del_func(lst->content);
		free(lst);
	}
}

//	frees the entire list using del_func to free the content
void	llist_clear(t_llist **lst, t_contentf del_func)
{
	t_llist	*next;

	while (lst != NULL && *lst != NULL)
	{
		next = (*lst)->next;
		llist_del(*lst, del_func);
		*lst = next;
	}
	lst = NULL;
}
