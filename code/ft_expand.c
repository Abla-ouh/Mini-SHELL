/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:14:20 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/28 13:19:26 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_find_name(char *arg)
{
	int	name_len;

	name_len = 1;
	if (ft_isdigit(arg[1]))
		return (ft_substr(arg, 0, 2));
	while (ft_isalnum(arg[name_len]) || arg[name_len] == '_')
		name_len++;
	if (name_len == 1 && arg[name_len] == '?')
		name_len++;
	if (name_len == 1)
		return (NULL);
	return (ft_substr(arg, 0, name_len));
}

int	replace_arg(char **arg, int i, char *name)
{
	char	*temp;
	char	*var_value;
	int		name_len;

	//glob.exit_status = 1;
	if (!name)
		return (1);
	if (!ft_strncmp(name, "$?", 2))
		var_value = ft_itoa(glob.exit_status);
	else
		var_value = return_value(name + 1);
	temp = *arg;
	*arg = ft_find_replace(*arg, i, name, var_value);
	if (!var_value)
		name_len = 0;
	else
		name_len = ft_strlen(var_value);
	free(temp);
	free(var_value);
	return (name_len);
}

char	*expand(char *arg)
{
	int		i;
	char	*name;
	char	quote;

	i = 0;
	quote = '\0';
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			if (quote == '\0')
				quote = arg[i];
			else if (quote == arg[i])
				quote = '\0';
		}
		if (arg[i] != '$' || quote == '\'')
			i++;
		else
		{
			name = ft_find_name(&arg[i]);
			i += replace_arg(&arg, i, name);
		}
	}
	return (arg);
}
