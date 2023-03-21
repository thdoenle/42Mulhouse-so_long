/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foes.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:49:29 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 11:29:26 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_foe(t_data *data)
{
	t_foe	*new;

	new = foenew(data->tracks->newest);
	if (!new)
		abort_game(data);
	foeadd_front(&data->foes, new);
	new->t = -TIME_FOE_SPAWN * data->foe_delay + data->anim->foe_spawn.t_max;
	data->foe_delay += 1.;
}

void	draw_foes(t_data *data)
{
	t_foe	*foe;
	int		f_h;

	foe = data->foes;
	f_h = 0;
	if (data->p->move >= MOVE_IDLE)
		f_h = data->p_h;
	while (foe)
	{
		if (foe->img)
			draw_image(data->img->main_layer, foe->img, foe->x - data->o_x,
				foe->y - data->o_y - f_h);
		foe = foe->next;
	}
}

bool	is_in(int n, int min, int max)
{
	if (min <= n && n <= max)
		return (true);
	return (false);
}

bool	is_player_colliding_with_foe(t_data *data)
{
	t_foe	*foe;

	foe = data->foes;
	while (foe)
	{
		if (foe->move_type == MOVE_IDLE
			&& (is_in(data->p->x + LEN_TILE / 2, foe->x, foe->x + LEN_TILE)
				&& is_in(data->p->y + LEN_TILE / 2, foe->y, foe->y + LEN_TILE)))
			return (true);
		foe = foe->next;
	}
	return (false);
}
