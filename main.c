/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:43:16 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/26 21:14:52 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	error(void)
{
	ft_putstr("error\n");
	return (1);
}

int	main(int ac, char *av[])
{
	t_map	*map;
	t_piece	*pieces;

	if (ac == 2)
	{
		if ((pieces = parse(av[1])) != NULL)
		{
			if ((map = fillit(pieces)))
			{
				print_map(map);
				free_map(map);
				abort_fillit(NULL, &pieces);
			}
			else
				return (error());
		}
		else
			return (error());
	}
	else
		ft_putstr("usage: ./fillit file\n");
	return (ac != 2);
}
