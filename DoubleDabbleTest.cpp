// Double Dabble  

// binary to BCD conversion no multiplies or divides

// also efficient div 10, mod 10 for MCUs such as MSP430 with hardware multiply but not divide

#include <iostream>

long bin2BCD(long binary) { // double dabble: 8 decimal digits in 32 bits BCD
  if (!binary) return 0;
  long bit = 0x4000000; //  99999999 max
  while (!(binary & bit)) bit >>= 1;  // skip to MSB

  long bcd = 0;
  long carry = 0;
  while (1) {
    bcd <<= 1;
    bcd += carry; // carry 6s to next BCD digits (10 + 6 = 0x10 = LSB of next BCD digit)
    if (bit & binary) bcd |= 1;
    if (!(bit >>= 1)) return bcd;
    carry = ((bcd + 0x33333333) & 0x88888888) >> 1; // carrys: 8s -> 4s
    carry += carry >> 1; // carrys 6s  
  }
}

int main() {
  printf("%X\n", bin2BCD(12345678));
  printf("%X\n", bin2BCD(87654321));
  printf("%X\n", bin2BCD(55555555));
  printf("%X\n", bin2BCD(99999999));

// ldiv by 10 using only HW MPY:
  const int Tenth32 = 0x1999999A;

  _int64 N = 987654321;
  _int64 tenth = N * Tenth32;
  _int64 Ndiv10 = tenth >> 32;
  _int64 Nmod10 = (tenth & 0xFFFFFFFF) * 10 >> 32;

  std::cout << Ndiv10 << " " << Nmod10;
}
