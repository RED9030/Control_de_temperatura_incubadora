//INICIO CONEXIÓN DE MODULO LCD
sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC2_bit;
sbit LCD_D5 at RC3_bit;
sbit LCD_D6 at RC4_bit;
sbit LCD_D7 at RC5_bit;

sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC2_bit;
sbit LCD_D5_Direction at TRISC3_bit;
sbit LCD_D6_Direction at TRISC4_bit;
sbit LCD_D7_Direction at TRISC5_bit;
//FIN CONEXIÓN DE MODULO LCD

void verificacion(unsigned long valor_a);//Procedimiento para verificar la temperatura del sensor.
void SONIDO();//Procedimiento para tocar una nota.

char txt1[]="VALOR";
char txt2;
unsigned long valor;

void main() {
INTCON=0x00;
ANSEL = 0x04;
ANSELH = 0x00;

Sound_Init(&PORTE, 2); //Envía la secuencia de bits del tono audible a través del pin 2

TRISA=0xFF;
TRISD=0x00;

PORTD=0x00;

C1ON_bit = 0x00;                   // Disable comparators
C2ON_bit = 0x00;

Lcd_Init();                        // Initialize LCD
Lcd_Cmd(_LCD_CLEAR);               // Clear display
Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
ADC_Init();

           Lcd_Out(1,1,txt1);
           while(1){
                    valor = ADC_Read(2);
                    valor = valor * 5000/1023;
                    txt2 = valor/1000;
                    Lcd_Chr(2,1,48+txt2);
                    txt2 = (valor/100)%10;  //Centena
                    Lcd_Chr_CP(48+txt2);
                    txt2 = (valor/10)%10;  //Decena
                    Lcd_Chr_CP(48+txt2);
                    Lcd_Chr_CP('.'); //Punto decimal para decifrar que tipo de valor es
                    txt2 = (valor/1)%10;   //Unidad
                    Lcd_Chr_CP(48+txt2);
                    verificacion(valor);  //Verifico el rango de altura baja y alta
                    }
}

void verificacion(unsigned long valor_a)
{
                    if((valor_a/100)<4.0)
                    {
                      PORTD.RD0=1;
                      PORTD.RD1=0;
                      SONIDO();
                    }else{
	              PORTD.RD0=0;
        	      PORTD.RD1=0;
                      if((valor_a/100)>=7.0)
                     {
                      PORTD.RD0=0;
                      PORTD.RD1=1;
                      SONIDO();
                     }
                       }
}


void SONIDO(){
  //switch ()
  //{
  //case 0x3F: //caso si Portc se encuentra mostrando el numero 0
  Sound_Play(698, 300); //FA // Frequency = 698Hz, duration = 300ms
  delay_ms(100);
  //break;
  //}
}