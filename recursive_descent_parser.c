#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define BUFFER 1024

// Structure to hold parsing state
typedef struct {
  const char *input;
  int index;
  bool error;
} ParserState;

// Function prototypes
void parse_S(ParserState *state);
void parse_E(ParserState *state);
void parse_T(ParserState *state);
void parse_F(ParserState *state);
void parse_G(ParserState *state);
void parse_H(ParserState *state);

// Helper functions
bool is_at_end(ParserState *state) {
  return state->input[state->index] == '\0';
}

char peek(ParserState *state) { return state->input[state->index]; }

void advance(ParserState *state) {
  if (!is_at_end(state)) {
    state->index++;
  }
}

bool match(ParserState *state, char expected) {
  if (is_at_end(state) || peek(state) != expected) {
    return false;
  }
  advance(state);
  return true;
}

void error(ParserState *state, const char *message) {
  if (!state->error) {
    printf("Error at index %d: %s\n", state->index, message);
    state->error = true;
  }
}

// Parsing functions
void parse_S(ParserState *state) {
  parse_E(state);
  if (!is_at_end(state)) {
    error(state, "Expected end of input");
  }
}

void parse_E(ParserState *state) {
  parse_T(state);
  parse_G(state);
}

void parse_T(ParserState *state) {
  parse_F(state);
  parse_H(state);
}

void parse_F(ParserState *state) {
  if (match(state, '(')) {
    parse_E(state);
    if (!match(state, ')')) {
      error(state, "Expected closing parenthesis");
    }
  } else if (match(state, 'a')) {
    // 'a' represents any letter
  } else {
    error(state, "Expected '(' or letter");
  }
}

void parse_G(ParserState *state) {
  if (match(state, '+')) {
    parse_T(state);
    parse_G(state);
  }
  // ε production: do nothing
}

void parse_H(ParserState *state) {
  if (match(state, '*')) {
    parse_F(state);
    parse_H(state);
  }
  // ε production: do nothing
}

// Input preprocessing
void preprocess_input(char *input) {
  for (int i = 0; input[i] != '\0'; i++) {
    if (isalpha((unsigned char)input[i])) {
      input[i] = 'a';
    }
  }
}

int main() {
  char input[BUFFER];
  scanf("%s", input);

  preprocess_input(input);

  ParserState state = {input, 0, false};
  parse_S(&state);

  if (!state.error) {
    printf("Input is valid\n");
  } else {
    printf("Input is invalid\n");
  }

  return 0;
}