#ifndef EEPROM_private_h
#define EEPROM_private_h


#include"std_Types.h"


#define EEPROM_EESIZE           (*((volatile uint32*)0x400AF000))// EEPROM Size Information
#define EEPROM_EEBLOCK          (*((volatile uint32*)0x400AF004))// EEPROM Current Block
#define EEPROM_EEOFFSET        (*((volatile uint32*) 0x400AF008))// EEPROM Current Offset
#define EEPROM_EERDWR          (*((volatile uint32*) 0x400AF010))// EEPROM Read-Write
#define EEPROM_EERDWRINC       (*((volatile uint32*) 0x400AF014))// EEPROM Read-Write with Increment
#define EEPROM_EEDONE          (*((volatile uint32*) 0x400AF018)) // EEPROM Done Status
#define EEPROM_EESUPP          (*((volatile uint32*) 0x400AF01C)) // EEPROM Support Control and
#define EEPROM_RCGCEEPROM      (*((volatile uint32*)0x400FE658))// provided a clock and accesses to module
#define EEPROM_SREEPROM        (*((volatile uint32*)0x400FE558))
#define EEPROM_PREEPROM        (*((volatile uint32 *)0x400FEA58)) //CHEK ON whether the EEPROM module is ready to be accessed




#define EEPROM_EEDONE_WORKING_MASK   0x00000000
                                            // Status
#define EEPROM_EEUNLOCK         0x400AF020  // EEPROM Unlock
#define EEPROM_EEPROT           0x400AF030  // EEPROM Protection
#define EEPROM_EEPASS0          0x400AF034  // EEPROM Password
#define EEPROM_EEPASS1          0x400AF038  // EEPROM Password
#define EEPROM_EEPASS2          0x400AF03C  // EEPROM Password
#define EEPROM_EEINT            0x400AF040  // EEPROM Interrupt
#define EEPROM_EEHIDE0          0x400AF050  // EEPROM Block Hide 0
#define EEPROM_EEHIDE           0x400AF050  // EEPROM Block Hide
#define EEPROM_EEHIDE1          0x400AF054  // EEPROM Block Hide 1
#define EEPROM_EEHIDE2          0x400AF058  // EEPROM Block Hide 2
#define EEPROM_EEDBGME          0x400AF080  // EEPROM Debug Mass Erase
#define EEPROM_PP               0x400AFFC0  // EEPROM Peripheral Properties
#define EEPROM_EESUPP_PRETRY_MASK 0x00000003
#define EEPROM_EESUPP_ERETRY_MASK 0x00000002
#define EEPROM_EESUPP_START_MASK  0x00000000
#define EEPROM_SREEPROM_RO_MASK  0x00000000
#define EEPROM_PREEPROM_RO_MASK     0x00000000
#define EEPROM_EEOFFSET_OFFSET_MASK (0x0000000F)



void  EEPROM_init(void);
void EEPROMMassErase(void);
void EEPROMRead(int* Data,int Address ,int word_Count);
int EEPROM_Write (int* Data, int Address,int word_Count);

#endif
