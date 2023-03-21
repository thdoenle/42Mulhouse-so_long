/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:14:27 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/10 16:57:32 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_flood *flood, int l, int c)
{
	if (flood->map[l][c] == '1')
		return ;
	if (flood->map[l][c] == 'E')
		flood->exit = 1;
	if (flood->map[l][c] == 'C')
		flood->nb_col++;
	flood->map[l][c] = '1';
	flood_fill(flood, l + 1, c);
	flood_fill(flood, l, c + 1);
	flood_fill(flood, l - 1, c);
	flood_fill(flood, l, c - 1);
}

void	check_if_doable(t_data *data)
{
	t_flood	flood;

	if (!data->p)
		abort_parsing(data, NULL, 0, "No player in map");
	if (!data->e)
		abort_parsing(data, NULL, 0, "No exit in map");
	if (!data->max_col)
		abort_parsing(data, NULL, 0, "No collectible in map");
	ft_bzero(&flood, sizeof(flood));
	flood.map = str_tab_copy(data->map);
	if (!flood.map)
		abort_parsing(data, NULL, 0, NULL);
	flood_fill(&flood, data->p->l, data->p->c);
	free_map(flood.map);
	if (!flood.exit)
		abort_parsing(data, NULL, 0, "Player cannot reach exit");
	if (flood.nb_col != data->max_col)
		abort_parsing(data, NULL, 0, "Player cannot collect everything");
}

void	check_char(t_data *data, int l_i, int c_i, char c)
{
	if ((!l_i || !c_i || l_i == data->map_h - 1 || c_i == data->map_w - 1)
		&& c != '1')
		abort_parsing(data, NULL, 0, "Map should be surrounded by walls");
	else if (c == 'P')
	{
		if (data->p)
			abort_parsing(data, NULL, 0, "More than one player in map");
		set_player_coords(data, l_i, c_i);
	}
	else if (c == 'E')
	{
		if (data->e)
			abort_parsing(data, NULL, 0, "More than one exit in map");
		set_exit_coords(data, l_i, c_i);
	}
	else if (c == 'C')
		add_collectible(data, l_i, c_i);
	else if (c != '0' && c != '1')
		abort_parsing(data, NULL, 0, "Unknown character");
}

void	check_map(t_data *data)
{
	int	l;
	int	c;

	l = 0;
	while (l < data->map_h)
	{
		c = 0;
		while (data->map[l][c] != '\n' && data->map[l][c])
		{
			check_char(data, l, c, data->map[l][c]);
			c++;
		}
		if (c != data->map_w)
			abort_parsing(data, NULL, 0, "Map is not rectangular");
		l++;
	}
	check_if_doable(data);
}

void	parse_map(t_data *data, char *file)
{
	if (check_file_ext(file, ".ber") == ERR)
		error("Map file should have '.ber' extension");
	data->map_h = count_lines(file);
	if (data->map_h < 3)
		error("Not enough lines in map");
	store_map(data, file);
	data->map_w = ft_strlen(data->map[0]) - 1;
	set_map_offset(data);
	check_map(data);
}
