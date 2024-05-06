#include "led.h"

void RGB_ON(RGB_Config *ptr)
{
    switch (ptr->RGB_Color)
    {
    case red:
        Dio_WriteChannel(DioConf_LED_R_CHANNEL_ID_INDEX,STD_HIGH); // use dio instead of address of regs 
        break;
    case blue:
        Dio_WriteChannel(DioConf_LED_B_CHANNEL_ID_INDEX,STD_HIGH);
        break;
    case green:
    {
        Dio_WriteChannel(DioConf_LED_G_CHANNEL_ID_INDEX,STD_HIGH);
        break;
    }
    case yellow:
    {
        Dio_WriteChannel(DioConf_LED_R_CHANNEL_ID_INDEX , STD_HIGH);
        Dio_WriteChannel(DioConf_LED_G_CHANNEL_ID_INDEX ,STD_HIGH);
        break;
    }
    case magenta:
    {
        Dio_WriteChannel(DioConf_LED_R_CHANNEL_ID_INDEX , STD_HIGH);
        Dio_WriteChannel(DioConf_LED_B_CHANNEL_ID_INDEX , STD_HIGH);
        break;
    }
    case cyan:
    {
        Dio_WriteChannel(DioConf_LED_G_CHANNEL_ID_INDEX , STD_HIGH);
        Dio_WriteChannel(DioConf_LED_B_CHANNEL_ID_INDEX , STD_HIGH);
        break;
    }
    case white:
    {
        Dio_WriteChannel(DioConf_LED_R_CHANNEL_ID_INDEX,STD_HIGH);
        Dio_WriteChannel(DioConf_LED_G_CHANNEL_ID_INDEX , STD_HIGH);
        Dio_WriteChannel(DioConf_LED_B_CHANNEL_ID_INDEX , STD_HIGH);
        break;
    }
    }
}

void RGB_OFF(void)
{
    Dio_WriteChannel(DioConf_LED_R_CHANNEL_ID_INDEX,STD_LOW);  // turn off all leds
    Dio_WriteChannel(DioConf_LED_B_CHANNEL_ID_INDEX , STD_LOW);
    Dio_WriteChannel(DioConf_LED_G_CHANNEL_ID_INDEX,STD_LOW);
}

