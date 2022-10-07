/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midfath <midfath@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:37:10 by midfath           #+#    #+#             */
/*   Updated: 2022/10/05 13:51:24 by midfath          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

int	ft_env(t_list *env)
 {
	while (env)
	{
		if (((t_env *)env->content)->value)
		{
			printf("%s=", ((t_env *)env->content)->title);
			printf("%s\n", ((t_env *)env->content)->value);
		}
		env = env->next;
	}
	return (1);
 }

t_env	*init_lst_env(void)
{
	t_env *new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	return (new);
}

t_env	*env_str(char *str)
{
	t_env	*node;
	int		i;

	i = ft_istrchr(str, '=');
	if (i == -1)
		return (NULL);
	node = init_lst_env();
	if (!node)
		return (NULL);
	node->title = ft_substr(str, 0, i++);
	node->value = ft_substr(str + i, 0, ft_strlen(str + i));
	if (!node->title || !node->value)
	{
		free (node);
		return (NULL);
	}
	return (node);
}

t_list	*env_list(char **env)
{
	int		i;
	t_list	*head;
	t_list	*node;
	t_env	*st_env;
	
	i = 0;
	while (env[i])
	{
		st_env = env_str(env[i]);
		node = ft_lstnew(st_env);
		if (!st_env || !node)
			return (NULL);
		ft_lstadd_back(&head, node);
		i++;
	}
	return (head);
}
