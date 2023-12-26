#include "freertos/FreeRTOS.h"
#include "nvs_flash.h" 		   	//non volatile storage


#include "wifi_app.h"


/* LOG tags: */
static const char* TAG_MAIN = "esp main: ";


const uint8_t data_to_send[16000] = {1};


void app_main(void)
{
	esp_err_t ret = nvs_flash_init();
	if (ret != ESP_OK)
	{
	  nvs_flash_erase();
	  nvs_flash_init();
	  ESP_LOGI(TAG_MAIN, "First need to erase nvs flash.....");
	}

	/* Communication init */
	Wifi_connection();
	Udp_socket_connection();
	ESP_LOGI(TAG_MAIN, "udp socket connection");



    while(true)
    {
//        vTaskDelay(300 / portTICK_PERIOD_MS);
    	Udp_send_packet((uint8_t*)data_to_send, 16000);

    }
}

