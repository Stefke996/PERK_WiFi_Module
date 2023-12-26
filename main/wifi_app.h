/*
 * wifi_app.h
 *
 *  Created on: Dec 25, 2023
 *      Author: sstoj
 */

#ifndef MAIN_WIFI_APP_H_
#define MAIN_WIFI_APP_H_


#include <string.h>
#include "esp_system.h" 	//esp_init funtions esp_err_t
#include "esp_wifi.h" 		//esp_wifi_init functions and wifi operations
#include "esp_log.h"
#include "lwip/sockets.h"



/* UDP server address and port: */
#define SERVER_IP "192.168.0.17"  // Replace with the IP address of your server
//#define SERVER_IP "192.168.43.224"
#define SERVER_PORT 12345



void Wifi_connection();
void Udp_socket_connection();

void Udp_send_packet(uint8_t *data, uint16_t size);


#endif /* MAIN_WIFI_APP_H_ */
