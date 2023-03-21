/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:43:46 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/14 15:53:25 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_foe	*foenew(t_move *move_ptr)
{
	t_foe	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->x = move_ptr->x_from;
	new->y = move_ptr->y_from;
	new->t = 0.;
	new->move_ptr = move_ptr;
	new->move_type = MOVE_SPAWN;
	new->img = NULL;
	new->next = NULL;
	return (new);
}

void	foeadd_front(t_foe **foes, t_foe *new)
{
	new->next = *foes;
	*foes = new;
}

void	foesclear(t_foe **foes)
{
	t_foe	*next;

	while (*foes)
	{
		next = (*foes)->next;
		free(*foes);
		*foes = next;
	}
}
