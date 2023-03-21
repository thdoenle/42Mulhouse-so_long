/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:43:46 by thdoenle          #+#    #+#             */
/*   Updated: 2023/02/21 18:42:29 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_lst	*lstnew(int l, int c, int x, int y)
{
	t_lst	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->l = l;
	new->c = c;
	new->x = x;
	new->y = y;
	new->draw = true;
	new->next = NULL;
	return (new);
}

void	lstadd_front(t_lst **lst, t_lst *new)
{
	new->next = *lst;
	*lst = new;
}

t_lst	*lstget(t_lst *lst, int l, int c)
{
	while (lst && (lst->l != l || lst->c != c))
		lst = lst->next;
	return (lst);
}

void	lstclear(t_lst **lst)
{
	t_lst	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
}
