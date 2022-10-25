/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:45:26 by midfath           #+#    #+#             */
/*   Updated: 2022/10/25 17:34:10 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	glob_init(char **env)
{
	glob.sig_c = 0;
	glob.env = NULL;
	glob.exit_status = 0;
	glob.envx = env_list(env);
	glob.perv_fd = 0;
}

void	ft_arrfreey()
{
	int	i;

	i = 0;
	while (glob.env && glob.env[i])
	{
		free(glob.env[i]);
		i++;
	}
	glob.env = NULL;
}

int	ft_isbuiltin(t_cmds *shel_l)
{
	if (!check_execut(shel_l))
		return(0);
	if (!ft_strcmp(shel_l->args[0] ,"cd"))
		return (1);
	else if ((!ft_strcmp(shel_l->args[0] ,"exit")))
		return (2);
	else if ((!ft_strcmp(shel_l->args[0] ,"export")))
		return (3);
	else if ((!ft_strcmp(shel_l->args[0] ,"echo")))
		return (4);
	else if ((!ft_strcmp(shel_l->args[0] ,"unset")))
		return (5);
	else if ((!ft_strcmp(shel_l->args[0] ,"env")) && \
	shel_l->args[1] == NULL)
		return (6);
	else if ((!ft_strcmp(shel_l->args[0] ,"pwd")))
		return (7);
	else if ((!ft_strcmp(shel_l->args[0] ,"env")) && shel_l->args)
		return (8);
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
	else if (flag == 8)
		return (ft_perror("env", NULL, "too many arguments"));
	else if (flag == 6)
		return (ft_env(shel_l->args ,glob.envx));
	else if (flag == 7)
		return (ft_pwd(shel_l->args));
	return (0);
}

char *return_value(char *title)
{
	t_list	*tmp;

	tmp = glob.envx;
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
