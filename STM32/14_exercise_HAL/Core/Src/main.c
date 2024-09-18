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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// 1.����ȫ�ֱ���
uint8_t buffer[20] = { 0 };
uint8_t size = 0;
uint8_t Plan_BRF = 0;

// 2.ѭ���ķ���(-1,0,1,2)
Plan_Statue plan_statue = No_Plan;

// 3.��һ����ά���鱣����ˮ�Ʒ���
uint8_t LED_plans[3][2] = { 0 };

// 4.�������е�LED�Ƶ�����
uint16_t leds[3] = { LED1_Pin,LED2_Pin,LED3_Pin };

// 5. �����ַ���������
void LED_LoadPlan(void);


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
    MX_I2C2_Init();
    MX_USART1_UART_Init();
    /* USER CODE BEGIN 2 */

    // ��ʼ�ź�
    printf("LED_Plan ---> Start\n");
    // �ж�EEPROM�����Ƿ������ݣ�����ͨ��IIC����LED_LoadPlan
    if ((HAL_I2C_Mem_Read(&hi2c2, 0xA1, 0, I2C_MEMADD_SIZE_8BIT, buffer, 11, HAL_MAX_DELAY)) == HAL_OK)
    {
        if (buffer[0] != 0)
        {
            printf("IIC-----------> buffer = %s\n", buffer);
            LED_LoadPlan();
        }
    }
    // ����һ��UART��Ϣ���������ر��жϣ������жϻὫBRF��Ϊ1
    HAL_UARTEx_ReceiveToIdle_IT(&huart1, buffer, 11);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */
        if (Plan_BRF)
        {
            Plan_BRF = 0;
            // �ٴο���USART�жϵȴ���һ�ν���
            HAL_UARTEx_ReceiveToIdle_IT(&huart1, buffer, 11);
            printf("USART----------> buffer = %s\n", buffer);
            // ͨ��USART����LED_LoadPlan�����������յ�������ͨ��IIC����EEPROM
            LED_LoadPlan();
            HAL_I2C_Mem_Write(&hi2c2, 0xA0, 0, I2C_MEMADD_SIZE_8BIT, buffer, 11, HAL_MAX_DELAY);
        }
        
        if (plan_statue != No_Plan)
        {
            // 1.�ر����е�
            for (uint8_t i = 0; i < 3; i++)
            {
                HAL_GPIO_WritePin(GPIOA, leds[i], GPIO_PIN_SET);
            }

            // 2.ͨ��״̬������Ӧ��
            for (uint8_t i = 0; i < 2; i++)
            {
                HAL_GPIO_WritePin(GPIOA, leds[LED_plans[plan_statue][i] - 1], GPIO_PIN_RESET);
                printf("LED%d_On\n", LED_plans[plan_statue][i]);
                HAL_Delay(1500);
                HAL_GPIO_WritePin(GPIOA, leds[LED_plans[plan_statue][i] - 1], GPIO_PIN_SET);
            }
        }
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
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
/**
 * ����LED�Ƶ����üƻ�
 *
 * ��������һ��Ԥ���buffer�н�����LED�Ƶ������ƻ�����ÿ�ּƻ������������ֽ����
 * �����ɹ��󣬽�����plan_statue��ָʾ��ǰ�ļƻ�״̬
 *
 * ע�⣺�˴�ʹ��sscanf�����ֽڽ��������ܴ��ڰ�ȫ�Է���Ӧȷ��buffer�е�������Դ�ɿ�
 */
void LED_LoadPlan(void) {
    // ��buffer�н���LED�Ƶ������ƻ����ã�ÿ���ƻ����ð��������ֽڵ�����
    sscanf((char*)buffer, "%hhu,%hhu#%hhu,%hhu#%hhu,%hhu",
        &LED_plans[0][0], &LED_plans[0][1],
        &LED_plans[1][0], &LED_plans[1][1],
        &LED_plans[2][0], &LED_plans[2][1]);

    // ��ӡbuffer�����ݣ����ڵ���Ŀ��
    printf("LED_LoadPlan() ---> buffer = %s\n", buffer);

    // ����plan_statue��ָ���һ���ƻ�
    plan_statue = Plan_1;
}

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
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
       /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
