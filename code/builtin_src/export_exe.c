/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:26:58 by midfath           #+#    #+#             */
/*   Updated: 2022/10/15 11:26:50 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

void	export_var(char *input)
{
	char	**new_var;
	int		len;
	
	new_var = get_var(input);
	len = ft_strlen(new_var[0]);
	if (new_var[0][len - 1] == '+')
	{
		new_var[0][len - 1] = 0;
		var_cat(new_var);
	}
	else
		var_update(new_var);
}

int	vars_check(char *var)
{
	int	i;
	
	i = 0;
	if (!ft_isalpha(var[0]) && !(var[0] == '_'))
		return (0);
	while (var[i] && (ft_isalpha(var[i]) || ft_isdigit(var[i]) \
		|| var[i] == '_') && var[i] != '=' && var[i] != '+')
		i++;
	return ((var[i] == '+' && var[i + 1] == '=') \
		|| !var[i] || var[i] == '=');
}

void	put_export()
{
	t_env *env;
	t_list *tmp;
	
	tmp =glob.envx;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->title, "_"))
		{
			ft_putstr("declare -x ");
			ft_putstr(env->title);
			if (env->value)
			{
				write(1, "=", 1);
				write(1, "\"", 1);
				ft_putstr(env->value);
				write(1, "\"", 1);
			}
			ft_putstr("\n");
		}
		tmp = tmp->next;
	}
}

int	ft_export(char **vars)
{
	int	i;
	int	err;

	err = 0;
	if (!vars[1])
		put_export();
	i = 1;
	while (vars[i])
	{
		if (vars_check(vars[i]))
			export_var(vars[i]);
		else
		{
			err = 1;
			ft_perror("export", vars[i], "not a valid identifier");
		}
		i++;
	}
	return (err);
}
