#pragma once
#include "mqtt_client.h"

namespace MQTTClient
{
    class MQTTClient
    {
        private:
        static esp_mqtt_client_config_t mqtt_config;
        static esp_mqtt_client_handle_t msg_client;

        public:

        MQTTClient(const char* broker_url);

        static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
        static void mqtt_system_start(void);
        static void publish_mqtt(const char *topic, const char *data, int len);

    };
}