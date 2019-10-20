#ifdef CS333_P2
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) 
{
  
  int runtime_start = uptime();
  int rc = fork();
  if (rc < 0) {
    printf(2, "Error: forking failed");
    exit();
  } else if (rc == 0) {
    char ** cargv = (char**) malloc(sizeof(char*)*(argc));
    for(int i = 0; i < argc-1; i++) {
      cargv[i] = (char*) malloc(sizeof(char) * strlen(argv[i+1]));
      memmove(cargv[i], argv[i+1], strlen(argv[i+1]));
    }
    exec(cargv[0], cargv);
  } else {
    wait();
    int runtime_total =  uptime() - runtime_start;
    int runtime_seconds = runtime_total / 1000;
    int runtime_ms = runtime_total % 1000;
    printf(1, "%s ran in %d.%d seconds\n", argv[1], runtime_seconds, runtime_ms);
  }
  exit();
}
#endif
