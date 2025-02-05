#include "user.hpp"
#include "notecard.hpp"
#include "RFD900x.hpp"
#include "main.h"

#define START_CHAR 0xFF
#define ESC_CHAR 0x2F
#define END_CHAR 0x3F

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

	uint8_t setup[] = "{\"req\":\"hub.set\",\"product\":\"com.gmail.solargatorstelemetry:test\",\"mode\":\"continuous\"}\n";

	HAL_UART_Transmit(&huart2, setup, sizeof(setup)/sizeof(setup[0]), HAL_MAX_DELAY);

	HAL_Delay(200);


	/*
	char frame_data[] = "{\"req\":\"note.add\",\"body\":{\"CAN_ID\":{\"data\":\"[0xE4,0x3D,0x2A]\",\"len\":3}}}";
	HAL_UART_Transmit(&huart2, (uint8_t*)frame_data, sizeof(frame_data)/sizeof(frame_data[0]), HAL_MAX_DELAY);
	*/

	uint8_t frame_test[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
	char json_packet[100];
	uint8_t packet_len = snprintf(json_packet, sizeof(json_packet), "{\"req\":\"note.add\",\"body\":{\"%u\":{\"data\":\"[%u,%u,%u,%u,%u,%u,%u]\",\"len\":7}}}",
	frame_test[0], frame_test[1], frame_test[2], frame_test[3], frame_test[4], frame_test[5], frame_test[6], frame_test[7]);

	HAL_UART_Transmit(&huart2, (uint8_t*)json_packet, packet_len, HAL_MAX_DELAY);


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
