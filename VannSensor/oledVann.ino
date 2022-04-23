// include the library code:
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED skjerm bredde i pixler
#define SCREEN_HEIGHT 64 // OLED skjerm høyde i pixler

#define OLED_RESET 4 // reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// definerer motorer og brytere
#define motor 10
#define bryter25 6
#define bryter50 7
#define bryter75 8
#define bryter100 9

String currentText;

unsigned long sisteEndring = 0;

bool sisteStat[4] = {false, false, false, false};

void setup()
{
    display.begin(SSD1306_SWITCHAPVCC, 0x3D);

    // leser av verdier på brytere
    pinMode(bryter25, INPUT);
    pinMode(bryter50, INPUT);
    pinMode(bryter75, INPUT);
    pinMode(bryter100, INPUT);

    // deffinerer motor variablen
    pinMode(motor, OUTPUT);
}

void loop()
{
    // setter en bollsk verdi på variablene for å få en true eller false verdi
    bool vann25 = digitalRead(bryter25);
    bool vann50 = digitalRead(bryter50);
    bool vann75 = digitalRead(bryter75);
    bool vann100 = digitalRead(bryter100);

    bool pumpen = digitalRead(motor);

    OLED.clearDisplay();
    OLED.setTextSize(1);
    OLED.setColor(WHITE);
    OLED.setCursor(0, 0);

    // sjekker om det er vann i koppen, hvis det ikke er starter pumpen.
    if (!vann25 && !vann50 && !vann75 && !vann100)
    {
        digitalWrite(motor, HIGH);
        OLED.print("Pumpen går");
    }
    // sjekker etter feil
    else
    {
        if ((!vann25 && (vann50 || vann75 || vann100)) || (!vann50 && (vann75 || vann100)) || (!vann75 && vann100))
        {
            digitalWrite(motor, LOW);
            OLED.print("Feil i tanken");
        }
        // hvis det er vann i koppen sjekker den nivået og displayer mengde
        else
        {
            // sjekker om det kommer endringer på last state som er  3 sek
            if (!pumpen && ((!vann25 && sisteStat[0] != vann25) || (!vann50 && sisteStat[1] != vann50) || (!vann75 && sisteStat[2] != vann75) || (!vann100 && sisteStat[3] != vann100)))
            {
                // Sjekker om den sisteendingen øker sjappere enn Millis
                if (sisteEndring > millis())
                {
                    // viser til at motoren starter å går
                    digitalWrite(motor, HIGH);

                    // viser til skjerm at det er uvalig bruk
                    OLED.print("Uvanlig bruk av vann")

                        // viser til skjermen at pumpen starter
                        OLED.setCursor(1, 0);
                    OLED.print("Starter Pumpen");
                }

                //øker verdien på variablen siste endring, essensiell for at det skal funke med at den tømmes for fort
                sisteEndring = millis() + 3000;
            }
            else
            {
                OLED.print(vann100 ? "100%" : vann75 ? "75%"
                                          : vann50   ? "50%"
                                          : vann25   ? "25%"
                                                     : "0%");
                // stopper pumpen når det er fult i koppen
                if (vann100 == true)
                {
                    digitalWrite(motor, LOW);
                }
            }
            sisteStat[0] = vann25;
            sisteStat[1] = vann50;
            sisteStat[2] = vann75;
            sisteStat[3] = vann100;
        }
    }
    OLED.display();
    delay(5000);
}