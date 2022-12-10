/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:32:58 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/10 12:06:23 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	int		first_fd;
	int		bonus;

	input_test(argc, argv);
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		bonus = 2;
		here_doc(argc, argv);
		first_fd = open(TEMP_FILE, O_RDONLY);
	}
	else
	{
		bonus = 0;
		first_fd = open(argv[1], O_RDONLY);
	}
	pipex(argc, argv, first_fd, bonus);
	unlink(TEMP_FILE);
	return (0);
}

void	here_doc(int argc, char *argv[])
{
	int		fd;
	char	*temp;

	if (!access(TEMP_FILE, F_OK))
		unlink(TEMP_FILE);
	close(open(TEMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR));
	fd = open(TEMP_FILE, O_WRONLY);
	if (fd < 0)
		error_close('t', -1);
	while (1)
	{
		temp = get_next_line(0);
		if (!ft_strncmp(temp, argv[2], ft_strlen(argv[2])))
		{
			free(temp);
			break ;
		}	
		ft_putstr_fd(temp, fd);
		free(temp);
	}
	close(fd);
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
	waitpid(0, NULL, 0);
	output = read_file(new_fd);
	out_fd = open(argv[argc - 1], O_WRONLY);
	if (output)
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
	int			debug;

	if (pipe(fd))
		error_close('p', infd);
	pid = fork();
	if (pid < 0)
		error_close('f', infd);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		dup2(infd, STDIN);
		close(fd[1]);
		close(infd);
		execve(SHELL_PATH, args, env);
	}
	else
	{
		close(fd[1]);
		return (fd[0]);
	}
}
