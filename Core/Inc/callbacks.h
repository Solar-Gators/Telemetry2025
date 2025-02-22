#ifndef CALLBACKS_H
#define CALLBACKS_H

// need for CAN definitions
#include "stm32l4xx_hal.h"

extern uint8_t can_data_rx_flag;

extern CAN_RxHeaderTypeDef RxHeader;
extern uint8_t RxData[8];
extern volatile uint8_t datacheck;

extern void ErrorHandler(void);

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);


#endif // CALLBACKS_H
