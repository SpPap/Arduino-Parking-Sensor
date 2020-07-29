int echoPin = 2;
int trigPin = 3;
int redPin = 4;
int greenPin = 5;
int yellowPins[] = {6, 7};

void setup()
{

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    for (int i = 4; i <= 7; i++)
        pinMode(i, OUTPUT);

    Serial.begin(9600);
}

void loop()
{

    long duration = 0, distanceCM = 0;
    long FirstWarningDistance = 100;
    long SecondWarningDistance = 50 ;
    long maxDistance = 20;

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
        digitalWrite(greenPin, HIGH);
        digitalWrite(yellowPins[0], HIGH);
        digitalWrite(yellowPins[1], HIGH);
        digitalWrite(redPin, HIGH);
    }
    else if (distanceCM <= SecondWarningDistance)
    {
        digitalWrite(greenPin, HIGH);
        digitalWrite(yellowPins[0], HIGH);
        digitalWrite(yellowPins[1], HIGH);
        digitalWrite(redPin, LOW);
    }
    else if (distanceCM <= FirstWarningDistance)
    {
        digitalWrite(greenPin, HIGH);
        digitalWrite(yellowPins[0], HIGH);
        digitalWrite(yellowPins[1], LOW);
        digitalWrite(redPin, LOW);
    }
    else
    {
        digitalWrite(greenPin, HIGH);
        digitalWrite(yellowPins[0], LOW);
        digitalWrite(yellowPins[1], LOW);
        digitalWrite(redPin, LOW);
    }

    Serial.print("Distance: ");
    Serial.print(distanceCM);
    Serial.print(" cm\n");
}