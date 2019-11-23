/*
 * gps.c
 *
 * Author: Dawson Moore (11/10/2019)
 */

#include "gps.h"

/*
 * Function: gpsTask()
 *
 * Gathers pressure using raw temp and pressure for altitude
 * calculations
 * 
 * MTK Packet Format
 * $ | PTMK | ### | DATA | * | CHECKSUM | <CR><LF>
 * Preamble | Talker ID | Packet Type | Data Field | * | CHK1, CHK2 | CR, LF
 *
 */
void gpsTask()
{
    char * returnSentence = malloc(sizeof(char) * 86); //Max NMEA length *should be* 79 excluding CR, LF
    while (PSP == GREAT)
    {
        
    }
}

/*
 * Function gpsInit()
 * 
 * Initializes the GPS utilizing the cold start without time, 
 * position, almanacs, or ephemeris data at restart 
 * 
 * $ | PTMK | ### | DATA | * | CHECKSUM | <CR><LF>
 * Preamble | Talker ID | Packet Type | Data Field | * | CHK1, CHK2 | CR, LF
 * 
 * Note: Command 314 (Found at https://cdn-shop.adafruit.com/datasheets/PMTK_A11.pdf)
 * can set message frequency. I don't know what's needed, so they're all set to default (on)
 * right now.
 * 
 */
void gpsInit()
{
    char * cmdString = malloc(sizeof(char) * 23);
    if (cmdString == NULL)
    {
        //We have an issue. . .
        //Handle the error here and DO NOT FREE cmdString

        return;
    }
    cmdString = "$PMTK103*30<CR><LF>"; //Run from cold start
    HAL_USART_Transmit(GPS_UART, cmdString, 19, HAL_MAX_DELAY);
    cmdString = "$PMTK220,200*2C<CR><LF>"; //Run at 5 Hz
    HAL_USART_Transmit(GPS_UART, cmdString, 24, HAL_MAX_DELAY);
    cmdString = "$PMTK397,0.2*3F<CR><LF>"; //Set movement threshold to 0.2 m/s
    HAL_USART_Transmit(GPS_UART, cmdString, 23, HAL_MAX_DELAY);

    free(cmdString);

    //Look through the document above and decide what needs to be done and doesn't. The default
    //values seem pretty good, so I'm leaving them as is for the time being. It should be pretty
    //easy to replicate given the code I have here.
}