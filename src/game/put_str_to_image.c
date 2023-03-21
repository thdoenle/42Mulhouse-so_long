/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str_to_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:18:40 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 17:00:09 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_area_at_icon_char(t_img_area *area, char c, uint32_t *x_offset)
{
	if (c == 'm')
	{
		*x_offset -= LEN_PIXEL * 2;
		area->x = LEN_TILE * 27;
		area->y = LEN_TILE * 4;
	}
	else if (c == 'k')
	{
		*x_offset -= LEN_PIXEL * 2;
		area->x = LEN_TILE * 29;
		area->y = LEN_TILE * 2;
	}
	else if (c <= 13)
	{
		*x_offset -= LEN_PIXEL * 3;
		area->x = LEN_TILE * (c - 1);
		area->y = LEN_TILE * 3;
	}
	else if (c == 't')
	{
		area->x = LEN_TILE * 12;
		area->y = LEN_TILE * 3;
	}
}

void	set_area_at_char(t_img_area *area, char c, uint32_t *x_offset)
{
	if (c >= 'A' && c <= 'Z')
		area->x = LEN_TILE * (c - 'A' + 1);
	else if (c >= '0' && c <= '9')
	{
		area->x = LEN_TILE * (c - '0' + 1);
		area->y = LEN_TILE;
	}
	else if (c == '/')
	{
		area->x = LEN_TILE * 13;
		area->y = LEN_TILE;
	}
	else if (c == '.')
		area->y = LEN_TILE;
	else
		set_area_at_icon_char(area, c, x_offset);
}

void	put_char_to_image(t_data *data, mlx_image_t *dst, char c, uint32_t *xy)
{
	t_img_area	area;
	uint32_t	x_offset;
	uint32_t	y_offset;

	area.img = data->img->font;
	x_offset = 5 * LEN_PIXEL;
	y_offset = 2 * LEN_PIXEL;
	area.x = 0;
	area.y = 0;
	set_area_at_char(&area, c, &x_offset);
	area.x += x_offset;
	area.y += y_offset;
	area.w = LEN_TILE - 2 * x_offset;
	area.h = LEN_TILE - 2 * y_offset;
	draw_image_from_image_area(dst, &area, xy[0], xy[1]);
	xy[0] += area.w + 2 * LEN_PIXEL;
}

void	put_nbr_to_image(void *data_dst[2], uint32_t n, uint32_t len,
	uint32_t *xy)
{
	if (n >= 10 || (len > 0 && len < 10))
		put_nbr_to_image(data_dst, n / 10, len - 1, xy);
	put_char_to_image(data_dst[0], data_dst[1], (n % 10) + '0', xy);
}

void	put_str_to_image(t_data *data, mlx_image_t *dst, char *msg,
	uint32_t *xy_nums)
{
	uint32_t	num_i;
	void		*data_dst[2];

	data_dst[0] = data;
	data_dst[1] = dst;
	num_i = 2;
	while (*msg)
	{
		if (*msg == '$')
		{
			if (msg[1] == 'l')
			{
				msg += 2;
				put_nbr_to_image(data_dst, xy_nums[num_i], *msg - '0' - 1,
					xy_nums);
			}
			else
				put_nbr_to_image(data_dst, xy_nums[num_i], 0, xy_nums);
			num_i++;
		}
		else
			put_char_to_image(data, dst, *msg, xy_nums);
		msg++;
	}
}
