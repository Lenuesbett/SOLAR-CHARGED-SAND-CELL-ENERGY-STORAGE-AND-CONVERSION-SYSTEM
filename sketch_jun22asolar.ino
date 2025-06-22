#define SOLAR_VOLTAGE_PIN A0
#define TEMP_SENSOR_PIN A1
#define RELAY_PIN 7
#define HEATER_PIN 6

float readTemperature() {
  int analogVal = analogRead(TEMP_SENSOR_PIN);
  float voltage = (analogVal / 1023.0) * 5.0;
  float tempC = voltage * 100.0; // For LM35: 10mV/°C
  return tempC;
}

float readSolarVoltage() {
  int analogVal = analogRead(SOLAR_VOLTAGE_PIN);
  return (analogVal / 1023.0) * 12.0; // Assuming a divider to scale 12V
}

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(HEATER_PIN, LOW);
}

void loop() {
  float solarV = readSolarVoltage();
  float temp = readTemperature();

  Serial.print("Solar V: ");
  Serial.print(solarV);
  Serial.print(" V | Temp: ");
  Serial.print(temp);
  Serial.println(" C");

  // Charging condition
  if (solarV > 5.5 && temp < 80.0) {
    digitalWrite(HEATER_PIN, HIGH); // Heat the sand
  } else {
    digitalWrite(HEATER_PIN, LOW);
  }

  // Discharge condition (e.g., after sunset)
  if (solarV < 2.0 && temp > 60.0) {
    digitalWrite(RELAY_PIN, HIGH); // Supply energy to output
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  delay(1000);
}
