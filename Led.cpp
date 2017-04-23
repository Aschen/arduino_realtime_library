#include "Arduino.h"

#define INFINITE 4294967295

class Led
{
  private:

    enum State
    {
      OFF = 0,
      ON = 1
    };

  private:

    int                 m_pin;
    State               m_state;
    unsigned long int   m_lastBlink;
    unsigned long int   m_blinkCount;
    int                 m_blinkInterval;

  public:

    Led(int pin)
      : m_pin(pin), m_state(OFF), m_lastBlink(0), m_blinkCount(0), m_blinkInterval(0)
    {
    }

    Led() {}

    void setup()
    {
      pinMode(m_pin, OUTPUT);
    }

    void loop()
    {
      if (m_blinkCount == 0)
        return;

      unsigned long int currentTime = millis();

      if (currentTime > m_lastBlink + m_blinkInterval)
      {
        toggle();
        m_lastBlink = currentTime;
        --m_blinkCount;
      }

    }

    void turnOn()
    {
      digitalWrite(m_pin, ON);
    }

    void turnOff()
    {
      m_blinkCount = 0;
      digitalWrite(m_pin, OFF);
    }

    void toggle()
    {
      m_state = m_state == ON ? OFF : ON;
      digitalWrite(m_pin, m_state);
    }

    void blinkOnce(int interval)
    {
      m_blinkInterval = interval;
      // Need 2 loop turn : Loop 1 => ON, Loop 2 => OFF
      m_blinkCount = 2;
      m_lastBlink = 0;
      turnOff();
    }

    void blinkOnceSync(int interval)
    {
      turnOff();
      delay(interval);
      turnOn();
      delay(interval);
      turnOff();
    }

    void startBlinking(int interval)
    {
      m_blinkInterval = interval;
      m_blinkCount = INFINITE;
      m_lastBlink = 0;
    }

    void stopBlinking()
    {
      m_blinkInterval = 0;
      m_lastBlink = 0;
      m_blinkCount = 0;
      digitalWrite(m_pin, OFF);
    }
};
