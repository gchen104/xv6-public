#include "types.h"
#include "stat.h"
#include "user.h"

void schedulerTest()
{
  int pid[10];
  int status;

  int x, y;
  for (x = 0; x < 10; x++)
  {
    if ((pid[x] = fork()) == 0)
    {
      // Child goes here
      changePriority(16 - x); // 16, 15, 14, 13, 12, 11, 10, 9, 8, 7
      for (y = 0; y < 10000000; y++)
      {
        // Hi
        y += 1;
      }
      exit(0);
    }
    else if (pid[x] < 0)
    {
      // Error
      printf(1, "Error after fork().\n");
      exit(-1);
    }
  }

  for (x = 0; x < 10; x++)
  {
    wait(&status);
  }
}

int main(int argc, char *argv[])
{
  printf(1, "------- Begin lab2test -------\n");
  schedulerTest();
  printf(1, "------- End lab2test -------\n");
  exit(0);
}
