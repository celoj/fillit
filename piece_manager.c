/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:48:19 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/26 21:15:36 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char	**delete_piece_array(char **t, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		free(t[i]);
	free(t);
	return (0);
}

char		**make_piece(int height, int width)
{
	int		i;
	int		j;
	char	**s;

	if (!(s = (char **)malloc(height * sizeof(char *))))
		return (0);
	i = -1;
	while (++i < height)
	{
		if (!(s[i] = ft_strnew(width)))
			return (delete_piece_array(s, i));
		j = -1;
		while (++j < width)
			s[i][j] = '.';
		s[i][j] = '\0';
	}
	return (s);
}

t_piece		*abort_fillit(char **buffer, t_piece **pieces)
{
	t_piece *next;

	if (pieces)
	{
		while (*pieces)
		{
			next = (*pieces)->next;
			if ((*pieces)->piece)
				delete_piece_array((*pieces)->piece, (*pieces)->height);
			free(*pieces);
			*pieces = next;
		}
	}
	if (buffer)
	{
		ft_memdel((void **)buffer);
		buffer = NULL;
	}
	return (NULL);
}

void		update_component(char *data, t_piece *piece,
		int i, t_base *piece_pos)
{
	if (data[i] != '.')
		piece->piece[piece_pos->y][piece_pos->x] = piece->ordinal;
	data[i] = '.';
}
