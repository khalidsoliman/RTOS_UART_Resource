/*
 * main.c
 *
 *  Created on: Feb 3, 2018
 *      Author: Khalid
 */

/* Include OS Header files */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include <avr/io.h>
/* Include Drivers Header files */
#include "UART/UART.h"
/* Proto. */
void T_Server (void * pvData);
void T_SMS (void * pvData);
void System_Init(void);
/* OS Serv , Declaration */
xSemaphoreHandle bsUartRes ;



int main ()
{
	/* Pr . Init .*/
	System_Init();
	/* OS Serv . Create And Init */
	vSemaphoreCreateBinary(bsUartRes,1);
	/* Tasks Create */
	xTaskCreate(T_SMS,NULL,100,NULL,1,NULL);
	xTaskCreate(T_Server,NULL,100,NULL,2,NULL);
	/* Start OS or Sched */
	vTaskStartScheduler();
	return 0 ;
}
/*
 *
 * void T_Name (void * pvData)
 * {
 * code
 * while(1)
 * {
 * code
 * }
 * code (Dead code)
 * }
 *
 *
 *
 */
void T_Server (void * pvData)
{
	while(1)
	{
		if(xSemaphoreTake(bsUartRes,0xffff))
		{
			UART_send_string("AT+Server1\n");
			UART_send_string("AT+Server2\n");
			xSemaphoreGive(bsUartRes);
		}
		vTaskDelay(5);
	}
}
void T_SMS (void * pvData)
{
	while(1)
	{
		if(xSemaphoreTake(bsUartRes,0xffff))
		{
			UART_send_string("AT+SMS1\n");
			UART_send_string("AT+SMS2\n");
			xSemaphoreGive(bsUartRes);
		}

	}
}
void System_Init(void)
{
	UART_Init(9600);

}
