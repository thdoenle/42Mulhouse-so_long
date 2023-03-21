/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resized_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:40:20 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/02 14:40:57 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_resized_pixel(mlx_image_t *img, uint32_t color,
	uint32_t *t_xy, uint32_t scale)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	t_x;
	uint32_t	t_y;

	t_x = t_xy[0] * scale;
	t_y = t_xy[1] * scale;
	y = 0;
	while (y < scale)
	{
		x = 0;
		while (x < scale)
		{
			((uint32_t *)img->pixels)[(t_y + y) * img->width + t_x + x]
				= color;
			x++;
		}
		y++;
	}
}

mlx_image_t	*texture_to_image_resized(mlx_t *mlx, mlx_texture_t *t,
	uint32_t scale)
{
	mlx_image_t	*img;
	u_int32_t	xy[2];

	img = mlx_new_image(mlx, scale * t->width, scale * t->height);
	if (!img)
		return (NULL);
	xy[1] = 0;
	while (xy[1] < t->height)
	{
		xy[0] = 0;
		while (xy[0] < t->width)
		{
			draw_resized_pixel(img,
				((uint32_t *)t->pixels)[xy[1] * t->width + xy[0]], xy, scale);
			xy[0]++;
		}
		xy[1]++;
	}
	return (img);
}
