int driveMotor(int pin1, int pin2, bool invert, float speed, bool brake, bool allowEnableValue) {
  //idle mode
  if (allowEnableValue) {
    if (speed == 0) {
      if (brake) {
        pin1Value = 255;
        pin2Value = 255;
        analogWrite(pin1, pin1Value);
        analogWrite(pin2, pin2Value);
      } else {
        pin1Value = 0;
        pin2Value = 0;
        analogWrite(pin1, pin1Value);
        analogWrite(pin2, pin2Value);
      }
    }
    if (invert) {
      speed = speed * -1;
    }

    //if reverse
    if (speed < 0) {
      pin1Value = 0;
      pin2Value = 255.0 * abs(speed);
      analogWrite(pin1, pin1Value);
      analogWrite(pin2, pin2Value);
    }
    //if forward
    if (speed > 0) {
      pin1Value = 255.0 * abs(speed);
      pin2Value = 0;
      analogWrite(pin1, pin1Value);
      analogWrite(pin2, pin2Value);
    }
  }

  //if disabled coast
  else {
    pin1Value = 0;
    pin2Value = 0;
    analogWrite(pin1, pin1Value);
    analogWrite(pin2, pin2Value);
  }
  return pin1Value;
  return pin2Value;
}