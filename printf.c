#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define putchar(x) write(1, chardup(x), 1);
/*chardup takes a char and convert into a string */
char *chardup(const char ch) {
  static char buf[2];
  char *p;
  p = buf;
  *p++ = ch;
  *p-- = 0;
  return buf;
}

unsigned int _strlen(const char *str) {
  unsigned int len;
  len = 0;
  while (*str++)
    len++;
  return len;
}

int _puts(const char *str) {
  unsigned int len;
  len = _strlen(str);
  if (len == 0)
    return -1;
  return write(1, str, len);
}

#include <stdlib.h>

char *_itoa(int n) {
  int negative = n < 0;

  // Handle 0 and negative numbers safely
  unsigned int num = negative ? 0u - (unsigned int)n : (unsigned int)n;

  char *str = malloc(2);
  if (str == NULL)
    return NULL;

  int curr = 0;

  do {
    str[curr++] = '0' + num % 10;
    num /= 10;

    char *temp = realloc(str, curr + 2);
    if (temp == NULL) {
      free(str);
      return NULL;
    }
    str = temp;
  } while (num > 0);

  if (negative) {
    char *temp = realloc(str, curr + 2);
    if (temp == NULL) {
      free(str);
      return NULL;
    }
    str = temp;
    str[curr++] = '-';
  }

  str[curr] = '\0';

  int l = 0, h = curr - 1;

  while (l < h) {
    char temp = str[h];
    str[h] = str[l];
    str[l] = temp;
    l++;
    h--;
  }

  return str;
}

#include <stdarg.h>
#include <stdio.h>

int _printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  while (*fmt) {
    if (*fmt != '%') {
      putchar(*fmt++);
      continue;
    }

    fmt++; // Skip '%'

    switch (*fmt) {
    case '%':
      putchar('%');
      break;

    case 'c': {
      char ch = (char)va_arg(args, int);
      putchar(ch);
      break;
    }

    case 's': {
      const char *str = va_arg(args, const char *);
      _puts(str);
      break;
    }

    case 'd': {
      int num = va_arg(args, int);
      char *str = _itoa(num);
      _puts(str);
      break;
    }

    default:
      putchar('%');
      if (*fmt != '\0') {
        putchar(*fmt);
      }
      break;
    }

    if (*fmt != '\0') {
      fmt++;
    }
  }

  va_end(args);
  return 0;
}
int main() {

  _printf("Hello, %s you have %d\n", "Harsh", 123);
  return 0;
}
