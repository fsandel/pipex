/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:20:52 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/16 10:46:07 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	input_test(int argc, char *argv[])
{
	if (argc < 5)
		error_exit("not enough arguments", 0, -1);
	if (access(argv[1], R_OK) && ft_strncmp(argv[1], "here_doc", 9))
	{
		perror("pipex: input");
		return ;
	}
	if (access(argv[argc - 1], W_OK) == -1 && access(argv[argc - 1]
			, F_OK) == 0 && ft_strncmp(argv[1], "here_doc", 9))
	{
		perror("pipex: output");
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

int	here_doc(char *argv[])
{
	int		fd[2];
	char	*temp;
	char	*limiter;

	if (pipe(fd) < 0)
		error_exit("piping failed", 0, -1);
	limiter = ft_strjoin(argv[2], "\n");
	while (1)
	{
		temp = get_next_line(STDIN);
		if (temp == NULL)
			break ;
		if (!ft_strncmp(temp, limiter, ft_strlen(limiter)))
			break ;
		ft_putstr_fd(temp, fd[1]);
		free(temp);
	}
	free(limiter);
	free(temp);
	close(fd[1]);
	return (fd[0]);
}
