bool checkAllowEnable(bool connected,bool enableButton){
  if(connected == 1 && enableButton == 1){
    allowEnable = true;
  }
  else{
    allowEnable = false;
  }
  return allowEnable;
}

void toggleEnableButton() {
  delay(250);
  enableButton = !enableButton;
}