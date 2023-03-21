/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtoimage_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:01:45 by thdoenle          #+#    #+#             */
/*   Updated: 2023/03/16 18:24:09 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

uint32_t	numtoimage_len(uint32_t n, uint32_t l)
{
	uint32_t	len;

	len = 0;
	while (n >= 10 || l > 0)
	{
		len += LEN_TILE - 8 * LEN_PIXEL;
		n /= 10;
		if (l)
			l--;
	}
	return (len + LEN_TILE - 10 * LEN_PIXEL);
}

uint32_t	chartoimage_len(char c)
{
	if (c == 'm' || c == 'k')
		return (LEN_TILE - 6 * LEN_PIXEL);
	if (c <= 13)
		return (LEN_TILE - 4 * LEN_PIXEL);
	return (LEN_TILE - 10 * LEN_PIXEL);
}

uint32_t	strtoimage_len(char *s, uint32_t *nums)
{
	uint32_t	len;

	len = 0;
	while (*s)
	{
		if (*s == '$')
		{
			if (s[1] == 'l')
			{
				s += 2;
				len += numtoimage_len(*nums, *s - '0' - 1);
			}
			else
				len += numtoimage_len(*nums, 0);
		}
		else
			len += chartoimage_len(*s);
		s++;
		if (*s)
			len += 2 * LEN_PIXEL;
	}
	return (len);
}
