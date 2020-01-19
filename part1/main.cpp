#include "helper.h"
#include "object.h"
#include "str.h"
#include "list.h"
#include <unistd.h>

int main(int argc, char** argv) {
  Sys* sys = new Sys();
  char *fvalue = const_cast<char *>("data.sor");
  int from = 1;
  int len = 10;
  int cli_opt;

  FILE * pFile;
  char * buffer;
  size_t result;

  pFile = fopen ( fvalue , "r" );
  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

  // allocate memory to contain the whole file:
  buffer = new char[len];
  if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // move to from start to "from"
  fseek ( pFile , from , SEEK_SET );
  // copy the number of bytes in len into the buffer:
  result = fread (buffer,1,len,pFile);

  bool skip_first = from == 0;
  bool skip_last = len < ftell(pFile);
  rewind(pFile); // reset after getting size

  char delimiter[2] = "\n";
  char* token;
  
  StrList* token_list = new StrList();
  token = strtok(buffer, delimiter);
  token_list->push_back(new String(token));
  delete token;
  
  while (token != NULL) {
    token = strtok(NULL, delimiter);
    token_list->push_back(new String(token));
    delete token;
  }

  for(size_t i = 0; i < token_list->size(); i++) {
    sys->pln(token_list->get(i)->str_);
  }

  // terminate
  fclose (pFile);
  delete buffer;
  delete token_list;
  return 0;

}