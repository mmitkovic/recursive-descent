/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:06:10 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/03 12:39:16 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# ifdef DEBUG_TRACE
# include <stdio.h>
static int g_depth = 0;
#  define INDENT() do { for (int _i=0; _i<g_depth; _i++) printf("  "); } while(0)
#  define ENTER(tag) do { INDENT(); printf("→ %s\n", tag); g_depth++; } while(0)
#  define LEAVE(tag, val) do { g_depth--; INDENT(); printf("← %s = %lld\n", tag, (long long)(val)); } while(0)
# else
#  define ENTER(tag)      do {} while(0)
#  define LEAVE(tag, val) do {} while(0)
# endif
#endif
