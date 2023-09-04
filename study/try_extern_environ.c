/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_extern_environ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:56:07 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/21 16:56:29 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

extern char **environ; // Declare the environ variable

int main() {
    // Iterate through the environment variables and print them
    for (int i = 0; environ[i] != NULL; i++) {
        printf("Environment variable %d: %s\n", i, environ[i]);
    }

    return 0;
}
