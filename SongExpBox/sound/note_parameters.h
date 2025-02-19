#pragma once

#define PWM_CLOCK_SOURCE 125000000.0000000000

// C_10
#define C_10_FREQUENCY 16744.036 //Best Frequency Found: = 16744.2480
#define C_10_WRAP 4593
#define C_10_INTEGER 1
#define C_10_FRACTIONAL 10.0000
#define C_10_DIVIDER  1.6250

//--------------------------------------------------------------------

// Bs9
#define Bs9_FREQUENCY C_10_FREQUENCY 
#define Bs9_WRAP C_10_WRAP 
#define Bs9_INTEGER C_10_INTEGER
#define Bs9_FRACTIONAL C_10_FRACTIONAL
#define Bs9_DIVIDER C_10_DIVIDER

// B_9
#define B_9_FREQUENCY 15804.266 //Best Frequency Found: = 15804.2803
#define B_9_WRAP 7443
#define B_9_INTEGER 1
#define B_9_FRACTIONAL 1.0000
#define B_9_DIVIDER 1.0625 

// As4 - Bb4
#define As9_Bb9_FREQUENCY 14917.240 //Best Frequency Found: = 14917.1357
#define As9_Bb9_WRAP 3117
#define As9_Bb9_INTEGER 2
#define As9_Bb9_FRACTIONAL 11.0000
#define As9_Bb9_DIVIDER 2.6875

// A_9
#define A_9_FREQUENCY 14080.000 //Best Frequency Found: = 14080.1445
#define A_9_WRAP 7475
#define A_9_INTEGER 1
#define A_9_FRACTIONAL 3.0000
#define A_9_DIVIDER 1.1875

// Gs9 - Ab9
#define Gs9_Ab9_FREQUENCY 13289.750 //Best Frequency Found: = 13289.9199
#define Gs9_Ab9_WRAP 1489
#define Gs9_Ab9_INTEGER 6
#define Gs9_Ab9_FRACTIONAL 5.0000 
#define Gs9_Ab9_DIVIDER 6.3126 

// G_9
#define G_9_FREQUENCY 12543.854 //Best Frequency Found: = 12543.9033
#define G_9_WRAP 7971
#define G_9_INTEGER 1
#define G_9_FRACTIONAL 4.0000
#define G_9_DIVIDER 1.2500

// Fs9 - Gb9
#define Fs9_Gb9_FREQUENCY 11839.822 //Best Frequency Found: = 11839.8545
#define Fs9_Gb9_WRAP 1232 
#define Fs9_Gb9_INTEGER 8
#define Fs9_Gb9_FRACTIONAL 9.0000
#define Fs9_Gb9_DIVIDER 8.5625 

// F_9
#define F_9_FREQUENCY 11175.304 //Best Frequency Found: = 11175.3066
#define F_9_WRAP 4161
#define F_9_INTEGER 2
#define F_9_FRACTIONAL 11.0000
#define F_9_DIVIDER 2.6875

// Fb9
#define Fb9_FREQUENCY E_9_FREQUENCY
#define Fb9_WRAP E_9_WRAP
#define Fb9_INTEGER E_9_INTEGER
#define Fb9_FRACTIONAL E_9_FRACTIONAL
#define Fb9_DIVIDER E_9_DIVIDER

// Es9
#define Es9_FREQUENCY F_9_FREQUENCY 
#define Es9_WRAP F_9_WRAP 
#define Es9_INTEGER F_9_INTEGER
#define Es9_FRACTIONAL F_9_FRACTIONAL 
#define Es9_DIVIDER F_9_DIVIDER

// E_9
#define E_9_FREQUENCY 10548.082 //Best Frequency Found: = 10548.0781
#define E_9_WRAP 1383
#define E_9_INTEGER 8
#define E_9_FRACTIONAL 9.0000
#define E_9_DIVIDER 8.5625 

// Ds9 - Eb9
#define Ds9_Eb9_FREQUENCY 9956.064 //Best Frequency Found: = 9956.0439
#define Ds9_Eb9_WRAP 6926
#define Ds9_Eb9_INTEGER 1
#define Ds9_Eb9_FRACTIONAL 13.0000
#define Ds9_Eb9_DIVIDER 1.8125

// D_9
#define D_9_FREQUENCY 9397.272 //Best Frequency Found: = 9397.2598
#define D_9_WRAP 9673
#define D_9_INTEGER 1
#define D_9_FRACTIONAL 6.0000
#define D_9_DIVIDER 1.3750

// Cs9 - Db9
#define Cs9_Db9_FREQUENCY 8869.844 //Best Frequency Found: = 8869.8086
#define Cs9_Db9_WRAP 8052
#define Cs9_Db9_INTEGER 1
#define Cs9_Db9_FRACTIONAL 12.0000
#define Cs9_Db9_DIVIDER 1.7500

