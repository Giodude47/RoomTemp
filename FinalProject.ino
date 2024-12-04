#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

// OLED display TWI address
int OLED_ADDR = 0x3C;

// Pin for the DHT11 sensor
int DHTPIN = 9;
DHT dht(DHTPIN, DHT11); // Initialize DHT sensor (DHT11 or DHT22)

// Pin for potentiometer
int POT_PIN = A0; // Potentiometer pin

Adafruit_SSD1306 display(-1);

void setup() {
  // Initialize the serial monitor
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();

  // Initialize and clear the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
}

void loop() {
  // Read the potentiometer value (0-1023)
  int potValue = analogRead(POT_PIN);

  // Map the potentiometer value to either 0 (temperature) or 1 (humidity)
  int displayState = map(potValue, 0, 1023, 0, 1); // 0 for temperature, 1 for humidity

  // Read temperature and humidity from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if the readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print readings to the serial monitor for debugging
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Clear the OLED display for the next update
  display.clearDisplay();

  // Set text properties
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Show either temperature or humidity depending on the potentiometer position
  if (displayState == 0) {
    // Display Temperature
    display.setCursor(0, 0);
    display.print("Temperature: ");
    display.print(temperature);
    display.println(" C");
  } else {
    // Display Humidity
    display.setCursor(0, 0);
    display.print("Humidity: ");
    display.print(humidity);
    display.println(" %");
  }

  // Update the OLED display
  display.display();

  // Wait a bit before the next reading
  delay(1000);
}