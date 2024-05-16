#include <stdio.h>
#include "tm4c123gh6pm_registers.h"
#include "EEPROM.h"
#include "Platform_Types.h"
#include "Compiler.h"
#include "Gpt.h"
#include "Std_Types.h"
#include "Common_Macros.h"




// Enable eeprom clk
// wait until clk work eepromdone


inline int EEPROM_BLOCK_FROM_ADDRESS (int ADDRESS)
{
     return ((int) ((ADDRESS) >> 6));
}

inline int OFFSET_FROM_ADDRESS (int ADDRESS)
{
    return (((ADDRESS) >> 2) & 0x0F );
}



//#define EEPROM_BLOCK_FROM_ADDRESS (ADDRESS)  (uint32) ((ADDRESS) >> 6)
//#define OFFSET_FROM_ADDRESS (ADDRESS)      (((ADDRESS) >> 2) & 0x0F )

  int P_E_Retry_Status = 0;


 void EEPROM_init(void)
 {
    EEPROM_RCGCEEPROM|=0x01;//ACTIVATING EEPROM CLK

    delay_ms(0.0005);//MUST DELAY 6 CYCLES

    while (BIT_IS_SET(EEPROM_EEDONE,EEPROM_EEDONE_WORKING_MASK)); //Polling until working bit is set

//    if ((EEPROM_EESUPP && (0x0C))!= 0x00)
//    {
//       P_E_Retry_Status = 1;
//    }

 /*
  * Polling on  PRETRY,ERETRY Flags until they are cleared (Operation is done Successfully)
  */
      while ( (BIT_IS_SET(EEPROM_EESUPP,EEPROM_EESUPP_PRETRY_MASK) ) || (BIT_IS_SET(EEPROM_EESUPP,EEPROM_EESUPP_ERETRY_MASK) ) )
      {

          SET_BIT(EEPROM_EESUPP,EEPROM_EESUPP_START_MASK);

      }



    /*
     * Setting bit 0 in SREEPROM to start reset operation
     * Polling on  bit 0 in  PREEPROM to ensure that peripherals are ready
     * Clear bit 0 in SREEPROM to end reset operation
     */
      SET_BIT(EEPROM_SREEPROM,EEPROM_SREEPROM_RO_MASK);
     // while( BIT_IS_CLEAR(EEPROM_PREEPROM,EEPROM_PREEPROM_RO_MASK) ); // Infinite loop
      CLEAR_BIT(EEPROM_SREEPROM,EEPROM_SREEPROM_RO_MASK);



      delay_ms(0.0005);//MUST DELAY 6 CYCLES  //MUST DELAY 6 CYCLES + function overhead


      while (BIT_IS_SET(EEPROM_EEDONE,EEPROM_EEDONE_WORKING_MASK)); //Polling until working bit is set

      /*
        * Polling on  PRETRY,ERETRY Flags until they are cleared (Operation is done Successfully)
        */
            while ( (BIT_IS_SET(EEPROM_EESUPP,EEPROM_EESUPP_PRETRY_MASK) ) || (BIT_IS_SET(EEPROM_EESUPP,EEPROM_EESUPP_ERETRY_MASK) ) )
            {

                SET_BIT(EEPROM_EESUPP,EEPROM_EESUPP_START_MASK);

            }



//     while((EEPROM_EEDONE&&0x00000001)==1);//CHEKING EEPROM EEDONE MUST 1 BIT =1
//
//     if ((EEPROM_EESUPP&&(0x0C))!= 0x00){
//    P_E_Retry_Status = 1;
//    }

 }
 


 void EEPROMMassErase(void)
 {


 }


 void EEPROMRead(int* Data,int Address ,int word_Count)

 {

//set offset and block and go to eerdwe wor r and return it if needed


// Set the block and offset appropriately to read Specified address.
    EEPROM_EEBLOCK = EEPROM_BLOCK_FROM_ADDRESS(Address);
    EEPROM_EEOFFSET = OFFSET_FROM_ADDRESS(Address);

    //
    // Convert the byte count to a word count.
    //
     // Count /= 4;
    // Read each word in turn.
    //
    while( word_Count != 0)
    {
        //
        // Read the next word through the autoincrementing register.
        //
          *Data = EEPROM_EERDWRINC;

          /*
           * Polling on  PRETRY,ERETRY Flags until they are cleared (Operation is done Successfully)
           */

          while ( (BIT_IS_SET(EEPROM_EESUPP,EEPROM_EESUPP_PRETRY_MASK) ) || (BIT_IS_SET(EEPROM_EESUPP,EEPROM_EESUPP_ERETRY_MASK) ) )
                {

                    SET_BIT(EEPROM_EESUPP,EEPROM_EESUPP_START_MASK);

                }

        /*
         * Incrementing the data pointer to point to the next adrress in the array
         * Decrement count of words
         */

         Data++;

         word_Count--;

        //
        // Do we need to move to the next block?  This is the case if the
        // offset register has just wrapped back to 0.  Note that we only
        // write the block register if we have more data to read.  If this
        // register is written, the hardware expects a read or write operation
        // next.  If a mass erase is requested instead, the mass erase will
        // fail.
        //

        if( ( EEPROM_EEOFFSET & EEPROM_EEOFFSET_OFFSET_MASK ) == 0)
        {
            EEPROM_EEBLOCK += 1;
        }

        else
        {

        }
    }
		
 }


  int EEPROM_Write(int* Data, int Address,int word_Count)
 
 {

 //uint32 Status;


// do
//    {
//        //
//        // Read the status.
//        //
//
//     /*
//      *   Check on the other flags in EEDONE  (RAFAHYAT) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//      */
//         Status = EEPROM_EEDONE;
//    }
//    while( BIT_IS_SET(EEPROM_EEDONE,EEPROM_EEDONE_WORKING_MASK) );

 while( BIT_IS_SET(EEPROM_EEDONE,EEPROM_EEDONE_WORKING_MASK) );



    //
    // Set the block and offset appropriately to program the first word.
    //
    (EEPROM_EEBLOCK) =  EEPROM_BLOCK_FROM_ADDRESS(Address);
    (EEPROM_EEOFFSET) = OFFSET_FROM_ADDRESS(Address);

    /*
               * Polling on  PRETRY,ERETRY Flags until they are cleared (Operation is done Successfully)
               */

              while ( (BIT_IS_SET(EEPROM_EESUPP,EEPROM_EESUPP_PRETRY_MASK) ) || (BIT_IS_SET(EEPROM_EESUPP,EEPROM_EESUPP_ERETRY_MASK) ) )
                    {

                        SET_BIT(EEPROM_EESUPP,EEPROM_EESUPP_START_MASK);

                    }


    //
    // Convert the byte count to a word count.
    //
   // ui32Count /= 4;

    //
    // Write each word in turn.
    //

while(word_Count != 0)//still there counting till finish
    {

        // Write the next word through the auto incrementing register.

        (EEPROM_EERDWRINC) = *Data;

         delay_ms(0.0005);

//        do
//            {
//                //
//                // Read the status.
//                //
//
//             /*
//              *   Check on the other flags in EEDONE  (RAFAHYAT) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//              */
//                 Status = EEPROM_EEDONE;
//            }
//            while( BIT_IS_SET(EEPROM_EEDONE,EEPROM_EEDONE_WORKING_MASK) );

        while( BIT_IS_SET(EEPROM_EEDONE,EEPROM_EEDONE_WORKING_MASK) );


        //
        // Move on to the next word.
        //
        Data++;
        word_Count--;

        if( ( EEPROM_EEOFFSET & EEPROM_EEOFFSET_OFFSET_MASK ) == 0)
                {
                    EEPROM_EEBLOCK += 1;
                }

                else
                {

                }



    }



   return((EEPROM_EEDONE));

 }

 
 /////////////////////////////////////////////////////////////////////////////////////////////