// C_9
#define C_9_FREQUENCY 8372.018 //Best Frequency Found: = 8372.0186
#define C_9_WRAP 4048
#define C_9_INTEGER 3
#define C_9_FRACTIONAL 11.0000
#define C_9_DIVIDER 3.6875 

// Cb9
#define Cb9_FREQUENCY B_8_FREQUENCY
#define Cb9_WRAP B_8_WRAP
#define Cb9_INTEGER B_8_INTEGER
#define Cb9_FRACTIONAL B_8_FRACTIONAL
#define Cb9_DIVIDER B_8_DIVIDER

//--------------------------------------------------------------------

// Bs8
#define Bs8_FREQUENCY C_9_FREQUENCY 
#define Bs8_WRAP C_9_WRAP 
#define Bs8_INTEGER C_9_INTEGER
#define Bs8_FRACTIONAL C_9_FRACTIONAL
#define Bs8_DIVIDER C_9_DIVIDER

// B_8
#define B_8_FREQUENCY 7458.620	//Best Frequency Found: = 7458.6230
#define B_8_WRAP 14896
#define B_8_INTEGER 1
#define B_8_FRACTIONAL 2.0000
#define B_8_DIVIDER 1.1250

// As8 - Bb8
#define As8_Bb8_FREQUENCY 
#define As8_Bb8_WRAP 
#define As8_Bb8_INTEGER 
#define As8_Bb8_FRACTIONAL 
#define As8_Bb8_DIVIDER  

// A_8
#define A_8_FREQUENCY 7040.000 //Best Frequency Found: = 7039.9976
#define A_8_WRAP 1010
#define A_8_INTEGER 17
#define A_8_FRACTIONAL 9.0000
#define A_8_DIVIDER 17.5625 

// Gs4 - Ab4
#define Gs8_Ab8_FREQUENCY 6644.875 //Best Frequency Found: = 6644.8716
#define Gs8_Ab8_WRAP 12540
#define Gs8_Ab8_INTEGER 1
#define Gs8_Ab8_FRACTIONAL 8.0000
#define Gs8_Ab8_DIVIDER 1.5000 

// G_8
#define G_8_FREQUENCY 6271.927 //Best Frequency Found: = 6271.9517	
#define G_8_WRAP 15943
#define G_8_INTEGER 1
#define G_8_FRACTIONAL 4.0000 
#define G_8_DIVIDER 1.2500 

// Fs8 - Gb8
#define Fs8_Gb8_FREQUENCY 5919.911 //Best Frequency Found: = 5919.9272
#define Fs8_Gb8_WRAP 18768
#define Fs8_Gb8_INTEGER 1 
#define Fs8_Gb8_FRACTIONAL 2.0000
#define Fs8_Gb8_DIVIDER 1.1250 

// F_8
#define F_8_FREQUENCY 5587.652 //Best Frequency Found: = 5587.6533
#define F_8_WRAP 8323
#define F_8_INTEGER 2
#define F_8_FRACTIONAL 11.0000
#define F_8_DIVIDER 2.6875 

// Fb8
#define Fb8_FREQUENCY E_8_FREQUENCY
#define Fb8_WRAP E_8_WRAP
#define Fb8_INTEGER E_8_INTEGER
#define Fb8_FRACTIONAL E_8_FRACTIONAL
#define Fb8_DIVIDER E_8_DIVIDER

// Es8
#define Es8_FREQUENCY F_8_FREQUENCY 
#define Es8_WRAP F_8_WRAP 
#define Es8_INTEGER F_8_INTEGER
#define Es8_FRACTIONAL F_8_FRACTIONAL 
#define Es8_DIVIDER F_8_DIVIDER

// E_8
#define E_8_FREQUENCY 5274.041	//Best Frequency Found: = 5274.0391
#define E_8_WRAP 2767
#define E_8_INTEGER 8
#define E_8_FRACTIONAL 9.0000
#define E_8_DIVIDER 8.5625 

// Ds8 - Eb8
#define Ds8_Eb8_FREQUENCY 4978.032 //Best Frequency Found: = 4978.0342
#define Ds8_Eb8_WRAP 11478
#define Ds8_Eb8_INTEGER 2
#define Ds8_Eb8_FRACTIONAL 3.0000
#define Ds8_Eb8_DIVIDER 2.1875

// D_8
#define D_8_FREQUENCY 4698.636 //Best Frequency Found: = 4698.6411
#define D_8_WRAP 15764
#define D_8_INTEGER 1
#define D_8_FRACTIONAL 11.0000
#define D_8_DIVIDER 1.6875

// Cs8 - Db8
#define Cs8_Db8_FREQUENCY 4434.922 //Best Frequency Found: = 4434.9141
#define Cs8_Db8_WRAP 3726
#define Cs8_Db8_INTEGER 7
#define Cs8_Db8_FRACTIONAL 9.0000
#define Cs8_Db8_DIVIDER 7.5625

