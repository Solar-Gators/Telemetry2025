#include "user.hpp"
#include "notecard.hpp"
#include "RFD900x.hpp"
#include "main.h"

// Main C++ loop
void user_loop_cpp()
{
	RFD900x rfd900x(&huart1);
	Notecard notecard(&huart2);

	// Create a test CAN frame
	uint8_t data[] = {0x19, 0x39, 0x5, 0x19};
	TESTFrame frame;
	frame.can_id = 0x000045E2;
	memcpy(frame.data, data, sizeof(data));
	frame.len = 4;

	// Must give notecard time to setup
	HAL_Delay(4000);

	// Setup connection to Notehub
	uint8_t setup[] = "{\"req\":\"hub.set\",\"product\":\"edu.ufl.nathan.achinger:flare_telemetry\",\"mode\":\"continuous\"}\n";
	HAL_UART_Transmit(&huart2, setup, sizeof(setup)/sizeof(setup[0]), HAL_MAX_DELAY);

	HAL_Delay(200);

	char frame_data[] = "{\"req\":\"note.add\",\"body\":{\"CAN_ID\":{\"data\":\"[0xE4,0x3D,0x2A]\",\"len\":3}}}";
	HAL_UART_Transmit(&huart2, frame_data, sizeof(frame_data)/sizeof(frame_data[0]), HAL_MAX_DELAY);

	/*
	{
	  "req": "note.add",
	  "body": {
		"CAN_ID": {
		  "data": [0xE4, 0x3D, 0x2A],
		  "len": 3
		}
	  }
	}
	*/


	//uint8_t rx_buff[50];
	//HAL_UART_Receive(&huart2, rx_buff, 5, 1000);

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
