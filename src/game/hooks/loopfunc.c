/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loopfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:20:06 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 14:19:28 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_fps(t_data *data)
{
	static uint		fps = 0;
	static double	time = 0.;

	time += data->mlx->delta_time;
	fps++;
	while (time >= 1.)
	{
		time -= 1.;
		data->fps = fps;
		fps = 0;
	}
}

void	update_timer(t_data *data)
{
	if (data->p->move >= MOVE_IDLE && data->nb_mv)
		data->timer += data->mlx->delta_time;
}

void	loopfunc(void *param)
{
	update_fps(param);
	update_timer(param);
	update(param);
}
