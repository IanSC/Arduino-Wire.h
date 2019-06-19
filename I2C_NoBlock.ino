#include "Wire.h"

#define DS3231_ADDRESS 0x68

void setup() {

    Serial.begin( 9600 );
    delay( 100 );

    Serial.println( "begin()" );
    Wire.begin();

    //
    // NON-BLOCKING
    //
    Serial.println();
    Serial.println( "NON-BLOCKING..." );
    Wire.setTimeout( 1000 );
    RunTest();

    //
    // BLOCKING
    //    
    Serial.println();
    Serial.println( "BLOCKING..." );
    Wire.setTimeout( 0 ); // this is the default settings
    RunTest();
    
}

void RunTest() {
  
    Serial.println( "beginTransmission()" );
    Wire.beginTransmission( DS3231_ADDRESS );

    Serial.println( "write()" );
    if ( Wire.write( 0 ) != 1 )
        Serial.println( "   write error" );
    
    Serial.println( "endTransmission()" );
    uint8_t endTransmissionResult = Wire.endTransmission();
    switch ( endTransmissionResult ) {
    case 0:  Serial.println( "no error" ); break;
    case 1:  Serial.println( "length too long for buffer" ); break;
    case 2:  Serial.println( "address send, NACK received" ); break;
    case 3:  Serial.println( "data send, NACK received" ); break;
    case 4:  Serial.println( "other twi error" ); break;
    default: Serial.println( "unexpected error" ); break;
    }

    Serial.println( "requestFrom()" );
    uint8_t requestBytesRead = Wire.requestFrom( DS3231_ADDRESS, 1 );

    // if you can disconnect the wires at this exact moment
    // one would probably block and the other return 0 length
    if ( requestBytesRead != 1 )
        Serial.println( "   request error" );
    
    Serial.println( "read()" );
    uint8_t ss = Wire.read();
    //Serial.println( ss, BIN );
    bool isRunning = !(ss>>7);

    if( isRunning )
        Serial.println( "DS3231 is running" );
    else
        Serial.println( "DS3231 is NOT running" );    
}

void loop() {
}
