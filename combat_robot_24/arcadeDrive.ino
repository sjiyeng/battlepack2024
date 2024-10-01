float arcadeDrive(float translationValue, float rotationValue){
  leftMotorSpeed = translationValue + rotationValue;
  rightMotorSpeed = translationValue - rotationValue;

  if(leftMotorSpeed > 1){
    leftMotorSpeed = 1;
  }
  if(rightMotorSpeed > 1){
    rightMotorSpeed = 1;
  }
  if(leftMotorSpeed < -1){
    leftMotorSpeed = -1;
  }
  if(rightMotorSpeed < -1){
    rightMotorSpeed = -1;
  }

  return leftMotorSpeed;
  return rightMotorSpeed;
}