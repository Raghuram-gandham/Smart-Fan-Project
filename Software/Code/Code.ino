// Pin configurations
#define TRIG_PIN 6
#define ECHO_PIN 7
#define ENABLE_PIN 5
#define INPUT1_PIN 3
#define INPUT2_PIN 4

// Distance threshold in centimeters 
const int DISTANCE_THRESHOLD = 40; 

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(INPUT1_PIN, OUTPUT);
  pinMode(INPUT2_PIN, OUTPUT);
  
  digitalWrite(INPUT1_PIN, LOW);
  digitalWrite(INPUT2_PIN, LOW);
  analogWrite(ENABLE_PIN, 0);
  
  Serial.println("Dual-Power Proximity Fan Initialized.");
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  
  int distance = duration * 0.034 / 2;
  
  if (distance > 0 && distance < 400) {
    Serial.print("Target Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    if (distance <= DISTANCE_THRESHOLD) {
      Serial.println("Target detected. Running fan at safe 9V scale...");
      
      digitalWrite(INPUT1_PIN, HIGH);
      digitalWrite(INPUT2_PIN, LOW);
      
      analogWrite(ENABLE_PIN, 160); 
    } 
    else {
      Serial.println("Clear. Fan idling...");
      
      // Turn off motor
      digitalWrite(INPUT1_PIN, LOW);
      digitalWrite(INPUT2_PIN, LOW);
      analogWrite(ENABLE_PIN, 0);
    }
  }
  
  delay(200); 
}
