/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:44:03 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/26 21:15:51 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		print_map(t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->n)
	{
		ft_putstr(map->map[i]);
		ft_putchar('\n');
	}
}

static int	get_list_size(t_piece *pieces)
{
	int			size;
	t_piece		*walker;

	size = 0;
	walker = pieces;
	while (walker)
	{
		size++;
		walker = walker->next;
	}
	return (size);
}

int			calc_best_size(t_piece *pieces)
{
	int size;
	int min_size;

	min_size = 2;
	size = get_list_size(pieces) * 4;
	while (min_size * min_size < size)
		min_size++;
	return (min_size);
}

t_map		*gen_map(int n)
{
	int		i;
	int		j;
	t_map	*map;

	if (!(map = malloc(sizeof(map))))
		return (NULL);
	if (!(map->map = (char **)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	map->n = n;
	map->map[n] = NULL;
	i = -1;
	while (++i < n)
	{
		if (!(map->map[i] = ft_strnew(n)))
		{
			map->n = i;
			free_map(map);
			return (NULL);
		}
		j = -1;
		while (++j < n)
			map->map[i][j] = '.';
		map->map[i][n] = '\0';
	}
	return (map);
}

void		free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->n)
		free(map->map[i]);
	free(map->map);
	free(map);
	map = NULL;
}
