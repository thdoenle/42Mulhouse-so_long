/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:27:40 by thdoenle          #+#    #+#             */
/*   Updated: 2023/02/18 20:15:54 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_pixelset(void *addr, uint32_t val, size_t len)
{
	uint32_t	*ptr;

	ptr = addr;
	while (len)
	{
		*ptr = val;
		len--;
		ptr++;
	}
}

void	ft_bzero(void *addr, size_t len)
{
	char	*ptr;

	ptr = addr;
	while (len)
	{
		*ptr = 0;
		len--;
		ptr++;
	}
}

char	*ft_strdup(char *s)
{
	char	*new;
	int		i;

	i = ft_strlen(s);
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	new[i] = '\0';
	while (i)
	{
		i--;
		new[i] = s[i];
	}
	return (new);
}

char	**abort_str_tab_copy(char **tab)
{
	char	**ptr;

	ptr = tab;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(tab);
	return (NULL);
}

char	**str_tab_copy(char **tab)
{
	char	**new;
	int		tab_len;
	int		i;

	tab_len = 0;
	while (tab[tab_len])
		tab_len++;
	new = malloc(sizeof(*new) * (tab_len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < tab_len)
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			return (abort_str_tab_copy(new));
		i++;
	}
	new[i] = NULL;
	return (new);
}
