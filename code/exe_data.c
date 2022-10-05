/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:45:26 by midfath           #+#    #+#             */
/*   Updated: 2022/10/04 15:40:19 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	gdexe_init(t_gexe *exe, char **env)
{
	exe = (t_gexe *)malloc(sizeof(t_gexe));
	ft_memset(exe, 0, sizeof(*exe));
	exe->id = getpid();
	//exe->env = env_list(env);
	exe->p_cwd = getcwd(NULL, 0);
	if (!(exe->env) || !(exe->p_cwd))
		return (0);
	(void )env;
	 return (1);
}

void	gdexe_free(t_gexe *exe)
{
	ft_leak((void **)&exe->p_cwd);
	ft_lstclear(&exe->env, free);
}