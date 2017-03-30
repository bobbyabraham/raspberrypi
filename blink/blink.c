/* Code from http://wiringpi.com/examples/blink/
* Uses the WiringPi library
* to compile -> gcc -o blink blink.c -lwiringPi
*
* Blinks an LED wired up to a RaspberryPi
*/
#include <wiringPi.h>

int main(void){
 wiringPiSetup();
 pinMode(29, OUTPUT);

 for(;;){
   digitalWrite(29, HIGH); 
   delay(500);
   digitalWrite(29, LOW); 
   delay(500);
 }
 return 0;

}
