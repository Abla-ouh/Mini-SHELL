/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:03:28 by midfath           #+#    #+#             */
/*   Updated: 2022/10/25 17:30:20 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>
# include <readline/readline.h>
# include <readline/history.h>

int	ft_pwd(char **ar)
{
	char *cwd;
	
	(void)ar;
	cwd =  getcwd(NULL, 0);
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
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		glob.exit_status = 1;
	}
}