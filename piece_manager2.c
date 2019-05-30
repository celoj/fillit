/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_manager2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:14:12 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/26 21:15:31 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_piece		*ft_lstrev(t_piece *previous_node, t_piece *current_node)
{
	t_piece *t;

	t = current_node;
	if (current_node->next)
		t = ft_lstrev(current_node, current_node->next);
	current_node->next = previous_node;
	return (t);
}

t_piece				*lstrev(t_piece *pieces)
{
	return (ft_lstrev(NULL, pieces));
}
