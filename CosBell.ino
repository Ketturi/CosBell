/*CosBell (Doorbell for cos)
 * 
 * Arduino controlled bell ringer.
 * Two tone bell is connected trough
 * 2 mosfets.
 * 
 * Pin 7 goes low when button is pressed.
 * Pin 9 and 8 are control lines, active high.
 * 
 * Pin 8 plays "DingDong" sound, 
 * Pin 9 plays "Dong" sound.
 * By aplying voltage to coil again shortly after "Ding", 
 * "Dong" won't be rang.
 * 
 * Ketturi 2015
 */

//Some defines
const int ButtonPin = 7;
const int LowBellPin = 9;
const int HighBellPin = 8;

const int HammerTime = 20;      //How long hammer solennoid is powered

//Adjust these if high bell strikes also low bell
const int PullDelay = 20;    //Delay from striking high note bell to before hitting low note bell
const int PullTime = 10;     //Time to stop hammer hitting low note bell

int counter = 0;

void setup() {
  //Set pin direction
  pinMode(ButtonPin, INPUT_PULLUP);
  pinMode(LowBellPin, OUTPUT);
  pinMode(HighBellPin, OUTPUT);

  //Make extra sure everything is low!
  digitalWrite(LowBellPin, LOW);
  digitalWrite(HighBellPin, LOW);
}

void loop() {
  if (digitalRead(ButtonPin) == LOW) {
    if (counter >= 1){ //If button is held down bell will ring more alarming
      DoorBellRing();
      }
    
    else {             //If button is quicly pressed it will just ring once
      counter = counter+1;
      PlayBellSingle();
      delay(500);
      }
    
  if (digitalRead(ButtonPin) == HIGH){
    counter = 0;
    }
  } 
 }

void PlayBellSingle(){   //Doorbell song
  RingHighBell();
  delay(500);
  RingHighBell();
  delay(500);
  RingLowBell();
 }


void DoorBellRing(){  // Knock knock knock
  delay(250);
  RingLowBell();
  delay(250);
}


void RingHighBell(){ //pull hammer to high tone bell
  digitalWrite(HighBellPin, HIGH); //Strike
  delay(HammerTime);
  digitalWrite(HighBellPin, LOW);
  delay(PullDelay);
  digitalWrite(HighBellPin, HIGH);  //Pullback so hammer does not hit low note bell
  delay(PullTime);
  digitalWrite(HighBellPin, LOW);
 }

void RingLowBell(){ //pull hammer to low tone bell
  digitalWrite(LowBellPin, HIGH); //Strike
  delay(HammerTime);
  digitalWrite(LowBellPin, LOW);
 }

  /* 
   * In a world of magnets and miracles
   * Our thoughts strayed constantly and without boundary
   * The ringing of the division bell had begun
   *  High Hopes - Pink Floyd
   */
