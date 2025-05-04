// Function Declarations
unsigned int readThermistor();
unsigned int readThermocouple();
unsigned int readPot();

void initADC();
#define FLAME_THRESHOLD 1000 // Adjustable!!
#define BUFFER 0
unsigned int readADC(char Channel);
int flame_Detect(void);