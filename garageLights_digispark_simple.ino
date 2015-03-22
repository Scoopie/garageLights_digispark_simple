#define INTERNAL_LIGHT_INPUT 0 // active low
#define REMOTE_INPUT 2 // active low

#define FRONT_LIGHTS_OUTPUT 1

bool remoteButtonPreviousPoll = true; // pullup sets line high if button not pressed
bool onViaRemote = false;

// the setup function runs once when you press reset or power the board
void setup() 
{
  pinMode(FRONT_LIGHTS_OUTPUT, OUTPUT);
  digitalWrite(FRONT_LIGHTS_OUTPUT, LOW);    
  
  // input, with pullup resistor enabled
  pinMode(INTERNAL_LIGHT_INPUT, OUTPUT);
  digitalWrite(INTERNAL_LIGHT_INPUT, HIGH); 
  pinMode(INTERNAL_LIGHT_INPUT, INPUT);

  // input, with pullup resistor enabled
  pinMode(REMOTE_INPUT, OUTPUT);
  digitalWrite(REMOTE_INPUT, HIGH); 
  pinMode(REMOTE_INPUT, INPUT);
}

void loop() 
{
  if(!onViaRemote) 
  {
    digitalWrite(FRONT_LIGHTS_OUTPUT, !digitalRead(INTERNAL_LIGHT_INPUT));
  }
  if(remoteButtonRequested())
  {
    onViaRemote = !digitalRead(FRONT_LIGHTS_OUTPUT);
    digitalWrite(FRONT_LIGHTS_OUTPUT, onViaRemote);   
  }
}

bool remoteButtonRequested()
{
  bool remoteButtonThisPoll = digitalRead(REMOTE_INPUT);
  bool result = (remoteButtonPreviousPoll == true && remoteButtonThisPoll == false);
  remoteButtonPreviousPoll = remoteButtonThisPoll;
  
  return result;
}
