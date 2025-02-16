#pragma once

#define PWM_CLOCK_SOURCE 125000000.0000000000

// C_6
#define C_6_FREQUENCY 1046.502 //Best Frequency Found: = 1046.5018
#define C_6_WRAP 57912
#define C_6_INTEGER 2
#define C_6_FRACTIONAL 1.0000
#define C_6_DIVIDER 2.0625

//------------------------------------------------------------------

// Bs5
#define Bs5_FREQUENCY C_6_FREQUENCY 
#define Bs5_WRAP C_6_WRAP 
#define Bs5_INTEGER C_6_INTEGER
#define Bs5_FRACTIONAL C_6_FRACTIONAL
#define Bs5_DIVIDER C_6_DIVIDER

// B_5
#define B_5_FREQUENCY 987.7666 //Best Frequency Found: = 987.7665
#define B_5_WRAP 36813
#define B_5_INTEGER 3
#define B_5_FRACTIONAL 7.0000 
#define B_5_DIVIDER 3.4375

// As5 - Bb5
#define As5_Bb5_FREQUENCY 932.3275 //Best Frequency Found: = 932.3275
#define As5_Bb5_WRAP 5322
#define As5_Bb5_INTEGER 25
#define As5_Bb5_FRACTIONAL 3.0000
#define As5_Bb5_DIVIDER 25.1875

// A_5
#define A_5_FREQUENCY 880.0000 //Best Frequency Found: = 879.9997
#define A_5_WRAP 8087
#define A_5_INTEGER 17
#define A_5_FRACTIONAL 9.0000
#define A_5_DIVIDER 17.5625

// Gs5 - Ab5
#define Gs5_Ab5_FREQUENCY 830.6094 //Best Frequency Found: = 830.6093
#define Gs5_Ab5_WRAP 55996
#define Gs5_Ab5_INTEGER 2
#define Gs5_Ab5_FRACTIONAL 11.0000
#define Gs5_Ab5_DIVIDER 2.6875

// G_5
#define G_5_FREQUENCY 783.9909 //Best Frequency Found: = 783.9909
#define G_5_WRAP 56689
#define G_5_INTEGER 2
#define G_5_FRACTIONAL 13.0000
#define G_5_DIVIDER 2.8125

// Fs5 - Gb5
#define Fs5_Gb5_FREQUENCY 739.9888 //Best Frequency Found: = 739.9887
#define Fs5_Gb5_WRAP 61425
#define Fs5_Gb5_INTEGER 2
#define Fs5_Gb5_FRACTIONAL 12.0000
#define Fs5_Gb5_DIVIDER 2.7500

// F_5
#define F_5_FREQUENCY 698.4565 //Best Frequency Found: = 698.4567
#define F_5_WRAP 33295
#define F_5_INTEGER 5
#define F_5_FRACTIONAL 6.0000
#define F_5_DIVIDER 5.3750  

// Fb5
#define Fb5_FREQUENCY E_5_FREQUENCY
#define Fb5_WRAP E_5_WRAP
#define Fb5_INTEGER E_5_INTEGER
#define Fb5_FRACTIONAL E_5_FRACTIONAL
#define Fb5_DIVIDER E_5_DIVIDER

// Es5
#define Es5_FREQUENCY F_5_FREQUENCY 
#define Es5_WRAP F_5_WRAP 
#define Es5_INTEGER F_5_INTEGER
#define Es5_FRACTIONAL F_5_FRACTIONAL 
#define Es5_DIVIDER F_5_DIVIDER

// E_5
#define E_5_FREQUENCY 659.2551	//Best Frequency Found: = 659.2553
#define E_5_WRAP 7205
#define E_5_INTEGER 26
#define E_5_FRACTIONAL 5.0000
#define E_5_DIVIDER 26.3125

// Ds5 - Eb5
#define Ds5_Eb5_FREQUENCY 622.2540 //Best Frequency Found: = 622.2539
#define Ds5_Eb5_WRAP 63021
#define Ds5_Eb5_INTEGER 3
#define Ds5_Eb5_FRACTIONAL 3.0000
#define Ds5_Eb5_DIVIDER 3.1875

