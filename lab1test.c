#include "types.h"
#include "stat.h"
#include "user.h"

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
      printf(1, "Child process created successfully with the PID: [%d]\n", getpid());
      exit(0); // Can pass in any int for testing purposes
    }
  }
}

int main(int argc, char *argv[])
{
  printf(1, "Begin lab1test...\n");
  waitpidTest();
  exit(0);
}
