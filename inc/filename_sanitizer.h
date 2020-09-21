#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define ASCII_DOT 0x2E
#define ASCII_UNDERSCORE 0x5F


void sanitize(uint8_t *input, uint8_t input_s, uint8_t *output);
char is_allowed(char eval, bool dot_valid);
void create_output(uint8_t length, uint8_t **buffer);
uint8_t get_argument_length(char *input);
void check_args(int arg_nb);
void error_handler(uint8_t* message, uint8_t action);
