#include <time.h>
#include <stdio.h>
#include <unistd.h>

void wait(int sec){
  clock_t end_wait;
  printf("The frequency of the statistics clock on this machine is: %li ticks per second.\n",
          sysconf(_SC_CLK_TCK));
  printf("Macro CLOCKS_PER_SEC's value on this machine is %i\n", CLOCKS_PER_SEC);

  printf("Start_wait time in clock_t: %li\n", clock());
  /* sysconf -- get configurable system variable. <unistd.h>
  long sysconf(int name);
  The sysconf() function provides a method for applications to determine the
  current value of a configurable system limit or option variable. The 'name'
  argument specifies the system variable to be queried. Symbolic constants for
  each name value are found in the include file <unistd.h>.
  In this case, _SC_CLK_TCK can be used to query the frequency of the statistics
  clock in ticks per second.

  sysconf(_SC_CLK_TCK) and CLOCKS_PER_SEC have totally different values, they are
  designed for different using scenarios. In clock() function, we use the CLOCKS_PER_SEC
  accroding its documentation. */
  end_wait = clock() + sec * CLOCKS_PER_SEC;
  /* CLOCKS_PER_SEC macro is the number of clock ticks per second MEASURED by the
  clock() function. POSIX requires that this value be one million independent of
  the actual resolution.

  clock_t clock(void); <time.h>
  The clock() function determines the amount of processor time used since the
  invocation of the calling process, MEASURED in CLOCKS_PER_SECs of a second.*/
  while(clock() < end_wait){} /* Just wait, do nothing at all for demo purpose.*/
  printf("End_wait time in clock_t: %li\n", clock());
}

int main(){
  puts("Start the Wait!");
  wait(5); /* Wait 5 seconds in processor time concept. */
  puts("End wait!");
  return 0;
}
