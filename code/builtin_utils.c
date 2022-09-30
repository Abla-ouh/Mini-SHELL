/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:05:12 by midfath           #+#    #+#             */
/*   Updated: 2022/09/29 19:18:40 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

char **find_title(t_list *env, char *title)
{
	while (env)
	{
		if (((t_env *)env->content)->title)
		{
			if (!ft_strcmp(((t_env *)env->content)->title, title))
				return (&((t_env *)env->content)->value);
		}
		env = env->next;
	}
	return (NULL);
}
