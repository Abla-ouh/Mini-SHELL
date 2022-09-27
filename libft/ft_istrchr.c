/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:35:17 by midfath           #+#    #+#             */
/*   Updated: 2022/09/25 18:35:27 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_istrchr(const char *str, char c)
{
	int index;

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
