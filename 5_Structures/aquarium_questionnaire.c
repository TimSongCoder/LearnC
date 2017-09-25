typedef struct {
  unsigned int first_visit:1; /* One bit is enough: Yes or No. */
  unsigned int come_again:1; /* One bit is enough: Yes or No. */
  unsigned int fingers_lost:4; /* Range: 0-10; need 4 bits. */
  unsigned int shark_attack:1; /* Yes or No. */
  unsigned int days_a_week:3; /* Range: 0-7; need 3 bits. */
} survey;