// C_8
#define C_8_FREQUENCY 4186.009 //Best Frequency Found: = 4186.0093	
#define C_8_WRAP 8097
#define C_8_INTEGER 3
#define C_8_FRACTIONAL 11.0000 
#define C_8_DIVIDER 3.6875

// Cb8
#define Cb8_FREQUENCY B_7_FREQUENCY
#define Cb8_WRAP B_7_WRAP
#define Cb8_INTEGER B_7_INTEGER
#define Cb8_FRACTIONAL B_7_FRACTIONAL
#define Cb8_DIVIDER B_37_DIVIDER

//--------------------------------------------------------------------

// Bs7
#define Bs7_FREQUENCY C_8_FREQUENCY 
#define Bs7_WRAP C_8_WRAP 
#define Bs7_INTEGER C_8_INTEGER
#define Bs7_FRACTIONAL C_8_FRACTIONAL
#define Bs7_DIVIDER C_8_DIVIDER

// B_7
#define B_7_FREQUENCY 3951.066	//Best Frequency Found: = 3951.0701
#define B_7_WRAP 29775
#define B_7_INTEGER 1
#define B_7_FRACTIONAL 1.0000
#define B_7_DIVIDER 1.0625

// As7 - Bb7
#define As7_Bb7_FREQUENCY 3729.310 //Best Frequency Found: = 3729.3115
#define As7_Bb7_WRAP 29793
#define As7_Bb7_INTEGER 1
#define As7_Bb7_FRACTIONAL 2.0000
#define As7_Bb7_DIVIDER 1.1250 

// A_7
#define A_7_FREQUENCY 3520.000 //Best Frequency Found: = 3519.9988
#define A_7_WRAP 2021
#define A_7_INTEGER 17
#define A_7_FRACTIONAL 9.0000
#define A_7_DIVIDER 17.5625 

// Gs7 - Ab7
#define Gs7_Ab7_FREQUENCY 3322.438 //Best Frequency Found: = 3322.4358
#define Gs7_Ab7_WRAP 25081
#define Gs7_Ab7_INTEGER 1
#define Gs7_Ab7_FRACTIONAL 8.0000
#define Gs7_Ab7_DIVIDER 1.5000 

// G_7
#define G_7_FREQUENCY 3135.963	//Best Frequency Found: = 3135.9612
#define G_7_WRAP 20572
#define G_7_INTEGER 1
#define G_7_FRACTIONAL 15.0000
#define G_7_DIVIDER 1.9375 

// Fs7 - Gb7
#define Fs7_Gb7_FREQUENCY 2959.955 //Best Frequency Found: = 2959.9548
#define Fs7_Gb7_WRAP 30712
#define Fs7_Gb7_INTEGER 1
#define Fs7_Gb7_FRACTIONAL 6.0000
#define Fs7_Gb7_DIVIDER 1.3750 

// F_7
#define F_7_FREQUENCY 2793.826 //Best Frequency Found: = 2793.8267
#define F_7_WRAP 16647
#define F_7_INTEGER 2
#define F_7_FRACTIONAL 11.0000
#define F_7_DIVIDER 2.6875 

// Fb7
#define Fb7_FREQUENCY E_7_FREQUENCY
#define Fb7_WRAP E_7_WRAP
#define Fb7_INTEGER E_7_INTEGER
#define Fb7_FRACTIONAL E_7_FRACTIONAL
#define Fb7_DIVIDER E_7_DIVIDER

// Es7
#define Es7_FREQUENCY F_7_FREQUENCY 
#define Es7_WRAP F_7_WRAP 
#define Es7_INTEGER F_7_INTEGER
#define Es7_FRACTIONAL F_7_FRACTIONAL 
#define Es7_DIVIDER F_7_DIVIDER

// E_7
#define E_7_FREQUENCY 2637.020 //Best Frequency Found: = 2637.0195
#define E_7_WRAP 5535
#define E_7_INTEGER 8
#define E_7_FRACTIONAL 9.0000
#define E_7_DIVIDER 8.5625

// Ds7 - Eb7
#define Ds7_Eb7_FREQUENCY 2489.016 //Best Frequency Found: = 2489.0171
#define Ds7_Eb7_WRAP 30904
#define Ds7_Eb7_INTEGER 1
#define Ds7_Eb7_FRACTIONAL 10.0000
#define Ds7_Eb7_DIVIDER 1.6250 

// D_7
#define D_7_FREQUENCY 2349.318 //Best Frequency Found: = 2349.3176
#define D_7_WRAP 18112
#define D_7_INTEGER 2
#define D_7_FRACTIONAL 15.0000
#define D_7_DIVIDER 2.9375

// Cs7 - Db7
#define Cs7_Db7_FREQUENCY 2217.461	//Best Frequency Found: = 2217.4597
#define Cs7_Db7_WRAP 15286
#define Cs7_Db7_INTEGER 3
#define Cs7_Db7_FRACTIONAL 11.0000
#define Cs7_Db7_DIVIDER 3.6875

