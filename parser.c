/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:01:48 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/26 21:15:22 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int			read_dimensions(char *data, t_piece *piece,
		int i, int *start)
{
	int count;

	count = 0;
	data[i] = '$';
	if ((i % 5) < ((*start) % 5))
		*start -= 1;
	if ((i % 5) + 1 <= 4 && data[i + 1] == '#')
	{
		(piece->width)++;
		count += read_dimensions(data, piece, i + 1, start);
	}
	if ((i % 5) - 1 >= 0 && data[i - 1] == '#')
	{
		if ((i / 5) > 0 && data[i - 6] != '$')
			(piece->width)++;
		count += read_dimensions(data, piece, i - 1, start);
	}
	if ((i / 5) < 3 && data[i + 5] == '#')
	{
		(piece->height)++;
		count += read_dimensions(data, piece, i + 5, start);
	}
	return (1 + count);
}

static void			copy_piece(char *data, t_piece *piece,
		int i, t_base *piece_pos)
{
	update_component(data, piece, i, piece_pos);
	if ((i % 5) + 1 <= 4 && data[i + 1] == '$')
	{
		piece_pos->x += 1;
		copy_piece(data, piece, i + 1, piece_pos);
		piece_pos->x -= 1;
	}
	if ((i % 5) - 1 >= 0 && data[i - 1] == '$')
	{
		piece_pos->x -= 1;
		copy_piece(data, piece, i - 1, piece_pos);
		piece_pos->x += 1;
	}
	if ((i / 5) < 3 && data[i + 5] == '$')
	{
		piece_pos->y += 1;
		copy_piece(data, piece, i + 5, piece_pos);
		piece_pos->y -= 1;
	}
	if ((i / 5) > 0 && data[i - 5] == '$')
	{
		piece_pos->y -= 1;
		copy_piece(data, piece, i - 5, piece_pos);
		piece_pos->y += 1;
	}
}

static int			save_piece(char *data, int i, t_piece **pieces)
{
	t_piece		*piece;
	t_base		*piece_pos;
	int			start;

	if (!(piece = (t_piece *)malloc(sizeof(t_piece))))
		return (0);
	piece->piece = NULL;
	piece->height = 1;
	piece->width = 1;
	piece->next = *pieces;
	if (*pieces && (*pieces)->ordinal == 'Z')
		return (0);
	piece->ordinal = !(*pieces) ? 'A' : (*pieces)->ordinal + 1;
	*pieces = piece;
	start = i;
	if (read_dimensions(data, piece, i, &start) != 4
			|| (!(piece->piece = make_piece(piece->height, piece->width)))
				|| (!(piece_pos = (t_base *)malloc(sizeof(t_base)))))
		return (0);
	piece_pos->x = 0;
	piece_pos->y = 0;
	copy_piece(data, piece, start, piece_pos);
	free(piece_pos);
	return (1);
}

static int			create_piece(char *data, t_piece **pieces)
{
	int		i;
	int		found;

	i = -1;
	found = 0;
	while (++i < BUFF_SIZE - 1)
	{
		if (!found && data[i] == '#')
		{
			found = 1;
			if (!save_piece(data, i, pieces))
				return (0);
		}
		else if (data[i] != '.' && !(data[i] == '\n' && ((i + 1) % 5) == 0))
			return (0);
	}
	return (found && (data[i] == '\0' || data[i] == '\n'));
}

t_piece				*parse(char *file)
{
	int			fd;
	int			last_bytes_read;
	int			bytes_read;
	char		*buffer;
	t_piece		*pieces;

	pieces = NULL;
	last_bytes_read = -1;
	fd = open(file, O_RDONLY);
	if (!(buffer = ft_strnew(BUFF_SIZE)))
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFF_SIZE)) >= BUFF_SIZE - 1)
	{
		last_bytes_read = bytes_read;
		if (!create_piece(buffer, &pieces))
			return (abort_fillit(&buffer, &pieces));
		ft_bzero(buffer, BUFF_SIZE);
	}
	close(fd);
	if (bytes_read != 0 || last_bytes_read != 20)
		return (abort_fillit(&buffer, &pieces));
	pieces = lstrev(pieces);
	free(buffer);
	return (pieces);
}
