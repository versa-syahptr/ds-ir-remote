// **** TSOP is connected to port PB2 **** //////
//#define MOUSE_SENSITIVITY 5
#define REPEAT_DELAY 160

//Set to 0 after finding your codes
#define DEBUG 0


//Specify your 16remote codes here:
#include "remote.h"


volatile uint8_t m = 0, tcnt = 0, startflag = 0;
uint32_t irdata = 0, keydata = 0 ;
bool mouse = false;
bool pressed = false;
bool complete = false;
int lastMouseX=0, lastMouseY=0;

#include <avr/delay.h>
#include "TrinketHidCombo.h"


void setup() {
  //delay(30000);
  DDRB |= (1 << DDB1); //P1 (LED) OUT not used in sketch
  PORTB |= 1 << PB2; // a PB2 lift will not hurt.
  GIMSK |= 1 << INT0; //interrupt int0 enable
  MCUCR |= 1 << ISC00; //Any logical change on INT0 generates an interrupt request
  GTCCR |= 1 << PSR0; TCCR0A = 0;
  TCCR0B = (1 << CS02) | (1 << CS00); // divider /1024
  TIMSK = 1 << TOIE0; //interrupt Timer/Counter1 Overflow  enable
  TrinketHidCombo.begin(); // start the USB device engine and enumerate
  digitalWrite(1, HIGH);
  delay(1000);
  digitalWrite(1, LOW);
}

void loop() {

  if (complete) { // if a code has been received

    if (keydata != 0) //if a code is new
    {
      Action(keydata);
      pressed = true;
    }
//    else if(mouse)//Make mouse movements accelerate
//      {
//        lastMouseX*=2;
//        if(lastMouseX>64)
//          lastMouseX=64;
//        else if(lastMouseX<-64)
//          lastMouseX=-64;  
//        lastMouseY*=2;
//        if(lastMouseY>64)
//          lastMouseY=64;
//        else if(lastMouseY<-64)
//          lastMouseY=-64; 
//      }
//       
//      TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, 0);

    complete = false;
    ms_delay(REPEAT_DELAY);// to balance repeating/input delay of the remote

  }
  else if (pressed)
  {
    digitalWrite(1, LOW);
    if (mouse)
      TrinketHidCombo.mouseMove(0, 0, 0);
    else
      TrinketHidCombo.pressKey(0, 0);
    pressed = false;
  }
  else
  {
    _delay_ms(1);//restrain USB polling on empty cycles
    TrinketHidCombo.poll(); // check if USB needs anything done
  }

}

ISR (INT0_vect) {
  if (PINB & 1 << 2) { // If log1
    TCNT0 = 0;
  }
  else {
    tcnt = TCNT0; // If log0
    if (startflag) {
      if (30 > tcnt  && tcnt > 2) {
        if (tcnt > 15 && m < 32) {
          irdata |= (2147483648 >> m);
        }
        m++;
      }
    }
    else  startflag = 1;
  }
}
ISR (TIMER0_OVF_vect) {
  if (m)
    complete = true; 
    m = 0; 
//    if (mouse) { 
      startflag = 1;
//    }
//    else {
//      startflag = 0;
//      } 
    keydata = irdata; 
    irdata = 0; // if the index is not 0, then create an end flag
}

void ms_delay(uint16_t x) // USB polling delay function
{
  for (uint16_t m = 0; m < (x / 10); m++) {
    _delay_ms(10);
    TrinketHidCombo.poll();
  }
}

