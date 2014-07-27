/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#include <stdint.h>
#include "TouchScreen.h"

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define DARK_GREY  0x7BEF
#define LIGHT_GREY 0xBDF7

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

float average = 0;

int num = 0;
int cur = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("ILI9341 Test!");

    tft.begin();
    tft.fillRect(0,0,240,320, BLACK);
    
    tft.fillRect(0,0, 240, 50, BLACK);
    tft.fillRect(0,50,240,50, RED);
    tft.fillRect(0,100, 240, 50, YELLOW);
    tft.fillRect(0,150, 240, 50, WHITE);
    tft.fillRect(0,200, 240, 50, GREEN);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(100, 20);
    tft.print("1");
    tft.setCursor(100, 70);
    tft.print("2");
    tft.setCursor(100,120);
    tft.setTextColor(BLACK);
    
    tft.print("3");
    tft.setCursor(100,170);
    tft.print("4");
    tft.setCursor(100,220);
    tft.print("5");
}


void loop(void) {


  TSPoint p = ts.getPoint();

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
    if (p.z > ts.pressureThreshhold) {
        Serial.print("X = "); Serial.print(p.x);
        Serial.print("\tY = "); Serial.print(p.y);
        Serial.print("\tPressure = "); Serial.println(p.z);
        
        if(p.y <= 150)
        {
            Serial.println("1");
            avg(average, num, 1);
        
        }
        else if(p.y <= 300)
        {
            Serial.println("2");
            avg(average, num, 2);
        }
        else if(p.y <= 450)
        {
            Serial.println("3");
            avg(average, num, 3);
        }
        else if(p.y <= 600)
        {
            Serial.println("4");
            avg(average, num, 4);
        }
        else if(p.y <= 750)
        {
            Serial.println("5");
            avg(average, num, 5);
        }
        else Serial.print("0");
    
        tft.setTextSize(2);
        tft.setCursor(50, 270);
        if(average <= 0.5)
        {
            tft.fillRect(10, 260, 220, 50, BLACK);
            tft.setTextColor(WHITE);
            tft.print("Average: ");
            tft.print(average);
        }
        else if(average <=1.5)
        {
            tft.fillRect(10, 260, 220, 50, RED);
            tft.setTextColor(WHITE);
            tft.print("Average: ");
            tft.print(average);
        }
        else if(average <=2.5)
        {
            tft.fillRect(10, 260, 220, 50, YELLOW);
            tft.setTextColor(BLACK);
            tft.print("Average: ");
            tft.print(average);
        }
        else if(average <= 3.5)
        {
            tft.fillRect(10, 260, 220, 50, WHITE);
            tft.setTextColor(BLACK);
            tft.print("Average: ");
            tft.print(average);
        }
        else if(average <= 4.5)
        {
            tft.fillRect(10, 260, 220, 50, GREEN);
            tft.setTextColor(BLACK);
            tft.print("Average: ");
            tft.print(average);
        }
        
        Serial.print("Average ");
        Serial.println(average);
        Serial.print("Number ");
        Serial.println(num);
    }
    delay(100);
}
float avg( float p, int n, int c)
{
    Serial.println("p,n,c");
    Serial.print(p); Serial.print(n); Serial.println(c);
    float a = (p * n);
    Serial.print("a="); Serial.println(a);
    float b = a + c;
    Serial.print("b="); Serial.println(b);
    float d = n + 1;
    Serial.println("d="); Serial.print(d);
    float avg = b / d;
    Serial.print("avg="); Serial.println(avg);
    average = avg;
    Serial.print("average");
    Serial.println(average);
    num = n+1;
    cur = c;
    
    return avg;
}
