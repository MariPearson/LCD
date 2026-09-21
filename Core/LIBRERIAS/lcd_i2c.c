#include "lcd_i2c.h"

extern I2C_HandleTypeDef hi2c1;

static HAL_StatusTypeDef lcd_transmit(uint8_t *data, uint16_t size)
{
    return HAL_I2C_Master_Transmit(
        &hi2c1,
        (uint16_t)(SLAVE_ADDRESS_LCD << 1),
        data,
        size,
        100);
}

static void lcd_write_nibble(uint8_t nibble, uint8_t rs)
{
    uint8_t data[2];
    uint8_t control = LCD_BL | (rs ? LCD_RS : 0U);

    data[0] = (nibble & 0xF0U) | control | LCD_EN;
    data[1] = (nibble & 0xF0U) | control;
    lcd_transmit(data, 2);
}

void lcd_send_cmd(char cmd)
{
    lcd_write_nibble((uint8_t)cmd & 0xF0U, 0U);
    lcd_write_nibble(((uint8_t)cmd << 4) & 0xF0U, 0U);
}

void lcd_send_data(char data)
{
    lcd_write_nibble((uint8_t)data & 0xF0U, 1U);
    lcd_write_nibble(((uint8_t)data << 4) & 0xF0U, 1U);
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
        case 2:
            col |= 0x94;
            break;
        case 3:
            col |= 0xD4;
            break;
    }
    lcd_send_cmd(col);
}

void lcd_init(void)
{
    HAL_Delay(50);
    lcd_write_nibble(0x30U, 0U);
    HAL_Delay(5);
    lcd_write_nibble(0x30U, 0U);
    HAL_Delay(1);
    lcd_write_nibble(0x30U, 0U);
    HAL_Delay(10);
    lcd_write_nibble(0x20U, 0U); // Inicialización en modo 4 bits
    HAL_Delay(10);

    // Configuración del Display
    lcd_send_cmd(0x28); // 2 líneas, 5x8 puntos
    HAL_Delay(1);
    lcd_send_cmd(0x08); // Display OFF
    HAL_Delay(1);
    lcd_send_cmd(0x01); // Limpiar pantalla
    HAL_Delay(2);
    lcd_send_cmd(0x06); // Incremento de dirección
    HAL_Delay(1);
    lcd_send_cmd(0x0C); // Display ON, Cursor OFF
}

void lcd_send_string(char *str)
{
    while (*str) lcd_send_data(*str++);
}

void I2C_Lcd_Cmd(char out_char)
{
    lcd_send_cmd(out_char);
}

void I2C_Lcd_Init(void)
{
    lcd_init();
}

void I2C_Lcd_Chr(char row, char column, char out_char)
{
    lcd_put_cur(row - 1, column - 1);
    lcd_send_data(out_char);
}

void I2C_Lcd_Chr_Cp(char out_char)
{
    lcd_send_data(out_char);
}

void I2C_Lcd_CreateChar(uint8_t location, const uint8_t character[8])
{
    location &= 0x07U;
    lcd_send_cmd((char)(0x40U | (location << 3)));

    for (uint8_t row = 0; row < 8; row++)
    {
        lcd_send_data((char)(character[row] & 0x1FU));
    }

    lcd_send_cmd(0x02);
}

void I2C_Lcd_Text(char row, char col, char *text)
{
    lcd_put_cur(row - 1, col - 1);
    while (*text)
    {
        lcd_send_data(*text++);
    }
}

void I2C_Lcd_Text_Cp(char *text)
{
    while (*text)
    {
        lcd_send_data(*text++);
    }
}

void I2C_Lcd_chr_propio(uint8_t fila, uint8_t columna, const uint8_t cual, const char *vect)
{
    (void)fila;
    (void)columna;
    (void)cual;
    (void)vect;
}