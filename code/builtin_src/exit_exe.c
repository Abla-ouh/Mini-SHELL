/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:46:46 by midfath           #+#    #+#             */
/*   Updated: 2022/10/10 18:24:19 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_exit(char **ar)
{
//	unsigned int	signe;
	
	if (!ar[1])
		exit(glob.exit_status);
	return(0);
//	signe	 = ft_atoui();
}