#include "types.h"
#include "stat.h"
#include "user.h"

void waitTest()
{
  changePriority(0);
  int pid[4];
  int status;
  int returnPid;

  int x, y;
  for (x = 0; x < 4; x++)
  {
    if ((pid[x] = fork()) == 0)
    {
      // Child goes here
      for (y = 0; y < 100000; y++)
        ;

      changePriority(16 - x * 3); // 16, 13, 10, 7
      exit(x + 5);                // Can pass in any int for testing purposes
    }
    else if (pid[x] < 0)
    {
      // Error
      printf(1, "Error after fork().\n");
      exit(-1);
    }
  }

  for (x = 0; x < 4; x++)
  {
    returnPid = wait(&status);
    printf(1, "Child [%d] waited.\n", returnPid);
  }
}

void waitpidTest()
{
  int pids[4];
  int returnStatus;
  int status = 0;

  /*  This part tests if waitpid(...) actually waits for the specified child process */
  int x;
  for (x = 0; x < 3; x++)
  {
    if ((pids[x] = fork()) > 0)
    {
      // Only parent process goes here
      if ((returnStatus = waitpid(pids[x], &status, 0)) == -1)
      {
        // If a child process cannot be found, display this message.
        printf(1, "Could not find the child with the PID: [%d]\n", pids[x]);
      }
      else
      {
        // If a child process was found and waited, display this message.
        printf(1, "Finished waiting for child process with PID: [%d], return status: [%d], and exit status: [%d]\n", pids[x], returnStatus, status);
      }
    }
    else if (pids[x] < 0)
    {
      printf(1, "Error forking\n");
      exit(0);
    }
    else if (pids[x] == 0)
    {
      // Only child process goes here
      printf(1, "Child process created successfully with the PID: [%d]\nChild process exiting with status: [%d]\n", getpid(), getpid() + 1);
      exit(getpid() + 1); // Can pass in any int for testing purposes
    }
  }
}

int main(int argc, char *argv[])
{
  printf(1, "------- Begin lab1test -------\n\t");

  if (atoi(argv[1]) == 1)
  {
    printf(1, "Test: wait(int *)\n");
    waitTest();
  }
  else if (atoi(argv[1]) == 2)
  {
    printf(1, "Test: waitpid(int, int *, int)\n");
    waitpidTest();
  }
  else
  {
    printf(1, "Command line arguments: pass 1 to test wait(int *) or 2 to test waitpid(int, int*, int).\n");
  }
  exit(0);
}
