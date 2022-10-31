/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:29:26 by midfath           #+#    #+#             */
/*   Updated: 2022/10/31 17:23:36 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	ft_wait_cmd(void)
{
	int	flag;
	int	exit_flag;

	flag = 1;
	exit_flag = 0;
	while (flag != -1)
	{
		flag = waitpid(-1, &exit_flag, 0);
		if (flag == g_glob.last_pid)
		{
			if (WIFSIGNALED(exit_flag))
			{
				g_glob.exit_status = WTERMSIG(exit_flag) + 128;
				if (WTERMSIG(exit_flag) == SIGINT)
					write(1, "\n", 1);
				else if (WTERMSIG(exit_flag) == SIGQUIT)
					write(1, "Quit :3\n", 8);
			}
			else
				g_glob.exit_status = WEXITSTATUS(exit_flag);
		}
	}
}

char	**env_lst_to_matrix(t_list *lst)
{
	int		size;
	char	**env;
	char	*tmp;
	char	*buff;
	t_list	*env_list;

	tmp = NULL;
	env_list = lst;
	size = ft_lstsize(env_list);
	env = malloc((sizeof(char *) * (size + 1)));
	size = 0;
	while (env_list)
	{
		buff = ft_strdup(((t_env *)env_list->content)->value);
		tmp = ft_strjoin("=", buff);
		env[size] = ft_strjoin(((t_env *)env_list->content)->title, tmp);
		free(tmp);
		free(buff);
		if (!(env[size]))
			ft_arrfreey();
		size++;
		env_list = env_list->next;
	}
	env[size] = NULL;
	return (env);
}

void	ft_reset_g_glob(void)
{
	ft_lstclear(&g_glob.envx, free);
	g_glob.envx = NULL;
	ft_arrfreey();
	g_glob.env = NULL;
	exit (g_glob.exit_status);
}
