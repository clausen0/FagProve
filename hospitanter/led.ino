
// C++ code
//
//Her definerer vi hvilke pinner vi skal bruke.
//Vi velger også om de skal ta imot eller sende ut signaler.
void setup()
{
    pinMode(8, INPUT); //Nummeret er pinnen som er valgt, og INPUT betyr at den skal ta imot signaler.
    pinMode(9, OUTPUT); //Output betyr at pinnen skal sende ut signaler
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
}//Loopen er der hoveddelen av koden vår ligger.
void loop()
{
    if (digitalRead(8) == 1) { //Dette er en if-loop. Den sørger for at hvis det er signal på pin 8, vil den kjøre koden som er inne i loopen.
    digitalWrite(9, HIGH); //Her vil pin 9 sende ut et signal
    delay(500); //Vi tar en pause på 500 millisekunder, eller 0,5 sekunder
    digitalWrite(9, LOW); //Her skrur vi av signalet til pin 9, og på til 10
    digitalWrite(10, HIGH);
    delay(500); 
    digitalWrite(10, LOW); //10 skrus av, og 11 skrus på
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(11, LOW); //11 skrus av, og 12 skrus på
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(12, LOW);
    } else { //Her definerer vi hva som skjer om det ikke er signal på pin 8
    digitalWrite(9, LOW); // Da vil signalet til alle pinnene være av
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    }
}

