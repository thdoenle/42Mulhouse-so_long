/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:01:00 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 13:07:46 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	calc_offset(t_data *data)
{
	data->o_x = data->p->x + LEN_TILE / 2 - LEN_SCREEN / 2;
	if (data->o_x < 0)
		data->o_x = 0;
	else if (data->o_x > (int)data->img->bg.bg->width - LEN_SCREEN)
		data->o_x = data->img->bg.bg->width - LEN_SCREEN;
	data->o_y = data->p->y + LEN_TILE / 2 - LEN_SCREEN / 2;
	if (data->o_y < 0)
		data->o_y = 0;
	else if (data->o_y > (int)data->img->bg.bg->height - LEN_SCREEN)
		data->o_y = data->img->bg.bg->height - LEN_SCREEN;
}

void	update_player_height(t_data *data)
{
	if (data->p->move == MOVE_WIN)
	{
		data->p_h -= data->mlx->delta_time / TIME_DIE * LEN_TILE;
		if (data->p_h < -LEN_TILE)
		{
			data->p_h = -LEN_TILE;
			data->win = true;
		}
	}
	else
		data->p_h = nearbyint(2 * (cos(mlx_get_time() * 10) + 1));
}

void	update_positions(t_data *data)
{
	update_player_height(data);
	if (data->p->move >= MOVE_IDLE)
	{
		update_player_pos(data);
		calc_offset(data);
	}
	tracks_update_current_move(data);
}
