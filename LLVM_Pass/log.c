#include <stdio.h>

void funcStartLogger(char *funcName) {
  printf("[LOG] Start function '%s'\n", funcName);
}

void callLogger(char *callerName, char *calleeName, long int valID) {
  printf("[LOG] CALL '%s' -> '%s' {%ld}\n", callerName, calleeName, valID);
}

void funcEndLogger(char *funcName, long int valID) {
  printf("[LOG] End function '%s' {%ld}\n", funcName, valID);
}

void binOptLogger(int val, int arg0, int arg1, char *opName, char *funcName,
                  long int valID) {
  printf("[LOG] In function '%s': %d = %d %s %d {%ld}\n", funcName, val, arg0,
         opName, arg1, valID);
}

void resIntLogger(long int res, long int valID) {
  printf("[LOG] Result %ld {%ld}\n", res, valID);
}
