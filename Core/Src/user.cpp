#include "user.hpp"
#include "notecard.hpp"
#include "RFD900x.hpp"
#include "main.h"

// Main C++ loop
void user_loop_cpp()
{
	RFD900x rfd900x(&huart1);
	Notecard notecard(&huart2);

	while(1) {
		HAL_GPIO_TogglePin(OK_LED_GPIO_Port, OK_LED_Pin);
		HAL_Delay(1000);
	}
}

extern "C"
{
    void user_loop_c()
    {
        user_loop_cpp();
    }
}
