
#define SENSOR1 0
#define SENSOR2 1

long currentMillis1 = 0;
long previousMillis1 = 0;
int interval = 1000;
long currentMillis2 = 0;
long previousMillis2 = 0;
float calibrationFactor = 4.5;
volatile byte pulseCount1;
byte pulse1Sec1 = 0;
float flowRate1;
unsigned int flowMilliLitres1;
unsigned long totalMilliLitres1;
volatile byte pulseCount2;
byte pulse1Sec2 = 0;
float flowRate2;
unsigned int flowMilliLitres2;
unsigned long totalMilliLitres2;

void pulseCounter1()
{
  pulseCount1++;
}

void pulseCounter2()
{
  pulseCount2++;
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR1, INPUT_PULLUP);
  pinMode(SENSOR2, INPUT_PULLUP);

  pulseCount1 = 0;
  flowRate1 = 0.0;
  flowMilliLitres1 = 0;
  totalMilliLitres1 = 0;
  previousMillis1 = 0;

  pulseCount2 = 0;
  flowRate2 = 0.0;
  flowMilliLitres2 = 0;
  totalMilliLitres2 = 0;
  previousMillis2 = 0;

  attachInterrupt(digitalPinToInterrupt(SENSOR1), pulseCounter1, FALLING);
  attachInterrupt(digitalPinToInterrupt(SENSOR2), pulseCounter2, FALLING);
}
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);
  currentMillis1 = millis();
  if (currentMillis1 - previousMillis1 > interval) {
    pulse1Sec1 = pulseCount1;
    pulseCount1 = 0;
    flowRate1 = ((1000.0 / (millis() - previousMillis1)) * pulse1Sec1) / calibrationFactor;
    previousMillis1 = millis();

  }
  currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 > interval) {
    pulse1Sec2 = pulseCount2;
    pulseCount2 = 0;
    flowRate2 = ((1000.0 / (millis() - previousMillis2)) * pulse1Sec2) / calibrationFactor;
    previousMillis2 = millis();
  }

  // Print the flow rate for this second in litres / minute
  Serial.print("Water In Flow rate: ");
  Serial.print(int(flowRate1));  // Print the integer part of the variable
  Serial.print("L/min");
  Serial.print("\t");        // Print tab space
  
  // Print the flow rate for this second in litres / minute
  Serial.print("Water Out Flow rate: ");
  Serial.print(int(flowRate2));  // Print the integer part of the variable
  Serial.println("L/min");
  // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
}
