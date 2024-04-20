#include "reciver.h"

void Reciver::init() { 
  pinMode(receivePin, INPUT); 
}

void Reciver::start() {
  protocolMethod();
}

char Reciver::binaryToChar(byte binary[8]) {
  char c = 0;
  for (int j = 0; j < 8; j++) {
    c |= (binary[j] << (j));
  }
  return c;
}