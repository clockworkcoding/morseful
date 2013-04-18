#include "pebble_os.h"
#include "morse.h"

void morse_format_string(char *string, size_t length, uint32_t *durations) {
  int i = 0;

  for (size_t j = 0; j < length; j++) {
    char c = string[j];

    switch (c) {
    case '0': WRITE_MORSE(0, i, durations); break;
    case '1': WRITE_MORSE(1, i, durations); break;
    case '2': WRITE_MORSE(2, i, durations); break;
    case '3': WRITE_MORSE(3, i, durations); break;
    case '4': WRITE_MORSE(4, i, durations); break;
    case '5': WRITE_MORSE(5, i, durations); break;
    case '6': WRITE_MORSE(6, i, durations); break;
    case '7': WRITE_MORSE(7, i, durations); break;
    case '8': WRITE_MORSE(8, i, durations); break;
    case '9': WRITE_MORSE(9, i, durations); break;
    }

    durations[i - 1] = SGAP;
  }
}

