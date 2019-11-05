/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:00:14 by derachte          #+#    #+#             */
/*   Updated: 2019/11/03 13:38:17 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_var(char *s1, char *s2)
{
	int 	i;
	int 	j;
	char	*ret;

	i = 0;
	j = 0;
	ret = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i++] = '=';
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

char	*var_namecut(t_envlist *env_list)
{
	int		i;
	char	*ret;

	i = 0;
	while (env_list->line[i] != '=')
		i++;
	ret = ft_strndup(env_list->line, i - 1);
	return (ret);
}
