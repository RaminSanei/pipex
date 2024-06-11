/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:18:54 by ssanei            #+#    #+#             */
/*   Updated: 2024/06/10 19:08:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

void	ft_exit_handler(void);
int		ft_open_file(char *file, int infile_or_outfile);
void	ft_memory_free(char *str[]);
char	*ft_find_path(char *env[]);
char	*ft_get_path(char *cmd[], char *env[]);
void	error(void);

#endif