void motorControl() {
  myStepper.setSpeed(700); // Set stepper motor speed

  myStepper.step(2048/8);  // Move motor 45 degrees clockwise

  delay(3000);             // Wait 3 seconds

  myStepper.step(-2048/8); // Move motor 45 degrees counter-clockwise
}