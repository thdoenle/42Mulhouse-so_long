/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:43:16 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 12:44:41 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	reset_player(t_data *data)
{
	data->p->l = data->p_l;
	data->p->c = data->p_c;
	data->p->x = data->map_o_x + LEN_TILE * data->p_c;
	data->p->y = data->map_o_y + LEN_TILE * data->p_l;
	data->p->move = MOVE_SPAWN;
	data->dir = MOVE_DOWN;
	data->p->t = 0.;
	data->anim->p_spawn.t = 0.;
	data->anim->p_death.t = 0.;
}

void	reset_collectibles(t_data *data)
{
	t_lst	*col;

	col = data->c;
	while (col)
	{
		col->draw = true;
		col = col->next;
	}
	data->anim->col.t = 0.;
}

void	reset_foes(t_data *data)
{
	foesclear(&data->foes);
	movesclear(&data->tracks->oldest);
	data->tracks->newest = NULL;
	data->foe_delay = 1.;
	data->anim->foe_death.t = 0.;
}

void	restart_game(t_data *data)
{
	reset_player(data);
	reset_collectibles(data);
	reset_foes(data);
	data->timer = 0.;
	data->nb_mv = 0;
	data->nb_col = 0;
	data->win = false;
	calc_offset(data);
}
