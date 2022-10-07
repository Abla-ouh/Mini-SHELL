/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:05:12 by midfath           #+#    #+#             */
/*   Updated: 2022/10/07 11:22:14 by midfath          ###   ########.fr       */
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
// int main (int ac , char **av, char **en)
// {
// 	char **f;
// 	t_list *env;
// 	(void)av;
// 	(void)ac;
// 	env = env_list(en);
// 	f = find_title(env, "PWD");
// 	if ((*f))
// 		printf("%s\n", *f);
// }