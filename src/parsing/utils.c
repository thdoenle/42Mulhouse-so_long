/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:24:42 by thdoenle          #+#    #+#             */
/*   Updated: 2023/02/16 15:17:41 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_file_ext(char *file, char *ext)
{
	int	i;
	int	ext_i;

	i = ft_strlen(file);
	if (i < 4)
		return (ERR);
	ext_i = ft_strlen(ext);
	while (ext_i)
	{
		ext_i--;
		i--;
		if (file[i] != ext[ext_i])
			return (ERR);
	}
	return (0);
}

int	count_nl_in_buf(char *buf, ssize_t len)
{
	ssize_t	i;
	int		nb;

	i = 0;
	nb = 0;
	while (i < len)
	{
		if (buf[i] == '\n')
			nb++;
		i++;
	}
	return (nb);
}

int	count_lines(char *file)
{
	int		fd;
	int		nb;
	char	buf[BUFFER_SIZE];
	ssize_t	n;

	fd = open(file, O_RDONLY);
	if (fd == ERR)
		error(NULL);
	nb = 0;
	n = BUFFER_SIZE;
	while (n == BUFFER_SIZE)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == ERR)
			abort_parsing(NULL, NULL, fd, NULL);
		nb += count_nl_in_buf(buf, n);
	}
	if (!n)
		n = BUFFER_SIZE;
	if (nb && buf[n - 1] != '\n')
		nb++;
	close(fd);
	return (nb);
}

void	store_map(t_data *data, char *file)
{
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == ERR)
		error(NULL);
	data->map = malloc(sizeof(*(data->map)) * (data->map_h + 1));
	if (!data->map)
		abort_parsing(data, NULL, fd, NULL);
	i = 0;
	while (i < data->map_h)
	{
		data->map[i] = get_next_line(fd);
		if (!data->map[i])
			abort_parsing(data, NULL, fd, NULL);
		i++;
	}
	data->map[i] = NULL;
	close(fd);
}
