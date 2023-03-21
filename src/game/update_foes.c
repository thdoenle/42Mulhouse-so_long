/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_foes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:36:58 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 11:42:32 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*get_foe_img_from_dir(t_data *data, t_move_type dir)
{
	if (dir == MOVE_UP)
		return (data->img->foe_u);
	else if (dir == MOVE_DOWN)
		return (data->img->foe_d);
	else if (dir == MOVE_LEFT)
		return (data->img->foe_l);
	else if (dir == MOVE_RIGHT)
		return (data->img->foe_r);
	return (NULL);
}

void	update_foe(t_data *data, t_foe *foe)
{
	if (data->p->move < MOVE_IDLE)
	{
		foe->img = get_anim_img(&data->anim->foe_death);
		return ;
	}
	while (foe->t >= foe->move_ptr->time)
	{
		foe->t -= foe->move_ptr->time;
		foe->move_ptr = foe->move_ptr->next;
		if (foe == data->foes)
			tracks_rm_oldest_move(data);
		foe->img = get_foe_img_from_dir(data, foe->move_ptr->dir);
	}
	foe->x = nearbyint((foe->move_ptr->x_to - foe->move_ptr->x_from)
			* foe->t / TIME_MOVE) + foe->move_ptr->x_from;
	foe->y = nearbyint((foe->move_ptr->y_to - foe->move_ptr->y_from)
			* foe->t / TIME_MOVE) + foe->move_ptr->y_from;
}

void	update_spawning_foe(t_data *data, t_foe *foe)
{
	if (data->p->move < MOVE_IDLE)
		foe->t -= data->mlx->delta_time;
	if (foe->t >= data->anim->foe_spawn.t_max)
	{
		foe->t -= data->anim->foe_spawn.t_max;
		foe->move_type = MOVE_IDLE;
		foe->img = get_foe_img_from_dir(data, foe->move_ptr->dir);
	}
	else
	{
		data->anim->foe_spawn.t = foe->t;
		foe->img = get_anim_img(&data->anim->foe_spawn);
	}
	foe->x = foe->move_ptr->x_from;
	foe->y = foe->move_ptr->y_from;
}

void	update_foes(t_data *data)
{
	t_foe	*foe;

	foe = data->foes;
	while (foe)
	{
		if (data->p->move >= MOVE_IDLE)
			foe->t += data->mlx->delta_time;
		if (foe->move_type == MOVE_SPAWN)
			update_spawning_foe(data, foe);
		if (foe->move_type == MOVE_IDLE)
			update_foe(data, foe);
		foe = foe->next;
	}
}
