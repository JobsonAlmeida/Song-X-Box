#pragma once

#define PWM_CLOCK_SOURCE 125000000.0000000000

// C_5
#define C_5_FREQUENCY 523.2511 //Best Frequency Found: = 523.2512
#define C_5_WRAP 64783
#define C_5_INTEGER 3
#define C_5_FRACTIONAL 11.0000
#define C_5_DIVIDER 3.6875 

// Bs4
#define Bs4_FREQUENCY C_5_FREQUENCY 
#define Bs4_WRAP C_5_WRAP 
#define Bs4_INTEGER C_5_INTEGER
#define Bs4_FRACTIONAL C_5_FRACTIONAL
#define Bs4_DIVIDER (PWM_CLOCK_SOURCE/(Bs4_FREQUENCY*(Bs4_WRAP+1)))

// B_4
#define B_4_FREQUENCY 493.8833 //Best Frequency Found: = 493.8833
#define B_4_WRAP 51259
#define B_4_INTEGER 4
#define B_4_FRACTIONAL 15.0000
#define B_4_DIVIDER 4.9375 

// As4 - Bb4
#define As4_Bb4_FREQUENCY 466.1638 //Best Frequency Found: = 466.1637
#define As4_Bb4_WRAP 10645
#define As4_Bb4_INTEGER 25
#define As4_Bb4_FRACTIONAL 3.0000
#define As4_Bb4_DIVIDER 25.1875 

// A_4
#define A_4_FREQUENCY 440.0000 //Best Frequency Found: = 440.0002
#define A_4_WRAP 25112
#define A_4_INTEGER 11
#define A_4_FRACTIONAL 5.0000
#define A_4_DIVIDER 11.3125 

// Gs4 - Ab4
#define Gs4_Ab4_FREQUENCY 415.3047 //Best Frequency Found: = 415.3046
#define Gs4_Ab4_WRAP 55996
#define Gs4_Ab4_INTEGER 5
#define Gs4_Ab4_FRACTIONAL 6.0000
#define Gs4_Ab4_DIVIDER 5.3750 

// G_4
#define G_4_FREQUENCY 391.9954 //Best Frequency Found: = 391.9955
#define G_4_WRAP 56689
#define G_4_INTEGER 5
#define G_4_FRACTIONAL 10.0000
#define G_4_DIVIDER 5.6250 

// Fs4 - Gb4
#define Fs4_Gb4_FREQUENCY 369.9944 //Best Frequency Found: = 369.9944
#define Fs4_Gb4_WRAP 61425
#define Fs4_Gb4_INTEGER 5
#define Fs4_Gb4_FRACTIONAL 8.0000
#define Fs4_Gb4_DIVIDER 5.5000 
// F_4
#define F_4_FREQUENCY 349.2282 //Best Frequency Found: = 349.2281
#define F_4_WRAP 21610
#define F_4_INTEGER 16
#define F_4_FRACTIONAL 9.0000
#define F_4_DIVIDER 16.5625 

// Fb4
#define Fb4_FREQUENCY E_4_FREQUENCY
#define Fb4_WRAP E_4_WRAP
#define Fb4_INTEGER E_4_INTEGER
#define Fb4_FRACTIONAL E_4_FRACTIONAL
#define Fb4_DIVIDER (PWM_CLOCK_SOURCE/(Fb4_FREQUENCY*(Fb4_WRAP+1)))

// Es4
#define Es4_FREQUENCY F_4_FREQUENCY 
#define Es4_WRAP F_4_WRAP 
#define Es4_INTEGER F_4_INTEGER
#define Es4_FRACTIONAL F_4_FRACTIONAL 
#define Es4_DIVIDER (PWM_CLOCK_SOURCE/(Es4_FREQUENCY*(Es4_WRAP+1)))

// E_4
#define E_4_FREQUENCY 329.6276	//Best Frequency Found: = 329.6276
#define E_4_WRAP 50986
#define E_4_INTEGER 7
#define E_4_FRACTIONAL 7.0000
#define E_4_DIVIDER 7.4375 

// Ds4 - Eb4
#define Ds4_Eb4_FREQUENCY 311.1270 //Best Frequency Found: = 311.1270
#define Ds4_Eb4_WRAP 4986
#define Ds4_Eb4_INTEGER 80
#define Ds4_Eb4_FRACTIONAL 9.0000
#define Ds4_Eb4_DIVIDER 80.5625 

// D_4
#define D_4_FREQUENCY 293.6648 //Best Frequency Found: = 293.6648
#define D_4_WRAP 37626
#define D_4_INTEGER 11
#define D_4_FRACTIONAL 5.0000
#define D_4_DIVIDER 11.3125 

// Cs4 - Db4
#define Cs4_Db4_FREQUENCY 277.1826 //Best Frequency Found: = 277.1826
#define Cs4_Db4_WRAP 51538
#define Cs4_Db4_INTEGER 8
#define Cs4_Db4_FRACTIONAL 12.0000
#define Cs4_Db4_DIVIDER 8.7500 

// C_4
#define C_4_FREQUENCY 261.6256 //Best Frequency Found: = 261.6256
#define C_4_WRAP 64783
#define C_4_INTEGER 7
#define C_4_FRACTIONAL 6.0000
#define C_4_DIVIDER 7.3750 

