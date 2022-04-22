
//starter biblioteket for skjem
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


///deklarer knappe variablene
int UpButton = A1;
int DownButton = A2;
int SelectButton = A3;

//variablen peker på menyer og actions
int menu = 1;

//nødstopp og lys for nødstopp
int Ebrake = A0;
int LEDStopp = 10;

//inter diodene som skal bli brukt for pumpe og ventil
int LED1 = 7;
int LED2 = 6;

//setup for inganger og utganger
void setup(){
    lcd.begin(16, 2);
    pinMode(UpButton, INPUT_PULLUP);
    pinMode(DownButton, INPUT_PULLUP);
    pinMode(SelectButton, INPUT_PULLUP);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(Ebrake, INPUT);

    updateMenu();
}

//loopen hvor koden kjøres i

void loop(){
    bool down = !digitalRead(DownButton);
    bool up = !digitalRead(UpButton);
    bool select = !digitalRead(SelectButton);

    int EmergencyStopp;

    EmergencyStopp = digitalRead(Ebrake);

        if (EmergencyStopp == HIGH)
        {
            emergency();
        }
        else{
            if(down){ //neste meny
                menu++;
                updateMenu();
                delay(10);
                while(!digitalRead(DownButton));
            }

            if(up){ //forrige meny
                menu--;
                updateMenu();
                delay(10);
                while(!digitalRead(UpButton));
            }

            if(select){ //gjenomfører en action
                execute();
                updateMenu;
                delay(10);
                while(!digitalRead(SelectButton));
        }

    }
        
}
//oppdaterer hvilken meny som bir valgt med en switch case
void updateMenu(){
    switch (menu)
    {
    case 0:
        menu = 1;
        break;
    
    case 1:
        lcd.clear();
        lcd.print("> valve on");
        lcd.setCursor(0, 1);
        lcd.print(" Valve off");
        break;
    
    case 2:
        lcd.clear();
        lcd.print(" Valve on");
        lcd.setCursor(0, 1);
        lcd.print("> Valve off");
        break;
    
    case 3:
        lcd.clear();
        lcd.print("> Run pump");
        lcd.setCursor(0, 1);
        lcd.print(" stop pump");
        break;
    
    case 4:
        lcd.clear();
        lcd.print(" Run pump");
        lcd.setCursor(0, 1);
        lcd.print("> Stop pump");
        break;
    
    case 5:
        menu = 4;
        break;
    }
}

//Executer de actione som er under. blir valgt i casen over hvis select knappen blir trykket på.
void execute(){
    switch (menu)
    {
    case 1:
        action1();
        break;
    case 2:
        action2();
        break;
    case 3:
        action3();
        break;
    case 4:
        action4();
        break;
    }
}

//definerer hva actions i switch casen over er. Actionen fikser på lcd skejmern og hva de forskjellige actionene skal printe samt aktive de forskjellige releene.

void action1(){
    lcd.clear();
    lcd.print(">VALVE OPEN");
    delay(150);
    lcd.print(".");
    delay(150);
    lcd.print(".");
    delay(150);
    lcd.print(".");

    digitalWrite(LED1, HIGH);
    digitalWrite(LEDStopp, LOW);
    delay(500);
}
void action2(){
    lcd.clear();
    lcd.print(">VALVA CLOSE");
    delay(150);
    lcd.print(".");
    delay(150);
    lcd.print(".");
    delay(150);
    lcd.print(".");

    digitalWrite(LED1, LOW);
  	digitalWrite(LEDStopp, LOW);
    delay(500);
}
void action3(){
    lcd.clear();
    lcd.print(">PUMP ACTIVE");
    delay(150);
    lcd.print(".");
    delay(150);
    lcd.print(".");
    delay(150);
    lcd.print(".");

    digitalWrite(LED2, HIGH);
 	digitalWrite(LEDStopp, LOW);
    delay(500);
}
void action4(){
    lcd.clear();
    lcd.print(">PUMP STOPS");
    delay(150);
    lcd.print(".");
    delay(150);
    lcd.print(".");
    delay(150);
    lcd.print(".");

    digitalWrite(LED2, LOW);
  	digitalWrite(LEDStopp, LOW);
    delay(500);
}


//lager en funksjon for nødstopp
void emergency(){

     digitalWrite(LEDStopp, HIGH); // indikerer at stoppen er aktivert

     digitalWrite(LED1, LOW);
     digitalWrite(LED2, LOW);
}