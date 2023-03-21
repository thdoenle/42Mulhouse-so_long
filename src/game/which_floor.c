/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_floor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:28:21 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/11 17:33:36 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*which_floor_n_s(t_data *data, int l, int c)
{
	if (is_wall(data, l, c - 1))
	{
		if (is_wall(data, l, c + 1))
			return (data->img->bg.floor_nswe);
		else
			return (data->img->bg.floor_nsw);
	}
	else
	{
		if (is_wall(data, l, c + 1))
			return (data->img->bg.floor_nse);
		else
			return (data->img->bg.floor_ns);
	}
}

mlx_image_t	*which_floor_n_nots(t_data *data, int l, int c)
{
	if (is_wall(data, l, c - 1))
	{
		if (is_wall(data, l, c + 1))
			return (data->img->bg.floor_nwe);
		else
			return (data->img->bg.floor_nw);
	}
	else
	{
		if (is_wall(data, l, c + 1))
			return (data->img->bg.floor_ne);
		else
			return (data->img->bg.floor_n);
	}
}

mlx_image_t	*which_floor_notn_s(t_data *data, int l, int c)
{
	if (is_wall(data, l, c - 1))
	{
		if (is_wall(data, l, c + 1))
			return (data->img->bg.floor_swe);
		else
			return (data->img->bg.floor_sw);
	}
	else
	{
		if (is_wall(data, l, c + 1))
			return (data->img->bg.floor_se);
		else
			return (data->img->bg.floor_s);
	}
}

mlx_image_t	*which_floor_notn_nots(t_data *data, int l, int c)
{
	if (is_wall(data, l, c - 1))
	{
		if (is_wall(data, l, c + 1))
			return (data->img->bg.floor_we);
		else
			return (data->img->bg.floor_w);
	}
	else
	{
		if (is_wall(data, l, c + 1))
			return (data->img->bg.floor_e);
		else
			return (data->img->bg.floor);
	}
}

mlx_image_t	*which_floor_to_draw_at_tile(t_data *data, int l, int c)
{
	if (is_wall(data, l - 1, c))
	{
		if (is_wall(data, l + 1, c))
			return (which_floor_n_s(data, l, c));
		else
			return (which_floor_n_nots(data, l, c));
	}
	else
	{
		if (is_wall(data, l + 1, c))
			return (which_floor_notn_s(data, l, c));
		else
			return (which_floor_notn_nots(data, l, c));
	}
}
