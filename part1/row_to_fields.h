#include <cstring>
#include "list.h"
#include "object.h"
#include "str.h"

StrList *row_to_fields(String *row_string) {
  StrList *fields = new StrList();
  size_t field_idx = 0;
  bool value_found = false;
  int start_bracket_idx = -1;  // indices tracking start of a field, negative means currently unassigned
  bool in_quotes = false;
  for (size_t idx = 0; idx < row_string->size(); idx++) {
    char cur_char = row_string->get(idx);
    if (cur_char == '<') {
      if (start_bracket_idx < 0) start_bracket_idx = idx;
    }
    else if (start_bracket_idx > -1  && ((cur_char == '>') ||
        (in_quotes && cur_char == '"') ||
        (value_found && cur_char == ' ' && !in_quotes))) {
      size_t end_idx = in_quotes ? idx + 1 : idx;
      String *slice = row_string->get_slice(start_bracket_idx + 1, end_idx);
      fields->set(field_idx, slice);
      field_idx += 1;
      start_bracket_idx = -1;
      value_found = false;
      in_quotes = false;
    }
    else if (cur_char == ' ' && start_bracket_idx >= 0 && !in_quotes) {
      // TODO handle case of space in field between non-space characters not in quotes
      start_bracket_idx += 1;
    }
    else if (cur_char == ' ' && start_bracket_idx >= 0 && value_found && !in_quotes) {
      // TODO handle case of space in field between non-space characters not in quotes
      puts("can't have spaces in a value unless that value is surrounded by double quotes");
      exit(1);
    }
    else if (cur_char == '"') {
      in_quotes = true;
      value_found = true;
    }
    else if (cur_char != ' ') {
      value_found = true;
    }
  }
  return fields;
}