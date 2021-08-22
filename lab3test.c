#include "types.h"
#include "stat.h"
#include "user.h"
#include "memlayout.h"

int recursiveProgram(int num)
{
  if (num == 0)
  {
    return num;
  }
  else
  {
    num += recursiveProgram(num - 1);
  }

  return -987654321; // This function always return this number.
}

int main(int argc, char *argv[])
{
  printf(1, "------- Begin lab3test -------\n");

  // Needs 1 int function parameter
  if (argc > 1)
  {
    // Pass an arbitrary int that triggers page fault
    recursiveProgram(atoi(argv[1]));
  }
  else
  {
    printf(1, "Please pass any int to the program parameter to trigger page fault. Program exsiting..\n");
    exit(0);
  }

  printf(1, "------- End lab3test -------\n");
  exit(0);
}
