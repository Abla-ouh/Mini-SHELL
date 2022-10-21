/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_n_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 21:25:15 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/20 21:41:43 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * find and replace the first occurence of 'find' in str by 'replace'
 * 
 * @param	str the string to use
 * @param	find the search word
 * @param	replace the word to repleace it with
 * @return	the new string allocated in memory
 */
char	*ft_find_replace(char *str, int start_i, char *find, char *replace)
{
	char	*start;
	char	*end;
	char	*output;

	if (!str || !find)
		return (NULL);
	start = ft_substr(str, 0, start_i);
	end = ft_substr(
			str, start_i + ft_strlen(find),
			ft_strlen(str));
	if (!replace)
		replace = "";
	output = ft_multijoin(3, start, replace, end);
	free(start);
	free(end);
	return (output);
}
