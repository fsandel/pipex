/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:20:52 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/15 16:15:06 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_free(char *first, char *second)
{
	char	*output;

	if (!first)
	{
		first = ft_calloc(1, 1);
		if (!first)
			return (NULL);
	}
	output = ft_strjoin(first, second);
	free(first);
	return (output);
}

char	*read_file(int fd)
{
	char	*temp;
	char	*long_map;

	temp = get_next_line(fd);
	if (!temp)
		return (NULL);
	long_map = ft_strdup(temp);
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
		if (!temp)
			break ;
		long_map = ft_strjoin_free(long_map, temp);
	}
	return (long_map);
}

void	input_test(int argc, char *argv[])
{
	if ((argc != 5) && (BONUS == 0))
		error_exit("4 arguments needed for mandatory part", 0, -1);
	if (argc < 5)
		error_exit("not enough arguments", 0, -1);
	if (access(argv[1], R_OK) && ft_strncmp(argv[1], "here_doc", 9))
	{
		perror("pipex: input");
		return ;
	}
	if (!ft_strncmp(argv[1], "here_doc", 9) && argc < 6)
		error_exit("not enough arguments for here_doc", 0, -1);
}

void	error_exit(char *str, int exit_code, int fd)
{
	if (fd > 0)
		close(fd);
	perror(str);
	exit(exit_code);
}