// C_7
#define C_7_FREQUENCY 2093.005 //Best Frequency Found: = 2093.0046
#define C_7_WRAP 16195
#define C_7_INTEGER 3
#define C_7_FRACTIONAL 11.0000
#define C_7_DIVIDER 3.6875

// Cb7
#define Cb7_FREQUENCY B_6_FREQUENCY
#define Cb7_WRAP B_6_WRAP
#define Cb7_INTEGER B_6_INTEGER
#define Cb7_FRACTIONAL B_6_FRACTIONAL
#define Cb7_DIVIDER B_6_DIVIDER

//--------------------------------------------------------------------

// Bs6
#define Bs6_FREQUENCY C_7_FREQUENCY 
#define Bs6_WRAP C_7_WRAP 
#define Bs6_INTEGER C_7_INTEGER
#define Bs6_FRACTIONAL C_7_FRACTIONAL
#define Bs6_DIVIDER C_7_DIVIDER

// B_6
#define B_6_FREQUENCY 1975.533 //Best Frequency Found: = 1975.5331
#define B_6_WRAP 18406
#define B_6_INTEGER 3
#define B_6_FRACTIONAL 7.0000
#define B_6_DIVIDER 3.4375

// As6 - Bb6
#define As6_Bb6_FREQUENCY 1864.655 //Best Frequency Found: = 1864.6558	
#define As6_Bb6_WRAP 59587
#define As6_Bb6_INTEGER 1
#define As6_Bb6_FRACTIONAL 2.0000
#define As6_Bb6_DIVIDER 1.1250 

// A_6
#define A_6_FREQUENCY 1760.000	//Best Frequency Found: = 1759.9994
#define A_6_WRAP 4043
#define A_6_INTEGER 17
#define A_6_FRACTIONAL 9.0000
#define A_6_DIVIDER 17.5625 

// Gs6 - Ab6
#define Gs6_Ab6_FREQUENCY 1661.219 //Best Frequency Found: = 1661.2192
#define Gs6_Ab6_WRAP 63364
#define Gs6_Ab6_INTEGER 1
#define Gs6_Ab6_FRACTIONAL 3.0000
#define Gs6_Ab6_DIVIDER 1.1875 

// G_6
#define G_6_FREQUENCY 1567.982 //Best Frequency Found: = 1567.9818
#define G_6_WRAP 51020
#define G_6_INTEGER 1
#define G_6_FRACTIONAL 9.0000
#define G_6_DIVIDER 1.5625 

// Fs6 - Gb6
#define Fs6_Gb6_FREQUENCY 1479.978 //Best Frequency Found: = 1479.9785
#define Fs6_Gb6_WRAP 64350
#define Fs6_Gb6_INTEGER 1
#define Fs6_Gb6_FRACTIONAL 5.0000
#define Fs6_Gb6_DIVIDER 1.3125 

// F_6
#define F_6_FREQUENCY 1396.913 //Best Frequency Found: = 1396.9133
#define F_6_WRAP 33295
#define F_6_INTEGER 2
#define F_6_FRACTIONAL 11.0000
#define F_6_DIVIDER 2.6875 

// Fb6
#define Fb6_FREQUENCY E_6_FREQUENCY
#define Fb6_WRAP E_6_WRAP
#define Fb6_INTEGER E_6_INTEGER
#define Fb6_FRACTIONAL E_6_FRACTIONAL
#define Fb6_DIVIDER E_6_DIVIDER

// Es6
#define Es6_FREQUENCY F_6_FREQUENCY 
#define Es6_WRAP F_6_WRAP 
#define Es6_INTEGER F_6_INTEGER
#define Es6_FRACTIONAL F_6_FRACTIONAL 
#define Es6_DIVIDER F_6_DIVIDER

// E_6
#define E_6_FREQUENCY 1318.510 //Best Frequency Found: = 1318.509
#define E_6_WRAP 11071
#define E_6_INTEGER 8
#define E_6_FRACTIONAL 9.0000
#define E_6_DIVIDER 8.5625  

// Ds6 - Eb6
#define Ds6_Eb6_FREQUENCY 1244.508 //Best Frequency Found: = 1244.5078
#define Ds6_Eb6_WRAP 31510
#define Ds6_Eb6_INTEGER 3
#define Ds6_Eb6_FRACTIONAL 3.0000
#define Ds6_Eb6_DIVIDER 3.1875

// D_6
#define D_6_FREQUENCY 1174.659 //Best Frequency Found: = 1174.6588
#define D_6_WRAP 36225
#define D_6_INTEGER 2
#define D_6_FRACTIONAL 15.0000
#define D_6_DIVIDER 2.9375

