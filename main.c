#include <cstdio>
#include <cstdlib>
#include <cstring>

#define BUFFER_SIZE (16 * 1024)

void usage(char* argv[]) { printf("Usage: %s inputFile.txt\n", argv[0]); }

uint64_t lineCount(char* start, char* end) {
  int lineCounter = 0;
  while ((start = (char*)memchr(start, '\n', end - start))) {
    ++lineCounter;
    ++start;
  }
  return lineCounter;
}

int main(int argc, char* argv[]) {
  FILE* pFile;
  size_t bytesRead;
  char buffer[BUFFER_SIZE];

  uint64_t lineCounter, totalRead;
  lineCounter = totalRead = 0;

  if (argc < 2) {
    usage(argv);
    return EXIT_FAILURE;
  }

  pFile = fopen(argv[1], "r");
  if (pFile == NULL) {
    fputs("File error", stderr);
    return EXIT_FAILURE;
  }

  while ((bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, pFile)) > 0) {
    totalRead += bytesRead;
    lineCounter += lineCount(buffer, buffer + bytesRead);
  }

  printf("lines:%llu bytes:%llu file:%s\n", ++lineCounter, totalRead, argv[1]);
  fclose(pFile);
  return EXIT_SUCCESS;
}
