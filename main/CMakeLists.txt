set(SOURCES main.cpp message.pb-c.c MQTTClient.cpp network/WiFiClient.cpp)

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS . ../include)
