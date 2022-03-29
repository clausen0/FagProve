// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//definerer motorer og brytere
#define motor 10
#define bryter25 6
#define bryter50 7
#define bryter75 8
#define bryter100 9

String currentText;

unsigned long sisteEndring = 0;

bool sisteStat[4] = {false, false, false, false};

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

    //tømmer teskt som står på skjermen
    lcd.clear();


    //printer til skjermen en basis text
    lcd.setCursor(0, 0);
    lcd.print("Vannnivaa:");

    //flytter til linjen under på LCD skjermen
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

    bool pumpen = digitalRead(motor);

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
            //sjekker om det kommer endringer på last state som er under 3 sek
            if(!pumpen &&((!vann25 && sisteStat[0] != vann25) || (!vann50 && sisteStat[1] != vann50) || (!vann75 && sisteStat[2] != vann75) || (!vann100 && sisteStat[3] != vann100))){
                //Sjekker om den sisteendingen øker sjappere enn Millis
                if(sisteEndring > millis()){
                    //viser til at motoren starter å går
                    digitalWrite(motor, HIGH);

                    //viser til skjerm at det er uvalig bruk
                    skjerm("Uvanlig Bruk");
                    delay(1000);

                    //viser til skjermen at pumpen starter
                    skjerm("Pumpen er starta");
                    delay(1000);
                }

                //øker verdien på variablen siste endring, essensiell for at det skal funke med at den tømmes for fort 
                sisteEndring = millis() + 3000;
            }
            else
            {
                skjerm(vann100 ? "100%" : vann75 ? "75%" : vann50 ? "50%" : vann25 ? "25%" : "0%");
                //stopper pumpen når det er fult i koppen
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
}