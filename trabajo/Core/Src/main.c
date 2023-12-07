/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include <stdint.h>
#include "API_lcd.h"
#include "API_delay.h"
#include "API_debounce.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_NMEA_LENGTH 82
#define LCD_ADDRESS 0x4E
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;

I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
void lcdSendCommand(char);
void lcdSendText(char);
void lcdInit(void);
void lcdSendString(char*, uint8_t);
void lcdLineOne(void);
void lcdLineTwo(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_I2C2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  char gpsData[1] = "";
  char parseLine[MAX_NMEA_LENGTH] = "";
  lcdInit ();
  char latitude[] =   "LAT:    .       ";
  char longitude[] =  "LON:    .       ";
  char satellites[] = "Satellites:     ";
  char error[] =      "Error:  .  x25m ";
  char time[] =       "Time:    :      ";
  char date[] =       "Date:    /  /   ";
  enum lcdScreen{gpsPos, gpsSat, gpsDat};
  enum lcdScreen gpsScreen = gpsSat;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  	  HAL_UART_Receive(&huart2, ((uint8_t*) gpsData), 1, HAL_MAX_DELAY);
//  	  HAL_UART_Transmit(&huart3, ((uint8_t*) gpsData), 1, HAL_MAX_DELAY);

  	  if (gpsData[0] == '$'){
  		  uint8_t i = 0;
  		  while(gpsData[0] != '\n'){
  			  parseLine[i] = gpsData[0];
  			  HAL_UART_Receive(&huart2, ((uint8_t*) gpsData), 1, HAL_MAX_DELAY);
  			  i++;
  			  // Con esto me aseguro de tener una condición de salida
  			  if (i > MAX_NMEA_LENGTH){
  				  break;
  			  }
  		  }
  		if (parseLine[4] == 'G'){
  		    latitude[6] = parseLine[17];
		    latitude[7] = parseLine[18];
			latitude[9] = parseLine[19];
			latitude[10] = parseLine[20];
			latitude[11] = parseLine[22];
			latitude[12] = parseLine[23];
			latitude[13] = parseLine[24];
			latitude[15] = parseLine[28];
			longitude[5] = parseLine[30];
			longitude[6] = parseLine[31];
			longitude[7] = parseLine[32];
			longitude[9] = parseLine[33];
			longitude[10] = parseLine[34];
			longitude[11] = parseLine[36];
			longitude[12] = parseLine[37];
			longitude[13] = parseLine[38];
			longitude[15] = parseLine[42];
			satellites[13] = parseLine[46];
			satellites[14] = parseLine[47];
			error[7] = parseLine[49];
			error[9] = parseLine[51];
			error[10] = parseLine[52];

			HAL_UART_Transmit(&huart3, ((uint8_t*) latitude), 16, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) "\n\r"), 2, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) longitude), 16, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) "\n\r"), 2, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) satellites), 16, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) "\n\r"), 2, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) error), 16, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) "\n\r"), 2, HAL_MAX_DELAY);
			if (gpsScreen == gpsPos){
				lcdLineOne();
				lcdSendString(latitude,16);
				lcdLineTwo();
				lcdSendString(longitude,16);
			}
			if (gpsScreen == gpsSat){
				lcdLineOne();
				lcdSendString(satellites,16);
				lcdLineTwo();
				lcdSendString(error,16);
			}
  		}
  		if (parseLine[4] == 'M'){
			time[7] = parseLine[7];
			time[8] = parseLine[8];
			time[10] = parseLine[9];
			time[11] = parseLine[10];
			time[13] = parseLine[11];
			time[14] = parseLine[12];
			date[7] = parseLine[53];
			date[8] = parseLine[54];
			date[10] = parseLine[55];
			date[11] = parseLine[56];
			date[13] = parseLine[57];
			date[14] = parseLine[58];

			HAL_UART_Transmit(&huart3, ((uint8_t*) time), 16, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) "\n\r"), 2, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) date), 16, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, ((uint8_t*) "\n\r"), 2, HAL_MAX_DELAY);
			if (gpsScreen == gpsDat){
				lcdLineOne();
				lcdSendString(date,16);
				lcdLineTwo();
				lcdSendString(time,16);
			}
  		}

 	  }
  	  switch(gpsScreen){
  	  case gpsPos:
  		  if (isButtonReleased()){
  			  gpsScreen = gpsSat;
  			  HAL_UART_Transmit(&huart3, ((uint8_t*) "Paso a Satelites\n\r"), 18, HAL_MAX_DELAY);
  		  }
  	  case gpsSat:
  		  if (isButtonReleased()){
  			  gpsScreen = gpsDat;
  			  HAL_UART_Transmit(&huart3, ((uint8_t*) "Paso a FechaHora\n\r"), 18, HAL_MAX_DELAY);
  		  }
  	  case gpsDat:
  		  if (isButtonReleased()){
  			  gpsScreen = gpsPos;
  			  HAL_UART_Transmit(&huart3, ((uint8_t*) "Paso a Posicion\n\r"), 17, HAL_MAX_DELAY);
  		  }
  	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }


  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

void lcdSendCommand(char command){
  char data_msb, data_lsb;
	uint8_t data[4];
	data_msb = (command & 0xf0);
	data_lsb = ((command << 4) & 0xf0);
	data[0] = data_msb | 0x0C;  // Subo el Enable
	data[1] = data_msb | 0x08;  // Bajo el Enable, para que lea la mitad alta
	data[2] = data_lsb | 0x0C;  // Subo el Enable
	data[3] = data_lsb | 0x08;  // Bajo el Enable, para que lea la mitad baja
	HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDRESS,(uint8_t*) data, 4, 100);
}

void lcdInit(void){
	// Los delays son mayores que los pedidos en la hoja de datos.
	HAL_Delay(50);
	lcdSendCommand(0x30); // Function set
	HAL_Delay(10);
	lcdSendCommand(0x28); // Function set: 2 lineas, caracteres 8x5
	HAL_Delay(10);
	lcdSendCommand(0x28); // Function set
	HAL_Delay(10);
	lcdSendCommand(0x0C); // Display ON/OFF control: Display encendido
	HAL_Delay(10);
	lcdSendCommand(0x01); // Display Clear
	HAL_Delay(10);
	lcdSendCommand(0x06); // Entry Mode Set: De derecha a izquierda
	HAL_Delay(10);
	lcdSendCommand(0x02); // Return Home
	HAL_Delay(10);
}

void lcdSendText(char text){
	char data_msb, data_lsb;
	uint8_t data[4];
	data_msb = (text & 0xf0);
	data_lsb = ((text << 4) & 0xf0);
	data[0] = data_msb | 0x0D;  // Subo el Enable
	data[1] = data_msb | 0x09;  // Bajo el Enable, para que lea la mitad alta
	data[2] = data_lsb | 0x0D;  // Subo el Enable
	data[3] = data_lsb | 0x09;  // Bajo el Enable, para que lea la mitad baja
	HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDRESS,(uint8_t*) data, 4, 100);
}

void lcdSendString(char* text, uint8_t length){
    for (uint8_t i = 0 ; i < length ; i++){
    	lcdSendText(text[i]);
    }
}

void lcdLineOne(void){
	lcdSendCommand(0x80);
}

void lcdLineTwo(void){
	lcdSendCommand(0xC0);
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
