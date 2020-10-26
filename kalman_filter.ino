float run_kalmanFilter(float measurement){
  kalmanGain = errorEst / (errorEst + errorMea);
  currentEst = lastEst + (kalmanGain * (measurement - lastEst));
  errorEst = (1 - kalmanGain) * errorEst + fabs(lastEst - currentEst) * variance; 
  lastEst = currentEst;
  return currentEst;
}
