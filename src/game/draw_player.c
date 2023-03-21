/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:20:38 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/13 15:32:28 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_player_winning(t_data *data)
{
	t_img_area	area;

	if (data->p->x != data->p->x_to)
		data->p->x = data->p->x_from;
	if (data->p->y != data->p->y_to)
		data->p->y = data->p->y_from;
	area.x = 0;
	area.y = 0;
	area.w = LEN_TILE;
	area.h = LEN_TILE + (int)nearbyint(data->p_h);
	area.img = data->img->player_d;
	draw_image_from_image_area(data->img->main_layer, &area,
		data->p->x - data->o_x,
		data->p->y - data->o_y - (int)nearbyint(data->p_h));
}

void	draw_player(t_data *data)
{
	mlx_image_t	*player_img;

	if (data->p->move == MOVE_WIN)
	{
		draw_player_winning(data);
		return ;
	}
	if (data->p->move == MOVE_SPAWN)
		player_img = get_anim_img(&data->anim->p_spawn);
	else if (data->p->move == MOVE_DEATH)
		player_img = get_anim_img(&data->anim->p_death);
	else if (data->dir == MOVE_DOWN)
		player_img = data->img->player_d;
	else if (data->dir == MOVE_UP)
		player_img = data->img->player_u;
	else if (data->dir == MOVE_LEFT)
		player_img = data->img->player_l;
	else
		player_img = data->img->player_r;
	draw_image(data->img->main_layer, player_img,
		data->p->x - data->o_x, data->p->y - data->o_y - (int)data->p_h);
}
