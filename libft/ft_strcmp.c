/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:55:49 by abouhaga          #+#    #+#             */
/*   Updated: 2022/07/05 20:55:50 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && (unsigned char)s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
