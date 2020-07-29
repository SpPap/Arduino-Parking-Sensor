int echoPin = 2;
int trigPin = 3;
int redPin;
int greenPin;
int yellowPins[] = {};

 void setup()
{

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
}

void loop()
{

    long duration = 0, distanceCM = 0;

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

    Serial.print("Distance: ");
    Serial.print(distanceCM);
    Serial.print(" cm\n");
}