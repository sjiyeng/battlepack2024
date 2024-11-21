float applyDeadband(float var, float tolerance){
  if(var > 1){
    var = 1;
  }
  if(var < -1){
    var = -1;
  }
  if (abs(var) < tolerance) {
    var = 0;
  }
  return var;
}