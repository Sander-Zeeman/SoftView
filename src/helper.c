#include "helper.h"

bool isnumber(char *num) {
  if (!num)
    return false;

  while (num && *num != '\0') {
    if (*num < '0' || *num > '9') {
      return false;
    }
    num++;
  }
  return true;
}
