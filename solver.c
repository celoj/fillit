/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:24:29 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/26 21:16:03 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		set_piece(t_map *map, t_piece *piece, int i, int j)
{
	int		k;
	int		l;
	int		unset;

	k = -1;
	if (piece->height > 1 && map->map[i + 1][j] == piece->ordinal)
		unset = 1;
	else if (piece->width > 1 && map->map[i][j + 1] == piece->ordinal)
		unset = 1;
	while (++k < piece->height)
	{
		l = -1;
		while (++l < piece->width)
		{
			if (unset && map->map[i + k][j + l] == piece->ordinal)
				map->map[i + k][j + l] = '.';
			else if (piece->piece[k][l] != '.')
				map->map[i + k][j + l] = piece->ordinal;
		}
	}
}

int				place(t_map *map, t_piece *piece, int i, int j)
{
	int		k;
	int		l;

	k = -1;
	while (++k < piece->height)
	{
		l = -1;
		while (++l < piece->width)
		{
			if (map->map[i + k][j + l] != '.' && piece->piece[k][l] != '.')
				return (0);
		}
	}
	set_piece(map, piece, i, j);
	return (1);
}

static int		solve(t_map *map, t_piece *pieces)
{
	int		i;
	int		j;

	if (!pieces)
		return (1);
	i = -1;
	while (++i < map->n - pieces->height + 1)
	{
		j = -1;
		while (++j < map->n - pieces->width + 1)
		{
			if (place(map, pieces, i, j))
			{
				if (solve(map, pieces->next))
					return (1);
				else
					set_piece(map, pieces, i, j);
			}
		}
	}
	return (0);
}

t_map			*fillit(t_piece *pieces)
{
	int		n;
	t_map	*map;

	n = calc_best_size(pieces);
	if (!(map = gen_map(n)))
		return (NULL);
	while (!solve(map, pieces))
	{
		n++;
		free_map(map);
		map = gen_map(n);
	}
	return (map);
}
