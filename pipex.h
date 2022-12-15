/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:33:20 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/15 20:21:23 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

# define SHELL_PATH "/bin/bash"

# define STDIN 0
# define STDOUT 1

# ifndef BONUS
#  define BONUS 0
# endif

void	input_test(int argc, char *argv[]);
void	error_exit(char *str, int exit_code, int fd);
void	dup_all(int in_out[2], int last, int pipefd);
int		here_doc(char *argv[]);

int		execute_child(int in_out[2], char *cmd, char **env, int last);
void	pipex(int argc, char *argv[], int in_out[2], char **env);
int		create_output_file(int argc, char *argv[], int here_doc);

#endif
