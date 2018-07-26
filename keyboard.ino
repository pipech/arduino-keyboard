#include <Keyboard.h>
#include <Mouse.h>

#define b1Btn 21
#define b2Btn 20
#define b3Btn 19
#define b4Btn 18
#define b5Btn 15

#define g1Btn 14
#define g2Btn 16
#define g3Btn 10

#define r1a 2
#define r1b 4
#define r1cli 6

#define r2a 3
#define r2b 5
#define r2cli 7

volatile boolean r1fired;
volatile boolean r1up;

volatile boolean r2fired;
volatile boolean r2up;

static int monit = 0;
unsigned long clickTime;
unsigned long actionTime;
unsigned long diffTime;

char ctrlKey = KEY_LEFT_CTRL;
char altKey = KEY_LEFT_ALT;
char shiftKey = KEY_LEFT_SHIFT;
char windowsKey = KEY_LEFT_GUI;
char enterKey = KEY_RETURN;
char upKey = KEY_UP_ARROW;
char downKey = KEY_DOWN_ARROW;
char leftKey = KEY_LEFT_ARROW;
char rightKey = KEY_RIGHT_ARROW;

void setup() {
  
  pinMode(b1Btn, INPUT_PULLUP);
  pinMode(b2Btn, INPUT_PULLUP);
  pinMode(b3Btn, INPUT_PULLUP);
  pinMode(b4Btn, INPUT_PULLUP);
  pinMode(b5Btn, INPUT_PULLUP);
  
  pinMode(g1Btn, INPUT_PULLUP);
  pinMode(g2Btn, INPUT_PULLUP);
  pinMode(g3Btn, INPUT_PULLUP);

  pinMode(r1a, INPUT_PULLUP);
  pinMode(r1b, INPUT_PULLUP);
  pinMode(r1cli, INPUT_PULLUP);

  pinMode(r2a, INPUT_PULLUP);
  pinMode(r2b, INPUT_PULLUP);
  pinMode(r2cli, INPUT_PULLUP);

  attachInterrupt (digitalPinToInterrupt(r1a), r1inter, CHANGE);
  attachInterrupt (digitalPinToInterrupt(r2a), r2inter, CHANGE);
  
  Serial.begin(9600);
  Keyboard.begin();
  Mouse.begin();
  delay(200);

  diffTime = 20000;
  clickTime = 0;
  
}

