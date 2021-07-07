/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017
   -------------------------------------------------------------------------------------
*/

/*
HX711_ADC configuration

Allowed values for "SAMPLES" is 1, 2, 4, 8, 16, 32, 64 or 128.
Higher value = improved filtering/smoothing of returned value, but longer settling time and increased memory usage
Lower value = vice versa

The settling time can be calculated as follows:
Settling time = SAMPLES + IGN_HIGH_SAMPLE + IGN_LOW_SAMPLE / SPS

Example on calculating settling time using the values SAMPLES = 16, IGN_HIGH_SAMPLE = 1, IGN_LOW_SAMPLE = 1, and HX711 sample rate set to 10SPS:
(16+1+1)/10 = 1.8 seconds settling time.

Note that you can also override (reducing) the number of samples in use at any time with the function: setSamplesInUse(samples).

*/

//number of samples in moving average dataset, value must be 1, 2, 4, 8, 16, 32, 64 or 128.
#ifdef HX711_SAMPLES
#define SAMPLES HX711_SAMPLES
#else
#define SAMPLES 16  // default value: 16
#endif

//adds extra sample(s) to the dataset and ignore peak high/low sample, value must be 0 or 1.
#ifdef HX711_IGN_HIGH_SAMPLE
#define IGN_HIGH_SAMPLE HX711_IGN_HIGH_SAMPLE
#else
#define IGN_HIGH_SAMPLE 1  // default value: 1
#endif
#ifdef HX711_IGN_LOW_SAMPLE
#define IGN_LOW_SAMPLE HX711_IGN_LOW_SAMPLE
#else
#define IGN_LOW_SAMPLE 1  // default value: 1
#endif

//microsecond delay after writing sck pin high or low. This delay could be required for faster mcu's.
//So far the only mcu reported to need this delay is the ESP32 (issue #35), both the Arduino Due and ESP8266 seems to run fine without it.
//Change the value to '1' to enable the delay.
#ifdef HX711_SCK_DELAY
#define SCK_DELAY HX711_SCK_DELAY
#else
#define SCK_DELAY 0  // default value: 0
#endif

//if you have some other time consuming (>60μs) interrupt routines that trigger while the sck pin is high, this could unintentionally set the HX711 into "power down" mode
//if required you can change the value to '1' to disable interrupts when writing to the sck pin.
#ifdef HX711_SCK_DISABLE_INTERRUPTS
#define SCK_DISABLE_INTERRUPTS HX711_SCK_DISABLE_INTERRUPTS
#else
#define SCK_DISABLE_INTERRUPTS 0  // default value: 0
#endif