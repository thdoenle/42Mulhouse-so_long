/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:23:42 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/15 16:27:35 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	tracks_add_move(t_data *data)
{
	t_move	*new;

	new = movenew(data->p, data->dir);
	if (!new)
		abort_game(data);
	if (data->tracks->newest)
	{
		data->tracks->newest->next = new;
		data->tracks->newest = new;
	}
	else
	{
		data->tracks->oldest = new;
		data->tracks->newest = new;
	}
}

void	tracks_rm_oldest_move(t_data *data)
{
	t_move	*to_free;

	to_free = data->tracks->oldest;
	data->tracks->oldest = data->tracks->oldest->next;
	if (to_free == data->tracks->newest)
		data->tracks->newest = NULL;
	free(to_free);
}

void	tracks_update_current_move(t_data *data)
{
	if (data->tracks->newest)
		data->tracks->newest->time += data->mlx->delta_time;
}

void	init_tracks(t_data *data)
{
	data->tracks = malloc(sizeof(*data->tracks));
	if (!data->tracks)
		abort_game(data);
	data->tracks->oldest = NULL;
	data->tracks->newest = NULL;
}
