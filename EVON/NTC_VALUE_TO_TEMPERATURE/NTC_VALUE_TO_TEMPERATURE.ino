#define thermistorPin 4
void setup() {
  pinMode(thermistorPin,INPUT);
  Serial.begin(9600);
  analogReadResolution(10); // Set the ADC resolution to 12 bits
}

void loop() {
  float value = analogRead(thermistorPin);
  float vout = ((float)value / 1024) * 3.3*1000;
  float temperature = (float)vout/10;
  float fahrenheit = (float)temperature*(9/5)+32;
  Serial.print("Raw value: ");
  Serial.println(value);
  Serial.print("Vout(mv) = ");
  Serial.println(vout);
  Serial.print("Temperature: ");
  Serial.println(temperature);//Here 10mv is for every degree celsius.
  Serial.print("Farenheit: ");
  Serial.println(fahrenheit);
  delay(500);
}