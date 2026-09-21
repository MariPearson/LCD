/*
 * LCD_I2C.H
 *
 *  Created on: Feb 26, 2023
 *      Author: Alcides Ramos
 */

#ifndef LIBRERIA_lcd_i2c_h_
#define LIBRERIA_lcd_i2c_h_
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

#define _LCD_FIRST_ROW          0x80     
#define _LCD_SECOND_ROW         0xC0     

#define _LCD_CLEAR              0x01     //Clear display
#define _LCD_RETURN_HOME        0x02     //Return cursor to home position, returns a shifted display to
                                         //its original position. Display data RAM is unaffected.
#define _LCD_CURSOR_OFF         0x0C     //Turn off cursor
#define _LCD_UNDERLINE_ON       0x0E     //Underline cursor on
#define _LCD_BLINK_CURSOR_ON    0x0F     //Blink cursor on
#define _LCD_MOVE_CURSOR_LEFT   0x10     //Move cursor left without changing display data RAM
#define _LCD_MOVE_CURSOR_RIGHT  0x14     //Move cursor right without changing display data RAM
#define _LCD_TURN_ON            0x0C     //Turn Lcd display on
#define _LCD_TURN_OFF           0x08     //Turn Lcd display off
#define _LCD_SHIFT_LEFT         0x18     //Shift display left without changing display data RAM
#define _LCD_SHIFT_RIGHT        0x1E     //Shift display right without changing display data RAM



#define LCD_ADDR 0x27        
#define SLAVE_ADDRESS_LCD LCD_ADDR

#define LCD_BL 0x08
#define LCD_EN 0x04
#define LCD_RS 0x01

void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_clear(void);
void lcd_put_cur(int row, int col);
void lcd_init(void);
void lcd_send_string(char *str);

void I2C_Lcd_Cmd(char out_char);
void I2C_Lcd_Init();
void I2C_Lcd_Chr(char row, char column, char out_char);
void I2C_Lcd_Chr_Cp(char out_char);
void I2C_Lcd_CreateChar(uint8_t location, const uint8_t character[8]);
void I2C_Lcd_Text(char row, char col, char *text);
void I2C_Lcd_Text_Cp(char *text);
void  I2C_Lcd_chr_propio(uint8_t fila,uint8_t columna,const uint8_t cual,const char *vect);


#endif /* LIBRERIA_lcd_i2c_h_ */
