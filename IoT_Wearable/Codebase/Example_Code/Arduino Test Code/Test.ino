// SIMPLE BLINK CODE EXAMPLE 
// to test the working of the board 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(1000);                    
  digitalWrite(LED_BUILTIN, LOW); 
  delay(1000);                     
}