// Cs6 - Db6
#define Cs6_Db6_FREQUENCY 1108.731 //Best Frequency Found: = 1108.7305
#define Cs6_Db6_WRAP 51538
#define Cs6_Db6_INTEGER 2
#define Cs6_Db6_FRACTIONAL 3.0000
#define Cs6_Db6_DIVIDER 2.1875

// C_6
#define C_6_FREQUENCY 1046.502 //Best Frequency Found: = 1046.5018
#define C_6_WRAP 57912
#define C_6_INTEGER 2
#define C_6_FRACTIONAL 1.0000
#define C_6_DIVIDER 2.0625

// Cb6
#define Cb6_FREQUENCY B_5_FREQUENCY
#define Cb6_WRAP B_5_WRAP
#define Cb6_INTEGER B_5_INTEGER
#define Cb6_FRACTIONAL B_5_FRACTIONAL
#define Cb6_DIVIDER B_5_DIVIDER

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

// As2 - Bb2
#define As2_Bb2_FREQUENCY 116.5409 //Best Frequency Found: = 116.5409
#define As2_Bb2_WRAP 54653
#define As2_Bb2_INTEGER 19
#define As2_Bb2_FRACTIONAL 10.0000
#define As2_Bb2_DIVIDER 19.6250

// A_2
#define A_2_FREQUENCY 110.0000 //Best Frequency Found: = 110.0000
#define A_2_WRAP 60005
#define A_2_INTEGER 18
#define A_2_FRACTIONAL 15.0000
#define A_2_DIVIDER 18.9375 

// Gs2 - Ab2
#define Gs2_Ab2_FREQUENCY 103.8262 //Best Frequency Found: = 103.8262
#define Gs2_Ab2_WRAP 61542
#define Gs2_Ab2_INTEGER 19
#define Gs2_Ab2_FRACTIONAL 9.0000
#define Gs2_Ab2_DIVIDER 19.5625 

// G_2
#define G_2_FREQUENCY 97.99886 //Best Frequency Found: = 97.9989
#define G_2_WRAP 61102
#define G_2_INTEGER 20
#define G_2_FRACTIONAL 14.0000
#define G_2_DIVIDER 20.8750 

// Fs2 - Gb2
#define Fs2_Gb2_FREQUENCY 92.49861 //Best Frequency Found: = 92.4986
#define Fs2_Gb2_WRAP 61953
#define Fs2_Gb2_INTEGER 21
#define Fs2_Gb2_FRACTIONAL 13.0000
#define Fs2_Gb2_DIVIDER 21.8125

// F_2
#define F_2_FREQUENCY 87.30706 //Best Frequency Found: = 87.3071
#define F_2_WRAP 54802
#define F_2_INTEGER 26
#define F_2_FRACTIONAL 2.0000
#define F_2_DIVIDER 26.1250

// Fb2
#define Fb2_FREQUENCY E_2_FREQUENCY
#define Fb2_WRAP E_2_WRAP
#define Fb2_INTEGER E_2_INTEGER
#define Fb2_FRACTIONAL E_2_FRACTIONAL
#define Fb2_DIVIDER E_2_DIVIDER

// Es2
#define Es2_FREQUENCY F_2_FREQUENCY 
#define Es2_WRAP F_2_WRAP 
#define Es2_INTEGER F_2_INTEGER
#define Es2_FRACTIONAL F_2_FRACTIONAL 
#define Es2_DIVIDER F_2_DIVIDER

// E_2
#define E_2_FREQUENCY 82.40689 //Best Frequency Found: = 82.4069
#define E_2_WRAP 59630
#define E_2_INTEGER 25
#define E_2_FRACTIONAL 7.0000
#define E_2_DIVIDER 25.4375 

// Ds2 - Eb2
#define Ds2_Eb2_FREQUENCY 77.78175 //Best Frequency Found: = 77.7817
#define Ds2_Eb2_WRAP 59936
#define Ds2_Eb2_INTEGER 26
#define Ds2_Eb2_FRACTIONAL 13.0000
#define Ds2_Eb2_DIVIDER 26.8125 

// D_2
#define D_2_FREQUENCY 73.41619 //Best Frequency Found: = 73.4162
#define D_2_WRAP 57110
#define D_2_INTEGER 29
#define D_2_FRACTIONAL 13.0000
#define D_2_DIVIDER 29.8125

// Cs2 - Db2
#define Cs2_Db2_FREQUENCY 69.29566 //Best Frequency Found: = 69.2957
#define Cs2_Db2_WRAP 63154
#define Cs2_Db2_INTEGER 28
#define Cs2_Db2_FRACTIONAL 9.0000
#define Cs2_Db2_DIVIDER 28.5625

// C_2
#define C_2_FREQUENCY 65.40639 //Best Frequency Found: = 65.4064
#define C_2_WRAP 64783
#define C_2_INTEGER 29
#define C_2_FRACTIONAL 8.0000
#define C_2_DIVIDER 29.5000 

