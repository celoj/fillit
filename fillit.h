/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 19:07:52 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/26 21:18:15 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 21

typedef struct		s_base
{
	int				x;
	int				y;
}					t_base;

typedef struct		s_piece
{
	int				ordinal;
	char			**piece;
	struct s_piece	*next;
	int				height;
	int				width;
}					t_piece;

typedef struct		s_map
{
	char			**map;
	int				n;
}					t_map;

t_piece				*parse(char *file);
t_map				*fillit(t_piece *pieces);
char				**make_piece(int height, int width);
t_piece				*abort_fillit(char **buffer, t_piece **pieces);
int					calc_best_size(t_piece *pieces);
t_map				*gen_map(int n);
void				free_map(t_map *map);
void				print_map(t_map *map);
t_piece				*lstrev(t_piece *pieces);
void				update_component(char *data, t_piece *piece,
						int i, t_base *piece_pos);

#endif
