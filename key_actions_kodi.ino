#ifdef KEY_ACTIONS_KODI

void Action(uint32_t keycode)
{
  if (DEBUG) {
    TrinketHidCombo.println(keydata, HEX);
  }
  else {
    switch (keycode)
    {
      case R_OK:
        if (mouse)
        {
           lastMouseX=0;
           lastMouseY=0;
           TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, MOUSEBTN_LEFT_MASK);
        }
        else
          TrinketHidCombo.pressKey(0, KEYCODE_ENTER);
        break;
  
      case R_LEFT:
        if (mouse)
        {
          lastMouseX=-MOUSE_SENSITIVITY;
          lastMouseY=0;
          TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, 0);
        }
          
        else
          TrinketHidCombo.pressKey(0, KEYCODE_ARROW_LEFT);
        break;
  
      case R_RIGHT:
        if (mouse)
          {
            lastMouseX=MOUSE_SENSITIVITY;
            lastMouseY=0;
            TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, 0);
          }
        else
          TrinketHidCombo.pressKey(0, KEYCODE_ARROW_RIGHT);
        break;
      case R_DOWN:
        if (mouse)
          {
            lastMouseX=0;
            lastMouseY=MOUSE_SENSITIVITY;
            TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, 0);
          }
        else
          TrinketHidCombo.pressKey(0, KEYCODE_ARROW_DOWN);
        break;
      case R_UP:
        if (mouse)
          {
            lastMouseX=0;
            lastMouseY=-MOUSE_SENSITIVITY;
            TrinketHidCombo.mouseMove(lastMouseX, lastMouseY, 0);
          }
        else
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
      case R_SET:
        mouse = !mouse;
        lastMouseX=0;
        lastMouseY=0;
        break;

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

#endif
