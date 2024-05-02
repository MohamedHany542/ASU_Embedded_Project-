#define switch_mask  0x10
#define GREEN_LED_mask    0x08
void switch1_int();
void LED_Green_int();
unsigned char read_switch1();
void GREEN_LED_out (unsigned char LED_in );
void GREEN_LED_clear (void);
