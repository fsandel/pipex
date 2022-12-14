/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:33:20 by fsandel           #+#    #+#             */
/*   Updated: 2022/12/14 20:26:23 by florian          ###   ########.fr       */
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

char	*ft_strjoin_free(char *first, char *second);
char	*read_file(int fd);
void	input_test(int argc, char *argv[]);
void	error_close(char c, int fd);

int		execute_child(int infd, char *cmd, char **env);
void	pipex(int argc, char *argv[], int old_fd, char **env);
int		here_doc(char *argv[]);
int		create_output_file(int argc, char *argv[], int bonus);

#endif
