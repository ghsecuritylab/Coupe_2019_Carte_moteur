/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"


/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

/* USART3 init function */

void MX_USART3_UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/**USART3 GPIO Configuration
	PD8     ------> USART3_TX
	PD9     ------> USART3_RX
	*/
	GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;	// USART 3

	huart3.Instance = USART3;
	huart3.Init.BaudRate = 57600;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK){
	_Error_Handler(__FILE__, __LINE__);
	}
	NVIC_EnableIRQ(USART3_IRQn);

	USART3->CR1 |= USART_CR1_UE 	// UART Enable
				| USART_CR1_TE 		// Tx enable
				| USART_CR1_RE		// Rx enbale
				| USART_CR1_RXNEIE;	// Rx enable interrupt
}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/**USART6 GPIO Configuration
	PG9     ------> USART6_RX
	PG14     ------> USART6_TX
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	RCC->APB2ENR |= RCC_APB2ENR_USART6EN;	// USART 6

	huart6.Instance = USART6;
	huart6.Init.BaudRate = 57600;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK){
	_Error_Handler(__FILE__, __LINE__);
	}

	NVIC_EnableIRQ(USART6_IRQn);

	USART6->CR1 |= USART_CR1_UE 	// UART Enable
				| USART_CR1_TE 		// Tx enable
				| USART_CR1_RE		// Rx enbale
				| USART_CR1_RXNEIE;	// Rx enable interrupt

}

//void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
//{
//
//  GPIO_InitTypeDef GPIO_InitStruct;
//  if(uartHandle->Instance==USART3)
//  {
//  /* USER CODE BEGIN USART3_MspInit 0 */
//
//  /* USER CODE END USART3_MspInit 0 */
//    /* USART3 clock enable */
//    __HAL_RCC_USART3_CLK_ENABLE();
//
//    /**USART3 GPIO Configuration
//    PD8     ------> USART3_TX
//    PD9     ------> USART3_RX
//    */
//    GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
//    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
//
//  /* USER CODE BEGIN USART3_MspInit 1 */
//
//  /* USER CODE END USART3_MspInit 1 */
//  }
//  else if(uartHandle->Instance==USART6)
//  {
//  /* USER CODE BEGIN USART6_MspInit 0 */
//
//  /* USER CODE END USART6_MspInit 0 */
//    /* USART6 clock enable */
//    __HAL_RCC_USART6_CLK_ENABLE();
//
//    /**USART6 GPIO Configuration
//    PG9     ------> USART6_RX
//    PG14     ------> USART6_TX
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_14;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
//    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
//
//  /* USER CODE BEGIN USART6_MspInit 1 */
//
//  /* USER CODE END USART6_MspInit 1 */
//  }
//}
//
//void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
//{
//
//  if(uartHandle->Instance==USART3)
//  {
//  /* USER CODE BEGIN USART3_MspDeInit 0 */
//
//  /* USER CODE END USART3_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_USART3_CLK_DISABLE();
//
//    /**USART3 GPIO Configuration
//    PD8     ------> USART3_TX
//    PD9     ------> USART3_RX
//    */
//    HAL_GPIO_DeInit(GPIOD, STLK_RX_Pin|STLK_TX_Pin);
//
//  /* USER CODE BEGIN USART3_MspDeInit 1 */
//
//  /* USER CODE END USART3_MspDeInit 1 */
//  }
//  else if(uartHandle->Instance==USART6)
//  {
//  /* USER CODE BEGIN USART6_MspDeInit 0 */
//
//  /* USER CODE END USART6_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_USART6_CLK_DISABLE();
//
//    /**USART6 GPIO Configuration
//    PG9     ------> USART6_RX
//    PG14     ------> USART6_TX
//    */
//    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_9|GPIO_PIN_14);
//
//  /* USER CODE BEGIN USART6_MspDeInit 1 */
//
//  /* USER CODE END USART6_MspDeInit 1 */
//  }
//}

/* USER CODE BEGIN 1 */
int __io_putchar(int ch){
	USART6->DR = ch;
	// Loop while character not sent
	while(!(USART6->SR & USART_SR_TXE));
	USART6->SR &= ~USART_SR_TXE;
	return(ch);
}

int __io_getchar(void){

  // Loop until the reception buffer is not empty
  while(!(USART6->SR & USART_SR_RXNE));

  return((int)USART6->DR);
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
