/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 02:18:43 by midfath           #+#    #+#             */
/*   Updated: 2022/05/12 09:29:13 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrdupix(char **mat)
{
	int		i;
	char	**ptr;

	i = 0;
	while (mat && mat[i])
		i++;
	ptr = malloc(sizeof(char *) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (mat[i])
	{
		ptr[i] = ft_strdup(mat[i]);
		if (!mat[i])
		{
			ft_matfreex(&ptr);
			return (NULL);
		}
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
