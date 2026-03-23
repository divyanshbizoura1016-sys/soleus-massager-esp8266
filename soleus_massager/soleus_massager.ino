// -------------------------------
// Soleus Massager - ESP8266
// Adjustable Inflation Time
// -------------------------------

// Pin Definitions
const int pumpPin = D5;
const int solenoidPin = D6;
const int powerSwitch = D2;
const int incButton = D7;
const int decButton = D8;

// Timing (in milliseconds)
int inflateTime = 10000;   // Default 10 sec
int deflateTime = 15000;   // Fixed 15 sec

// Limits
const int minTime = 5000;   // 5 sec
const int maxTime = 20000;  // 20 sec

void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);

  pinMode(powerSwitch, INPUT);
  pinMode(incButton, INPUT);
  pinMode(decButton, INPUT);

  digitalWrite(pumpPin, LOW);
  digitalWrite(solenoidPin, LOW);

  Serial.begin(9600);
}

void loop() {

  // Check ON/OFF switch
  if (digitalRead(powerSwitch) == HIGH) {

    // -------- Button Controls --------
    if (digitalRead(incButton) == HIGH) {
      inflateTime += 1000;  // increase by 1 sec
      if (inflateTime > maxTime) inflateTime = maxTime;
      delay(200); // debounce
    }

    if (digitalRead(decButton) == HIGH) {
      inflateTime -= 1000;  // decrease by 1 sec
      if (inflateTime < minTime) inflateTime = minTime;
      delay(200); // debounce
    }

    // -------- Inflate --------
    digitalWrite(solenoidPin, LOW);   // Close valve
    digitalWrite(pumpPin, HIGH);      // Pump ON
    delay(inflateTime);

    // -------- Deflate --------
    digitalWrite(pumpPin, LOW);       // Pump OFF
    digitalWrite(solenoidPin, HIGH);  // Valve OPEN
    delay(deflateTime);

  } 
  else {
    // System OFF
    digitalWrite(pumpPin, LOW);
    digitalWrite(solenoidPin, LOW);
  }
}
