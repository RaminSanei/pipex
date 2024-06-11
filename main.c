/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:13:42 by ssanei            #+#    #+#             */
/*   Updated: 2024/06/11 12:42:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void exec(char *arg, char *env[])
{
	char **cmd;
	char *path;

	cmd = ft_split(arg, ' ');
	path = ft_get_path(cmd, env);
	if (!path)
	{
		ft_memory_free(cmd);
		free(path);
		exit(127);
	}
	if (execve(path, cmd, env) == -1)
	{
		ft_memory_free(cmd);
		free(path);
		error();
		ft_putendl_fd("pipex: there is not such a command", 2);
		// ft_putchar_fd('\n', 2);
		// exit(0);
	}
}

static void child_process(int fd[], char *argv[], char *env[], int p_fd)
{
	dup2(p_fd, 0);
	dup2(fd[1], 1);
	close(p_fd);
	close(fd[0]);
	close(fd[1]);
	exec(argv[2], env);
}

static void parent_process(int fd[], char *argv[], char *env[], int p_fd)
{
	dup2(p_fd, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	exec(argv[3], env);
}

int main(int argc, char *argv[], char *env[])
{
	int outfile;
	int infile;
	int pid;
	int fd[2];

	if (argc != 5)
		ft_exit_handler();
	infile = ft_open_file(argv[1], 0);
	outfile = ft_open_file(argv[4], 1);
	if (infile < 0 || outfile < 0)
		return (-1);
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		child_process(fd, argv, env, infile);
	waitpid(pid, NULL, 0);
	parent_process(fd, argv, env, outfile);
	return (0);
}
