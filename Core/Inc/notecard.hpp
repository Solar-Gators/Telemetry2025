#ifndef NOTECARD_HPP
#define NOTECARD_HPP

/*
EXAMPLE USE CASE

Notecard.SendCommand(NOTECARD_INIT);

void periodic_task() {
    Notecard.LoadFrame(MitsubaFrame0::Instance());
    Notecard.LoadFrame(MitsubaFrame1::Instance());
    Notecard.LoadFrame(MitsubaFrame2::Instance());
    ...
    Notecard.LoadFrame(MPPTInputMeasurementsFrame1::Instance());

    Notecard.SendCommand(NOTECARD_SYNC);
}
*/

/*
EXAMPLE JSON FORMAT

body {
    0xCAN_ID1 {
        frame_len : 6,
        data : [0x2F, 0x12, ..., 0x01]
    }
    0xCAN_ID2 {
        frame_len : 4,
        data : [0x4F, 0xF2, ..., 0x3E]
    }
    ...
    0xCAN_ID3 {
        frame_len : 7,
        data : [0x5A, 0x1C, ..., 0xD2]
    }
}
*/

#include "stm32l4xx_hal.h"

#include "TESTFrame.h"

#include <string.h>
#include <cstdio>

//#define NOTE_PRODUCT_UID "edu.ufl.nathan.achinger:flare_telemetry"

#define NOTECARD_INIT "{\"req\":\"hub.set\",\"product\":\"edu.ufl.nathan.achinger:flare_telemetry\",\"mode\":\"continuous\"}\n"
#define JSON_CAN_FORMAT "{\"req\":\"note.add\",\"body\":{\"%u\":{\"frame_len\":%u,\"data\":%s}}}"
#define NOTECARD_STATUS "{\"req\":\"card.status\"}\n"

#define MAX_FRAME_LEN 8


class Notecard {
public:
    Notecard(UART_HandleTypeDef *huart);
    void getStatus();
    HAL_StatusTypeDef SendCommand(const char *command);
    HAL_StatusTypeDef LoadFrame(TESTFrame &frame);

private:
    HAL_StatusTypeDef SendByte(uint8_t *data, uint8_t len);

    UART_HandleTypeDef *huart;
    // array of frame data
    char frame_data[2 + (MAX_FRAME_LEN * 2)];
    // formatted json packet
    uint8_t json_packet[sizeof(JSON_CAN_FORMAT) + sizeof(frame_data) + 5];
};

#endif // NOTECARD_HPP
