// Facebook Interview Question:
// You are given a function Read4K(char *buf) which reads either 4096 bytes or
// remaining bytes from a file, whichever is less, into buf and returns the number
// of bytes read. Using this API, implement Read(char *buf, int n) which reads any
// number of bytes and returns the number of bytes read.

int Read (char *buf, int n) {
  int totalbytes = 0;
  char aux[4096];

  while (n > 0) {
    int bytes = Read4K(aux);

    if (bytes) {
      bytes = n < bytes ? n : bytes;

      memcpy (buf, aux, bytes);

      buf += bytes;
      totalbytes += bytes;
      n -= bytes;
    } else {
      break;
    }
  }

  return totalbytes;
}