// Cb2
#define Cb2_FREQUENCY B_1_FREQUENCY
#define Cb2_WRAP B_1_WRAP
#define Cb2_INTEGER B_1_INTEGER
#define Cb2_FRACTIONAL B_1_FRACTIONAL
#define Cb2_DIVIDER B_1_DIVIDER

//--------------------------------------------------------------------

// Bs2
#define Bs1_FREQUENCY C_2_FREQUENCY 
#define Bs1_WRAP C_2_WRAP 
#define Bs1_INTEGER C_2_INTEGER
#define Bs1_FRACTIONAL C_2_FRACTIONAL
#define Bs1_DIVIDER C_2_DIVIDER

// B_1
#define B_1_FREQUENCY 61.73541 //Best Frequency Found: = 61.7354
#define B_1_WRAP 63646
#define B_1_INTEGER 31
#define B_1_FRACTIONAL 13.0000
#define B_1_DIVIDER 31.8125 

// As1 - Bb1
#define As1_Bb1_FREQUENCY 58.27047 //Best Frequency Found: = 58.2705
#define As1_Bb1_WRAP 59899
#define As1_Bb1_INTEGER 35
#define As1_Bb1_FRACTIONAL 13.0000
#define As1_Bb1_DIVIDER 35.8125 

// A_1
#define A_1_FREQUENCY 55.00000 //Best Frequency Found: = 55.0000
#define A_1_WRAP 61528
#define A_1_INTEGER 36
#define A_1_FRACTIONAL 15.0000
#define A_1_DIVIDER 36.9375

// Gs1 - Ab1
#define Gs1_Ab1_FREQUENCY 51.91309 //Best Frequency Found: = 51.9131
#define Gs1_Ab1_WRAP 55432 
#define Gs1_Ab1_INTEGER 43
#define Gs1_Ab1_FRACTIONAL 7.0000
#define Gs1_Ab1_DIVIDER 43.4375 

// G_1
#define G_1_FREQUENCY 48.99943 //Best Frequency Found: = 48.9994
#define G_1_WRAP 62410
#define G_1_INTEGER 40
#define G_1_FRACTIONAL 14.0000
#define G_1_DIVIDER 40.8750 

// Fs1 - Gb1
#define Fs1_Gb1_FREQUENCY 46.24930	//Best Frequency Found: = 46.2493
#define Fs1_Gb1_WRAP 62945
#define Fs1_Gb1_INTEGER 42
#define Fs1_Gb1_FRACTIONAL 15.0000
#define Fs1_Gb1_DIVIDER 42.9375

// F_1
#define F_1_FREQUENCY 43.65353 //Best Frequency Found: = 43.6535
#define F_1_WRAP 60762
#define F_1_INTEGER 47
#define F_1_FRACTIONAL 2.0000
#define F_1_DIVIDER 47.1250 

// Fb1
#define Fb1_FREQUENCY E_1_FREQUENCY
#define Fb1_WRAP E_1_WRAP
#define Fb1_INTEGER E_1_INTEGER
#define Fb1_FRACTIONAL E_1_FRACTIONAL
#define Fb1_DIVIDER E_1_DIVIDER

// Es1
#define Es1_FREQUENCY F_1_FREQUENCY 
#define Es1_WRAP F_1_WRAP 
#define Es1_INTEGER F_1_INTEGER
#define Es1_FRACTIONAL F_1_FRACTIONAL 
#define Es1_DIVIDER F_1_DIVIDER

// E_1
#define E_1_FREQUENCY 41.20344 //Best Frequency Found: = 41.2034
#define E_1_WRAP 63783
#define E_1_INTEGER 47
#define E_1_FRACTIONAL 9.0000
#define E_1_DIVIDER 47.5625 

// Ds1 - Eb1
#define Ds1_Eb1_FREQUENCY 38.89087 //Best Frequency Found: = 38.8909
#define Ds1_Eb1_WRAP 62561
#define Ds1_Eb1_INTEGER 51
#define Ds1_Eb1_FRACTIONAL 6.0000
#define Ds1_Eb1_DIVIDER 51.3750

// D_1
#define D_1_FREQUENCY 36.70810 //Best Frequency Found: = 36.7081
#define D_1_WRAP 60604
#define D_1_INTEGER 56
#define D_1_FRACTIONAL 3.0000
#define D_1_DIVIDER 56.1875

// Cs1 - Db1
#define Cs1_Db1_FREQUENCY 34.64783 //Best Frequency Found: = 34.6478	
#define Cs1_Db1_WRAP 64930
#define Cs1_Db1_INTEGER 55
#define Cs1_Db1_FRACTIONAL 9.0000
#define Cs1_Db1_DIVIDER 55.5625

// C_1
#define C_1_FREQUENCY 32.70320 //Best Frequency Found: = 32.7032
#define C_1_WRAP 61094
#define C_1_INTEGER 62
#define C_1_FRACTIONAL 9.0000
#define C_1_DIVIDER 62.5625

