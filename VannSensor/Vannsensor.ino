// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define motor 10
#define bryter25 6
#define bryter50 7
#define bryter75 8
#define bryter100 9

String currentText;

void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    //leser av verdier på brytere
    pinMode(bryter25, INPUT);
    pinMode(bryter50, INPUT);
    pinMode(bryter75, INPUT);
    pinMode(bryter100, INPUT);

    pinMode(motor, OUTPUT);
}


//funksjon for skjerm og hva som ksal printes på skjermen
void skjerm(String text){
    if (text == currentText) return;
    currentText = text;

    lcd.clear();
    lcd.setCursor(0, 0);

    //printer til skjermen en basis text
    lcd.print("Vannnivaa:");
    lcd.setCursor(0, 1);

    //printer meldingen om statusen til vannet
    lcd.print(text);
}

void loop() {
    //setter en bollsk verdi på variablene for å få en true eller false verdi  
    bool vann25 = digitalRead(bryter25);
    bool vann50 = digitalRead(bryter50);
    bool vann75 = digitalRead(bryter75);
    bool vann100 = digitalRead(bryter100);

    //sjekker om det er vann i koppen, hvis det ikke er starter pumpen.
    if (!vann25 && !vann50 && !vann75 && !vann100)
    {
        digitalWrite(motor, HIGH);
        skjerm("Pumpe Gaar");
    }
    //sjekker etter feil
    else{
        if ((!vann25 && (vann50 || vann75 || vann100)) || (!vann50 && (vann75 || vann100)) || (!vann75 && vann100))
        {
            skjerm("Feil");
            digitalWrite(motor, LOW);
        }
        //hvis det er vann i koppen sjekker den nivået og displayer mengde
        else
        {
            skjerm(vann100 ? "100%" : vann75 ? "75%" : vann50 ? "50%" : vann25 ? "25%" : "0%");
            // digitalWrite(motor, LOW);
            //stopper pumpen når det er fult i koppen
            if (vann100 == true)
            {
                digitalWrite(motor, LOW);
            }
            
        }
    }
}