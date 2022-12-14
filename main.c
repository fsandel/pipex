/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:32:58 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/14 20:25:52 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **env)
{
	int		first_fd;

	input_test(argc, argv);
	if (!ft_strncmp(argv[1], "here_doc", 9))
		first_fd = here_doc(argv);
	else
		first_fd = open(argv[1], O_RDONLY);
	if (first_fd < 0)
		error_close('F', -1);
	pipex(argc, argv, first_fd, env);
	return (0);
}

int	here_doc(char *argv[])
{
	int		fd[2];
	char	*temp;
	char	*limiter;

	if (pipe(fd) < 0)
		error_close('t', -1);
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

void	pipex(int argc, char *argv[], int fd, char **env)
{
	char	*output;
	int		out_fd;
	int		i;
	int		bonus;

	if (!ft_strncmp(argv[1], "here_doc", 9))
		bonus = 1;
	else
		bonus = 0;
	i = 2 + bonus;
	while (i < argc - 1)
	{
		fd = execute_child(fd, argv[i++], env);
		if (fd < 0)
			error_close('e', fd);
	}
	waitpid(0, NULL, 0);
	output = read_file(fd);
	out_fd = create_output_file(argc, argv, bonus);
	if (output)
		ft_putstr_fd(output, out_fd);
	free(output);
	close(fd);
}

int	create_output_file(int argc, char *argv[], int bonus)
{
	int	out_fd;

	if (bonus)
		out_fd = open(argv[argc - 1],
				O_WRONLY | O_APPEND | O_CREAT , 00644);
	else
		out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	return (out_fd);
}

int	execute_child(int infd, char *cmd, char **env)
{
	int			fd[2];
	pid_t		pid;
	char *const	args[4] = {SHELL_PATH, "-c", cmd, NULL};

	if (pipe(fd))
		error_close('p', infd);
	pid = fork();
	if (pid < 0)
		error_close('f', infd);
	else if (pid == 0)
	{
		dup2(fd[1], STDOUT);
		dup2(infd, STDIN);
		close(fd[0]);
		close(fd[1]);
		close(infd);
		execve(SHELL_PATH, args, env);
		return (-1);
	}
	close(fd[1]);
	close(infd);
	return (fd[0]);
}
