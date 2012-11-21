#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MEM_SIZE 30000
#define BUF_SIZE 1024
#define DEBUG 0

char memory_space[MEM_SIZE];
char* p;

void debug(char* message) {
  if(DEBUG)
    printf("%s\n", message);
}


void execute(char c) {
  if(DEBUG) printf("Interpreting %c\t*p = %d\n", c, *p);
  switch(c) {
    case '+':
      debug("incr");
      (*p)++;
      break;
    case '-':
      debug("decr");
      (*p)--;
      break;
    case '>':
      debug("pincr");
      p++;
      break;
    case '<':
      debug("pdecr");
      p--;
      break;
    case '.':
      debug("print");
      printf("%c", *p);
      break;
    case ',':
      debug("read");
      scanf("%c", p);
      break;
    case '[':
      // TODO
      debug("begin loop");
      break;
    case ']':
      // TODO
      debug("end loop");
      break;
    default:
      break;
  }
}

void zero_memory() {
  int i;
  p = memory_space;
  for(i = 0; i < MEM_SIZE; i++)
    *(p++) = 0;
  p = memory_space;
}

void run_file(char* fname) {
  char buf[BUF_SIZE];
  char* inst;
  int f, bytes_read, i;
  
  f = open(fname, O_RDONLY);
  if(f == -1) {
    perror(fname);
    return;
  }

  zero_memory();

  do {
    bytes_read = read(f, buf, BUF_SIZE);
    for(i = 0, inst = buf; i < bytes_read; i++, inst++) {
      execute(*inst);
    }
  } while(bytes_read);
}

int main(int argc, char** argv) {
  int i;
  for(i = 1; i < argc; i++) {
    run_file(argv[i]);
  }
  return 0;
}
