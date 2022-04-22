#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 //OLED skjerm bredde i pixler
#define SCREEN_HEIGHT 64 //OLED skjerm høyde i pixler

#define OLED_RESET 4 //reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup()
{
    display.begin(SSD1306_SWITCHAPVCC, 0x3D);
}

void loop(
    {
        display.clearDisplay();

        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 28);
        display.println("Hello World");
        display.display();
        delay(2000);
        display.clearDisplay();
    }
)