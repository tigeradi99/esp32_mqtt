#include "protodefs/message.pb-c.h"

class MQTTMessage
{
    private:
    SampleData sample_data;

    public:
    MQTTMessage(){
        sample_data = SAMPLE_DATA__INIT;
    }

    void set_greeting(const char* greeting)
    {
        sample_data.greeting = (char*)greeting;
    }
    
    void clear_greeting()
    {
        sample_data__init(&sample_data);
    }

    const char* get_greeting()
    {
        return sample_data.greeting;
    }

    size_t get_packed_length()
    {
        return sample_data__get_packed_size(&sample_data);
    }

    void pack_to_buffer(uint8_t* buffer)
    {
        sample_data__pack(&sample_data, buffer);
    }
};