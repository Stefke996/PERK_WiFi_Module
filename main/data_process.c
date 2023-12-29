/*
 * data_process.c
 *
 *  Created on: Dec 28, 2023
 *      Author: sstoj
 */
#include "data_process.h"

/* LOG tags: */
static const char* TAG_DATA_PROCESS  = "esp data process: ";


/* Signals buffer */
SIGNAL signal_1;
SIGNAL signal_2;
SIGNAL signal_3;
SIGNAL signal_4;
SIGNAL signal_5;
SIGNAL signal_6;
SIGNAL signal_7;
SIGNAL signal_8;
SIGNAL signal_9;
SIGNAL signal_10;
SIGNAL signal_11;
SIGNAL signal_12;
SIGNAL signal_13;
SIGNAL signal_14;
SIGNAL signal_15;
SIGNAL signal_16;


/* Timer: */
static TimerHandle_t timer;
bool timerExpiredFlag = false;


/* Static functions: */
static void timer_callback(TimerHandle_t xTimer);




void Allocate_data_memory(void)
{
	signal_1.signal_id  = 1;
	signal_1.data  = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_2.signal_id  = 2;
	signal_2.data  = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_3.signal_id  = 3;
	signal_3.data  = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_4.signal_id  = 4;
	signal_4.data  = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_5.signal_id  = 5;
	signal_5.data  = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_6.signal_id  = 6;
	signal_6.data  = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_7.signal_id  = 7;
	signal_7.data  = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_8.signal_id  = 8;
	signal_8.data  = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_9.signal_id  = 9;
	signal_9.data  = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_10.signal_id = 10;
	signal_10.data = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_11.signal_id = 11;
	signal_11.data = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_12.signal_id = 12;
	signal_12.data = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_13.signal_id = 13;
	signal_13.data = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_14.signal_id = 14;
	signal_14.data = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_15.signal_id = 15;
	signal_15.data = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
	signal_16.signal_id = 16;
	signal_16.data = (uint16_t*)malloc(SIZE_OF_SIGNAL_BUFFER * sizeof(uint16_t));
}


void Data_process_init(void)
{
	/* Create a timer */
	timer = xTimerCreate( "Timer",      		// Timer name (just a string identifier)
	        			  pdMS_TO_TICKS(10),  	// Timer period in milliseconds (10ms in this case)
						  pdTRUE,         		// Auto-reload, so the timer repeats
						  0,              		// ID not used in this example
						  timer_callback ); 	// Callback function to be called when the timer expires


	/* Check if the timer was created successfully */
	if (timer == NULL)
	{
		// Timer creation failed
		ESP_LOGI(TAG_DATA_PROCESS, "Timer creation failed");
	}

	/* Start the timer */
	if (xTimerStart(timer, 0) != pdPASS)
	{
		// Timer start failed
		ESP_LOGI(TAG_DATA_PROCESS, "Timer start failed");
	}
}

void Data_process_run(void)
{
	if(timerExpiredFlag)
	{
		// Prepare data
		// Send all signlas
		timerExpiredFlag = false; 	// Clear flag

	}
}


static void timer_callback(TimerHandle_t xTimer)
{
	timerExpiredFlag = true; 	// Set flag
}


