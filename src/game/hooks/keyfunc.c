/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyfunc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:45:17 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 17:07:03 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	keyfunc(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		closefunc(param);
		return ;
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS
		&& data->p->move >= MOVE_WIN)
	{
		if (data->p->move < MOVE_IDLE)
			data->anim->p_death.t = data->anim->p_death.t_max;
		data->p->move = MOVE_DEATH;
	}
}
