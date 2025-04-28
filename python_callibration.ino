
 
 
 /*
 * RocketTestStand
 *
 * Device for gathering and logging thrust data for rocket motors
 */

/* INCLUDES */
#include <SPI.h>

/* DEFINES */
#define NEWTONS_PER_COUNT (0.0728 * 0.0098)
#define DEBUG (true)

/* GLOBAL VARIABLES */
const int dataPin = A5;
const int clkPin = A4;

unsigned long int zero_point = 0;

/* FUNCTIONS */
unsigned long int measure() {
  unsigned char i;    
  unsigned long int count = 0;
  while (digitalRead(dataPin) == HIGH)
    ;
  // read the value:
  for (int i = 0; i < 24; i++) {
    digitalWrite(clkPin, HIGH); 
    count = count << 1;
    digitalWrite(clkPin, LOW);
    if (digitalRead(dataPin))
      count++;
  }
  digitalWrite(clkPin, HIGH);
  count = count ^ 0x800000;
  digitalWrite(clkPin, LOW);
  if (count < zero_point) {
    count = zero_point;
  }
  return count;
}

void set_zero_point() {
  unsigned char i;
  unsigned long int val = 0;
  for (i = 0; i < 100; i++) {
    val += measure();
  }
  zero_point = val / 100;
  Serial.print("Zero Point found: ");
  Serial.println(val);
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(clkPin, OUTPUT);
  pinMode(dataPin, INPUT);
  digitalWrite(clkPin, LOW);

  Serial.println("Initializing...");

  // Zero the scale
  set_zero_point();
}

void loop() {
  float newtons;

  Serial.println("Logging data...");

  // CONTINUOUSLY LOG DATA s
  while (true) {
    newtons = NEWTONS_PER_COUNT * ((float)(measure() - zero_point));
    // make a string for assembling the data to log:
    String dataString = "";
    String t_str = String(millis() / 1000.0, 10); // 10 decimal places for seconds
    dataString.concat(t_str);
    dataString.concat("\t");  // Using a tab character for separation as per your example
    dataString.concat(String(newtons, 10)); // 10 decimal places for newtons
    Serial.println(dataString);

    // Add a delay here if needed
  }
}