void loop() {  

// rotary 1

  if (r1fired) {
    actionTime = millis();
    diffTime = actionTime - clickTime;
    
    if (diffTime < 7500) {
      if (r1up){
        switch (monit) {
          case 1:
              monit1Bri(-1);
            break;
          case 2:
              monit2Bri(-1);
            break;
          case 3:
            break;
        }
      } else {
        switch (monit) {
          case 1:
              monit1Bri(1);
            break;
          case 2:
              monit2Bri(1);
            break;
          case 3:
            break;
        }
      }
    }
    
    r1fired = false;
  }

  if (digitalRead(r1cli) != 1) {
   Serial.println ("click");
   delayTime();
  }

// rotary 2

  if (r2fired) {
    actionTime = millis();
    diffTime = actionTime - clickTime;
    
    if (diffTime < 7500) { 
      if (r2up){
        switch (monit) {
          case 1:
            break;
          case 2:
              monit2Con(-1);
            break;
          case 3:
            break;
        }
      } else {
        switch (monit) {
          case 1:
            break;
          case 2:
              monit2Con(1);
            break;
          case 3:
            break;
        }
      }
    } else {
      if (r2up){
        volLoud('x');
      } else {
        volLoud('z');
      }
    }
    
    r2fired = false;
  }

  if (digitalRead(r2cli) != 1) {
   Serial.println ("click");
   delayTime();
  }

// big board

  if (digitalRead(b1Btn) != 1) {
    actionTime = millis();
    diffTime = actionTime - clickTime;
    
    if (diffTime < 2000 && monit == 3) {
      monit3Pre('1');
      delay(350);
      clickTime = 0;
    } else {
      monitPreset('1');
    }
    
  }
  
  if (digitalRead(b2Btn) != 1) {
    actionTime = millis();
    diffTime = actionTime - clickTime;
    
    if (diffTime < 2000 && monit == 3) {
      monit3Pre('2');
      delay(350);
      clickTime = 0;
    } else {
      monitPreset('2');
    }
    
  }
  
  if (digitalRead(b3Btn) != 1) {
    actionTime = millis();
    diffTime = actionTime - clickTime;
    
    if (diffTime < 2000 && monit == 3) {
      monit3Pre('3');
      delay(350);
      clickTime = 0;
    } else {
      monitPreset('3');
    }
    
  }
  
  if (digitalRead(b4Btn) != 1) {
    actionTime = millis();
    diffTime = actionTime - clickTime;
    
    if (diffTime < 2000 && monit == 3) {
      monit3Pre('4');
      delay(350);
      clickTime = 0;
    } else {
      monitPreset('4');
    }
    
  }
  
  if (digitalRead(b5Btn) != 1) {
    actionTime = millis();
    diffTime = actionTime - clickTime;
    
    if (diffTime < 2000 && monit == 3) {
      monit3Pre('5');
      delay(350);
      clickTime = 0;
    } else {
      monitPreset('5');
    }
    
  }

// green board

  if (digitalRead(g1Btn) != 1) {
    monit = 1;
    clickTime = millis();
    delayTime();
  }
  
  if (digitalRead(g2Btn) != 1) {
    monit = 2;
    clickTime = millis();
    delayTime();
  }
  
  if (digitalRead(g3Btn) != 1) {
    monit = 3;
    clickTime = millis();
    delayTime();
  }

}

// keyboard shortcut
  // all monitor preset
    void monitPreset (char set) {
      Keyboard.press(ctrlKey);
      Keyboard.press(shiftKey);
      Keyboard.press(set);
      Keyboard.releaseAll();
      delayTime();
    }
  
  // monitor 1
    //brightness
    void monit1Bri (int inc) {
      Keyboard.press(ctrlKey);
      Keyboard.press(altKey);
      delay(20);
      Mouse.move(0,0,inc);
      delay(20);
      Keyboard.releaseAll();
    }
    
  // monitor2
    //brightness
    void monit2Bri (int inc) {
      Keyboard.press(ctrlKey);
      Keyboard.press(shiftKey);
      Keyboard.press(altKey);
      delay(20);
      Mouse.move(0,0,inc);
      delay(20);
      Keyboard.releaseAll();
    }
    //contrast
    void monit2Con (int inc) {
      Keyboard.press(ctrlKey);
      Keyboard.press(windowsKey);
      delay(20);
      Mouse.move(0,0,inc);
      delay(20);
      Keyboard.releaseAll();
    }
    
  // monitor3
    //preset
    void monit3Pre (int set) {
      Keyboard.press(ctrlKey);
      Keyboard.press(altKey);
      Keyboard.press(set);
      Keyboard.releaseAll();
      delayTime();
    }
    
  // volume
    //loudness
    void volLoud (char key) {
        Keyboard.press(shiftKey);
        Keyboard.press(altKey);
        Keyboard.press(key);
        Keyboard.releaseAll();
    }

// utilities
  void delayTime() {
    delay(100);
  }

  void printTime() {
    Serial.print("clickTime : ");
    Serial.print(clickTime);
    Serial.print("     actionTime : ");
    Serial.print(actionTime);
    Serial.print("     diffTime : ");
    Serial.println(diffTime);
  }

// interrupts
  void r1inter () {
    if (digitalRead (r1a)) {
      r1up = digitalRead (r1b);
      r1fired = false;
    } else {
      r1up = !digitalRead (r1b);
      r1fired = true;
    delay(2);
   }
  }
  
  
  void r2inter () {
    if (digitalRead (r2a)) {
      r2up = digitalRead (r2b);
      r2fired = false;
    } else {
      r2up = !digitalRead (r2b);
      r2fired = true;
    delay(2);
   }
  }