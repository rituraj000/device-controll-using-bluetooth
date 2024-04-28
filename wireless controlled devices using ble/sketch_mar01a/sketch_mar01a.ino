#define echoPin  PA_3 
#define trigPin  PA_4 
#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 
         
long duration;  
int distance;
void setup()
{
    pinMode(trigPin,OUTPUT); 
    pinMode(echoPin, INPUT);
    pinMode(5,OUTPUT); 
      myservo.attach(31);  // attaches the servo on Port F, pin 1 (Red LED pin) to the servo object
  dht.begin();

    Serial.begin(9600);
    Serial1.begin(9600);
}
void loop()
{
    delay(2000);

    float t = dht.readTemperature();
Serial1.print((" Temperature: "));
  Serial1.print(t);
  Serial1.print(("°C "));
  if(t>30)
  {
        digitalWrite(5,HIGH);
  Serial1.println("  BUZZER ON");

  }
  else
  {
    digitalWrite(5,LOW);
      Serial1.println("  BUZZER OFF");

  }
  digitalWrite(trigPin, LOW);
    delay(20); 
    digitalWrite(trigPin,HIGH); 
    delay(20); 
    digitalWrite(trigPin,LOW); 
    duration = pulseIn(echoPin, HIGH);
    distance= duration * 0.03 / 2;  
if(distance <10)
    {
     Serial1.print("Distance: ");
    Serial1.print(distance); // Print the output in serial monitor
    Serial1.print(" cm");
    myservo.write(180);              // tell servo to go to position in variable 'pos' 
    Serial1.println("   Gate is Opened");
    }
    else
    {
     Serial1.print("Distance: ");
    Serial1.print(distance); // Print the output in serial monitor
    Serial1.println(" cm");
        myservo.write(00);              // tell servo to go to position in variable 'pos' 
    Serial1.println("Gate is closed");
    }
    if(Serial1.available())
    {
    char a= Serial1.read();
    if(a=='A')
{
        myservo.write(180);              // tell servo to go to position in variable 'pos' 

    }
    else if(a=='B')
    {
          myservo.write(00);              // tell servo to go to position in variable 'pos' 

    }
}
}
