#include <Arduino.h>
#include <TM1637Display.h>

const int datArray[] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110, B00000000};
const int datArrayRev[] = {B11000000, B11111001, B10100100, B10110000, B10011001, B10010010, B10000010, B11111000, B10000000, B10010000, B11111111};

const int clock_led_1 = 19;
const int latch_led_1 = 18;
const int data_led_1 = 5;

const int clock_led_2 = 23;
const int latch_led_2 = 22;
const int data_led_2 = 21;

const int clock_1digit = 4;
const int latch_1digit = 16;
const int data_1digit = 17;

const int clock_4digit = 32;
const int data_4digit = 33;
TM1637Display display1(clock_4digit, data_4digit);

const int rgb_r = 25;
const int rgb_g = 26;
const int rgb_b = 27;

class DisplayData
{
public:
    int speed = 0;
    int gear = 0;
    byte revlights[2] = {B00000000, B00000000};

    void Init()
    {
        pinMode(clock_led_1, OUTPUT);
        pinMode(latch_led_1, OUTPUT);
        pinMode(data_led_1, OUTPUT);

        pinMode(clock_led_2, OUTPUT);
        pinMode(latch_led_2, OUTPUT);
        pinMode(data_led_2, OUTPUT);

        pinMode(clock_1digit, OUTPUT);
        pinMode(latch_1digit, OUTPUT);
        pinMode(data_1digit, OUTPUT);

        pinMode(clock_4digit, OUTPUT);
        pinMode(data_4digit, OUTPUT);

        pinMode(rgb_r, OUTPUT);
        pinMode(rgb_g, OUTPUT);
        pinMode(rgb_b, OUTPUT);

        ResetSchifters();
    }

    void Reset()
    {
        speed = 0;
        gear = 0;
        revlights[0] = B00000000;
        revlights[1] = B00000000;

        UpdateMFD();
    }

    void WelcomeLed()
    {

        for (int i = 0; i < 8; i++)
        {
            bitWrite(revlights[0], i, 1);
            digitalWrite(latch_led_1, LOW);
            shiftOut(data_led_1, clock_led_1, MSBFIRST, revlights[0]);
            digitalWrite(latch_led_1, HIGH);
            delay(50);
        }

        for (int i = 0; i < 8; i++)
        {
            bitWrite(revlights[1], i, 1);
            digitalWrite(latch_led_2, LOW);
            shiftOut(data_led_2, clock_led_2, MSBFIRST, revlights[1]);
            digitalWrite(latch_led_2, HIGH);
            delay(50);
        }

        for (int i = 0; i < 3; i++)
        {
            revlights[0] = B00000000;
            revlights[1] = B00000000;

            digitalWrite(latch_led_1, LOW);
            shiftOut(data_led_1, clock_led_1, MSBFIRST, revlights[0]);
            digitalWrite(latch_led_1, HIGH);
            digitalWrite(latch_led_2, LOW);
            shiftOut(data_led_2, clock_led_2, MSBFIRST, revlights[1]);
            digitalWrite(latch_led_2, HIGH);

            delay(200);

            revlights[0] = B11111111;
            revlights[1] = B11111111;

            digitalWrite(latch_led_1, LOW);
            shiftOut(data_led_1, clock_led_1, MSBFIRST, revlights[0]);
            digitalWrite(latch_led_1, HIGH);
            digitalWrite(latch_led_2, LOW);
            shiftOut(data_led_2, clock_led_2, MSBFIRST, revlights[1]);
            digitalWrite(latch_led_2, HIGH);

            delay(200);
        }

        Reset();
        display1.setBrightness(7, true);
    }

    void UpdateMFD()
    {
        // revs
        digitalWrite(latch_led_1, LOW);
        shiftOut(data_led_1, clock_led_1, MSBFIRST, revlights[0]);
        digitalWrite(latch_led_1, HIGH);

        digitalWrite(latch_led_2, LOW);
        shiftOut(data_led_2, clock_led_2, MSBFIRST, revlights[1]);
        digitalWrite(latch_led_2, HIGH);

        // speed
        display1.showNumberDec(speed);

        // gear
        digitalWrite(latch_1digit, LOW);
        shiftOut(data_1digit, clock_1digit, MSBFIRST, datArray[gear]);
        digitalWrite(latch_1digit, HIGH);
    }

    void RGB_color(int red, int green, int blue)
    {
        analogWrite(rgb_r, red);
        analogWrite(rgb_g, green);
        analogWrite(rgb_b, blue);

        // RGB_color(255, 0, 0); // Red
        // RGB_color(0, 255, 0); // Green
        // RGB_color(0, 0, 255); // Blue
        // RGB_color(255, 255, 125); // Raspberry
        // RGB_color(0, 255, 255); // Cyan
        // RGB_color(255, 0, 255); // Magenta
        // RGB_color(255, 255, 0); // Yellow
        // RGB_color(255, 255, 255); // White
    }

private:
    void ResetSchifters()
    {
        display1.setBrightness(0, false);
        gear = 10;
        revlights[0] = B00000000;
        revlights[1] = B00000000;

        UpdateMFD();
    }

} _DisplayData;
