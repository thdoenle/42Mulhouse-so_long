/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:56:25 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/13 10:58:12 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	put_num_at_str(char *str, int n)
{
	int	len;
	int	x;

	x = n;
	len = 0;
	if (!x)
		len++;
	while (x > 0)
	{
		x /= 10;
		len++;
	}
	x = len;
	while (x > 0)
	{
		x--;
		str[x] = (n % 10) + '0';
		n /= 10;
	}
	return (len);
}

mlx_image_t	*get_anim_image(mlx_t *mlx, const char *path, int n)
{
	char	img_path[128];
	char	*ext;
	int		i;

	i = 0;
	while (path[i])
	{
		img_path[i] = path[i];
		i++;
	}
	i += put_num_at_str((char *)img_path + i, n);
	ext = ".png";
	while (*ext)
	{
		img_path[i] = *ext;
		ext++;
		i++;
	}
	img_path[i] = '\0';
	return (get_image_from_png(mlx, img_path, LEN_TILE));
}

mlx_image_t	**get_anim_images(mlx_t *mlx, const char *path, int nb_img)
{
	mlx_image_t	**images;
	int			i;

	images = malloc(sizeof(*images) * nb_img);
	if (!images)
		return (NULL);
	i = 0;
	while (i < nb_img)
	{
		images[i] = get_anim_image(mlx, path, i);
		if (!images[i])
		{
			free(images);
			return (NULL);
		}
		i++;
	}
	return (images);
}

t_anim	get_anim(mlx_t *mlx, const char *path, int nb_img, double time)
{
	t_anim	anim;

	anim.nb_img = nb_img;
	anim.t_max = time;
	anim.t = 0.;
	anim.img = get_anim_images(mlx, path, nb_img);
	return (anim);
}

t_anim	get_rev_anim_copy(t_anim anim)
{
	mlx_image_t	**src_img;
	int			i;

	if (!anim.img)
		return (anim);
	src_img = anim.img;
	anim.img = malloc(sizeof(*(anim.img)) * (size_t)anim.nb_img);
	if (!anim.img)
		return (anim);
	i = 0;
	while (i < (int)anim.nb_img)
	{
		anim.img[i] = src_img[(int)anim.nb_img - i - 1];
		i++;
	}
	return (anim);
}
