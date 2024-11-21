#include <Bluepad32.h>
#include <ESP32Servo.h>

//timer
unsigned long startTime; // Variable to store start time
const unsigned long runDuration = 500; 
bool isRunning = false; // Variable to track whether the function is running
int currentStep = 0;

//Constants
bool invertLeft = false;
bool invertRight = false;
int leftMotorPin = 0;
int rightMotorPin = 1;



//Variables
float translation;
float rotation;
bool a;
bool lb;
bool rb;
bool dpadUp;
bool connected = false;
bool allowEnable = false;
bool enableButton = false;
float leftMotorSpeed;
float rightMotorSpeed;
float leftMotorOut;
float rightMotorOut;


Servo leftMotor;
Servo rightMotor;

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// Arduino setup function. Runs in CPU 1
void setup() {
  Serial.begin(9600);
  startTime = millis(); // Record the start time
  isRunning = true; // Set running flag to true

  //attach pins
  leftMotor.attach(leftMotorPin);
  rightMotor.attach(rightMotorPin);


  //controller
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t* addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();
  BP32.enableVirtualDevice(false);
}

// Arduino loop function. Runs in CPU 1.
void loop() {
  ControllerPtr ctl = myControllers[0];

  //deadbands
  translation = applyDeadband(translation, .05);
  rotation = applyDeadband(rotation, .05);

  //buttons
  if (lb) {
    toggleEnableButton();
  }
  if (rb && allowEnable) {
    delay(250);
    ctl->playDualRumble(0, 250, 0x80, 0x40);
  }


  allowEnable = checkAllowEnable(connected, enableButton);
  arcadeDrive(translation, rotation);
  leftMotorOut = 1500 + leftMotorSpeed * 500;
  rightMotorOut = 1500 + rightMotorSpeed * 500;
  if (allowEnable){
  leftMotor.writeMicroseconds(leftMotorOut);
  rightMotor.writeMicroseconds(rightMotorOut);
  }
  else {
  leftMotorOut = 1500;
  rightMotorOut = 1500;
  leftMotor.writeMicroseconds(leftMotorOut);
  rightMotor.writeMicroseconds(rightMotorOut);

  }

  bool dataUpdated = BP32.update();
  if (dataUpdated)
    processControllers();
  vTaskDelay(1);

  //Debugging
  Serial.printf("Left Motor Speed: %.2F || Right Motor Speed: %.2F\n",leftMotorOut,rightMotorOut);
}
