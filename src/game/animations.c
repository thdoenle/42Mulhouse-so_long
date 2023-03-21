/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:58:16 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 11:02:51 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_anim(t_anim *anim, double time, bool loop)
{
	anim->t += time;
	if (loop)
	{
		while (anim->t >= anim->t_max)
			anim->t -= anim->t_max;
	}
}

void	update_animations(t_data *data)
{
	update_anim(&data->anim->col, data->mlx->delta_time, true);
	if (data->p->move == MOVE_SPAWN)
	{
		update_anim(&data->anim->p_spawn, data->mlx->delta_time, false);
		if (data->anim->p_spawn.t >= data->anim->p_spawn.t_max)
			data->p->move = MOVE_IDLE;
	}
	else if (data->p->move == MOVE_DEATH)
		update_anim(&data->anim->p_death, data->mlx->delta_time, false);
	if (data->p->move == MOVE_DEATH || data->p->move == MOVE_WIN)
		update_anim(&data->anim->foe_death, data->mlx->delta_time, false);
}

mlx_image_t	*get_anim_img(t_anim *anim)
{
	if (anim->t < 0. || anim->t >= anim->t_max)
		return (NULL);
	return (anim->img[(int)floor(anim->t * anim->nb_img / anim->t_max)]);
}

void	init_animations(t_data *data)
{
	data->anim = malloc(sizeof(*(data->anim)));
	if (!data->anim)
		abort_game(data);
	data->anim->col = get_anim(data->mlx, "png/key/", 6, TIME_KEY);
	data->anim->p_death = get_anim(data->mlx, "png/player_death/", 5, TIME_DIE);
	data->anim->p_spawn = get_rev_anim_copy(data->anim->p_death);
	data->anim->foe_death = get_anim(data->mlx, "png/foe_death/", 5, TIME_DIE);
	data->anim->foe_spawn = get_rev_anim_copy(data->anim->foe_death);
	if (!data->anim->col.img
		|| !data->anim->foe_death.img || !data->anim->foe_spawn.img
		|| !data->anim->p_death.img || !data->anim->p_spawn.img)
		abort_game(data);
}
