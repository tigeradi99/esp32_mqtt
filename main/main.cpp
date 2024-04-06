#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "mqtt/MQTTMessage.hpp"
#include "mqtt/MQTTClient.h"
#include "network/WiFiClient.h"

#include "nvs_flash.h"

extern "C" void app_main(void)
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Create default Event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    //Initialize Wifi system
	Wifi::Wifi wifi_client;
    wifi_client.SetCredentials("Jiofiber_4G", "");
    wifi_client.Init();

    while(true)
    {
        if(wifi_client.GetState() == Wifi::Wifi::state_e::READY_TO_CONNECT)
        {
            wifi_client.Begin();
            break;
        }
    }

    while(true)
    {
    	if(wifi_client.GetState() == Wifi::Wifi::state_e::CONNECTED)
    	{
			  break;
    	}
    }

    //Initialize MQTT Client
    MQTTClient::MQTTClient mqtt_client_obj = MQTTClient::MQTTClient("mqtt://broker.hivemq.com");
    mqtt_client_obj.mqtt_system_start();

    MQTTMessage sample_message = MQTTMessage();
    sample_message.set_greeting("Hello World by protobuf!");
    size_t packed_length = sample_message.get_packed_length();

    uint8_t serialized_buffer[packed_length + 1];
    sample_message.pack_to_buffer(serialized_buffer);
    
    printf("Length is %d \n", packed_length);

    while(true)
    {   
		if(wifi_client.GetState() == Wifi::Wifi::state_e::CONNECTED)
		{
			printf("Loop\n");
        	mqtt_client_obj.publish_mqtt("djtiger/test_send", (const char*)serialized_buffer, packed_length);
        	vTaskDelay(pdMS_TO_TICKS(5000));
		}
		else if(wifi_client.GetState() == Wifi::Wifi::state_e::DISCONNECTED)    
		{
			printf("Reconnecting....\n");
			wifi_client.Begin();
		} 
    }
}
