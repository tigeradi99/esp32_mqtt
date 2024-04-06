#include "mqtt/MQTTClient.h"

esp_mqtt_client_handle_t MQTTClient::MQTTClient::msg_client{};
esp_mqtt_client_config_t MQTTClient::MQTTClient::mqtt_config{};

MQTTClient::MQTTClient::MQTTClient(const char* broker_url)
{
    mqtt_config.broker.address.uri = broker_url;
}

void MQTTClient::MQTTClient::mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{

    esp_mqtt_event_handle_t event = (esp_mqtt_event_t*)event_data;

    switch((esp_mqtt_event_id_t)event_id)
    {
        case MQTT_EVENT_CONNECTED:
            printf("MQTT_EVENT_CONNECTED\n");
            break;
        case MQTT_EVENT_PUBLISHED:
            printf("MQTT_EVENT_PUBLISHED, msg_id=%d \n", event->msg_id);
            break;
        case MQTT_EVENT_ERROR:
            printf("MQTT_EVENT_ERROR\n");
        default:
            break;
    }
}

void MQTTClient::MQTTClient::mqtt_system_start(void)
{
    msg_client = esp_mqtt_client_init(&mqtt_config);
    esp_mqtt_client_register_event(msg_client, (esp_mqtt_event_id_t)ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(msg_client);
}

void MQTTClient::MQTTClient::publish_mqtt(const char *topic, const char *data, int len)
{
    int msg_id = esp_mqtt_client_publish(msg_client, topic, data, len, 0, 0);
    printf("Message published. return value: %d \n", msg_id);
}