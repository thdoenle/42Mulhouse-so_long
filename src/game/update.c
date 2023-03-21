/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:16:28 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 17:09:54 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	reset_layers(t_data *data)
{
	uint32_t	win_color;

	draw_image_from_coords(data->img->bg.layer, data->img->bg.bg,
		data->o_x, data->o_y);
	ft_pixelset(data->img->main_layer->pixels, 0, LEN_SCREEN * LEN_SCREEN);
	win_color = 0;
	if (data->p->move == MOVE_WIN)
		win_color = -data->p_h * 0x70 / LEN_TILE;
	win_color = (win_color << 030) + 0x191324;
	ft_pixelset(data->img->win_layer->pixels, win_color,
		LEN_SCREEN * LEN_SCREEN);
}

void	draw_collectibles(t_data *data)
{
	t_lst		*col;

	col = data->c;
	while (col)
	{
		if (col->draw)
			draw_image(data->img->main_layer, get_anim_img(&(data->anim->col)),
				col->x - data->o_x, col->y - data->o_y);
		col = col->next;
	}
}

void	draw_elems(t_data *data)
{
	mlx_image_t	*exit_img;

	if (data->nb_col != data->max_col)
		exit_img = data->img->exit;
	else
		exit_img = data->img->exit_o;
	draw_image(data->img->main_layer, exit_img,
		data->e->x - data->o_x, data->e->y - data->o_y);
	draw_collectibles(data);
	draw_player(data);
	draw_foes(data);
}

void	check_collisions(t_data *data)
{
	t_lst	*c;

	if (is_player_colliding_with_foe(data))
		data->p->move = MOVE_DEATH;
	else if (data->map[data->p->l][data->p->c] == 'C')
	{
		c = lstget(data->c, data->p->l, data->p->c);
		if (c->draw)
		{
			data->nb_col++;
			c->draw = false;
			if (!data->tracks->newest)
				tracks_add_move(data);
			add_foe(data);
		}
	}
	else if (data->map[data->p->l][data->p->c] == 'E'
		&& data->nb_col == data->max_col && data->p->move >= MOVE_IDLE)
	{
		data->p->move = MOVE_WIN;
		data->p_h = 0.;
	}
}

void	update(t_data *data)
{
	update_positions(data);
	update_foes(data);
	if (data->p->move >= MOVE_IDLE)
		check_collisions(data);
	update_animations(data);
	if (data->anim->p_death.t >= data->anim->p_death.t_max)
		restart_game(data);
	reset_layers(data);
	draw_elems(data);
	update_hud(data);
}
