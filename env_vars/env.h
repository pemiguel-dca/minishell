/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemiguel <pemiguel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:21:12 by pemiguel          #+#    #+#             */
/*   Updated: 2023/03/19 14:25:13 by pemiguel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "../globals.h"
#include "../vector.h"

/*Puts environment variables in a vector*/
t_vec	create_envs(char **envp);

#endif
