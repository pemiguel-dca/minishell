/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:21:12 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/21 15:49:27 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "../globals.h"
#include "../vector.h"

/*Puts environment variables in a vector*/
t_vec	create_envs(char **envp);

/*Returns position of 'find' in vec or -1 'find' isn't in vector*/
int		pos_env_var(t_vec *env, char *find);

/*Sets a new value to env name*/
void	set_env(t_vec **env, char *name, char *value);

#endif
