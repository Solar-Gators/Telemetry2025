#ifndef USER_HPP
#define USER_HPP

#include "globals.h"

#include <stdint.h>
#include <stdio.h>

void user_loop_cpp();

#ifdef __cplusplus
extern "C"
{
#endif
void user_loop_c();
#ifdef __cplusplus
}
#endif

#endif // USER_HPP