// D_5
#define D_5_FREQUENCY 587.3295 //Best Frequency Found: = 587.3294
#define D_5_WRAP 57715
#define D_5_INTEGER 3
#define D_5_FRACTIONAL 11.0000
#define D_5_DIVIDER 3.6875

// Cs5 - Db5
#define Cs5_Db5_FREQUENCY 554.3653 //Best Frequency Found: = 554.3652
#define Cs5_Db5_WRAP 51538
#define Cs5_Db5_INTEGER 4
#define Cs5_Db5_FRACTIONAL 6.0000
#define Cs5_Db5_DIVIDER 4.3750

// C_5
#define C_5_FREQUENCY 523.2511 //Best Frequency Found: = 523.2512
#define C_5_WRAP 64783
#define C_5_INTEGER 3
#define C_5_FRACTIONAL 11.0000
#define C_5_DIVIDER 3.6875

// Cb5
#define Cb5_FREQUENCY B_4_FREQUENCY
#define Cb5_WRAP B_4_WRAP
#define Cb5_INTEGER B_4_INTEGER
#define Cb5_FRACTIONAL B_4_FRACTIONAL
#define Cb5_DIVIDER B_4_DIVIDER

//--------------------------------------------------------------------

// Bs4
#define Bs4_FREQUENCY C_5_FREQUENCY 
#define Bs4_WRAP C_5_WRAP 
#define Bs4_INTEGER C_5_INTEGER
#define Bs4_FRACTIONAL C_5_FRACTIONAL
#define Bs4_DIVIDER C_5_DIVIDER

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
#define Fb4_DIVIDER E_4_DIVIDER

// Es4
#define Es4_FREQUENCY F_4_FREQUENCY 
#define Es4_WRAP F_4_WRAP 
#define Es4_INTEGER F_4_INTEGER
#define Es4_FRACTIONAL F_4_FRACTIONAL 
#define Es4_DIVIDER F_4_DIVIDER

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

//--------------------------------------------------------------------

// Bs3
#define Bs3_FREQUENCY C_4_FREQUENCY 
#define Bs3_WRAP C_4_WRAP 
#define Bs3_INTEGER C_4_INTEGER
#define Bs3_FRACTIONAL C_4_FRACTIONAL
#define Bs3_DIVIDER C_4_DIVIDER

// B_3
#define B_3_FREQUENCY 246.9417 //Best Frequency Found: = 246.9417
#define B_3_WRAP 16837
#define B_3_INTEGER 30
#define B_3_FRACTIONAL 1.0000
#define B_3_DIVIDER 30.0625 

// As3 - Bb3
#define As3_Bb3_FREQUENCY 233.0819 //Best Frequency Found: = 233.0819
#define As3_Bb3_WRAP 44924
#define As3_Bb3_INTEGER 11
#define As3_Bb3_FRACTIONAL 15.0000
#define As3_Bb3_DIVIDER 11.9375

// A_3
#define A_3_FREQUENCY 220.0000 //Best Frequency Found: = 220.0000
#define A_3_WRAP 41510
#define A_3_INTEGER 13
#define A_3_FRACTIONAL 11.0000
#define A_3_DIVIDER 13.6875

// Gs3 - Ab3
#define Gs3_Ab3_FREQUENCY 207.6523	//Best Frequency Found: = 207.6523
#define Gs3_Ab3_WRAP 58020
#define Gs3_Ab3_INTEGER 10
#define Gs3_Ab3_FRACTIONAL 6.0000 
#define Gs3_Ab3_DIVIDER 10.3750

// G_3
#define G_3_FREQUENCY 195.9977 //Best Frequency Found: = 195.9977
#define G_3_WRAP 61102
#define G_3_INTEGER 10
#define G_3_FRACTIONAL 7.0000
#define G_3_DIVIDER 10.4375

