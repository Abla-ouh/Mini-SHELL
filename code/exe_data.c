/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:45:26 by midfath           #+#    #+#             */
/*   Updated: 2022/10/30 15:03:56 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	g_glob_init(char **env)
{
	g_glob.infd = dup(0);
	g_glob.outfd = dup(1);
	g_glob.sig_c = 0;
	g_glob.env = NULL;
	g_glob.exit_status = 0;
	g_glob.envx = env_list(env);
	g_glob.perv_fd = 0;
}

void	ft_arrfreey(void)
{
	int	i;

	i = 0;
	while (g_glob.env && g_glob.env[i])
	{
		free(g_glob.env[i]);
		i++;
	}
	free(g_glob.env);
	g_glob.env = NULL;
}

int	ft_isbuiltin(t_cmds *shel_l)
{
	if (!shel_l || !shel_l->is_exec || shel_l->in < 0 || \
	shel_l->out < 0 || !shel_l->args[0])
		return (0);
	if (!ft_strcmp(shel_l->args[0], "cd"))
		return (1);
	else if ((!ft_strcmp(shel_l->args[0], "exit")))
		return (2);
	else if ((!ft_strcmp(shel_l->args[0], "export")))
		return (3);
	else if ((!ft_strcmp(shel_l->args[0], "echo")))
		return (4);
	else if ((!ft_strcmp(shel_l->args[0], "unset")))
		return (5);
	else if ((!ft_strcmp(shel_l->args[0], "env")))
		return (6);
	else if ((!ft_strcmp(shel_l->args[0], "pwd")))
		return (7);
	return (0);
}

int	run_builtin(t_cmds *shel_l, int flag)
{
	if (flag == 1)
		return (ft_cd(shel_l->args));
	else if (flag == 2)
		return (ft_exit(shel_l->args));
	else if (flag == 3)
		return (ft_export(shel_l->args));
	else if (flag == 4)
		return (ft_echo(shel_l->args));
	else if (flag == 5)
		return (ft_unset(shel_l->args));
	else if (flag == 6)
		return (ft_env(shel_l->args, g_glob.envx));
	else if (flag == 7)
		return (ft_pwd(shel_l->args));
	return (0);
}

char	*return_value(char *title)
{
	t_list	*tmp;

	tmp = g_glob.envx;
	while (tmp)
	{
		if (((t_env *)tmp->content)->title)
		{
			if (!ft_strcmp(((t_env *)tmp->content)->title, title))
			{
				return (ft_strdup(((t_env *)tmp->content)->value));
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}
