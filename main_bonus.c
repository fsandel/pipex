/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:32:58 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/16 10:38:39 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char **env)
{
	int	in_out[2];

	input_test(argc, argv);
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		in_out[0] = here_doc(argv);
		in_out[1] = open(argv[argc - 1],
				O_WRONLY | O_APPEND | O_CREAT, 00644);
	}
	else
	{
		in_out[0] = open(argv[1], O_RDONLY);
		in_out[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	}
	pipex(argc, argv, in_out, env);
	waitpid(0, NULL, 0);
	close(in_out[1]);
	return (0);
}

void	pipex(int argc, char *argv[], int in_out[2], char **env)
{
	int		i;
	int		here_doc;

	if (!ft_strncmp(argv[1], "here_doc", 9))
		here_doc = 1;
	else
		here_doc = 0;
	i = 2 + here_doc;
	while (i < argc - 1)
	{
		in_out[0] = execute_child(in_out, argv[i], env, argc - i);
		if (in_out[0] < 0)
			error_exit("execute failed", 127, in_out[0]);
		i++;
	}
	close(in_out[0]);
}

int	execute_child(int in_out[2], char *cmd, char **env, int last)
{
	int			fd[2];
	pid_t		pid;
	char *const	args[4] = {SHELL_PATH, "-c", cmd, NULL};

	if (pipe(fd))
		error_exit("piping failed", 0, in_out[0]);
	pid = fork();
	if (pid < 0)
		error_exit("forking failed", 0, in_out[0]);
	else if (pid == 0)
	{
		dup_all(in_out, last, fd[1]);
		close(fd[0]);
		close(fd[1]);
		close(in_out[0]);
		close(in_out[1]);
		if (in_out[0] < 1)
			exit(1);
		execve(SHELL_PATH, args, env);
		error_exit(cmd, 127, -1);
	}
	close(fd[1]);
	close(in_out[0]);
	return (fd[0]);
}

void	dup_all(int in_out[2], int last, int pipefd)
{
	if (last == 2)
		dup2(in_out[1], STDOUT);
	else
		dup2(pipefd, STDOUT);
	dup2(in_out[0], STDIN);
}
