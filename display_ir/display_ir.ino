#include <IRremote.h>
#include <LiquidCrystal.h>

int power_state = LOW;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

decode_results results;


void setup()
{
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  lcd.begin(16, 2);
  lcd.print("yeeeeeeee");
}

void loop() {
  String command;

  lcd.display();
  if (irrecv.decode(&results)) {
    command = String(results.value, HEX);
    Serial.println(command);
    if(command == "ffa25d") {
      digitalWrite(12, !power_state);
      power_state = !power_state;
      digitalWrite(10, HIGH);
      delay(100);
      digitalWrite(10, LOW);
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
