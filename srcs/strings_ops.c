/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdervil <thdervil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:30:12 by derachte          #+#    #+#             */
/*   Updated: 2019/11/05 08:00:22 by thdervil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_size(char **tab)
{
	int i;
	int j;
	int ret;

	i = -1;
	j = -1;
	ret = 0;
	while (tab[++i])
	{
		while (tab[i][++j])
			ret++;
		j = -1;
	}
	ret += i;
	return (ret);
}

char	*create_path(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*buf;

	i = -1;
	j = 0;
	buf = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	while (s1[++i])
		buf[i] = s1[i];
	buf[i++] = '/';
	while (s2[j])
		buf[i++] = s2[j++];
	buf[i] = '\0';
	return (buf);
}

void	create_poss(t_mshell *mshell)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = -1;
	while (mshell->path_env[++i] && mshell->commands[0])
	{
		ret = create_path(mshell->path_env[i], mshell->commands[0]);
		if (!access(ret, X_OK))
		{
			mshell->bin_path = ft_strdup(ret);
			free(ret);
			return ;
		}
		free(ret);
	}
	if (!mshell->bin_path && mshell->is_binary)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(mshell->commands[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return ;
}

char	*ft_splittoone(char **tab)
{
	char	*ret;
	int		i;
	int		j;
	int		pos;

	i = 0;
	j = 0;
	pos = 0;
	ret = (char *)malloc(sizeof(char) * get_size(tab));
	while (tab[i])
	{
		while (tab[i][j])
			ret[pos++] = tab[i][j++];
		j = 0;
		if (tab[i + 1])
			ret[pos++] = ' ';
		i++;
	}
	ret[pos] = '\0';
	return (ret);
}

char	**lst_to_tab(t_envlist *envlist)
{
	t_envlist	*start;
	char		**ret;
	int			i;

	start = envlist;
	ret = NULL;
	i = 0;
	while (envlist)
	{
		i++;
		envlist = envlist->next;
	}
	envlist = start;
	if (!(ret = (char **)malloc(sizeof(char *) * i + 1)))
		return (NULL);
	i = 0;
	while (envlist)
	{
		ret[i++] = ft_strdup(envlist->line);
		envlist = envlist->next;
	}
	ret[i] = NULL;
	envlist = start;
	return (ret);
}
