/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:20:52 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/16 10:47:28 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_test(int argc, char *argv[])
{
	if (argc != 5)
		error_exit("4 arguments needed for mandatory part", 0, -1);
	if (access(argv[1], R_OK))
	{
		perror("pipex: input");
		return ;
	}
	if (access(argv[argc - 1], W_OK) == -1 && access(argv[argc - 1]
			, F_OK) == 0)
	{
		perror("pipex: output");
		return ;
	}
}

void	error_exit(char *str, int exit_code, int fd)
{
	if (fd > 0)
		close(fd);
	perror(str);
	exit(exit_code);
}
