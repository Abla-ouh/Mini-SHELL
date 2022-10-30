/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:55:45 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/30 10:08:09 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_buff;

	new_buff = (void *)malloc(new_size);
	if (!new_buff)
		return (NULL);
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr != NULL)
	{
		ft_memmove(new_buff, ptr, old_size);
		free(ptr);
	}
	return (new_buff);
}
