#include "callbacks.h"

// for error handler declaration
#include "main.h"

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
  {
	  Error_Handler();
  }
  if ((RxHeader.StdId == 0x103))
  {
	  can_data_rx_flag = 1;
  }
}
