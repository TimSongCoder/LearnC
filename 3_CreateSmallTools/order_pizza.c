#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *delivery = "";
  int thick = 0;
  int count = 0;
  char ch;

  /* command options are indicated by individual characters with optionally argument. */
  while((ch = getopt(argc, argv, "d:t")) != EOF){
    switch (ch) {
      case 'd': /* option argument is anticipated. */
        delivery = optarg; /* Point the delivery variable to the argument supplied with the 'd' option. */
        break;
      case 't': /* switch on or off */
        thick = 1; /* Remember: in C, any non-zero number is regarded as true. */
        break;
      default:
        fprintf(stderr, "Unknown option: '%c'\n", ch);
        return 1;
    }
  }

  /* optind contains the index to the next argv argument for a subsequent call to getopt().
    When the loop finishes, we tweak the argv and argc variables to skip past
    all of the options and get to the MAIN command-line arguments.
   */
  argc -= optind;
  argv += optind; /* POINTER arithmetic. */

  if(thick){
    puts("Thick crust.");
  }

  if(delivery[0]){ /* Check whehter the customer specify delivery detail. */
    printf("To be delivered %s.\n", delivery);
  }

  puts("Ingredients:");

  for (count = 0; count < argc; count++){
    puts(argv[count]);
  }

  return 0;
}
