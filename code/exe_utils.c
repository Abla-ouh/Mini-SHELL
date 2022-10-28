/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:29:26 by midfath           #+#    #+#             */
/*   Updated: 2022/10/28 15:11:13 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	ft_wait_cmd(pid_t pid)
{
	waitpid(pid, &g_glob.exit_status, 0);
	(void)pid;
	while (wait(&g_glob.exit_status) != -1)
		;
	g_glob.exit_status = WEXITSTATUS(g_glob.exit_status);
	g_glob.exit_status += 128;
}

char	**env_lst_to_matrix(t_list *lst)
{
	int		size;
	char	**env;
	char	*tmp;
	t_list	*env_list;

	tmp = NULL;
	env_list = lst;
	size = ft_lstsize(env_list);
	env = malloc((sizeof(char *) * (size + 1)));
	size = 0;
	while (env_list)
	{
		tmp = ft_strjoin("=", ((t_env *)env_list->content)->value);
		env[size] = ft_strjoin(((t_env *)env_list->content)->title, tmp);
		free(tmp);
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
	ft_lstclear(&g_glob.envx, ft_delenv);
	g_glob.envx = NULL;
	ft_arrfreey();
	g_glob.env = NULL;
}

int	check_exe(t_cmds *shel_l)
{
	if (!shel_l || !shel_l->is_exec)
		return (0);
	return (1);
}

void	ft_delenv(void *env)
{
	free(((t_env *)env)->title);
	free(((t_env *)env)->value);
	free((t_env *)env);
}
