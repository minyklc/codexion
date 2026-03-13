/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuizu <msuizu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:00:42 by msuizu            #+#    #+#             */
/*   Updated: 2026/03/13 10:00:43 by msuizu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

char	*need_args(void)
{
	return ("./a.out {nb_coders} {burnout_time} {compile_time}"
			" {debug_time} {refactor_time} {minimum_compile_nb}"
			" {dongle_cooldown} {scheduler}\n");
}
