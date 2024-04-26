#include <SPI.h>  // include the SPI library:


const int CS_X = 36;
const int CS_Y = 37;
const int CS_Z = 38;
const int clkPin = 25;

void setup() {
  Serial.println("Setting up the TMC4361 axes...");

  // set the slaveSelectPin as an output:
  pinMode (CS_X, OUTPUT);
  pinMode (CS_Y, OUTPUT);
  pinMode (CS_Z, OUTPUT);

  digitalWrite(CS_X,HIGH);  // make sure X axis is OFF
  digitalWrite(CS_Y,HIGH);  // make sure Y axis is OFF
  digitalWrite(CS_Z,HIGH);  // make sure Z axis is OFF

  analogWriteFrequency(clkPin, 18750000);  // try to get 18.75MHz clock signal out for TMC4361
  analogWrite(clkPin, 128);
  Serial.println("External clock signal for TMC4631 set...");

  delay(500);  // wait a bit for the TMC4361 to figure itself out.

  SPISettings spi_settings(2000000, MSBFIRST, SPI_MODE3); 

  // initialize SPI:
  SPI1.setMISO(39);
  SPI1.begin(); 
  SPI1.setMISO(39);
  SPI1.beginTransaction(spi_settings);
  Serial.println("SPI hardware initialised...");
  
  check_SPI(CS_X);
  check_SPI(CS_Y);
  check_SPI(CS_Z);

  byte spi_response[5];

  // set up motion axis X

  read_spi(CS_X, 0x20, spi_response);
  Serial.printf("Rampmode is:");
  print_spi_response(spi_response);

  read_spi(CS_X, 0x21, spi_response);
  Serial.printf("Position is:");
  print_spi_response(spi_response);

  // write ramp mode
  byte ramp_data[] = {0x20, 0x00, 0x00, 0x00, 0b00000101};  // POSITION mode, with trapezoidal ramp
  write_spi(CS_X, ramp_data);

  // write position
  byte xpos_data[] = {0x21, 0x00, 0xFF, 0xFF, 0xFF};
  write_spi(CS_X, xpos_data);
}

void loop() {
  
  delay(5000);
}

void print_spi_response(byte* response) {
  for (int i = 1; i < 5; i++) {
    Serial.printf("%x ", response[i]);
  } 
  Serial.printf("\n");
}

void check_SPI(int CS_pin) {
  /// checks if the TMC4361 at the CS_pin is giving the expected response.
  /// 
  /// It is recommend that you call this function before any SPI communication as the first response
  /// over SPI is nonsense or something. Anyway, this should make sure SPI is ready and working before
  /// you start going serious work over that serial interface.

  byte response[] = {0x00, 0x00, 0x00, 0x00, 0x00};
  read_spi(CS_pin, 0x00, response);  // read the general register (0x00)
  
  if (response[3] == 0x60 && response[4] == 0x20) {
    printf("SPI communication with CS %d is OK!\n", CS_pin);
  } else {
    printf("Did not get expected response over SPI for CS %d\n", CS_pin);
  }
}

void read_spi(int CS_pin, byte spi_register, byte* response) {
  /// Read register from SPI. 5 byte response, of which first contains information about status
  ///
  /// we first send 5 bytes to request the register info
  /// and then we can read the response back next SPI transmission. It doesn't really matter what we SEND in this 2nd transmission as long as its valid
  byte query[] = {spi_register,0x00,0x00,0x00,0x00};

  // take the SS pin low to select the chip:
  digitalWrite(CS_pin,LOW);

  Serial.printf("Reading register %x over SPI...",  spi_register);
  for (int i = 0; i < 5; i++) {
    SPI1.transfer(query[i]);
  } 

  digitalWrite(CS_pin,HIGH);  // take the SS pin high to de-select the chip

  // and read again, now the value should be latched and ready to read.
  read_spi_single(CS_pin, spi_register, response);
}

void read_spi_single(int CS_pin, byte spi_register, byte* response) {
  digitalWrite(CS_pin,LOW);  

  response[0] = SPI1.transfer(spi_register);
  for (int i = 1; i < 5; i++) {
    //Serial.printf("Query: %x\n", query[i]);
    response[i] = SPI1.transfer(0x00);
    //Serial.printf("got response (same cycle): %x\n", response[i]);
  } 

  // take the SS pin high to de-select the chip:
  digitalWrite(CS_pin,HIGH); 
}

void write_spi(int CS_pin, byte* data) {
  /// Write to register from SPI. data must be 5 byte array. Will check if the set values are actually set by reading back the register value over SPI.
  ///
  /// Note that the address SHOULD NOT contain the 0b10000000 (0x80) added to it, as this is done in the function. This makes the main
  /// code more readable.

  // to send write request we add 0b10000000 to the equivalent read address
  data[0] = data[0] + 0x80;

  digitalWrite(CS_pin,LOW);  // select chip
  Serial.printf("Writing over SPI: ");
  for (int i = 0; i < 5; i++) {
    Serial.printf("%x ", data[i]);
    SPI1.transfer(data[i]);
  }
  Serial.printf(" ... \n");
  digitalWrite(CS_pin,HIGH);  // take the SS pin high to de-select the chip

  // and we read back the value to check that it was set correctly
  byte readback[] = {0x00,0x00,0x00,0x00,0x00};
  read_spi_single(CS_pin, 0x00, readback);

  // compare values
  for (int i = 1; i < 5; i++) {
    // Serial.printf("readback %x \n", readback[i]);
    // Serial.printf("data %x \n", data[i]);
    if (readback[i] != data[i]) {
      Serial.printf("> SPI write mismatch: on byte %d, read %x but expected %x \n", i, readback[i], data[i]);
    }
  }
}