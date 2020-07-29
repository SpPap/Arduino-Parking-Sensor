#include <LiquidCrystal.h>

int echoPin = 2;
int trigPin = 3;
int speakerPin = 5;
int redPin = 4;
int greenPin = 1;
int yellowPins[] = {6, 7};
int rs = 12;
int enable = 13;
int d4 = 8, d5 = 9, d6 = 10, d7 = 11;

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    for (int i = 4; i <= 7; i++)
        pinMode(i, OUTPUT);
}

void loop()
{

    long duration = 0, distanceCM = 0;
    long FirstWarningDistance = 50;
    long SecondWarningDistance = 30;
    long ThirdWarningDistance = 20;
    long maxDistance = 10;
    int lcd_dt = 250; //delay time (LCD)

    //clear trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    //wave for 10 us
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    //echoPin reads wave travel time in us
    duration = pulseIn(echoPin, HIGH);

    distanceCM = 0.017 * duration;

    if (distanceCM <= maxDistance)
    {
        finalWarning();
        }
    else if (distanceCM <= ThirdWarningDistance)
    {
        thirdWarning(distanceCM, ThirdWarningDistance);
        redBlink(distanceCM, ThirdWarningDistance);
    }
    else if (distanceCM <= SecondWarningDistance)
    {
        secondWarning();
    }
    else if (distanceCM <= FirstWarningDistance)
    {
        firstWarning();
    }
    else
    {
        noWarning();
    }

    //LCD printing
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(distanceCM);
    lcd.print(" cm");
    delay(lcd_dt);
    lcd.clear();

    //Serial Monitor printing
    Serial.print("Distance: ");
    Serial.print(distanceCM);
    Serial.print(" cm\n");
}

void firstWarning()
{
    analogWrite(speakerPin, 0);
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPins[0], HIGH);
    digitalWrite(yellowPins[1], LOW);
    digitalWrite(redPin, LOW);
}

void secondWarning()
{
    analogWrite(speakerPin, 0);
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPins[0], HIGH);
    digitalWrite(yellowPins[1], HIGH);
    digitalWrite(redPin, LOW);
}

void thirdWarning(long distance, long thirdWarningValue)
{
    int dt = 100;
    while(distance <= thirdWarningValue){
        analogWrite(speakerPin, 100);
        delay(dt);
        analogWrite(speakerPin, 0);

        break;
    }
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPins[0], HIGH);
    digitalWrite(yellowPins[1], HIGH);
    digitalWrite(redPin, LOW);
}

void finalWarning()
{
    analogWrite(speakerPin, 100);
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPins[0], HIGH);
    digitalWrite(yellowPins[1], HIGH);
    digitalWrite(redPin, HIGH);
}

void noWarning()
{
    analogWrite(speakerPin, 0);
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPins[0], LOW);
    digitalWrite(yellowPins[1], LOW);
    digitalWrite(redPin, LOW);
}

void redBlink(long distance, long maxValue)
{

    int dt = 50;
    while (distance <= maxValue)
    {
        digitalWrite(redPin, HIGH);
        delay(dt);
        digitalWrite(redPin, LOW);
        delay(dt);

        break;
    }
}