// Fs3 - Gb3
#define Fs3_Gb3_FREQUENCY 184.9972 //Best Frequency Found: = 184.9971
#define Fs3_Gb3_WRAP 63593
#define Fs3_Gb3_INTEGER 10
#define Fs3_Gb3_FRACTIONAL 10.0000
#define Fs3_Gb3_DIVIDER 10.6250

// F_3
#define F_3_FREQUENCY 174.6141 //Best Frequency Found: = 174.6141
#define F_3_WRAP 54802
#define F_3_INTEGER 13
#define F_3_FRACTIONAL 1.0000
#define F_3_DIVIDER 13.0625

// Fb3
#define Fb3_FREQUENCY E_3_FREQUENCY
#define Fb3_WRAP E_3_WRAP
#define Fb3_INTEGER E_3_INTEGER
#define Fb3_FRACTIONAL E_3_FRACTIONAL
#define Fb3_DIVIDER E_3_DIVIDER

// Es3
#define Es3_FREQUENCY F_3_FREQUENCY 
#define Es3_WRAP F_3_WRAP 
#define Es3_INTEGER F_3_INTEGER
#define Es3_FRACTIONAL F_3_FRACTIONAL 
#define Es3_DIVIDER F_3_DIVIDER

// E_3
#define E_3_FREQUENCY 164.8138 //Best Frequency Found: = 164.8138
#define E_3_WRAP 50986
#define E_3_INTEGER 14
#define E_3_FRACTIONAL 14.0000
#define E_3_DIVIDER 14.8750

// Ds3 - Eb3
#define Ds3_Eb3_FREQUENCY 155.5635 //Best Frequency Found: = 155.5635
#define Ds3_Eb3_WRAP 9973
#define Ds3_Eb3_INTEGER 80
#define Ds3_Eb3_FRACTIONAL 9.0000
#define Ds3_Eb3_DIVIDER 80.5625

// D_3
#define D_3_FREQUENCY 146.8324 //Best Frequency Found: = 146.8324
#define D_3_WRAP 37626
#define D_3_INTEGER 22
#define D_3_FRACTIONAL 10.0000
#define D_3_DIVIDER 22.6250

// Cs3 - Db3
#define Cs3_Db3_FREQUENCY 138.5913 //Best Frequency Found: = 138.5913
#define Cs3_Db3_WRAP 51538
#define Cs3_Db3_INTEGER 17
#define Cs3_Db3_FRACTIONAL 8.0000
#define Cs3_Db3_DIVIDER 17.5000

// C_3
#define C_3_FREQUENCY 130.8128 //Best Frequency Found: = 130.8128
#define C_3_WRAP 64783
#define C_3_INTEGER 14
#define C_3_FRACTIONAL 12.0000
#define C_3_DIVIDER 14.7500

// Cb3
#define Cb3_FREQUENCY B_2_FREQUENCY
#define Cb3_WRAP B_2_WRAP
#define Cb3_INTEGER B_2_INTEGER
#define Cb3_FRACTIONAL B_2_FRACTIONAL
#define Cb3_DIVIDER B_2_DIVIDER

//------------------------------------------------------------------

// Bs2
#define Bs2_FREQUENCY C_3_FREQUENCY 
#define Bs2_WRAP C_3_WRAP 
#define Bs2_INTEGER C_3_INTEGER
#define Bs2_FRACTIONAL C_3_FRACTIONAL
#define Bs2_DIVIDER C_3_DIVIDER

// B_2
#define B_2_FREQUENCY 123.4708 //Best Frequency Found: = 123.4708
#define B_2_WRAP 56048
#define B_2_INTEGER 18
#define B_2_FRACTIONAL 1.0000
#define B_2_DIVIDER 18.0625
















// //------------------------------------------------------------------

// // Bs5
// #define Bs5_FREQUENCY C_6_FREQUENCY 
// #define Bs5_WRAP C_6_WRAP 
// #define Bs5_INTEGER C_6_INTEGER
// #define Bs5_FRACTIONAL C_6_FRACTIONAL
// #define Bs5_DIVIDER C_6_DIVIDER

