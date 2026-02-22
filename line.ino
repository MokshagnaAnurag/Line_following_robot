// Line Following Robot for Arduino Uno
// IR Sensor Configuration:
// - Left IR Sensor: Digital Pin 2
// - Right IR Sensor: Digital Pin 3
// Motor Configuration:
// - Motor A (Left): Enable Pin 5 (PWM), Input1: Pin 8, Input2: Pin 9
// - Motor B (Right): Enable Pin 6 (PWM), Input3: Pin 10, Input4: Pin 11

// Motor Pin Definitions
#define MOTOR_A_EN 5      // PWM pin for Motor A (left)
#define MOTOR_A_IN1 8     // Motor A direction control 1
#define MOTOR_A_IN2 9     // Motor A direction control 2

#define MOTOR_B_EN 6      // PWM pin for Motor B (right)
#define MOTOR_B_IN3 10    // Motor B direction control 1
#define MOTOR_B_IN4 11    // Motor B direction control 2

// Sensor Pin Definitions
#define LEFT_SENSOR 2     // Left IR sensor
#define RIGHT_SENSOR 3    // Right IR sensor

// Speed Constants
#define MAX_SPEED 255
#define BASE_SPEED 200
#define TURN_SPEED 150

void setup() {
  // Initialize motor pins as outputs
  pinMode(MOTOR_A_EN, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  
  pinMode(MOTOR_B_EN, OUTPUT);
  pinMode(MOTOR_B_IN3, OUTPUT);
  pinMode(MOTOR_B_IN4, OUTPUT);
  
  // Initialize sensor pins as inputs
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
  
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Line Following Robot Initialized");
  
  // Small delay to ensure stability
  delay(1000);
}

void loop() {
  // Read sensor values (HIGH = white/no line, LOW = black/line)
  int leftSensor = digitalRead(LEFT_SENSOR);
  int rightSensor = digitalRead(RIGHT_SENSOR);
  
  // Debug output
  Serial.print("Left: ");
  Serial.print(leftSensor);
  Serial.print(" | Right: ");
  Serial.println(rightSensor);
  
  // Line following logic
  if (leftSensor == LOW && rightSensor == LOW) {
    // Both sensors on line - move forward
    moveForward(BASE_SPEED);
  }
  else if (leftSensor == LOW && rightSensor == HIGH) {
    // Left sensor on line, right sensor off - turn left
    turnLeft(TURN_SPEED);
  }
  else if (leftSensor == HIGH && rightSensor == LOW) {
    // Right sensor on line, left sensor off - turn right
    turnRight(TURN_SPEED);
  }
  else {
    // Both sensors off line - stop (or implement search pattern)
    stopRobot();
  }
  
  delay(50); // Small delay for sensor stability
}

// Move forward at specified speed
void moveForward(int speed) {
  // Motor A (Left) - Forward
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_A_EN, speed);
  
  // Motor B (Right) - Forward
  digitalWrite(MOTOR_B_IN3, HIGH);
  digitalWrite(MOTOR_B_IN4, LOW);
  analogWrite(MOTOR_B_EN, speed);
}

// Move backward at specified speed
void moveBackward(int speed) {
  // Motor A (Left) - Backward
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  analogWrite(MOTOR_A_EN, speed);
  
  // Motor B (Right) - Backward
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, HIGH);
  analogWrite(MOTOR_B_EN, speed);
}

// Turn left (left motor slower/stopped, right motor faster)
void turnLeft(int speed) {
  // Motor A (Left) - Slow/Stop
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_A_EN, speed / 2);
  
  // Motor B (Right) - Full speed
  digitalWrite(MOTOR_B_IN3, HIGH);
  digitalWrite(MOTOR_B_IN4, LOW);
  analogWrite(MOTOR_B_EN, speed);
}

// Turn right (left motor faster, right motor slower/stopped)
void turnRight(int speed) {
  // Motor A (Left) - Full speed
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_A_EN, speed);
  
  // Motor B (Right) - Slow/Stop
  digitalWrite(MOTOR_B_IN3, HIGH);
  digitalWrite(MOTOR_B_IN4, LOW);
  analogWrite(MOTOR_B_EN, speed / 2);
}

// Stop all motors
void stopRobot() {
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_A_EN, 0);
  
  digitalWrite(MOTOR_B_IN3, LOW);
  digitalWrite(MOTOR_B_IN4, LOW);
  analogWrite(MOTOR_B_EN, 0);
}
