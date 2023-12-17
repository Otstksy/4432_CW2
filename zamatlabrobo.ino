int trigPin = 8;  // Trigger pin of the ultrasonic sensor
int echoPin = 9;  // Echo pin of the ultrasonic sensor
const int prox = 12;  // Signal pin of IRR seensor
const int button =13; //Push button


const int control = 11; //5v pin on driver module
//Motor driver pins
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
int now_state; //0=ready, 1=gogo, 2== stop

//led pins
int ledred =6;
int ledblue =7;
int ledgreen =10;

float distance_cm; //proximity value from ultrasonic sensor
int pressed; //Button pressed state
int inrange; //IR proximity value

void setup() {
  Serial.begin(9600); //initialize the Serial monitor
  
  //set pinmodes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(prox, INPUT);
  pinMode(button, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ledred, OUTPUT);
  pinMode(ledblue, OUTPUT);
  pinMode(ledgreen, OUTPUT);

 // make sure the motor is not active in the begining
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  digitalWrite(control, 1);

 //set statemachines starting position
  now_state = 0 ;
  pressed = 0;
 }
void check_distance(){//check distance from ultrasonic sensor

 digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);

 

  digitalWrite(trigPin, HIGH);         // Pulse for 10μ s to trigger ultrasonic detection
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

 

   distance_cm = pulseIn(echoPin, HIGH);     // Read receiver pulse time 
  distance_cm = distance_cm/58;             // Transform pulse time to distance 
           //Output distance in cm
  
  }

void in_range(){//check if anything is in the set range ofthe IR sensor


 inrange = digitalRead(prox);
 


 } 


void state_machine(){//State machine
  if(distance_cm < 30 || inrange == 0 ){
   if(now_state == 1){
    now_state = 2;  //this means stop
  }}
  if(now_state == 0){
    ledstate(0);

   pressed = digitalRead(button);
     if(pressed == 0){
      delay(1000);
      now_state =1;
    }}
  else if(now_state == 1){
    delay(1500);
    ledstate(1);

    motormove(1);
  }else if(now_state == 2){
    //run the motors in reverse for half a second and stop, then styate back to ready
    digitalWrite(control, 0);
    digitalWrite(control, 1);
    motormove(-1);
    delay(200);
    motormove(0);

     ledstate(2);

    delay(1000);
    ledstate(1);

    now_state = 0;
  }
 }
void motormove(int gogo){//control function for the motors.either 1,0,-1
  if(gogo == 1){//forward
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  }
  if (gogo == 0){//stop
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);}
  if(gogo == -1){// reverse
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  }
 }
void ledstate(int gogolike){
  if(gogolike == 0){//blue
    digitalWrite(ledred, 0);
    digitalWrite(ledblue, 1);
    digitalWrite(ledgreen, 0);
  }
  if(gogolike ==1){//green
    digitalWrite(ledred, 0);
    digitalWrite(ledblue, 0);
    digitalWrite(ledgreen, 1);
  }
  if(gogolike ==2){//red
    digitalWrite(ledred, 1);
    digitalWrite(ledblue, 0);
    digitalWrite(ledgreen,0);
  }
 }
void loop() {
 
 in_range();
 check_distance();
 state_machine();

 Serial.print(pressed);
  Serial.print(",");
  Serial.print(inrange);
  Serial.print(",");
  Serial.println(distance_cm);

 // Check for input from the Serial Monitor
  if (Serial.available() > 0) {
    // Read the input and perform an action based on the command
    int command = Serial.read();
    if (command == 1) {
      // Perform action for command 'A' (adjust as needed)
      Serial.println("Command A received");
    } else if (command == 0) {
      // Perform action for command 'B' (adjust as needed)
      Serial.println("Command B received");
    }
    // Add more commands as needed
  }
 Serial.println(inrange);
 }

