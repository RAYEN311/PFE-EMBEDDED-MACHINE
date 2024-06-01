// Define motor control pins
#define IN1 18
#define IN2 19
#define IN3 22
#define IN4 23

// Define step delay (milliseconds)
#define STEP_DELAY 50

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set all motor control pins to output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize motors to stop
  stopMotors();
}

// Function to move motors forward by a certain number of steps
void moveForward(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(STEP_DELAY);
  }
  stopMotors();
}

// Function to move motors backward by a certain number of steps
void moveBackward(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(STEP_DELAY);
  }
  stopMotors();
}

// Function to stop motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Function to parse and execute serial commands
void executeCommand(String command) {
  // Split the command into parts
  int spaceIndex = command.indexOf(' ');
  if (spaceIndex == -1) {
    Serial.println("Invalid command");
    return;
  }

  String action = command.substring(0, spaceIndex);
  int steps = command.substring(spaceIndex + 1).toInt();

  if (action == "FORWARD") {
    moveForward(steps);
    Serial.println("Motors moving forward " + String(steps) + " steps");
  } else if (action == "BACKWARD") {
    moveBackward(steps);
    Serial.println("Motors moving backward " + String(steps) + " steps");
  } else if (action == "STOP") {
    stopMotors();
    Serial.println("Motors stopped");
  } else {
    Serial.println("Unknown command");
  }
}

void loop() {
  // Check if there is any data available on the serial port
  if (Serial.available() > 0) {
    // Read the incoming command as a string
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove any leading/trailing whitespace

    // Execute the command
    executeCommand(command);
  }
}









// import serial
// import time

// # Replace 'COM3' with the appropriate port for your system
// ser = serial.Serial('COM3', 115200, timeout=1)

// def send_command(command):
//     ser.write((command + '\n').encode())
//     time.sleep(0.1)  # Small delay to ensure command is sent
//     response = ser.readline().decode().strip()
//     print(f"ESP32 Response: {response}")

// # Example usage
// if __name__ == "__main__":
//     try:
//         while True:
//             cmd = input("Enter command (e.g., FORWARD 100, BACKWARD 50, STOP): ")
//             send_command(cmd)
//     except KeyboardInterrupt:
//         print("Program terminated")
//     finally:
//         ser.close()