// // B_5
// #define B_5_FREQUENCY 
// #define B_5_WRAP 
// #define B_5_INTEGER 
// #define B_5_FRACTIONAL 
// #define B_5_DIVIDER 

// // As5 - Bb5
// #define As5_Bb5_FREQUENCY 
// #define As5_Bb5_WRAP 
// #define As5_Bb5_INTEGER 
// #define As5_Bb5_FRACTIONAL 
// #define As5_Bb5_DIVIDER 

// // A_5
// #define A_5_FREQUENCY 
// #define A_5_WRAP 
// #define A_5_INTEGER 
// #define A_5_FRACTIONAL 
// #define A_5_DIVIDER  

// // Gs5 - Ab5
// #define Gs5_Ab5_FREQUENCY 
// #define Gs5_Ab5_WRAP 
// #define Gs5_Ab5_INTEGER 
// #define Gs5_Ab5_FRACTIONAL 
// #define Gs5_Ab5_DIVIDER  

// // G_5
// #define G_5_FREQUENCY 
// #define G_5_WRAP 
// #define G_5_INTEGER 
// #define G_5_FRACTIONAL 
// #define G_5_DIVIDER  

// // Fs5 - Gb5
// #define Fs5_Gb5_FREQUENCY 
// #define Fs5_Gb5_WRAP 
// #define Fs5_Gb5_INTEGER 
// #define Fs5_Gb5_FRACTIONAL 
// #define Fs5_Gb5_DIVIDER 

// // F_5
// #define F_5_FREQUENCY 
// #define F_5_WRAP 
// #define F_5_INTEGER 
// #define F_5_FRACTIONAL 
// #define F_5_DIVIDER  

// // Fb5
// #define Fb5_FREQUENCY E_5_FREQUENCY
// #define Fb5_WRAP E_5_WRAP
// #define Fb5_INTEGER E_5_INTEGER
// #define Fb5_FRACTIONAL E_5_FRACTIONAL
// #define Fb5_DIVIDER E_5_DIVIDER

// // Es5
// #define Es5_FREQUENCY F_5_FREQUENCY 
// #define Es5_WRAP F_5_WRAP 
// #define Es5_INTEGER F_5_INTEGER
// #define Es5_FRACTIONAL F_5_FRACTIONAL 
// #define Es5_DIVIDER F_5_DIVIDER

// // E_5
// #define E_5_FREQUENCY 
// #define E_5_WRAP 
// #define E_5_INTEGER 
// #define E_5_FRACTIONAL 
// #define E_5_DIVIDER 

// // Ds5 - Eb5
// #define Ds5_Eb5_FREQUENCY 
// #define Ds5_Eb5_WRAP 
// #define Ds5_Eb5_INTEGER 
// #define Ds5_Eb5_FRACTIONAL 
// #define Ds5_Eb5_DIVIDER 

// // D_5
// #define D_5_FREQUENCY 
// #define D_5_WRAP 
// #define D_5_INTEGER 
// #define D_5_FRACTIONAL 
// #define D_5_DIVIDER 

// // Cs5 - Db5
// #define Cs5_Db5_FREQUENCY 
// #define Cs5_Db5_WRAP 
// #define Cs5_Db5_INTEGER 
// #define Cs5_Db5_FRACTIONAL 
// #define Cs5_Db5_DIVIDER 

// // C_5
// #define C_5_FREQUENCY 
// #define C_5_WRAP 
// #define C_5_INTEGER 
// #define C_5_FRACTIONAL 
// #define C_5_DIVIDER 

// // Cb5
// #define Cb5_FREQUENCY B_4_FREQUENCY
// #define Cb5_WRAP B_4_WRAP
// #define Cb5_INTEGER B_4_INTEGER
// #define Cb5_FRACTIONAL B_4_FRACTIONAL
// #define Cb5_DIVIDER B_4_DIVIDER

// //--------------------------------------------------------------------