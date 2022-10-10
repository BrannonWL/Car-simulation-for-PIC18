
// PIC18F4331 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = IRC        // Oscillator Selection bits (Internal oscillator block, CLKO function on RA6 and port function on RA7)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Oscillator Switchover bit (Internal External Switchover mode enabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset enabled)
// BORV = No Setting

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDPS = 32768     // Watchdog Timer Postscale Select bits (1:32768)
#pragma config WINEN = OFF      // Watchdog Timer Window Enable bit (WDT window disabled)

// CONFIG3L
#pragma config PWMPIN = OFF     // PWM output pins Reset state control (PWM outputs disabled upon Reset (default))
#pragma config LPOL = HIGH      // Low-Side Transistors Polarity (PWM0, 2, 4 and 6 are active-high)
#pragma config HPOL = HIGH      // High-Side Transistors Polarity (PWM1, 3, 5 and 7 are active-high)
#pragma config T1OSCMX = ON     // Timer1 Oscillator MUX (Low-power Timer1 operation when microcontroller is in Sleep mode)

// CONFIG3H
#pragma config FLTAMX = RC1     // FLTA MUX bit (FLTA input is multiplexed with RC1)
#pragma config SSPMX = RC7      // SSP I/O MUX bit (SCK/SCL clocks and SDA/SDI data are multiplexed with RC5 and RC4, respectively. SDO output is multiplexed with RC7.)
#pragma config PWM4MX = RB5     // PWM4 MUX bit (PWM4 output is multiplexed with RB5)
#pragma config EXCLKMX = RC3    // TMR0/T5CKI External clock MUX bit (TMR0/T5CKI external clock input is multiplexed with RC3)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (Enabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Low-Voltage ICSP Enable bit (Low-voltage ICSP enabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-000FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (001000-001FFF) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-000FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (001000-001FFF) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-000FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (001000-001FFF) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
  
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 1200000

//Current pins
//inputs:
//RD1, RD0, RC3, RD2, RD3, RC4
//outputs:
//15,16,17,
//24,25,26,33,34
//RC0, RC1, RC2 
//RC5, RC6, RC7, RB1, RB0
void Steer();
void CheckGas();
void CheckLights();
void LightFlags();

int counter = 0;
long int gas_tank = 200;
//Define output
#define  L_Sig RC2 //Left turn
#define R_Sig RA5 //Right turn
#define  W_Left RE1 //Wheel left
#define W_Right RC7 //Wheel Right
#define Light RC0  //Front lights
#define Brake RC1  //Brake
#define Lo_Gas RC6 //Gas 
#define Up_Gas RC5 //Gas

#define Drive_swt RD3
#define L_Sig_swt RD0
#define Lit_swt RC4
#define War_swt RC3
#define R_Sig_swt RD1
#define Lit_swt RC4
#define Refuel_swt RD2
int timer = 0;
int War_Flag = 0;
int Lit_Flag = 0;
int R_Flag = 0;
int L_Flag = 0;

void __interrupt() RTI(void){
    if(INTCONbits.TMR0IF){
        TMR0L = 0xFF;
        TMR0H = 0X0B;
        if(timer >= 1000){
        CheckGas();
        CheckLights();
        timer = 0;
       
        }
        
        timer++;
        INTCONbits.TMR0IF = 0;
        
    }
}


