#include <Arduino_EdgeControl.h>

constexpr unsigned int calibResistor { 7870 };
double val;
float volt;
float ntu;
void setup()
{
  Serial.begin(115200);

  auto startNow = millis() + 2500;
  while (!Serial && millis() < startNow)
    ;

  EdgeControl.begin();
  delay(2000);

  Serial.println("Hello, 10k");

  Power.on(PWR_3V3);
  Power.on(PWR_VBAT);

  Wire.begin();
  delay(500);

  Serial.print("Waiting for IO Expander Initialization...");
  while (!Expander.begin()) {
    Serial.print(".");
    delay(250);
  }
  Serial.println(" done.");

  Watermark.begin();
  Serial.println("Watermark OK");

  Watermark.calibrationMode(OUTPUT);
  Watermark.calibrationWrite(LOW);

  Watermark.commonMode(OUTPUT);
  Watermark.commonWrite(HIGH);

}

void loop()
{
  Watermark.enable();
  val = Watermark.analogRead(WATERMARK_CH01);

  float voltage = val * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.print("Turbidity Sensor Reading = ");
  Serial.print(voltage); // print out the value you read:
  Serial.println("  V");
  Watermark.disable();
  delay(1000);

}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
