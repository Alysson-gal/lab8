//Universidad del Valle de Guatemala
//Laboratorio#8
//Alysson Galindo
//Pantalla 320 de ancho x 240 de alto
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "ili9341.h" //funciones de pantalla
#include "Bitmaps.h"   // va a buscar todo lo que hay dentro de este archivo

/* USER CODE END Includes */

/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* USER CODE BEGIN PD */

// --- Colores en formato RGB565 ---
#define C_FONDO     0x0861   // Fondo oscuro para la pantalla "Gris"
#define C_BARRA     0x033D   // Barras azules para el titulo y el estado.
#define C_TARJETA   0x18E3   // gris oscuro para el pulso
#define C_BLANCO    0xFFFF // texto blanco
#define C_CIAN      0x07FF   // bordes con azul clarito
#define C_VERDE     0x07E0   // valor de SpO2 de verde natural
#define C_ROJO      0xF800   // valor del pulso
#define C_GRIS      0xC618   // texto secundario

/* USER CODE END PD */

/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void dibujarOximetro(void);//declaracion
/* USER CODE END PFP */

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

  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();          // inicializa la pantalla es lo primero
  dibujarOximetro();   // dibuja la interfaz
  /* USER CODE END 2 */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Configuro los pines de la pantalla en bajo al inicio */
  HAL_GPIO_WritePin(GPIOC, LCD_RST_Pin|LCD_D1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin|LCD_D7_Pin|LCD_D0_Pin|LCD_D2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin|LCD_D6_Pin|LCD_D3_Pin|LCD_D5_Pin|LCD_D4_Pin, GPIO_PIN_RESET);

  /* Pines de la pantalla en el puerto C */
  GPIO_InitStruct.Pin = LCD_RST_Pin|LCD_D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* Pines de la pantalla en el puerto A */
  GPIO_InitStruct.Pin = LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin|LCD_D7_Pin|LCD_D0_Pin|LCD_D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Pines de la pantalla en el puerto B */
  GPIO_InitStruct.Pin = LCD_CS_Pin|LCD_D6_Pin|LCD_D3_Pin|LCD_D5_Pin|LCD_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Dibuja el corazon mas grande (escala = 2 lo hace el doble, 3 el triple...)
void dibujarCorazonGrande(int x, int y, int escala)
{
    int ancho = 32, alto = 32;
    for (int j = 0; j < alto; j++) {
        for (int i = 0; i < ancho; i++) {
            uint16_t color = corazon[j * ancho + i];
            if (color != 0x07e0) {                 // si no es el verde transparente
                FillRect(x + i*escala, y + j*escala, escala, escala, color);
            }
        }
    }
}
void dibujarOximetro(void)
{
	// fondo general
	LCD_Clear(C_FONDO);

	//La barra de titulo para arriba
	FillRect(0,0,320,34,C_BARRA);
	//"OXIMETRO DE PULSO" contiene 17 letras *16tpx=272px-> centrado 320-272/2=24
	LCD_Print("OXIMETRO DE PULSO", 24, 9, 2, C_BLANCO, C_BARRA);

	// Para la tarjetita de SpO2 a la izquierda
	FillRect(18,52,135,120, C_TARJETA);//color de fondo de la tarjeta
	Rect(18,52,135,120, C_CIAN); //Para el bordesito

	LCD_Print("SpO2", 53, 66, 2, C_CIAN,  C_TARJETA);
	LCD_Print("98%",  61, 108, 2, C_VERDE,  C_TARJETA);
	FillRect(167, 52, 135, 120, C_TARJETA);
	    Rect(167, 52, 135, 120, C_CIAN);
	    LCD_Print("PULSO", 194, 66, 2, C_CIAN, C_TARJETA);
	// etiqueta
	    LCD_Print("72",   218, 104, 2, C_ROJO, C_TARJETA);
	// valor random
	    LCD_Print("bpm",  222, 132, 1, C_GRIS, C_TARJETA);
	// unidad con letra chica donde esta el 1
	// Para la tarjeta de pulso del lado derecho

	//Barra de estado de abajo
	    FillRect(0, 185, 320, 55, C_BARRA);
	    LCD_Print("Paciente estable", 96, 205, 1, C_BLANCO, C_BARRA);
	// ---- 6. Imagen ----
	  //  LCD_BitmapTransparent(15, 190, 32, 32, corazon, 0x07e0);
		    dibujarCorazonGrande(10, 174, 2);//agrandado

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
