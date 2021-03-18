
///////////////////////////////////////////////////////////////////////////////
///  CHEEPROM
///  A programmer for 28C64 and 28C256 EEPROM chips from Atmel/Microchip
///////////////////////////////////////////////////////////////////////////////

#define HC595_DATA      (3)
#define HC595_CLR       (2)
#define HC595_CLK       (13)
#define HC595_RCLK     (12)

#define DATA_LOW        PORTB
#define DATA_HIGH       PORTD
#define DATA_LOW_MASK   0xF0
#define DATA_HIGH_MASK  0x0F
#define DATA_DDR_LOW    DDRB
#define DATA_DDR_HIGH   DDRD


#define WE              (14)
#define OE              (15)
#define CE              (16)



void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(19200);

  pinMode(HC595_DATA, OUTPUT);
  pinMode(HC595_CLR, OUTPUT);
  pinMode(HC595_CLK, OUTPUT);
  pinMode(HC595_RCLK, OUTPUT);
  pinMode(WE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, HIGH);
  digitalWrite(WE, HIGH);
  digitalWrite(OE, HIGH);

  digitalWrite(HC595_CLR, LOW);
  digitalWrite(HC595_CLR, HIGH);

  // set data bus pins to outputs
  uint8_t tmp = DATA_DDR_LOW;
  tmp |= 0x0F;
  DATA_DDR_LOW = tmp;
  tmp = DATA_DDR_HIGH;
  tmp |= 0xF0;
  DATA_DDR_HIGH = tmp;
  
  

}

void loop() 
{
  // put your main code here, to run repeatedly:

}

void setOE(int val)
{
  if(val == 0)
  {
    digitalWrite(OE, LOW);
  }
  else
  {
    digitalWrite(OE, HIGH);
  }
}

void setCE(int val)
{
  if(val == 0)
  {
    digitalWrite(CE, LOW);
  }
  else
  {
    digitalWrite(CE, HIGH);
  }
}

void setWE(int val)
{
  if(val == 0)
  {
    digitalWrite(WE, LOW);
  }
  else
  {
    digitalWrite(WE, HIGH);
  }
}


void writeData(uint8_t data)
{
  uint8_t tmp = 0;
  tmp = DATA_LOW;
  tmp &= DATA_LOW_MASK;
  tmp |= (data & 0x0f);
  DATA_LOW = tmp;
  tmp = 0;
  tmp = DATA_HIGH;
  tmp &= DATA_HIGH_MASK;
  
  
}
void writeAdress(uint16_t addr)
{
  int bit;
  for(int bits = 0; bits < 16; bits++)
  {
    bit = addr & 0x8000;
    addr <<=1;
    if(bit != 0)
    {
      digitalWrite(HC595_DATA, HIGH);
    }
    else
    {
      digitalWrite(HC595_DATA, LOW);
    }
    digitalWrite(HC595_CLK, LOW);
    digitalWrite(HC595_CLK, HIGH);
  }
  digitalWrite(HC595_RCLK, LOW);
  digitalWrite(HC595_RCLK, HIGH);
}
