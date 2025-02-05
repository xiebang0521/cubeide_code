/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "can.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "rfid.h"
#include "oled.h"
#include "time.h"
#include "aes.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t read_flag = 0;
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
	// 修改密码
//  write_data.hot_bed_temp_H = 100;
//  write_data.hot_bed_temp_L = 40;
//  write_data.exthead_temp_L = 150;
//  write_data.exthead_temp_H = 400;
  Material_Data write_data;
  Material_Data read_data;
  memset(&write_data, 0, sizeof(write_data));
  memcpy(write_data.material_type, "PLA",sizeof("PLA"));
  memcpy(write_data.batch_number, "MD202411120001", sizeof("MD202411120001"));
  write_data.cavity_temp = 35;
  write_data.rgb[0] = 0xff;
  write_data.rgb[1] = 0xff;
  write_data.rgb[2] = 0xff;
  write_data.produced_date =1731578537;
  write_data.material_diameter = 1.75;
  write_data.material_density = 1.23;
  write_data.init_weight = 2000;
  write_data.empty_tray_weight = 150;
  write_data.residual_weight = 1500;
  memcpy(write_data.supplier, "MD9999",sizeof("MD9999"));
  memcpy(write_data.machines[0].machine_type, "MD1000D",sizeof("MD1000D"));
  write_data.machines[0].fan_speed = 100;
  write_data.machines[0].flow_ratio = 25.5;
  write_data.machines[0].nozzle_temp = 220;
  write_data.machines[0].nozzle_temp_l = 150;
  write_data.machines[0].nozzle_temp_h = 400;
  write_data.machines[0].hot_bed_temp = 50;
  write_data.machines[0].hot_bed_temp_l = 40;
  write_data.machines[0].hot_bed_temp_h = 100;
  write_data.machines[0].advance_pressure = 0.1;

/*
 * 50 4c 41 00 00 00 00 00 00 ff ff ff a9 ca 35 67
 * 5e a1 79 25 f7 e6 b7 93 f0 94 05 d2 ae 53 18 41// aes
 * 4d 44 30 30 30 30 31 00 28 00 64 00 96 00 90 01 (1)
 * 96 de fd 2a 09 c1 38 92 ab c0 5a c3 89 25 d2 ea// aes
 * d0 07 96 00 dc 05 01 00 00 00 e0 3f a4 70 9d 3f	(3)
 * 50 7a 6a 5d 0a d5 13 6d 5e 72 43 a4 5b 06 6a c0
 * */

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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

  OLED_Init();
  OLED_Clear();

  RFID_Rc523_Config();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


//	  OLED_ShowHexArray((uint8_t*)&write_data , 8, 1);
//	  OLED_ShowHexArray((uint8_t*)&write_data + 8, 8, 2);
//	  OLED_ShowHexArray((uint8_t*)&write_data + 16, 8, 3);
//	  OLED_ShowHexArray((uint8_t*)&write_data + 24, 8, 4);
//	  HAL_Delay(5000);
//	  OLED_Clear();
//	  OLED_ShowHexArray((uint8_t*)&write_data + 32, 8, 1);
//	  OLED_ShowHexArray((uint8_t*)&write_data + 40, 8, 2);
//	  HAL_Delay(5000);
//	  OLED_Clear();
	  //rfid_write_channel_data(0x02, &write_data);


	  memset(&read_data,0,sizeof(read_data));
	  rfid_read_channel_data(0x02, &read_data);
	  OLED_ShowHexArray((uint8_t*)&read_data , 8, 1);
	  OLED_ShowHexArray((uint8_t*)&read_data + 8, 8, 2);
	  OLED_ShowHexArray((uint8_t*)&read_data + 16, 8, 3);
	  OLED_ShowHexArray((uint8_t*)&read_data + 24, 8, 4);
	  HAL_Delay(5000);
	  OLED_Clear();
	  OLED_ShowHexArray((uint8_t*)&read_data + 32, 8, 1);
	  OLED_ShowHexArray((uint8_t*)&read_data + 40, 8, 2);
	  OLED_ShowHexArray((uint8_t*)&read_data + 48, 8, 3);
	  OLED_ShowHexArray((uint8_t*)&read_data + 56, 8, 4);
	  HAL_Delay(5000);
	  OLED_Clear();
	  OLED_ShowHexArray((uint8_t*)&read_data + 64, 8, 1);
	  OLED_ShowHexArray((uint8_t*)&read_data + 72, 8, 2);
	  OLED_ShowHexArray((uint8_t*)&read_data + 80, 8, 3);
	  OLED_ShowHexArray((uint8_t*)&read_data + 88, 8, 4);
	  HAL_Delay(5000);
	  OLED_Clear();

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
