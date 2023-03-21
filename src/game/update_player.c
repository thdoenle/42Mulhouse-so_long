/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:53:42 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/15 13:33:14 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player_move(t_data *data)
{
	data->nb_mv++;
	data->dir = data->p->move;
	data->p->x_from = data->p->x;
	data->p->y_from = data->p->y;
	data->p->x_to = data->p->x;
	data->p->y_to = data->p->y;
	if (data->p->move == MOVE_DOWN)
		data->p->y_to += LEN_TILE;
	else if (data->p->move == MOVE_LEFT)
		data->p->x_to -= LEN_TILE;
	else if (data->p->move == MOVE_RIGHT)
		data->p->x_to += LEN_TILE;
	else if (data->p->move == MOVE_UP)
		data->p->y_to -= LEN_TILE;
	if (data->foes)
		tracks_add_move(data);
}

void	check_move_input_list(t_data *data, int *key_udlr)
{
	ft_bzero(key_udlr, sizeof(*key_udlr) * 4);
	if ((mlx_is_key_down(data->mlx, MLX_KEY_W)
			|| mlx_is_key_down(data->mlx, MLX_KEY_UP))
		&& data->map[data->p->l - 1][data->p->c] != '1')
		key_udlr[0] = 1;
	if ((mlx_is_key_down(data->mlx, MLX_KEY_S)
			|| mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		&& data->map[data->p->l + 1][data->p->c] != '1')
		key_udlr[1] = 1;
	if ((mlx_is_key_down(data->mlx, MLX_KEY_A)
			|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		&& data->map[data->p->l][data->p->c - 1] != '1')
		key_udlr[2] = 1;
	if ((mlx_is_key_down(data->mlx, MLX_KEY_D)
			|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		&& data->map[data->p->l][data->p->c + 1] != '1')
		key_udlr[3] = 1;
}

void	check_move_input(t_data *data)
{
	int	key_udlr[4];
	int	key_nb;

	check_move_input_list(data, (int *)key_udlr);
	key_nb = key_udlr[0] + key_udlr[1] + key_udlr[2] + key_udlr[3];
	if (key_nb > 2)
		data->p->move = MOVE_IDLE;
	else if (key_udlr[0] && (data->p->move != MOVE_UP || key_nb < 2))
		data->p->move = MOVE_UP;
	else if (key_udlr[1] && (data->p->move != MOVE_DOWN || key_nb < 2))
		data->p->move = MOVE_DOWN;
	else if (key_udlr[2] && (data->p->move != MOVE_LEFT || key_nb < 2))
		data->p->move = MOVE_LEFT;
	else if (key_udlr[3] && (data->p->move != MOVE_RIGHT || key_nb < 2))
		data->p->move = MOVE_RIGHT;
	else
		data->p->move = MOVE_IDLE;
}

void	end_player_move(t_data *data)
{
	data->p->l += (data->p->y_to - data->p->y_from) / LEN_TILE;
	data->p->c += (data->p->x_to - data->p->x_from) / LEN_TILE;
	data->p->x = data->p->x_to;
	data->p->y = data->p->y_to;
	check_move_input(data);
	if (data->p->move != MOVE_IDLE)
	{
		data->p->t -= 1.;
		init_player_move(data);
	}
	else
	{
		data->p->t = 0.;
		if (data->foes)
			tracks_add_move(data);
	}
}

void	update_player_pos(t_data *data)
{
	if (data->p->move == MOVE_IDLE)
		check_move_input(data);
	if (data->p->move == MOVE_IDLE)
		return ;
	if (data->p->t == 0.)
		init_player_move(data);
	data->p->t += data->mlx->delta_time / TIME_MOVE;
	if (data->p->t >= 1.)
		end_player_move(data);
	if (data->p->move != MOVE_IDLE)
	{
		data->p->x = nearbyint((data->p->x_to - data->p->x_from) * data->p->t)
			+ data->p->x_from;
		data->p->y = nearbyint((data->p->y_to - data->p->y_from) * data->p->t)
			+ data->p->y_from;
	}
}
