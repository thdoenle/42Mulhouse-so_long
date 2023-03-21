/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:01:37 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 18:27:00 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_mv_col(t_data *data)
{
	uint32_t	xy_nums[5];

	xy_nums[0] = LEN_PIXEL * 4;
	xy_nums[1] = LEN_PIXEL * 3;
	xy_nums[2] = data->nb_mv;
	xy_nums[3] = data->nb_col;
	xy_nums[4] = data->max_col;
	put_str_to_image(data, data->img->main_layer, "m$ k$/$", xy_nums);
}

void	put_time(t_data *data)
{
	uint32_t	xy_nums[4];
	char		str[7];

	xy_nums[2] = (int)data->timer;
	xy_nums[3] = (int)((data->timer - (int)data->timer) * 100);
	str[0] = (int)(12 * (data->timer - (int)data->timer)) + 1;
	ft_strcpy((char *)str + 1, "$.$l2");
	xy_nums[0] = LEN_SCREEN - strtoimage_len(str, xy_nums + 2)
		- LEN_PIXEL * 4;
	xy_nums[1] = LEN_PIXEL * 3;
	put_str_to_image(data, data->img->main_layer, str, xy_nums);
}

void	put_fps(t_data *data)
{
	uint32_t	xy_nums[3];

	xy_nums[2] = data->fps;
	xy_nums[0] = LEN_SCREEN - strtoimage_len("FPS $", xy_nums + 2)
		- LEN_PIXEL * 4;
	xy_nums[1] = LEN_SCREEN - LEN_TILE + LEN_PIXEL * 2;
	put_str_to_image(data, data->img->main_layer, "FPS $", xy_nums);
}

void	put_win_msg(t_data *data)
{
	uint32_t	xy_nums[4];
	char		str[32];

	xy_nums[0] = (LEN_SCREEN - strtoimage_len("SO LONG", NULL)) / 2;
	xy_nums[1] = (LEN_SCREEN - LEN_TILE + LEN_PIXEL * 4) / 2 - LEN_TILE;
	put_str_to_image(data, data->img->win_layer, "SO LONG", xy_nums);
	ft_strcpy(str, "m$");
	xy_nums[2] = data->nb_mv;
	xy_nums[0] = (LEN_SCREEN - strtoimage_len(str, xy_nums + 2)) / 2;
	xy_nums[1] += LEN_TILE;
	put_str_to_image(data, data->img->win_layer, str, xy_nums);
	ft_strcpy(str, "t$.$l2");
	xy_nums[2] = (int)data->timer;
	xy_nums[3] = (int)((data->timer - (int)data->timer) * 100);
	xy_nums[0] = (LEN_SCREEN - strtoimage_len(str, xy_nums + 2)) / 2;
	xy_nums[1] += LEN_TILE;
	put_str_to_image(data, data->img->win_layer, str, xy_nums);
}

void	update_hud(t_data *data)
{
	if (!data->win)
	{
		put_mv_col(data);
		put_fps(data);
		put_time(data);
	}
	else
		put_win_msg(data);
}
