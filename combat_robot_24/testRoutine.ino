void testRoutine() {
  if (allowEnable) {
    // Check if the function has been called recently to control timing
    if (millis() - startTime < runDuration) {
      return;  // Exit if the runDuration hasn't elapsed yet
    }

    // Increment the currentStep for the next command
    currentStep++;
    startTime = millis();  // Reset start time for the next command

    switch (currentStep) {
      case 0:
        driveMotor(leftPin1, leftPin2, invertLeft, 0.25, brakeDrivetrain, allowEnable);  // Run left motor forward
        Serial.println("Running left motor forward");
        break;
      case 1:
        driveMotor(leftPin1, leftPin2, invertLeft, -0.25, brakeDrivetrain, allowEnable);  // Run left motor backward
        Serial.println("Running left motor backward");
        break;
      case 2:
        driveMotor(rightPin1, rightPin2, invertRight, 0.25, brakeDrivetrain, allowEnable);  // Run right motor forward
        Serial.println("Running right motor forward");
        break;
      case 3:
        driveMotor(rightPin1, rightPin2, invertRight, -0.25, brakeDrivetrain, allowEnable);  // Run right motor backward
        Serial.println("Running right motor backward");
        break;
      default:
        // Reset to the first step after the last command
        currentStep = -1;  // Set to -1 so it becomes 0 on the next increment
        break;
    }
  } else {
    Serial.println("NOT ENABLED");
  }
}