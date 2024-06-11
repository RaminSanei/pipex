/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssanei <ssanei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:09:44 by ssanei            #+#    #+#             */
/*   Updated: 2024/05/31 18:54:08 by ssanei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_file(char *file, int infile_or_outfile)
{
	int	ret;

	if (infile_or_outfile == 0)
		ret = open(file, O_RDONLY, 0777);
	if (infile_or_outfile == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ret == -1)
		exit(0);
	return (ret);
}

void	ft_exit_handler(void)
{
	ft_putendl_fd("correct structure: ./pipex infile cmd0 cmd1 outfile\n", 2);
	exit(0);
}

void	ft_memory_free(char *str[])
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_find_path(char *env[])
{
	int		i;
	char	*envs;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	envs = env[i] + 5;
	return (envs);
}

char	*ft_get_path(char *cmd[], char *env[])
{
	int		i;
	char	*envs;
	char	**paths;
	char	*all_path;
	char	*final_path;

	i = 0;
	envs = ft_find_path(env);
	paths = ft_split(envs, ':');
	while (paths[i])
	{
		all_path = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(all_path, cmd[0]);
		free(all_path);
		if (access(final_path, F_OK | X_OK) == 0)
		{
			ft_memory_free(paths);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	ft_memory_free(paths);
	return (cmd[0]);
}
