const int sensorpin = A0;
const int sensorpower = 8; // Pin D8 controls power to the sensor (VCC)
const int LED1 = 2;        // Red LED (Dry/Alarm)
const int LED2 = 3;        // Yellow LED (Optimal/Warning)
const int LED3 = 4;        // Green/Blue LED (Wet/Safe)
const int BUZZER_PIN = 5;  // Pin D5 for the audible alarm

int sensor;

const int delayTime = 1000; 

// "wet" and "dry" thresholds - these require calibration
// Note: Assuming analogRead returns a HIGH value when the soil is DRY.
int wet = 800;
int dry = 500;

void setup(){ // code that only runs once
  // set pins as outputs
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(sensorpower,OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT); // Set up the buzzer pin
  
  // initialize serial communication
  Serial.begin(9600);
}

void loop(){ // code that loops forever
  // power on sensor and wait briefly (corrosion prevention)
  digitalWrite(sensorpower,HIGH);
  delay(10);
  // take reading from sensor
  sensor = analogRead(sensorpin);
  // turn sensor off to help prevent corrosion
  digitalWrite(sensorpower,LOW);
  
  // print sensor reading
  Serial.println(sensor);
  
  // If sensor reading is greater than "wet" threshold (meaning the soil is very WET),
  // turn on the Green/Blue LED.
  if(sensor > wet){
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH); // Green/Blue LED ON (WET/SAFE)
    noTone(BUZZER_PIN);
  }
  // If it is less than the "dry" threshold, turn on the Red LED and sound the buzzer.
  else if(sensor < dry){
    digitalWrite(LED1,HIGH); // Red LED ON (DRY/ALARM)
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    tone(BUZZER_PIN, 1000); // Buzzer ON at 1000Hz [1]
  }
  // If it is in between the two values, turn on the Yellow LED.
  else{
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH); // Yellow LED ON (OPTIMAL/WARNING)
    digitalWrite(LED3,LOW);
    noTone(BUZZER_PIN);
  }
  
  // wait before taking next reading
  delay(delayTime);
  
}