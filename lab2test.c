#include "types.h"
#include "stat.h"
#include "user.h"

void schedulerTest()
{
  printf(1, "This test creates 10 child process.\n");
  printf(1, "Each process will have priority ranging from 0-16, 0 being the highest and 16 being the lowest.\n");
  printf(1, "The first child process has priority 16 and the next child process will have 15 and the next 14 and so on..\n");

  int pid[10];
  int status;

  int x, y, z, a;
  for (x = 0; x < 10; x++)
  {
    z = 0;
    if ((pid[x] = fork()) == 0)
    {
      // Child goes here
      changePriority(16 - x); // 16, 15, 14, 13, 12, 11, 10, 9, 8, 7
      for (y = 0; y < (100 * (1 + x * 0.1)); y++)
      {
        // Hi
        for (a = 0; a < getpid() * 500; a++)
        {
          z += y / 2;
        }
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

  printf(1, "Parent process begins waiting...\n");
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