// Cb1
#define Cb1_FREQUENCY B_0_FREQUENCY
#define Cb1_WRAP B_0_WRAP
#define Cb1_INTEGER B_0_INTEGER
#define Cb1_FRACTIONAL B_0_FRACTIONAL
#define Cb1_DIVIDER B_0_DIVIDER


//--------------------------------------------------------------------

// Bs0
#define Bs0_FREQUENCY C_1_FREQUENCY 
#define Bs0_WRAP C_1_WRAP 
#define Bs0_INTEGER C_1_INTEGER
#define Bs0_FRACTIONAL C_1_FRACTIONAL
#define Bs0_DIVIDER C_1_DIVIDER

// B_0
#define B_0_FREQUENCY 30.86771 //Best Frequency Found: = 30.8677
#define B_0_WRAP 63646
#define B_0_INTEGER 63
#define B_0_FRACTIONAL 10.0000 
#define B_0_DIVIDER  63.6250

// As0 - Bb0
#define As0_Bb0_FREQUENCY 29.13524 //Best Frequency Found: = 29.1352	
#define As0_Bb0_WRAP 63325
#define As0_Bb0_INTEGER 67
#define As0_Bb0_FRACTIONAL 12.0000
#define As0_Bb0_DIVIDER 67.7500 

// A_0
#define A_0_FREQUENCY 27.50000	//Best Frequency Found: = 27.5000
#define A_0_WRAP 64703
#define A_0_INTEGER 70
#define A_0_FRACTIONAL 4.0000
#define A_0_DIVIDER  70.2500

// Gs0 - Ab0
#define Gs0_Ab0_FREQUENCY 25.95654 //Best Frequency Found: = 25.9565	
#define Gs0_Ab0_WRAP 63260
#define Gs0_Ab0_INTEGER 76
#define Gs0_Ab0_FRACTIONAL 2.0000 
#define Gs0_Ab0_DIVIDER 76.1250 

// G_0
#define G_0_FREQUENCY 24.49971 	//Best Frequency Found: = 24.4997
#define G_0_WRAP 65463
#define G_0_INTEGER 77 
#define G_0_FRACTIONAL 15.0000
#define G_0_DIVIDER  77.9375

// Fs0 - Gb0
#define Fs0_Gb0_FREQUENCY 23.12465 //Best Frequency Found: = 23.1247
#define Fs0_Gb0_WRAP 64494
#define Fs0_Gb0_INTEGER 83
#define Fs0_Gb0_FRACTIONAL 13.0000 
#define Fs0_Gb0_DIVIDER  83.8125

// F_4
#define F_0_FREQUENCY 21.82676 //Best Frequency Found: = 21.8268
#define F_0_WRAP 65263
#define F_0_INTEGER 87
#define F_0_FRACTIONAL 12.0000
#define F_0_DIVIDER 87.7500

// Fb0
#define Fb0_FREQUENCY E_0_FREQUENCY
#define Fb0_WRAP E_0_WRAP
#define Fb0_INTEGER E_0_INTEGER
#define Fb0_FRACTIONAL E_0_FRACTIONAL
#define Fb0_DIVIDER E_0_DIVIDER

// Es0
#define Es0_FREQUENCY F_0_FREQUENCY 
#define Es0_WRAP F_0_WRAP 
#define Es0_INTEGER F_0_INTEGER
#define Es0_FRACTIONAL F_0_FRACTIONAL 
#define Es0_DIVIDER F_0_DIVIDER

// E_0
#define E_0_FREQUENCY 20.60172 //Best Frequency Found: = 60170.2813
#define E_0_WRAP 772
#define E_0_INTEGER 2
#define E_0_FRACTIONAL 11.0000
#define E_0_DIVIDER 2.6874

// Ds0 - Eb0
#define Ds0_Eb0_FREQUENCY 19.44544 //Best Frequency Found: = 19.4454
#define Ds0_Eb0_WRAP 64808
#define Ds0_Eb0_INTEGER 99
#define Ds0_Eb0_FRACTIONAL 3.0000
#define Ds0_Eb0_DIVIDER 99.1875

// D_0
#define D_0_FREQUENCY 18.35405 //Best Frequency Found: = 18.3540
#define D_0_WRAP 64477
#define D_0_INTEGER 105
#define D_0_FRACTIONAL 10.0000 
#define D_0_DIVIDER 105.6250 

// Cs0 - Db0
#define Cs0_Db0_FREQUENCY 17.32391 //Best Frequency Found: = 17.3239
#define Cs0_Db0_WRAP 64930
#define Cs0_Db0_INTEGER 111
#define Cs0_Db0_FRACTIONAL 2.0000
#define Cs0_Db0_DIVIDER 111.1251 

// C_0
#define C_0_FREQUENCY 16.352 //Best Frequency Found: = 16.3520
#define C_0_WRAP 65475
#define C_0_INTEGER 116
#define C_0_FRACTIONAL 12.0000
#define C_0_DIVIDER  116.7500

