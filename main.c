/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:32:58 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/09 20:20:48 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	int		first_fd;
	int		bonus;

	input_test(argc, argv);
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		bonus = 2;
		first_fd = here_doc(argc, argv);
		ft_printf("first_fd: %d", first_fd);
	}
	else
	{
		bonus = 0;
		first_fd = open(argv[1], O_RDONLY);
	}
	pipex(argc, argv, first_fd, bonus);
	waitpid(0, NULL, 0);
	unlink("tmp.txt");
	return (0);
}

int	here_doc(int argc, char *argv[])
{
	int		fd;
	char	*temp;
	if (!access("tmp.txt", F_OK))
		unlink("tmp.txt");
	fd = open("tmp.txt", O_CREAT | O_WRONLY | O_EXCL);
	if (fd < 0)
		error_close('t', -1);
	temp = get_next_line(0);
	write(fd, temp, ft_strlen(temp));
	return (fd);
}

void	pipex(int argc, char *argv[], int old_fd, int bonus)
{
	char	*output;
	int		out_fd;
	int		i;
	int		new_fd;

	i = 2 + bonus;
	while (i < argc - 1)
	{
		new_fd = execute_child(old_fd, argv[i++]);
		close(old_fd);
		old_fd = new_fd;
	}
	output = read_file(new_fd);
	out_fd = open(argv[argc - 1], O_WRONLY);
	write(out_fd, output, ft_strlen(output));
	free(output);
	close(out_fd);
	close(new_fd);
}

int	execute_child(int infd, char *cmd)
{
	int			fd[2];
	pid_t		pid;
	char *const	env[1] = {NULL};
	char *const	args[4] = {SHELL_PATH, "-c", cmd, NULL};

	if (pipe(fd))
		error_close('p', infd);
	pid = fork();
	if (pid < 0)
		error_close('f', infd);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		close(0);
		dup2(infd, 0);
		close(fd[1]);
		if (execve(SHELL_PATH, args, env))
			error_close('e', infd);
	}
	close(fd[1]);
	return (fd[0]);
}
