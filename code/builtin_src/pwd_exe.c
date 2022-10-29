/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:03:28 by midfath           #+#    #+#             */
/*   Updated: 2022/10/29 19:30:58 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>
#include <readline/readline.h>
#include <readline/history.h>

static	char	*key_get(int i, char **key)
{
	if (i == 0)
		*key = ft_strdup("PWD");
	else if (i == 1)
		*key = ft_strdup("SHLVL");
	else if (i == 2)
		*key = ft_strdup("_");
	else
		*key = NULL;
	return (*key);
}

char	**ft_empty_env(char **env)
{
	int		i;
	char	*tmp;
	char	*key;

	i = 0;
	tmp = NULL;
	key = NULL;
	if (!env || !env[0])
	{
		env = malloc(sizeof(char *) * 4);
		while (env[i] && key_get(i, &key))
		{
			if (i == 0)
				tmp = ft_strjoin("=", getcwd(NULL, 0));
			else if (i == 1)
				tmp = ft_strjoin("=", "1");
			else if (i == 2)
				tmp = ft_strjoin("=", "bin/minishell");
			env[i] = ft_strjoin(key, tmp);
			i++;
		}
		env[i] = NULL;
	}
	return (env);
}

int	ft_pwd(char **ar)
{
	char	*cwd;

	(void)ar;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = return_value("PWD");
		ft_putstr(cwd);
		ft_putstr("\n");
		return (0);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_glob.sig_c = 1;
		close(STDIN_FILENO);
	}
}
