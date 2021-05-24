#include <Servo.h>
#include <DHT.h>
#include <DHT_U.h>

#define dhtpin 7
#define dhttype DHT22
#define RELAY4 4 //Defining the pin 4 of the Arduino for the 4 relay module

DHT dht(dhtpin, dhttype);
Servo myservo; // create servo object to control a servo

#define servopin 9

int pos = 0; // variable to store the servo position
int ledPin = 13;
int pirPin = 2;
int pirStat = 0;
int pir = 0;
int checker = 0;

void setup()
{
  myservo.attach(servopin);
  // attaches the servo on pin 9 to the servo object
  pinMode(pirPin, INPUT);

  dht.begin();
  pinMode(RELAY4, OUTPUT); //Defining the pin 4 of the Arduino as output
  pinMode(13, OUTPUT);     //Defining the pin 4 of the Arduino as output
  digitalWrite(13, HIGH);
  digitalWrite(RELAY4, HIGH);
  Serial.begin(9600);
  Serial.println("start");
  delay(1000);
}

void loop()
{

  float tempc = dht.readTemperature();
  pirStat = digitalRead(pirPin);

  if (tempc > 23)
  {
    digitalWrite(RELAY4, LOW);

    if (pirStat == HIGH )
    {
      myservo.write(10);
      digitalWrite(13, LOW);
      delay(15);
      digitalWrite(13, HIGH);
      delay(15);

      checker = 0;
    }
    else if (pirStat == LOW )
    {
      myservo.write(80);
      digitalWrite(13, LOW);
      delay(15);
      digitalWrite(13, HIGH);
      delay(15);

      checker = 1;
    }
  }
  else
  {
    digitalWrite(RELAY4, HIGH);
  }

  delay(1000);

  Serial.print("temperature currently is >> ");
  Serial.println(tempc);
  if (pirStat == HIGH)
    Serial.println("motion >> active");
  else if (pirStat == LOW)
    Serial.println("motion not active> ");
    Serial.println();

}
