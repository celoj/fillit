/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:36:07 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/03 11:55:18 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	char	t;
	size_t	i;
	size_t	j;

	i = -1;
	j = ft_strlen(s);
	while (++i < --j)
	{
		t = s[i];
		s[i] = s[j];
		s[j] = t;
	}
	return (s);
}
