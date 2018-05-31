#include "libraries/TILCD.h"
#include "libraries/fontmap.h"

TILCD *lcd;
char l;
uint8_t i = 0;
uint8_t j = 0;
//                          "123456789abc"
static uint8_t message1[] = "  dat was   "; 
static uint8_t message2[] = "  ......fun ";
void setup()
{
    lcd = new TILCD(10, 12, A3, A0, A2, A1, 4, 5, 6, 7, 8, 9);
    lcd->init(48);
    for (int x = 0; x < 12; x++)
    {
        lcd->setX(x);
        for (int y = 0; y < 64; y++)
        {

            lcd->writeBinaryValue(1, 0);
        }
    }
    l = pgm_read_byte_near(FONTMAP);
    
}

void loop()
{
	//for(uint8_t i = 0; i < 255; i++){
        // Serial.println();
        // for(int y = 0; y < 8; y++){
        //     l = pgm_read_byte_near(FONTMAP + i*8 + y);
        //     for(int c = 7; c >= 0; c--){
        //         ((l >> c) & 1) ? Serial.print('#') : Serial.print(' ');
        //     }
        //     Serial.println();
        // }
        // delay(1000);
    i = j++;
	// for (int x = 0; x < 12; x++)
	// {
	// 	lcd->setX(x);
	// 	for (int y = 0; y < 64; y++)
	// 	{

	// 		lcd->writeBinaryValue(1, x);
	// 	}
	// }
    // for (int c = 0; c < 12; c++)
    // {
    //     lcd->setX(c);
    //     for(int r = 0; r < 8; r++){

    //         for(int y = 0; y < 8; y++){
    //             l = pgm_read_byte_near(FONTMAP + i*8 + y);
    //             lcd->writeBinaryValue(1, l);
    //         }
            
    //         i++;
    //     }
    // }
    for(int i = 0; i < 12; i++){
        delay(320);
        lcdputchar(message1[i], i, 3);
    }
    

    for(int i = 2; i < 12; i++){
        delay(320);
        lcdputchar(message2[i], i, 4);
    }
    //delay(500);
    //lcdputchar(3, 8, 2);
    delay(2000);
    for (int x = 0; x < 12; x++)
    {
        lcd->setX(x);
        for (int y = 0; y < 64; y++)
        {

            lcd->writeBinaryValue(1, 0);
        }
    }

    delay(2000);
}

void lcdputchar(uint8_t c, int x, int r){
    lcd->setX(x);
    lcd->setY(r*8);
    for(int y = 0; y < 8; y++){
        l = pgm_read_byte_near(FONTMAP + c*8 + y);
        lcd->writeBinaryValue(1, l);
    }
    
    return;
}