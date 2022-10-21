/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:29:26 by midfath           #+#    #+#             */
/*   Updated: 2022/10/20 16:58:59 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	ft_wait_cmd(pid_t pid)
{
	//
	// waitpid(pid, &glob.exit_status, 0);
	// if (glob.exit_status != 2 && glob.exit_status != 3)
	// else
	(void)pid;
	while (wait(&glob.exit_status) != -1)
		;
	glob.exit_status = WEXITSTATUS(glob.exit_status);
	glob.exit_status += 128;
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
	env = (char **)malloc((sizeof(char *) * size) + 1);
	size = 0;
	while (env_list)
	{
		tmp = ft_strjoin("=", ((t_env *)env_list->content)->value);
		env[size] = ft_strjoin(((t_env *)env_list->content)->title, tmp);
		free(tmp);
		size++;
		env_list = env_list->next;
	}
	env[size] = NULL;
	return (env);
}

void	ft_reset_glob(void)
{
	ft_lstclear(&glob.envx, ft_delenv);
	glob.envx = NULL;
	ft_arrfreey();
	glob.env = NULL;
}

int	check_execut(t_cmds *shel_l)
{
	if (!(shel_l->is_exec && shel_l->in >= 0 && shel_l->out >= 1))
		return (0);
	else if (shel_l->path == NULL)
		return (0);
	else
		return (1);
}

void	ft_delenv(void *env)
{
	free(((t_env *)env)->title);
	free(((t_env *)env)->value);
	free((t_env *)env);
}