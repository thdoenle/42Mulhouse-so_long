/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:05:12 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/13 13:59:39 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_image(mlx_image_t *dest, mlx_image_t *src, uint32_t x, uint32_t y)
{
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	*src_buf;
	uint32_t	*dest_buf;

	src_x = 0;
	src_y = 0;
	src_buf = (uint32_t *)src->pixels;
	dest_buf = (uint32_t *)dest->pixels;
	while (src_y < src->height)
	{
		if (x + src_x >= 0 && x + src_x < dest->width
			&& y + src_y >= 0 && y + src_y < dest->height
			&& (src_buf[src_x + src_y * src->width] & 0xff000000))
			dest_buf[(x + src_x) + (y + src_y) * dest->width]
				= src_buf[src_x + src_y * src->width];
		src_x++;
		if (src_x == src->width)
		{
			src_x = 0;
			src_y++;
		}
	}
}

void	draw_image_from_coords(mlx_image_t *dest, mlx_image_t *src, uint32_t x,
	uint32_t y)
{
	uint32_t	dest_x;
	uint32_t	dest_y;
	uint32_t	*src_buf;
	uint32_t	*dest_buf;

	dest_x = 0;
	dest_y = 0;
	src_buf = (uint32_t *)src->pixels;
	dest_buf = (uint32_t *)dest->pixels;
	while (dest_y < dest->height)
	{
		if (x + dest_x >= 0 && x + dest_x < src->width
			&& y + dest_y >= 0 && y + dest_y < src->height
			&& (src_buf[x + dest_x + (y + dest_y) * src->width] & 0xff000000))
			dest_buf[dest_x + dest_y * dest->width]
				= src_buf[x + dest_x + (y + dest_y) * src->width];
		dest_x++;
		if (dest_x == dest->width)
		{
			dest_x = 0;
			dest_y++;
		}
	}
}

void	draw_image_from_image_area(mlx_image_t *dest, t_img_area *src,
	uint32_t x, uint32_t y)
{
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	*src_buf;
	uint32_t	*dest_buf;

	src_x = src->x;
	src_y = src->y;
	src_buf = (uint32_t *)src->img->pixels;
	dest_buf = (uint32_t *)dest->pixels;
	while (src_y < src->y + src->h)
	{
		if (x + src_x - src->x >= 0 && x + src_x - src->x < dest->width
			&& y + src_y - src->y >= 0 && y + src_y - src->y < dest->height
			&& (src_buf[src_x + src_y * src->img->width] & 0xff000000))
			dest_buf[(x + src_x - src->x) + (y + src_y - src->y) * dest->width]
				= src_buf[src_x + src_y * src->img->width];
		src_x++;
		if (src_x == src->x + src->w)
		{
			src_x = src->x;
			src_y++;
		}
	}
}

mlx_image_t	*new_placeholder(mlx_t *mlx, uint32_t len, uint32_t color)
{
	mlx_image_t	*placeholder;

	placeholder = mlx_new_image(mlx, len, len);
	if (!placeholder)
		return (NULL);
	ft_pixelset(placeholder->pixels, color, len * len);
	return (placeholder);
}

mlx_image_t	*get_image_from_png(mlx_t *mlx, const char *path, uint32_t size)
{
	mlx_texture_t	*t;
	mlx_image_t		*img;

	t = mlx_load_png(path);
	if (!t)
		return (NULL);
	if (size)
		img = texture_to_image_resized(mlx, t, size / t->width);
	else
		img = mlx_texture_to_image(mlx, t);
	mlx_delete_texture(t);
	return (img);
}
