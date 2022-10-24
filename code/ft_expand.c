/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:14:20 by abouhaga          #+#    #+#             */
/*   Updated: 2022/10/22 13:31:09 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_find_name(char *arg)
{
	int name_len;

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

int	replace_arg(char **arg, int i, char *name)
{
	char	*temp;
	char	*var_value;
	char	*store;
	
	store = return_value(name);
	// printf("%s", name);
	// printf("%s", store);
	// exit (0);
	if (!name)
		return (1);
	if (!ft_strncmp(name, "$?", 2))
		var_value = ft_itoa(glob.exit_status);
	else
		var_value = return_value(name + 1);
	temp = *arg;
	*arg = ft_find_replace(*arg, i, name, var_value);
	free(temp);
	free(var_value);
	return (ft_strlen(name));
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

// char	*expand(char *arg, t_list *env)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*tmp3;
// 	char	*name;
// 	char	**value;

// 	i = 0;
// 	tmp = NULL;
// 	tmp2 = NULL;
// 	tmp3 = NULL;
// 	name = NULL;
// 	while (arg[i])
// 	{
// 		if (arg[i] == '$')
// 		{
// 			while (arg[i] == '$')
// 				i++;
// 			i--;
// 			tmp = ft_substr(arg, 0, i);
// 			name = ft_find_name(arg + i + 1);
// 			tmp2 = ft_substr(arg, i + 1 + ft_strlen(name), ft_strlen(arg));
// 			value = find_title(glob.envx, name);
// 			free(arg);
// 			if (value == NULL)
// 				arg = ft_strjoin(tmp, tmp2);
// 			else
// 			{
// 				tmp3 = ft_strjoin(tmp, *value);
// 				arg = ft_strjoin(tmp3, tmp2);
// 				i += ft_strlen(*value);
// 				// free(*value);
// 			}
// 			free(tmp);
// 			free(name);
// 			free(tmp2);
// 			free(tmp3);
// 		}
// 		else
// 			i++;
// 	}
// 	return (arg);
// }