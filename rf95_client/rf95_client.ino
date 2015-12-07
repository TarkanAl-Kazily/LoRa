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

uint8_t data[] = {0,0,0};
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t len;
 
void loop()
{
    Serial.println("Sending to rf95_server");
    // Send a message to rf95_server
    Serial.print((int)data[0]);
    Serial.print(" ");
    Serial.print((int)data[1]);
    Serial.print(" ");
    Serial.print((int)data[2]);
    Serial.print(" sent. Result: ");
    Serial.println(rf95.send(data, sizeof(data)));

    rf95.waitPacketSent();
    Serial.println("Packet sent");
    data[0]++;
    data[1] += 2;
    data[2] += 3;
}


