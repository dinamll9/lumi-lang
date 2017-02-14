#ifndef __MR_C_API__
#define __MR_C_API__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define not !
#define or ||
#define and &&

typedef int Int;
typedef char Char;
typedef unsigned char Byte;

typedef struct {
  int max_length;
  int actual_length;
  char* chars;
} String;

typedef enum {
  false = 0,
  true = 1
} Bool;

typedef enum {
  OK = EXIT_SUCCESS,
  ERR = EXIT_FAILURE
} Returncode;

typedef struct {
  int length;
  void* values;
} Array;

typedef Returncode (*Func)();

typedef FILE File;

typedef struct {} Sys;

#define RAISE { fprintf(stderr, "Error raised in %s:%d %s()\n", __FILE__, __LINE__, __FUNCTION__); \
  return ERR; }

#define CHECK(err) { Returncode _err = err; if (_err != OK) { \
  fprintf(stderr, "  called from %s:%d %s()\n", __FILE__, __LINE__, __FUNCTION__); \
  return _err; } }

#define MAIN_FUNC int main(int argc, char* argv[]) { \
  String* args_strings = malloc(argc * sizeof(String)); \
  if (args_strings == NULL) { \
    fprintf(stderr, "insufficient memory\n"); \
    return ERR; \
  } \
  Array* args_array = &(Array){argc, args_strings}; \
  int arg; \
  for (arg = 0; arg < argc; ++arg) { \
    args_strings[arg].chars = argv[arg]; \
    args_strings[arg].max_length = strnlen(args_strings[arg].chars, 1024); \
    args_strings[arg].actual_length = args_strings[arg].max_length; \
  } \
  CHECK(func(args_array)) \
  return OK; \
}

String* new_string(int length);
Array* new_array(int length, int value_size);

Returncode String_clear(String* this);
Returncode String_length(String* this, Int* length);
Returncode String_equal(String* this, String* other, Bool* equal);
Returncode String_get(String* this, Int index, Char* ch);
Returncode String_append(String* this, Char ch);
Returncode String_copy(String* this, String* source);
Returncode String_concat(String* this, String* ext);
Returncode String_find(String* this, String* pattern, Int* index);
Returncode String_replace(String* this, Char old_ch, Char new_ch);

Returncode Int_str(Int value, String* str);

Returncode File_close(File* this);
Returncode File_getc(File* this, Char* ch);
Returncode File_putc(File* this, Char ch);
Returncode File_write(File* this, String* line);

Returncode Sys_print(Sys*, String* text);
Returncode Sys_exit(Sys*, Int status);
Returncode Sys_system(Sys*, String* command, Int* status);
Returncode Sys_getenv(Sys*, String* name, Bool* exists, String* value);

#endif  /*__MR_C_API__*/
