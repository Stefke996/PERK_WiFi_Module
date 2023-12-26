/*
 * wifi_app.c
 *
 *  Created on: Dec 25, 2023
 *      Author: sstoj
 */
#include "wifi_app.h"


/* LOG tags: */
static const char* TAG_WIFI = "esp wifi: ";
static const char* TAG_UDP  = "esp udp: ";


/* Define the SSID and password for your WiFi network: */
const char *ssid = "Stojkovic";
const char *pass = "anastefan";
//const char* ssid = "HUAWEI P30 Pro";
//const char* pass = "555333iap";


/* UDP socket: */
int sockfd;
struct sockaddr_in server_addr;


/* Other: */
int retry_num = 0;
bool wifi_got_ip_flag = false;


/* Static functions: */
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data);




void Wifi_connection()
{
	esp_netif_init();
	esp_event_loop_create_default();     // event loop
	esp_netif_create_default_wifi_sta(); // WiFi station
	wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
	esp_wifi_init(&wifi_initiation);
	esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
	esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
	wifi_config_t wifi_configuration = {
			.sta = {
				.ssid = "",
				.password = "",
			   }
			};
	strcpy((char*)wifi_configuration.sta.ssid, ssid);
	strcpy((char*)wifi_configuration.sta.password, pass);

	esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);

	esp_wifi_start();
	esp_wifi_set_mode(WIFI_MODE_STA);
	esp_wifi_connect();
	ESP_LOGI(TAG_WIFI, "wifi_init_softap finished. SSID:%s  password:%s",ssid ,pass);
}



void Udp_socket_connection(void)
{
	while(!wifi_got_ip_flag)
	{
		vTaskDelay(300 / portTICK_PERIOD_MS);

	}


	// Create a UDP socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		ESP_LOGE(TAG_UDP, "Failed to create socket");
		while(true)
		{
			vTaskDelay(300 / portTICK_PERIOD_MS);
			ESP_LOGI(TAG_UDP, "...");
		}
	}


	// Set up the server address
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
	ESP_LOGI(TAG_UDP, "Socket successfully created");
}



void Udp_send_packet(uint8_t *data, uint16_t size)
{
	sendto(sockfd, data, size, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
//	ESP_LOGI(TAG_UDP, "Sent data");
}



static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data)
{
	if(event_id == WIFI_EVENT_STA_START)
	{
		ESP_LOGI(TAG_WIFI, "WIFI CONNECTING....");
	}
	else if (event_id == WIFI_EVENT_STA_CONNECTED)
	{
		ESP_LOGI(TAG_WIFI, "WiFi CONNECTED");
	}
	else if (event_id == SYSTEM_EVENT_STA_GOT_IP)
	{
		tcpip_adapter_ip_info_t ip_info;
		tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);
//		station_ip = ip_info.ip;
	}
	else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
	{
		ESP_LOGI(TAG_WIFI, "WiFi lost connection");
		if(retry_num<5)
		{
			esp_wifi_connect();
			retry_num++;
			ESP_LOGI(TAG_WIFI, "Retrying to Connect...");
		}
	}
	else if (event_id == IP_EVENT_STA_GOT_IP)
	{
		ESP_LOGI(TAG_WIFI, "Wifi got IP...");
		wifi_got_ip_flag = true;
	}
}


