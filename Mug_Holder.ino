// Very Cool Mug Holder to Keep you Hydratated

#define Led 3
#define Buzzer 5
#define Echo 7
#define Trigger 9

int distance;
long duration;
unsigned long previousMillis;
const long reminderInterval = 3600; // Change to the time in seconds when you want to be reminded to Drink 3600 is equal to an Hour and it's pretty fine.
bool glassOn = false;
bool Feedback = true;

void setup() {
  
 Serial.begin(9600);

 pinMode(Led, OUTPUT);
 pinMode(Buzzer, OUTPUT);
 pinMode(Echo, INPUT);
 pinMode(Trigger, OUTPUT);

 // Nice Feedback when plugging in the USB
 tone(Buzzer, 600, 800);
 digitalWrite(Led, HIGH);
 delay(100);
 tone(Buzzer, 800, 800);
 digitalWrite(Led, LOW);
 delay(100);
 tone(Buzzer, 600, 800);
 digitalWrite(Led, HIGH);
 delay(100);
 tone(Buzzer, 800, 800);
 digitalWrite(Led, LOW);
 
}

void loop() {

  // Enable the proximity Sensor to collect data
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);

  // Calculate distance from the proximity sensor
  duration = pulseIn(Echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(millis());
  
  // Glass On Audio Feedback, when we put the glass on the plate enable the feedback
  if (glassOn == false) {
    Feedback = true;
  }



 // Check if the Glass of Water is on the plate by checking it's distance from the proximity sensor
  if (distance <= 3) {

    // Plays a feedback sound when placing the glass on the plate
    if (Feedback == true) {
      tone(Buzzer, 700, 100);
      Feedback = false;
      delay(100);
    }

    // Turn of the Led and set the Glass is on State
    digitalWrite(Led, LOW);
    glassOn = true;
    Serial.println("Glass is On");
    delay(100);
    
  } else {

    // If the glass is not on, turn on the Led and set the Glass state
    digitalWrite(Led, HIGH);
    glassOn = false;
    Serial.println("Glass is Off");
    
  }

  
  // Compare the Arduino internal Timer with our Interval
  if (millis() - previousMillis >= reminderInterval * pow(10, 3)) {

    // Check if the glass is currently on the plate
    if (glassOn == true) {

      // When the glass is on and it's time to drink, play this little melody
      digitalWrite(Led, LOW);
      delay(100);
      tone(Buzzer, 600, 800);
      digitalWrite(Led, HIGH);
      delay(100);
      digitalWrite(Led, LOW);

      delay(100);
      tone(Buzzer, 800, 800);
      digitalWrite(Led, HIGH);
      delay(100);
      digitalWrite(Led, LOW);

      delay(250);
      tone(Buzzer, 600, 800);
      digitalWrite(Led, HIGH);
      delay(250);
      digitalWrite(Led, LOW);
      Serial.println("It's time to Drink some Water!");
      
      } else {

      // Otherwise if the glass is not on the plate reset the timer and turn off the led
      digitalWrite(Led, LOW);
      previousMillis = millis();  
    }  
  } 
}
