float run_kalmanFilter(float measurement){
  kalmanGain = errorEst / (errorEst + errorMea);
  currentEst = lastEst + (kalmanGain * (measurement - lastEst));
  errorEst - (1 - kalmanGain) * errorEst;
  lastEst = currentEst;
  return currentEst;
}
