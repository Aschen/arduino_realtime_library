#include "Arduino.h"

typedef void (*CallbackButton)(void);

class Button
{
  private:
  
    enum State
    {
      RELEASED = 0,
      REBOUND = 1,
      PRESSED = 2
    };
  
  private:
  
    int             m_pin;
    State           m_state;
    CallbackButton  m_callbackPressed;
    CallbackButton  m_callbackReleased;
    unsigned long int m_reboundStart;

  public:
  
    Button(int pin, CallbackButton callbackPressed = nullptr, CallbackButton callbackReleased = nullptr)
      : m_pin(pin), m_state(RELEASED), m_callbackPressed(callbackPressed), m_callbackReleased(callbackReleased)
    {
    }
    
    Button() {}

    void setup()
    {
      pinMode(m_pin, INPUT);
    }

    void loop()
    {
      if (m_state == REBOUND)
      {
        unsigned long int currentTime = millis();
        
        if (currentTime > m_reboundStart + 200)
        {
          m_state = RELEASED;
        }        
      }
      else
      {
        State state = digitalRead(m_pin) == 1 ? PRESSED : RELEASED;
         
        if (state == PRESSED && m_state == RELEASED)
        {
          m_state = PRESSED;
          eventPress();
        }
        else if (state == RELEASED && m_state == PRESSED)
        {
          m_state = REBOUND;
          m_reboundStart = millis();
          eventRelease();
        }
      }
      
    }
    
    Button onPressed(CallbackButton callback)
    {
      m_callbackPressed = callback;
      
      return *this;
    }

    Button onReleased(CallbackButton callback)
    {
      m_callbackReleased = callback;
      
      return *this;
    }
    
  private:
  
    void eventPress()
    {
      if (m_callbackPressed != nullptr)
        m_callbackPressed();
    }

    void eventRelease()
    {
      if (m_callbackReleased != nullptr)
        m_callbackReleased();
    }
};

