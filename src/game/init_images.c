/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:27:47 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 16:33:07 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_wall_images(mlx_t *mlx, t_bg_images *bg)
{
	bg->wall_tl = get_image_from_png(mlx, "png/bg/wall_tl.png", LEN_TILE);
	bg->wall_s = get_image_from_png(mlx, "png/bg/wall_s.png", LEN_TILE);
	bg->wall_tr = get_image_from_png(mlx, "png/bg/wall_tr.png", LEN_TILE);
	bg->wall_e = get_image_from_png(mlx, "png/bg/wall_e.png", LEN_TILE);
	bg->wall_w = get_image_from_png(mlx, "png/bg/wall_w.png", LEN_TILE);
	bg->wall_bl = get_image_from_png(mlx, "png/bg/wall_bl.png", LEN_TILE);
	bg->wall_n = get_image_from_png(mlx, "png/bg/wall_n.png", LEN_TILE);
	bg->wall_br = get_image_from_png(mlx, "png/bg/wall_br.png", LEN_TILE);
	bg->wall_nw = get_image_from_png(mlx, "png/bg/wall_nw.png", LEN_TILE);
	bg->wall_ne = get_image_from_png(mlx, "png/bg/wall_ne.png", LEN_TILE);
	bg->wall_nwe = get_image_from_png(mlx, "png/bg/wall_nwe.png", LEN_TILE);
	bg->wall = get_image_from_png(mlx, "png/bg/wall.png", LEN_TILE);
	bg->wall_h = get_image_from_png(mlx, "png/bg/wall_h.png", LEN_TILE);
}

void	init_floor_images(mlx_t *mlx, t_bg_images *bg)
{
	bg->floor = get_image_from_png(mlx, "png/bg/floor.png", LEN_TILE);
	bg->floor_n = get_image_from_png(mlx, "png/bg/floor_n.png", LEN_TILE);
	bg->floor_s = get_image_from_png(mlx, "png/bg/floor_s.png", LEN_TILE);
	bg->floor_w = get_image_from_png(mlx, "png/bg/floor_w.png", LEN_TILE);
	bg->floor_e = get_image_from_png(mlx, "png/bg/floor_e.png", LEN_TILE);
	bg->floor_ns = get_image_from_png(mlx, "png/bg/floor_ns.png", LEN_TILE);
	bg->floor_nw = get_image_from_png(mlx, "png/bg/floor_nw.png", LEN_TILE);
	bg->floor_ne = get_image_from_png(mlx, "png/bg/floor_ne.png", LEN_TILE);
	bg->floor_sw = get_image_from_png(mlx, "png/bg/floor_sw.png", LEN_TILE);
	bg->floor_se = get_image_from_png(mlx, "png/bg/floor_se.png", LEN_TILE);
	bg->floor_we = get_image_from_png(mlx, "png/bg/floor_we.png", LEN_TILE);
	bg->floor_nsw = get_image_from_png(mlx, "png/bg/floor_nsw.png", LEN_TILE);
	bg->floor_nse = get_image_from_png(mlx, "png/bg/floor_nse.png", LEN_TILE);
	bg->floor_nwe = get_image_from_png(mlx, "png/bg/floor_nwe.png", LEN_TILE);
	bg->floor_swe = get_image_from_png(mlx, "png/bg/floor_swe.png", LEN_TILE);
	bg->floor_nswe = get_image_from_png(mlx, "png/bg/floor_nswe.png", LEN_TILE);
}

void	init_bg_images(t_data *data, mlx_t *mlx, t_bg_images *bg)
{
	bg->layer = new_placeholder(mlx, LEN_SCREEN, 0xff777777);
	init_wall_images(mlx, bg);
	init_floor_images(mlx, bg);
	if (!bg->layer || !bg->wall_tl || !bg->wall_s || !bg->wall_tr
		|| !bg->wall_e || !bg->wall_w || !bg->wall_bl || !bg->wall_n
		|| !bg->wall_nw || !bg->wall_ne || !bg->wall_nwe || !bg->wall
		|| !bg->wall_br || !bg->wall_h || !bg->floor || !bg->floor_n
		|| !bg->floor_e || !bg->floor_w || !bg->floor_s || !bg->floor_ns
		|| !bg->floor_ne || !bg->floor_nw || !bg->floor_se || !bg->floor_sw
		|| !bg->floor_we || !bg->floor_nse || !bg->floor_nsw || !bg->floor_nwe
		|| !bg->floor_swe || !bg->floor_nswe)
		abort_game(data);
}

void	init_player_foe_images(t_data *data)
{
	data->img->player_d = get_image_from_png(data->mlx, "png/player/down.png",
			LEN_TILE);
	data->img->player_u = get_image_from_png(data->mlx, "png/player/up.png",
			LEN_TILE);
	data->img->player_l = get_image_from_png(data->mlx, "png/player/left.png",
			LEN_TILE);
	data->img->player_r = get_image_from_png(data->mlx, "png/player/right.png",
			LEN_TILE);
	data->img->foe_d = get_image_from_png(data->mlx, "png/foe/down.png",
			LEN_TILE);
	data->img->foe_u = get_image_from_png(data->mlx, "png/foe/up.png",
			LEN_TILE);
	data->img->foe_l = get_image_from_png(data->mlx, "png/foe/left.png",
			LEN_TILE);
	data->img->foe_r = get_image_from_png(data->mlx, "png/foe/right.png",
			LEN_TILE);
}

void	init_images(t_data *data)
{
	data->img = malloc(sizeof(*(data->img)));
	if (!data->img)
		abort_game(data);
	init_bg_images(data, data->mlx, &(data->img->bg));
	data->img->main_layer = new_placeholder(data->mlx, LEN_SCREEN, 0xff777777);
	data->img->win_layer = new_placeholder(data->mlx, LEN_SCREEN, 0x00777777);
	init_player_foe_images(data);
	data->img->exit = get_image_from_png(data->mlx, "png/exit.png", LEN_TILE);
	data->img->exit_o = get_image_from_png(data->mlx, "png/exit_o.png",
			LEN_TILE);
	data->img->font = get_image_from_png(data->mlx, "png/font.png",
			LEN_TILE * 32);
	if (!data->img->bg.layer || !data->img->main_layer || !data->img->player_u
		|| !data->img->player_d || !data->img->player_l || !data->img->player_r
		|| !data->img->exit || !data->img->font || !data->img->exit_o
		|| !data->img->win_layer)
		abort_game(data);
	init_background(data);
}
