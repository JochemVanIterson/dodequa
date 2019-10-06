
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
#include "printf.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 1;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);

/**********************************************************/

byte addresses[][6] = {"01Rec","01Sen"};

// Used to control whether this node is sending or receiving
bool role = 1; // 1=Transmitter, 0=Receiver

void setup() {
  Serial.begin(115200);
  while (!Serial);
  printf_begin();
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  SPI.setSCK(13);
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MIN);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  // Start the radio listening for data
  radio.enableDynamicPayloads() ;
  radio.setAutoAck( true ) ;
  radio.powerUp() ;
  radio.startListening();

  radio.printDetails();
}

void loop() {
/****************** Ping Out Role ***************************/  
  if (role == 1)  {
    radio.stopListening();                                     // First, stop listening so we can talk.
    Serial.println(F("Now sending"));

    unsigned long start_time = micros();                       // Take the time, and send it.  This will block until complete
    unsigned long send_time = millis();                       // Take the time, and send it.  This will block until complete
    byte sendableArray[5] = {253, 100, 0, 0, 101};
    sendableArray[2] = send_time/256;
    sendableArray[3] = send_time%256;
    if (!radio.write( &sendableArray, sizeof(sendableArray) )){
      Serial.println(F("Write failed"));
    }
        
    radio.startListening();                                    // Now, continue listening
    
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    while(!radio.available()){                                 // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
        timeout = true;
        break;
      }      
    }
        
    if ( timeout ){                                            // Describe the results
      Serial.println(F("Failed, response timed out."));
    } else {
      unsigned long got_time;                                  // Grab the response, compare, and send to debugging spew
      byte sendableArray[5] = {253, 100, 0, 0, 101};
      radio.read( &sendableArray, sizeof(sendableArray) );
      got_time = sendableArray[2]*256 + sendableArray[3];
      unsigned long end_time = micros();
      
      // Spew it
      Serial.print(F("Sent "));
      Serial.print(send_time);
      Serial.print(F(", Got response "));
      Serial.print(got_time);
      Serial.print(F(", Round-trip delay "));
      Serial.print(end_time-start_time);
      Serial.println(F(" microseconds"));
    }

    // Try again 1s later
    delay(1000);
  }

/****************** Pong Back Role ***************************/
  if ( role == 0 ){
    unsigned long got_time;
    byte receivedData[5];
    
    if(radio.available()){                                         // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &receivedData, sizeof(receivedData) );             // Get the payload
      }
     
      radio.stopListening();                                        // First, stop listening so we can talk   
      radio.write( &receivedData, sizeof(receivedData) );              // Send the final one back.      
      radio.startListening();                                       // Now, resume listening so we catch the next packets.     
      Serial.print(F("Sent response "));
      Serial.print(receivedData[0]);
      Serial.print(receivedData[1]);
      Serial.print(receivedData[2]);
      Serial.print(receivedData[3]);
      Serial.println(receivedData[4]);  
    }
  }

/****************** Change Roles via Serial Commands ***************************/
  if ( Serial.available() ){
    char c = toupper(Serial.read());
    if ( c == 'T' && role == 0 ){      
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      role = 1;                  // Become the primary transmitter (ping out)
   } else if ( c == 'R' && role == 1 ){
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));      
      role = 0;                // Become the primary receiver (pong back)
      radio.startListening();
    }
  }
} // Loop

