#include <IRremote.h>
#include <LiquidCrystal.h>
#include <SimpleDHT.h>

int RECV_PIN = 11;
int pinDHT11 = 9;

SimpleDHT11 dht11;
IRrecv irrecv(RECV_PIN);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

decode_results results;

byte temperature = 0;
byte humidity = 0;
int power_state = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  lcd.begin(16, 2);
  lcd.print("Yeeeeeee");
}

void loop() {
  String command;
  lcd.display();

  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }

  if (irrecv.decode(&results)) {
    command = String(results.value, HEX);
    Serial.println(command);
    if(command == "ffa25d") {
      digitalWrite(12, !power_state);
      power_state = !power_state;
      if(power_state == LOW) {
        lcd.display().
      }
      digitalWrite(10, HIGH);
      delay(100);
      digitalWrite(10, LOW);
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