void Action(uint32_t keycode)
{
  if (DEBUG) {
    TrinketHidCombo.println(keydata, HEX);
  }
  else {
    switch (keycode)
    {
      case R_OK:
//        if (mouse)
//        {
//           lastMouseX=0;
//           lastMouseY=0;
//           TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, MOUSEBTN_LEFT_MASK);
//        }
//        else
          TrinketHidCombo.pressKey(0, KEYCODE_ENTER);
        break;
  
      case R_LEFT:
//        if (mouse)
//        {
//          lastMouseX=-MOUSE_SENSITIVITY;
//          lastMouseY=0;
//          TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, 0);
//        }
//          
//        else
          TrinketHidCombo.pressKey(0, KEYCODE_ARROW_LEFT);
        break;
  
      case R_RIGHT:
//        if (mouse)
//          {
//            lastMouseX=MOUSE_SENSITIVITY;
//            lastMouseY=0;
//            TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, 0);
//          }
//        else
          TrinketHidCombo.pressKey(0, KEYCODE_ARROW_RIGHT);
        break;
      case R_DOWN:
//        if (mouse)
//          {
//            lastMouseX=0;
//            lastMouseY=MOUSE_SENSITIVITY;
//            TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, 0);
//          }
//        else
          TrinketHidCombo.pressKey(0, KEYCODE_ARROW_DOWN);
        break;
      case R_UP:
//        if (mouse)
//          {
//            lastMouseX=0;
//            lastMouseY=-MOUSE_SENSITIVITY;
//            TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, 0);
//          }
//        else
          TrinketHidCombo.pressKey(0, KEYCODE_ARROW_UP);
        break;
      case R_HOME:
        TrinketHidCombo.pressKey(0, KEYCODE_ESC);
        break;
      case R_BACK:
        TrinketHidCombo.pressKey(0, KEYCODE_BACKSPACE);
        break;
      case R_INFO:
        TrinketHidCombo.pressKey(0, KEYCODE_I);
        break;
      case R_MENU:
        TrinketHidCombo.pressKey(0, KEYCODE_C);
        break;
      case R_POWER:
        TrinketHidCombo.pressKey(KEYCODE_MOD_LEFT_ALT, KEYCODE_F1);
        break;
//      case R_MOUSE:4C000000
//        mouse = !mouse;
//        lastMouseX=0;
//        lastMouseY=0;
//        break;

      // MEDIA
      case R_VOLUP:
        TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_UP);
        break;
      case R_VOLDOWN:
        TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_DOWN);
        break;
      case R_PREV:
        TrinketHidCombo.pressMultimediaKey(MMKEY_SCAN_PREV_TRACK);
        break;
      case R_NEXT:
        TrinketHidCombo.pressMultimediaKey(MMKEY_SCAN_NEXT_TRACK);
        break;
      case R_PLAYPAUSE:
        TrinketHidCombo.pressKey(0, KEYCODE_SPACE);
        break;
      case R_MUTE:
        TrinketHidCombo.pressKey(0, KEYCODE_F8);
        break;
      case R_FORWARD:
        TrinketHidCombo.pressKey(0, KEYCODE_F);
        break;
      case R_REWIND:
        TrinketHidCombo.pressKey(0, KEYCODE_R);
        break;
      case R_STOP:
        TrinketHidCombo.pressKey(0, KEYCODE_X);
        break;
      case R_CH_UP:
        TrinketHidCombo.pressKey(KEYCODE_MOD_LEFT_ALT, KEYCODE_EQUAL);
        break;
      case R_CH_DOWN:
        TrinketHidCombo.pressKey(KEYCODE_MOD_LEFT_ALT, KEYCODE_MINUS);
        break;
        
      // COLOR
      case R_RED: // youtube
        TrinketHidCombo.pressKey(KEYCODE_MOD_LEFT_ALT, KEYCODE_Y);
        break;
      case R_GREEN: // live
        TrinketHidCombo.pressKey(0, KEYCODE_H);
        break;
      case R_YELLOW: 
        TrinketHidCombo.pressKey(0, KEYCODE_F3);
        break;
      case R_BLUE: 
        TrinketHidCombo.pressKey(0, KEYCODE_F4);
        break;
        
      default:
        int index = 0;
        for (index; index <= 10; index++){
          if( NUMS[index] == keycode ) {
            TrinketHidCombo.print(index);
          }
        }
        return;
        
    }
    
  }
  digitalWrite(1, HIGH);
}
