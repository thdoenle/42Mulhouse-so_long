/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_tile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:26:53 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/04 11:02:18 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_wall(t_data *data, int l, int c)
{
	if (c < 0 || l < 0 || c >= data->map_w || l >= data->map_h
		|| data->map[l][c] == '1')
		return (true);
	return (false);
}

void	calc_closed_parts(t_data *data, int l, int c,
	bool *tb_lr_is_closed)
{
	tb_lr_is_closed[0] = false;
	if (is_wall(data, l - 1, c) && is_wall(data, l, c - 1)
		&& is_wall(data, l - 1, c - 1))
		tb_lr_is_closed[0] = true;
	tb_lr_is_closed[1] = false;
	if (is_wall(data, l - 1, c) && is_wall(data, l, c + 1)
		&& is_wall(data, l - 1, c + 1))
		tb_lr_is_closed[1] = true;
	tb_lr_is_closed[2] = false;
	if (is_wall(data, l + 1, c) && is_wall(data, l, c - 1)
		&& is_wall(data, l + 1, c - 1))
		tb_lr_is_closed[2] = true;
	tb_lr_is_closed[3] = false;
	if (is_wall(data, l + 1, c) && is_wall(data, l, c + 1)
		&& is_wall(data, l + 1, c + 1))
		tb_lr_is_closed[3] = true;
}

mlx_image_t	*which_wall_to_draw_3_closed(t_data *data, int l, int c)
{
	if (!is_wall(data, l + 1, c + 1))
		return (data->img->bg.wall_tl);
	if (!is_wall(data, l + 1, c - 1))
		return (data->img->bg.wall_tr);
	if (!is_wall(data, l - 1, c + 1))
		return (data->img->bg.wall_bl);
	if (!is_wall(data, l - 1, c - 1))
		return (data->img->bg.wall_br);
	return (data->img->bg.wall_nwe);
}

mlx_image_t	*which_wall_to_draw_1or2_closed(t_data *data,
	bool tb_lr_is_closed[2][2], int nb_closed)
{
	if (nb_closed == 2)
	{
		if (tb_lr_is_closed[0][0] && tb_lr_is_closed[1][0])
			return (data->img->bg.wall_e);
		if (tb_lr_is_closed[0][1] && tb_lr_is_closed[1][1])
			return (data->img->bg.wall_w);
		if (tb_lr_is_closed[1][0] && tb_lr_is_closed[1][1])
			return (data->img->bg.wall_n);
		if (tb_lr_is_closed[1][0])
			return (data->img->bg.wall_ne);
		if (tb_lr_is_closed[1][1])
			return (data->img->bg.wall_nw);
	}
	else if (nb_closed == 1)
	{
		if (tb_lr_is_closed[1][0])
			return (data->img->bg.wall_ne);
		if (tb_lr_is_closed[1][1])
			return (data->img->bg.wall_nw);
	}
	return (data->img->bg.wall_nwe);
}

mlx_image_t	*which_image_to_draw_at_tile(t_data *data, int c, int l)
{
	bool	tb_lr_is_closed[2][2];
	int		nb_closed;

	if (c < 0 || l < 0 || c >= data->map_w || l >= data->map_h)
		return (data->img->bg.wall_h);
	if (!is_wall(data, l, c))
		return (which_floor_to_draw_at_tile(data, l, c));
	if (!is_wall(data, l + 1, c))
		return (data->img->bg.wall_s);
	calc_closed_parts(data, l, c, (bool *)tb_lr_is_closed);
	nb_closed = tb_lr_is_closed[0][0] + tb_lr_is_closed[0][1]
		+ tb_lr_is_closed[1][0] + tb_lr_is_closed[1][1];
	if (nb_closed == 4)
		return (data->img->bg.wall_h);
	else if (nb_closed == 3)
		return (which_wall_to_draw_3_closed(data, l, c));
	else if (nb_closed == 0 && is_wall(data, l - 1, c))
		return (data->img->bg.wall);
	else
		return (
			which_wall_to_draw_1or2_closed(data, tb_lr_is_closed, nb_closed));
}
