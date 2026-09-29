const int led1Pin = 2;
const int led2Pin = 3;
const int led3Pin = 4;
const int led4Pin = 5;
const int button1Pin = 7;
const int button2Pin = 8;
const int button3Pin = 9;
const int button4Pin = 10;

void setup(){
  Serial.begin(11200);
  randomSeed(analogRead(A0));
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  
  pinMode(button1Pin,INPUT_PULLUP);
  pinMode(button2Pin,INPUT_PULLUP);
  pinMode(button3Pin,INPUT_PULLUP);
  pinMode(button4Pin,INPUT_PULLUP);
  

}

int sequence[32];
int counter = 0;
bool computerTurn = true;
const int ledPin[] = {2, 3, 4, 5};

void blink(int number){
 digitalWrite(ledPin[number], HIGH);
 delay(100);
 digitalWrite(ledPin[number], LOW);
 delay(100);
}

void upVolt(){
 digitalWrite(led1Pin, HIGH);
 digitalWrite(led2Pin, HIGH);
 digitalWrite(led3Pin, HIGH);
 digitalWrite(led4Pin, HIGH);
 delay(100);
}

void downVolt(){
 digitalWrite(led1Pin, LOW);
 digitalWrite(led2Pin, LOW);
 digitalWrite(led3Pin, LOW);
 digitalWrite(led4Pin, LOW);
 delay(100);
}

void blinkAllFour(){
  for(int i = 0 ; i < 5 ; i++){
   upVolt();
   downVolt();
  }
}

bool press_btn(bool btnT, bool btnF1, bool btnF2, bool btnF3){
  if (btnT == false && btnF1 == true
      && btnF2 == true && btnF3 == true) return true;
  return false;
}

void loop(){
 
  if (computerTurn){
    for (int i = 0 ; i < counter ; i++){
     	blink(sequence[i]);
    }
    
    int number = random(0,4);
    sequence[counter] = number;
    counter++;
    blink(number);
    
    for (int i = 0 ; i < counter ; i++){
    	Serial.print(sequence[i] + 1);
    	Serial.print(" ");
    }
    Serial.println();
    computerTurn = false;
    delay(1500);
    
    
  }else{
  	int playerCounter = 0;
    int lastState = -1;
    while (playerCounter < counter){
      int state;
      bool btn1 = digitalRead(button1Pin);
      bool btn2 = digitalRead(button2Pin);
      bool btn3 = digitalRead(button3Pin);
      bool btn4 = digitalRead(button4Pin);
      if (press_btn(btn1, btn2, btn3, btn4)) state = 0; 
      else if (press_btn(btn2, btn1, btn3, btn4)) state = 1;
      else if (press_btn(btn3, btn1, btn2, btn4)) state = 2;
      else if (press_btn(btn4, btn1, btn2, btn3)) state = 3;
      else state = -1;
      
      if (lastState != state){
        
        if (state != -1 && state != sequence[playerCounter]){
      		Serial.println("Fail");
          	blinkAllFour();
          	counter = 0;
          	break;
      }else if (state != -1 && state == sequence[playerCounter]){
        blink(state);
        playerCounter++;
      }
        
      lastState = state;
      }
    }
    
    delay(1500);
    computerTurn = true;
  
  }
  
}