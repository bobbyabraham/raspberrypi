/* Code from http://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-the-raspberry-pi/
* Modfied the dht11.c program to read from DHT22 sensor
* Uses Wiring Pi library
* To Compile -> gcc -o dht22 dht22.c -lwiringPi -lwiringPidev
*
* Reads in temperature and humidity from DHT22 sensor connected to a RaspberryPi
*/
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAXTIMINGS  85
#define DHTPIN      7
int dht11_dat[5] = { 0, 0, 0, 0, 0 };
 
void read_dht11_dat()
{
    uint8_t laststate   = HIGH;
    uint8_t counter     = 0;
    uint8_t j       = 0, i;
    float   f; 
    int temp;
 
    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
    pinMode( DHTPIN, OUTPUT );
    digitalWrite( DHTPIN, LOW );
    delay( 6 );
    digitalWrite( DHTPIN, HIGH );
    delayMicroseconds( 40 );
    pinMode( DHTPIN, INPUT );

    for ( i = 0; i < MAXTIMINGS; i++ )
    {
        counter = 0;
        while ( digitalRead( DHTPIN ) == laststate )
        {
            counter++;
            delayMicroseconds( 1 );
            if ( counter == 255 )
            {
                break;
            }
        }
        laststate = digitalRead( DHTPIN );
 
        if ( counter == 255 )
            break;
 
        if ( (i >= 4) && (i % 2 == 0) )
        {
            dht11_dat[j / 8] <<= 1;
            if ( counter > 16 )
                dht11_dat[j / 8] |= 1;
            j++;
        }
    }
 
    if ( (j >= 40) &&
         (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
    {
	temp = (dht11_dat[2] << 8 ) + dht11_dat[3];
	printf("Temp = %d\n", temp);
        f = (temp/10.0) * 9. / 5. + 32;
        printf( "Humidity = %d.%d %% Temperature = %.1f C (%.1f F)\n",
            dht11_dat[0], dht11_dat[1], (temp/10.0), f );
    }else  {
        printf( "Data not good, skip\n" );
    }
}
 
int main( void )
{
    printf( "Raspberry Pi wiringPi DHT11 Temperature test program\n" );
 
    if ( wiringPiSetup() == -1 )
        exit( 1 );
 
    while ( 1 )
    {
        read_dht11_dat();
        delay( 2000 ); 
    }
 
    return(0);
}
