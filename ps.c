#ifdef CS333_P2
#include "types.h"
#include "user.h"
#include "uproc.h"

int
main(int argc, char *argv[])
{

  uint max;
  if(argc > 2)
  {
    exit();
  } else if(argc > 1) 
  {
    max = atoi(argv[1]);
  } else 
  {
    max = 16;
  }
  
  struct uproc* table = (struct uproc*) malloc(sizeof(struct uproc)*max);
  int found = getprocs(max, table); 

  if(found != 0) 
  {
#ifdef CS333_P4
    printf(1, "PID\tName\t\tUID\tGID\tPPID\tPrio\tElapsed\t\tCPU\tState\tSize\n");
#else
    printf(1, "PID\tName\t\tUID\tGID\tPPID\tElapsed\t\tCPU\tState\tSize\n");
#endif
  } else {
    printf(1, "No processes found");
    exit();
  }

  struct uproc* table_inc = table;
  for(int i = 0; i < found; i++)
  {
    int elapsed_ticks_seconds = table_inc->elapsed_ticks / 1000;
    int elapsed_ticks_ms = table_inc->elapsed_ticks % 1000;
    int CPU_total_ticks_seconds = table_inc->CPU_total_ticks / 1000;
    int CPU_total_ticks_ms = table_inc->CPU_total_ticks % 1000;
#ifdef CS333_P4
    printf(1, "%d\t%s\t\t%d\t%d\t%d\t%d\t", 
              table_inc->pid,
              table_inc->name,
              table_inc->uid,
              table_inc->gid,
              table_inc->ppid,
              table_inc->priority);
#else
    printf(1, "%d\t%s\t\t%d\t%d\t%d\t%d\t", 
              table_inc->pid,
              table_inc->name,
              table_inc->uid,
              table_inc->gid,
              table_inc->ppid);
#endif

    if(elapsed_ticks_ms < 10)
    {
      printf(1, "%d.00%d\t\t", elapsed_ticks_seconds, elapsed_ticks_ms);
    } else if(elapsed_ticks_ms < 100) 
    {
      printf(1, "%d.0%d\t\t", elapsed_ticks_seconds, elapsed_ticks_ms);
    } else
    {
      printf(1, "%d.%d\t\t", elapsed_ticks_seconds, elapsed_ticks_ms);
    }
 
    if(CPU_total_ticks_ms < 10)
    {
      printf(1, "%d.00%d\t", CPU_total_ticks_seconds, CPU_total_ticks_ms);
    } else if(CPU_total_ticks_ms < 100) 
    {
      printf(1, "%d.0%d\t", CPU_total_ticks_seconds, CPU_total_ticks_ms);
    } else
    {
      printf(1, "%d.%d\t", CPU_total_ticks_seconds, CPU_total_ticks_ms);
    }   

    printf(1, "%s\t%d\n", table_inc->state, (int)table_inc->size);   

    table_inc++;
  }

  free(table);

  exit();
}
#endif // CS333_P2
