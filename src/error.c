/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:23:39 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 17:08:08 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error(char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
		ft_putstr_fd(2, msg);
	else
	{
		perror("errno");
		ft_putstr_fd(2, "mlx_errno: ");
		ft_putstr_fd(2, (char *)mlx_strerror(mlx_errno));
	}
	ft_putstr_fd(2, "\n");
	exit(EXIT_FAILURE);
}

void	abort_parsing(t_data *data, void *to_free, int fd, char *msg)
{
	free(to_free);
	if (data)
		free_data(data);
	if (fd)
		close(fd);
	error(msg);
}

void	abort_game(t_data *data)
{
	free_data(data);
	error(NULL);
}
