/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:20:52 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/14 20:27:36 by florian          ###   ########.fr       */
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
		error_close('c', -1);
	if (argc < 5)
		error_close('c', -1);
	if (access(argv[1], R_OK) && ft_strncmp(argv[1], "here_doc", 9))
		error_close('i', -1);
	if (!ft_strncmp(argv[1], "here_doc", 9) && argc < 6)
		error_close('b', -1);
}

void	error_close(char c, int fd)
{
	if (fd > 0)
		close(fd);
	write(2, "Error\n", 6);
	if (c == 'p')
		perror("piping failed\n");
	else if (c == 'f')
		perror("forking failed\n");
	else if (c == 'c')
		perror("wrong amount of arguments\n");
	else if (c == 'i')
		perror("no access to infile");
	else if (c == 'o')
		perror("no access to outfile");
	else if (c == 'e')
		perror("execute failed");
	else if (c == 'b')
		perror("not enough arguments for bonus");
	else if (c == 't')
		perror("couldnt create tmp file");
	else if (c == 'F')
		perror("open of input failed");
	else
		perror("random error");
	exit(1);
}
