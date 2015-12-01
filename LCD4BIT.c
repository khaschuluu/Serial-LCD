sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB7_bit;
sbit LCD_D4 at RB3_bit;
sbit LCD_D5 at RB4_bit;
sbit LCD_D6 at RB5_bit;
sbit LCD_D7 at RB6_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB7_bit;
sbit LCD_D4_Direction at TRISB3_bit;
sbit LCD_D5_Direction at TRISB4_bit;
sbit LCD_D6_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB6_bit;

char start_text[] = "Working...";

char i;
char res;
int j = 0;

char uart_rd;

void main(){
  TRISB = 0;
  PORTB = 0xFF;
  TRISB = 0xff;
  Lcd_Init();
  Lcd_Out(1,4,start_text);
  UART1_Init(9600);
  Delay_ms(100);
  UART1_Write_Text(start_text);
  while (1) {
   if (UART1_Data_Ready() == 1) {
     uart_rd = UART1_Read();
     res = UART1_Read();
     Lcd_Chr_Cp(res);
     UART1_Write(uart_rd);
     Lcd_Chr(j/16+1, j%16+1, uart_rd);
     j = (j+1)%32;
    }
  }
}