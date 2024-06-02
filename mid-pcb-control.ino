#define IN1 18
#define IN2 19
#define IN3 22
#define IN4 23

#define STEP_DELAY 15
#define stop_step_delay 100

int countedX = 0 ;
int countedZ = 0 ;

bool finish = false ;

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();
}

void move(int steps_x ,int steps_z){
while(finish == false){
if(steps_x < countedX  && steps_x < 0){
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
delay(STEP_DELAY);
countedX = countedX - 1 ; 
}
stopMotors();
delay(stop_step_delay);
if(steps_x > countedX  && steps_x > 0){
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
delay(STEP_DELAY);
countedX = countedX + 1 ; 
}
stopMotors();
delay(stop_step_delay);
if(steps_z < countedZ  && steps_z < 0){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
delay(STEP_DELAY);
countedZ = countedZ - 1 ; 
}
stopMotors();
delay(stop_step_delay);
if(steps_z > countedZ  && steps_z > 0){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
delay(STEP_DELAY);
countedZ = countedZ + 1 ; 
}
stopMotors();
delay(stop_step_delay);
Serial.print("\n x-moving " + String(countedX)+" z-moving " + String(countedZ));
if(countedX == steps_x && countedZ == steps_z){
  finish = true ;
  countedX = 0 ;
  countedZ = 0 ;
}
}
}

void executeCommand(String command){
  int spaceIndex = command.indexOf(' ');
  int slachIndex = command.indexOf('/');
  if (spaceIndex == -1) {
    Serial.println("Invalid command");
    return;
  }
  String action = command.substring(0, spaceIndex);
  int steps_z = command.substring(spaceIndex + 1 , slachIndex).toInt();
  int steps_x = command.substring(slachIndex + 1).toInt();

  if (action == "MOVE") {
    finish = false;
    move(steps_x, steps_z);
    Serial.println("\n Motors moving x " + String(steps_x) + " x_steps"+ "& Motors moving z " + String(steps_z) + " z_steps");
  } else {
    Serial.println("Unknown command");
  }
}

void loop(){
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim(); 
    executeCommand(command);
    Serial.print("finiched executing");
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

