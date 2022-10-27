/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:35:17 by midfath           #+#    #+#             */
/*   Updated: 2022/10/26 12:31:28 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_istrchr(const char *str, char c)
{
	int	index;

	index = 0;
	if (!str)
		return (-1);
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}
