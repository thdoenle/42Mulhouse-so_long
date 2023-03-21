/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:59:39 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/13 13:36:00 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_player_coords(t_data *data, int l, int c)
{
	data->p = malloc(sizeof(*(data->p)));
	if (!data->p)
		abort_parsing(data, NULL, 0, NULL);
	data->p_l = l;
	data->p_c = c;
	data->p->l = l;
	data->p->c = c;
	data->p->x = data->map_o_x + LEN_TILE * c;
	data->p->y = data->map_o_y + LEN_TILE * l;
	data->p->move = MOVE_SPAWN;
	data->p->t = 0.;
}

void	set_exit_coords(t_data *data, int l, int c)
{
	data->e = malloc(sizeof(*(data->e)));
	if (!data->e)
		abort_parsing(data, NULL, 0, NULL);
	data->e->l = l;
	data->e->c = c;
	data->e->x = data->map_o_x + LEN_TILE * c;
	data->e->y = data->map_o_y + LEN_TILE * l;
}

void	set_map_offset(t_data *data)
{
	if (LEN_TILE * data->map_w < LEN_SCREEN)
		data->map_o_x = (LEN_SCREEN - LEN_TILE * data->map_w) / 2;
	else
		data->map_o_x = 0;
	if (LEN_TILE * data->map_h < LEN_SCREEN)
		data->map_o_y = (LEN_SCREEN - LEN_TILE * data->map_h) / 2;
	else
		data->map_o_y = 0;
}

void	add_collectible(t_data *data, int l, int c)
{
	t_lst	*new;

	new = lstnew(l, c, data->map_o_x + LEN_TILE * c,
			data->map_o_y + LEN_TILE * l);
	if (!new)
		abort_parsing(data, NULL, 0, NULL);
	lstadd_front(&(data->c), new);
	data->max_col++;
}
