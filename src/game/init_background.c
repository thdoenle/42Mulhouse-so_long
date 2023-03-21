/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:26:03 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/13 13:33:17 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	calc_nb_tiles_and_offset(int *nb_o, uint32_t *offset, int len)
{
	nb_o[0] = (*offset / LEN_TILE) * 2 + len;
	if (*offset % LEN_TILE)
	{
		nb_o[0] += 2;
		*offset = -(LEN_TILE / 2);
	}
	else
		*offset = 0;
	nb_o[1] = (nb_o[0] - len) / 2;
}

void	fill_background(t_data *data, uint32_t x_offset, uint32_t y_offset)
{
	int	x;
	int	y;
	int	nb_o_x[2];
	int	nb_o_y[2];

	calc_nb_tiles_and_offset(nb_o_x, &x_offset, data->map_w);
	calc_nb_tiles_and_offset(nb_o_y, &y_offset, data->map_h);
	y = 0;
	while (y < nb_o_y[0])
	{
		x = 0;
		while (x < nb_o_x[0])
		{
			draw_image(data->img->bg.bg,
				which_image_to_draw_at_tile(data, x - nb_o_x[1], y - nb_o_y[1]),
				x_offset + LEN_TILE * x, y_offset + LEN_TILE * y);
			x++;
		}
		y++;
	}
}

void	init_background(t_data *data)
{
	uint32_t	width;
	uint32_t	height;

	width = LEN_TILE * data->map_w;
	if (width < LEN_SCREEN)
		width = LEN_SCREEN;
	height = LEN_TILE * data->map_h;
	if (height < LEN_SCREEN)
		height = LEN_SCREEN;
	data->img->bg.bg = mlx_new_image(data->mlx, width, height);
	if (!data->img->bg.bg)
		abort_game(data);
	fill_background(data, data->map_o_x, data->map_o_y);
}
