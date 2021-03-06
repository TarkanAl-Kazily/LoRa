// rf95_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_server
// Tested with Anarduino MiniWirelessLoRa

#include <SPI.h>
#include <RH_RF95.h>

// Singleton instance of the radio driver
RH_RF95 rf95;

void setup()
{
    Serial.begin(9600);
    Serial.println("init starting");
    if (!rf95.init())
        Serial.println("init failed");
    // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
}

uint16_t data[] = {0, 0, 0};
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t len = 6;
 
void loop()
{
    Serial.print("Sending to rf95_server: ");
    // Send a message to rf95_server
    convertTo_uint8_t(data, 3);
    printArray(buf, len);
    Serial.print(" sent. Result: ");
    Serial.println(rf95.send(buf, len));
    rf95.waitPacketSent();
    //Serial.println("Packet sent");
    data[0]++;
    data[1] += 2;
    data[2] += 3;
}

void printArray(uint8_t arr[], int l)
{
    for (int i = 0; i < l; i++)
    {
        Serial.print("Entry " + String(i) + ": " + String(arr[i]) + " | ");
    }
}

void convertTo_uint8_t(uint16_t arr[], int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        uint16_t number = arr[i];
        Serial.print(number, HEX);
        Serial.print(" | ");
        uint16_t l = number & 0x00FF;
        uint8_t least = l;
        Serial.print(least, HEX);
        Serial.print(" | ");
        uint16_t s = number >> 8;
        s = s & 0x00FF;
        uint8_t second = s;
        Serial.println(second, HEX);
        //uint8_t third = number & 0x00FF0000;
        //uint8_t most = number & 0xFF000000;
        buf[2*i] = second;
        buf[(2*i)+1] = least;
    }
}

void convertTo_uint16_t(uint8_t arr[], int bufLength)
{
    for (int i = 0; i < bufLength; i++)
    {
        uint16_t most = arr[2*i];
        uint16_t least = arr[(2*i)+1];
        most = most << 8;
        most = most & 0xFF00;
        uint16_t data = most + least;
        buf[i] = data;
    }
}

