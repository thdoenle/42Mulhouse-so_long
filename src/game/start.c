/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:38:20 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 16:23:40 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_hooks(t_data *data)
{
	mlx_close_hook(data->mlx, closefunc, data);
	if (mlx_loop_hook(data->mlx, loopfunc, data) == false)
		abort_game(data);
	mlx_key_hook(data->mlx, keyfunc, data);
}

void	set_layers(t_data *data)
{
	mlx_image_to_window(data->mlx, data->img->bg.layer, 0, 0);
	mlx_set_instance_depth(data->img->bg.layer->instances, 0);
	mlx_image_to_window(data->mlx, data->img->main_layer, 0, 0);
	mlx_set_instance_depth(data->img->main_layer->instances, 1);
	mlx_image_to_window(data->mlx, data->img->win_layer, 0, 0);
	mlx_set_instance_depth(data->img->main_layer->instances, 1);
}

void	start_game(t_data *data)
{
	data->mlx = mlx_init(LEN_SCREEN, LEN_SCREEN, "SO LONG", false);
	if (!data->mlx)
		abort_game(data);
	init_tracks(data);
	init_images(data);
	init_animations(data);
	set_layers(data);
	set_hooks(data);
	data->foe_delay = 1.;
	data->dir = MOVE_DOWN;
	calc_offset(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
