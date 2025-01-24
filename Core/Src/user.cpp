#include "user.hpp"
#include "notecard.hpp"
#include "RFD900x.hpp"
#include "main.h"

// Main C++ loop
void user_loop_cpp()
{
	RFD900x rfd900x(&huart1);
	Notecard notecard(&huart2);

	HAL_Delay(4000); // Must give notecard time to setup

	uint8_t setup[] = "{\"req\":\"hub.set\",\"product\":\"edu.ufl.nathan.achinger:flare_telemetry\",\"mode\":\"continuous\"}\n";
	HAL_UART_Transmit(&huart2, setup, sizeof(setup)/sizeof(setup[0]), HAL_MAX_DELAY);

	HAL_Delay(200);

	//uint8_t packet[] = "{\"req\":\"card.status\"}";
	uint8_t packet[] = "{\"req\":\"note.add\",\"body\":{\"param1\":200,\"param2\":400}}\n";
	HAL_UART_Transmit(&huart2, packet, sizeof(packet)/sizeof(packet[0]), HAL_MAX_DELAY);

	uint8_t rx_buff[50];
	HAL_UART_Receive(&huart2, rx_buff, 5, 1000);

	HAL_Delay(500);

	while(1) {
		HAL_GPIO_TogglePin(OK_LED_GPIO_Port, OK_LED_Pin);
		HAL_Delay(500);
	}
}

extern "C"
{
    void user_loop_c()
    {
        user_loop_cpp();
    }
}
