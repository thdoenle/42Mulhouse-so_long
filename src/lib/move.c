/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:52:12 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/14 14:42:07 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_move	*movenew(t_coords *coords, t_move_type dir)
{
	t_move	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->dir = dir;
	if (coords->move == MOVE_IDLE)
	{
		new->x_from = coords->x;
		new->x_to = coords->x;
		new->y_from = coords->y;
		new->y_to = coords->y;
	}
	else
	{
		new->x_from = coords->x_from;
		new->y_from = coords->y_from;
		new->x_to = coords->x_to;
		new->y_to = coords->y_to;
	}
	new->time = 0.;
	new->next = NULL;
	return (new);
}

void	movesclear(t_move **moves)
{
	t_move	*next;

	while (*moves)
	{
		next = (*moves)->next;
		free(*moves);
		*moves = next;
	}
}