int main(void){
    //initalize inputs
    TRISAbits.RA4 = 1;
    TRISDbits.RD3 = 1;
    TRISDbits.RD2 = 1;
    TRISDbits.RD1 = 1;
    TRISDbits.RD0 = 1;
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;
    //initializes the ports to be output
    TRISEbits.RE1 = 0;
    TRISCbits.RC7 = 0;
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0; 
    TRISCbits.RC2 = 0;
   // TRISCbits.RC3 = 1;
    TRISCbits.RC5 = 0;
    TRISCbits.RC6 = 0; 
    TRISAbits.RA5 = 0;
    
    //Initializes A/D port
    ADCON0bits.ACONV = 0; //Sets to single shot mode 
    ADCON0bits.ADON = 1; //
    ADCON0bits.ACMOD = 0;//Sets to auto-convert single channel
    ADCON0bits.GO_DONE = 1;//Toggles A to D
    ADCON0bits.ACSCH = 0;//auto covert off
    ADCON2bits.ADFM = 1; // Right Justified
    ADCON2bits.ADCS = 0b111; //internal oscillator
    ANSEL0bits.ANS4 = 1; //sets analog input
    ADCHSbits.GASEL0 = 1; //sets second bit 1
    ADCHSbits.GASEL1 = 0; //sets first bit 0, enabling the AN4
   
    //Initialize timer
    T0CONbits.TMR0ON = 1;
    T0CONbits.T016BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.T0PS0 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS2 = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    
    TMR0H = 0x0B;
    TMR0L = 0XDC;
   
   IRCF0 = 0;
    IRCF1 = 1;
    IRCF2 = 1;

    LATEbits.LATE1 = 0;// light is off for the time to ensure interrupts work
    LATCbits.LATC7 = 0;
    LATCbits.LATC6 = 0;
    LATCbits.LATC5 = 0;
    LATCbits.LATC1 = 0;
    LATCbits.LATC2 = 0;
    LATCbits.LATC0 = 0;
    LATAbits.LATA5 = 0;
       
     Brake = 1;
while(1){
    if(Drive_swt == 1){
      ADCON0bits.GO_DONE = 1; 
        if(ADCON0bits.GO_DONE != 0){
        Steer();
    }   
     Brake = 0;  
    }
    if(Drive_swt == 0){
        Brake = 1;
        W_Left = 0;
        W_Right = 0;
    }
  
 }   
 }
void Steer(){
        counter = (int)ADRES/200;
    
    if (counter < 1){
        W_Left = 1;
        W_Right = 0;
    }
    
      if (counter >= 1 && counter < 4){ //LED 1 to 2 on
        W_Left = 1;
        W_Right = 1;
    }
      if (counter >= 4){//All on
        W_Left = 0;
        W_Right = 1;
    }
   
}
void CheckGas(){
         if(gas_tank > 150){
            Up_Gas = 1;
            Lo_Gas = 1;
            }
        if(gas_tank <= 150 && gas_tank > 100){
         Up_Gas = ~Up_Gas; 
         Lo_Gas = 1;
       }
         if(gas_tank <= 100 && gas_tank > 50){
             Up_Gas = 0;
             Lo_Gas = 1;
         }
         if(gas_tank <= 50 && gas_tank > 0){
             Lo_Gas = ~Lo_Gas;
         }       
         if(gas_tank <= 0){
             Brake = 1;
             W_Left = 0;
             W_Right = 0;
             R_Sig = 0;
             L_Sig = 0;
             Light = 0;
             Lo_Gas = 0;
             Up_Gas = 0;
           while(gas_tank <= 0){
               if(Refuel_swt == 1 && gas_tank <= 80){
                gas_tank = 200 ;
               }
           }  
         }
         gas_tank = gas_tank - 1;
    
}
void CheckLights(){
    

    if(Lit_swt == 1 && War_Flag == 0){
        Light = 1;
    }
     if(Lit_swt == 0 && War_Flag == 0){
     Light = 0;
     }
     if(R_Sig_swt == 1 && War_Flag == 0){
        R_Sig = ~R_Sig;
     }
     if(R_Sig_swt == 0 && War_Flag == 0){
        R_Sig = 0;
     }
     if(L_Sig_swt == 1 && War_Flag == 0){
        L_Sig = ~L_Sig;
     }
     if(L_Sig_swt == 0 && War_Flag == 0){
        L_Sig = 0;
     }
    
     if(War_swt == 1){
     War_Flag = 1;
     }
    
       if(War_Flag == 1){
            Light = ~Light;
            L_Sig = Light;
            R_Sig = L_Sig;
            
        }
    if(War_swt == 0){
        War_Flag = 0;
    }
    
       
}
