/*
 * data_process.h
 *
 *  Created on: Dec 28, 2023
 *      Author: sstoj
 */

#ifndef MAIN_DATA_PROCESS_H_
#define MAIN_DATA_PROCESS_H_

#include "freertos/FreeRTOS.h"
#include <freertos/timers.h>
#include "stdint.h"
#include "stdio.h"


#include "wifi_app.h"


#define SIZE_OF_SIGNAL_BUFFER 500



typedef struct signal
{
	uint8_t signal_id;
	uint16_t *data;
}SIGNAL;



void Allocate_data_memory(void);
void Data_process_init(void);
void Data_process_run(void);

#endif /* MAIN_DATA_PROCESS_H_ */
