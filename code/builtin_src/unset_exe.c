/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:06:47 by midfath           #+#    #+#             */
/*   Updated: 2022/10/30 14:15:18 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exe.h>

static int	env_del(char *ar)
{
	t_list	**tmp;
	t_list	*node;

	tmp = &g_glob.envx;
	while (*tmp)
	{
		if (!(ft_strcmp(ar, ((t_env *)(*tmp)->content)->title)))
		{
			node = *tmp;
			free(node->content);
			*tmp = (*tmp)->next;
			return (0);
		}
		tmp = &(*tmp)->next;
	}
	return (1);
}

int	check_ar(char *ar)
{
	int	i;

	i = 0;
	if (!ft_isalpha(ar[0]) && !(ar[0] == '_'))
		return (0);
	while ((ar[i] && ft_isalpha(ar[i])) \
		|| ft_isdigit(ar[i]) || ar[i] == '_')
		i++;
	return (!ar[i]);
}

int	ft_unset(char **ar)
{
	int	err;
	int	i;

	i = 1;
	err = 0;
	while (ar[i])
	{
		if (check_ar(ar[i]))
			env_del(ar[i]);
		else
		{
			err = 1;
			ft_perror(NULL, ar[i], "not a valid identifier");
		}
		i++;
	}
	return (err);
}
