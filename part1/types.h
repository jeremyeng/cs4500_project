#pragma once
#include <regex.h>
#include <stdio.h>

/* Enum class representing supported column types */
enum class DataType { BOOL, INT, FLOAT, STRING };

DataType get_type(String *sor_value) {
  /* Given a field value from a SOR file, returns the corresponding DataType of that value.
   * @param sor_value:
   * @return: DataType corresponding to given SOR value */
  const char *field_value = sor_value->str_;
  regex_t string_regex;
  regex_t float_regex;
  regex_t bool_regex;
  regex_t int_regex;

  int string_regex_compiled = regcomp(&string_regex, "[a-zA-Z]+", REG_EXTENDED);
  int float_regex_compiled = regcomp(&float_regex, "[-+]?[0-9]*\\.+[0-9]+", REG_EXTENDED);
  int bool_regex_compiled = regcomp(&bool_regex, "^[0|1]$", REG_EXTENDED);
  int int_regex_compiled = regcomp(&int_regex, "[-+]?[0-9]+", REG_EXTENDED);

  // check regex compilation
  assert(string_regex_compiled == 0);
  assert(float_regex_compiled == 0);
  assert(bool_regex_compiled == 0);
  assert(int_regex_compiled == 0);

  DataType field_type;
  if (regexec(&string_regex, field_value, 0, nullptr, 0) == 0) {
    field_type = DataType::STRING;
  }
  else if (regexec(&float_regex, field_value, 0, nullptr, 0) == 0) {
    field_type = DataType::FLOAT;
  }
  else if (regexec(&bool_regex, field_value, 0, nullptr, 0) == 0) {
    field_type = DataType::BOOL;
  }
  else if (regexec(&int_regex, field_value, 0, nullptr, 0) == 0) {
    field_type = DataType::INT;
  }
  else {
    field_type = DataType::BOOL;
  }

  // free regexes
  regfree(&float_regex);
  regfree(&string_regex);
  regfree(&int_regex);
  regfree(&bool_regex);

  return field_type;
};

void print_data_type(DataType data_type) {
  /* Prints out the given DataType
   * @param data_type: DataType to print
   * @return: None */
  switch (data_type) {
    case DataType::BOOL  :
      puts("BOOL");
      break;
    case DataType::INT  :
      puts("INT");
      break;
    case DataType::FLOAT  :
      puts("FLOAT");
      break;
    case DataType::STRING  :
      puts("STRING");
      break;
  }
}