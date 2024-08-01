#include <stdio.h>

#define MAX_TAPE_LEN 1024

/*
n_dirs: number of states that can be reached from current state
Xs: array of X characters for each state
Ys: array of Y characterss for each state
Ds: array of directions to move the input tape
next_states: array of states that can be reached from current state
state_desc: 0 - intermediate state, 1 - accept state, -1 - halt state
*/
struct State {
  int n_dirs;
  char *Xs;
  char *Ys;
  char *Ds;
  struct State **next_state;
  int state_desc;
};

void init_tape(char tape[]) {
  for (int i = 0; i < MAX_TAPE_LEN - 1; i++) {
    tape[i] = '$';
  }
  tape[MAX_TAPE_LEN - 1] = '\0';
}

void generate_state(struct State *curr, int n_dirs);

generate_turing_machine() {}

int main() {
  char tape[MAX_TAPE_LEN];

  init_tape(tape);

  struct State *start_state = (struct State *)malloc(sizeof(struct State));
  int num_of_states = 1;
  generate_turing_machine();

  run_turing_machine();

  return 0;
}