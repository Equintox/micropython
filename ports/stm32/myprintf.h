#ifndef _PRINTF_H_
#define _PRINTF_H_

#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Output a character to a custom device like UART.
 * This function is declared here only. You have to write your custom implementation somewhere.
 * \param character to output
 */
void _putchar(const char ch);


/**
 * Tiny printf implementation
 * You have to implement _putchar if you use printf()
 * \param format A string that specifies the format of the output
 * \return The number of characters that are written into the array, not counting the terminating null character
 */
int my_printf(const char* format, ...);


/**
 * Tiny sprintf implementation
 * Due to security reasons YOU SHOULD CONSIDER USING SNPRINTF INSTEAD!
 * \param buffer A pointer to the buffer where to store the formatted string
 * \param format A string that specifies the format of the output
 * \return The number of characters that are written into the array, not counting the terminating null character
 */
int my_sprintf(char* buffer, const char* format, ...);


/**
 * Tiny snprintf implementation
 * \param buffer A pointer to the buffer where to store the formatted string
 * \param count The maximum number of characters to store in the buffer, including a terminating null character
 * \param format A string that specifies the format of the output
 * \return The number of characters that are written into the array, not counting the terminating null character
 */
int my_snprintf(char* buffer, size_t count, const char* format, ...);


/**
 * Tiny vsnprintf implementation
 * \param buffer A pointer to the buffer where to store the formatted string
 * \param buffer_len The maximum number of characters to store in the buffer, including a terminating null character
 * \param format A string that specifies the format of the output
 * \param va A value identifying a variable arguments list initialized with va_start.
 * \return The number of characters that are written into the array, not counting the terminating null character
 */
#define vsnprintf(buffer, buffer_len, format, va) _vsnprintf(buffer, buffer_len, format, va)

#ifdef __cplusplus
}
#endif


#endif  // _PRINTF_H_