// Cb4
#define Cb4_FREQUENCY B_3_FREQUENCY
#define Cb4_WRAP B_3_WRAP
#define Cb4_INTEGER B_3_INTEGER
#define Cb4_FRACTIONAL B_3_FRACTIONAL
#define Cb4_DIVIDER B_3_DIVIDER

// Bs3
#define Bs3_FREQUENCY 
#define Bs3_WRAP 
#define Bs3_INTEGER 
#define Bs3_FRACTIONAL 
#define Bs3_DIVIDER (PWM_CLOCK_SOURCE/(Bs3_FREQUENCY*(Bs3_WRAP+1)))

// B_3
#define B_3_FREQUENCY 246.9417 //Best Frequency Found: = 246.9417
#define B_3_WRAP 16837
#define B_3_INTEGER 30
#define B_3_FRACTIONAL 1.0000
#define B_3_DIVIDER 30.0625 

// Bb3
#define Bb4_FREQUENCY 
#define Bb4_WRAP 
#define Bb4_INTEGER 
#define Bb4_FRACTIONAL 
#define Bb4_DIVIDER (PWM_CLOCK_SOURCE/(Bb4_FREQUENCY*(Bb4_WRAP+1)))










// Bs4
#define Bs4_FREQUENCY C_5_FREQUENCY 
#define Bs4_WRAP C_5_WRAP 
#define Bs4_INTEGER C_5_INTEGER
#define Bs4_FRACTIONAL C_5_FRACTIONAL
#define Bs4_DIVIDER (PWM_CLOCK_SOURCE/(Bs4_FREQUENCY*(Bs4_WRAP+1)))

// B_4
#define B_4_FREQUENCY
#define B_4_WRAP 
#define B_4_INTEGER 
#define B_4_FRACTIONAL 
#define B_4_DIVIDER 

// As4 - Bb4
#define As4_Bb4_FREQUENCY 
#define As4_Bb4_WRAP 
#define As4_Bb4_INTEGER 
#define As4_Bb4_FRACTIONAL 
#define As4_Bb4_DIVIDER 

// A_4
#define A_4_FREQUENCY 
#define A_4_WRAP 
#define A_4_INTEGER 
#define A_4_FRACTIONAL 
#define A_4_DIVIDER 

// Gs4 - Ab4
#define Gs4_Ab4_FREQUENCY 
#define Gs4_Ab4_WRAP 
#define Gs4_Ab4_INTEGER 
#define Gs4_Ab4_FRACTIONAL 
#define Gs4_Ab4_DIVIDER  

// G_4
#define G_4_FREQUENCY 
#define G_4_WRAP 
#define G_4_INTEGER
#define G_4_FRACTIONAL 
#define G_4_DIVIDER 

// Fs4 - Gb4
#define Fs4_Gb4_FREQUENCY 
#define Fs4_Gb4_WRAP 
#define Fs4_Gb4_INTEGER
#define Fs4_Gb4_FRACTIONAL 
#define Fs4_Gb4_DIVIDER  
// F_4
#define F_4_FREQUENCY 
#define F_4_WRAP 
#define F_4_INTEGER 
#define F_4_FRACTIONAL
#define F_4_DIVIDER 

// Fb4
#define Fb4_FREQUENCY E_4_FREQUENCY
#define Fb4_WRAP E_4_WRAP
#define Fb4_INTEGER E_4_INTEGER
#define Fb4_FRACTIONAL E_4_FRACTIONAL
#define Fb4_DIVIDER (PWM_CLOCK_SOURCE/(Fb4_FREQUENCY*(Fb4_WRAP+1)))

// Es3
#define Es3_FREQUENCY F_3_FREQUENCY 
#define Es3_WRAP F_3_WRAP 
#define Es3_INTEGER F_3_INTEGER
#define Es3_FRACTIONAL F_3_FRACTIONAL 
#define Es3_DIVIDER (PWM_CLOCK_SOURCE/(Es3_FREQUENCY*(Es3_WRAP+1)))

// E_3
#define E_3_FREQUENCY 
#define E_3_WRAP 
#define E_3_INTEGER 
#define E_3_FRACTIONAL 
#define E_3_DIVIDER  

// Ds3 - Eb3
#define Ds3_Eb3_FREQUENCY 
#define Ds3_Eb3_WRAP 
#define Ds3_Eb3_INTEGER 
#define Ds3_Eb3_FRACTIONAL 
#define Ds3_Eb3_DIVIDER 

// D_3
#define D_3_FREQUENCY 
#define D_3_WRAP 
#define D_3_INTEGER 
#define D_3_FRACTIONAL 
#define D_3_DIVIDER 

// Cs3 - Db3
#define Cs3_Db3_FREQUENCY 
#define Cs3_Db3_WRAP 
#define Cs3_Db3_INTEGER 
#define Cs3_Db3_FRACTIONAL 
#define Cs3_Db3_DIVIDER  

// C_3
#define C_3_FREQUENCY 
#define C_3_WRAP 
#define C_3_INTEGER 
#define C_3_FRACTIONAL 
#define C_3_DIVIDER 

// Cb3
#define Cb3_FREQUENCY B_2_FREQUENCY
#define Cb3_WRAP B_2_WRAP
#define Cb3_INTEGER B_2_INTEGER
#define Cb3_FRACTIONAL B_2_FRACTIONAL
#define Cb_DIVIDER 