// Cb0
#define Cb0_FREQUENCY B__1_FREQUENCY
#define Cb0_WRAP B__1_WRAP
#define Cb0_INTEGER B__1_INTEGER
#define Cb0_FRACTIONAL B__1_FRACTIONAL
#define Cb0_DIVIDER B__1_DIVIDER

//--------------------------------------------------------------------

// B_-1
#define B__1_FREQUENCY 15.434 //Best Frequency Found: = 15.4340
#define B__1_WRAP 64986
#define B__1_INTEGER 124
#define B__1_FRACTIONAL 10.0000
#define B__1_DIVIDER 124.6250







// //--------------------------------------------------------------------

// // Bs4
// #define Bs4_FREQUENCY C_5_FREQUENCY 
// #define Bs4_WRAP C_5_WRAP 
// #define Bs4_INTEGER C_5_INTEGER
// #define Bs4_FRACTIONAL C_5_FRACTIONAL
// #define Bs4_DIVIDER C_5_DIVIDER

// // B_4
// #define B_4_FREQUENCY 
// #define B_4_WRAP 
// #define B_4_INTEGER 
// #define B_4_FRACTIONAL 
// #define B_4_DIVIDER  

// // As4 - Bb4
// #define As4_Bb4_FREQUENCY 
// #define As4_Bb4_WRAP 
// #define As4_Bb4_INTEGER 
// #define As4_Bb4_FRACTIONAL 
// #define As4_Bb4_DIVIDER  

// // A_4
// #define A_4_FREQUENCY 
// #define A_4_WRAP 
// #define A_4_INTEGER 
// #define A_4_FRACTIONAL 
// #define A_4_DIVIDER  

// // Gs4 - Ab4
// #define Gs4_Ab4_FREQUENCY 
// #define Gs4_Ab4_WRAP 
// #define Gs4_Ab4_INTEGER 
// #define Gs4_Ab4_FRACTIONAL 
// #define Gs4_Ab4_DIVIDER  

// // G_4
// #define G_4_FREQUENCY 
// #define G_4_WRAP 
// #define G_4_INTEGER 
// #define G_4_FRACTIONAL 
// #define G_4_DIVIDER  

// // Fs4 - Gb4
// #define Fs4_Gb4_FREQUENCY 
// #define Fs4_Gb4_WRAP 
// #define Fs4_Gb4_INTEGER 
// #define Fs4_Gb4_FRACTIONAL 
// #define Fs4_Gb4_DIVIDER  

// // F_4
// #define F_4_FREQUENCY 
// #define F_4_WRAP 
// #define F_4_INTEGER 
// #define F_4_FRACTIONAL 
// #define F_4_DIVIDER  

// // Fb4
// #define Fb4_FREQUENCY E_4_FREQUENCY
// #define Fb4_WRAP E_4_WRAP
// #define Fb4_INTEGER E_4_INTEGER
// #define Fb4_FRACTIONAL E_4_FRACTIONAL
// #define Fb4_DIVIDER E_4_DIVIDER

// // Es4
// #define Es4_FREQUENCY F_4_FREQUENCY 
// #define Es4_WRAP F_4_WRAP 
// #define Es4_INTEGER F_4_INTEGER
// #define Es4_FRACTIONAL F_4_FRACTIONAL 
// #define Es4_DIVIDER F_4_DIVIDER

// // E_4
// #define E_4_FREQUENCY 
// #define E_4_WRAP 
// #define E_4_INTEGER 
// #define E_4_FRACTIONAL 
// #define E_4_DIVIDER  

// // Ds4 - Eb4
// #define Ds4_Eb4_FREQUENCY 
// #define Ds4_Eb4_WRAP 
// #define Ds4_Eb4_INTEGER
// #define Ds4_Eb4_FRACTIONAL 
// #define Ds4_Eb4_DIVIDER  

// // D_4
// #define D_4_FREQUENCY 
// #define D_4_WRAP 
// #define D_4_INTEGER 
// #define D_4_FRACTIONAL 
// #define D_4_DIVIDER 

// // Cs4 - Db4
// #define Cs4_Db4_FREQUENCY 
// #define Cs4_Db4_WRAP 
// #define Cs4_Db4_INTEGER 
// #define Cs4_Db4_FRACTIONAL 
// #define Cs4_Db4_DIVIDER 

// // C_4
// #define C_4_FREQUENCY 
// #define C_4_WRAP 
// #define C_4_INTEGER 
// #define C_4_FRACTIONAL 
// #define C_4_DIVIDER  

// // Cb4
// #define Cb4_FREQUENCY B_3_FREQUENCY
// #define Cb4_WRAP B_3_WRAP
// #define Cb4_INTEGER B_3_INTEGER
// #define Cb4_FRACTIONAL B_3_FRACTIONAL
// #define Cb4_DIVIDER B_3_DIVIDER
