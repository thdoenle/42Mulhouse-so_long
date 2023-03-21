/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:08:23 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/14 14:34:54 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	char	**ptr;

	ptr = map;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(map);
}

void	free_anim(t_anims *anim)
{
	free(anim->col.img);
	free(anim->foe_death.img);
	free(anim->foe_spawn.img);
	free(anim->p_death.img);
	free(anim->p_spawn.img);
	free(anim);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
		free_map(data->map);
	free(data->p);
	lstclear(&data->c);
	foesclear(&data->foes);
	if (data->tracks)
		movesclear(&data->tracks->oldest);
	free(data->tracks);
	free(data->e);
	free(data->img);
	if (data->anim)
		free_anim(data->anim);
	if (data->mlx)
		mlx_close_window(data->mlx);
}
