#ifndef LUMI_MAINFILE
#define LUMI_MAINFILE "lumi.c"
#define DEPTH 1
#include "lumi.3.h"
#else

#if LUMI_STAGE == LUMI_TYPEDEFS
static char* _lumi_file1_name = "lumi.3.lm";
#endif
#define LUMI_FILE_NAME _lumi_file1_name

/*  Builds executables from Lumi files

Gets input files as "<name>.<TL-version>.lm",
generates "<name>.c" files using TL<version> compiler.
Then compiles the last one to "<name>" executable using "CC" environment
variable, or "gcc" if not specified.
(TL0 and TL1 only supports one file)

Supports TL0, TL1, TL2 & TL3.
 */

#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode f_error_if(Bool is_error, String* error_msg);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_f_error_if = "f-error-if";
#define LUMI_FUNC_NAME _func_name_f_error_if
Returncode f_error_if(Bool is_error, String* error_msg) {
  if (is_error) {
    CHECK(14, Sys_print(sys, error_msg) )
    RAISE(15)
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif

#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode f_run_command(String* command, String* error_msg);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_f_run_command = "f-run-command";
#define LUMI_FUNC_NAME _func_name_f_run_command
Returncode f_run_command(String* command, String* error_msg) {
  CHECK(18, Sys_print(sys, command) )
  Int _Int0;
  CHECK(19, Sys_system(sys, command, &(_Int0)) )
  if (_Int0 != 0) {
    CHECK(20, Sys_print(sys, error_msg) )
    RAISE(21)
  }
  return OK;
}
#undef LUMI_FUNC_NAME
#endif

#if LUMI_STAGE == LUMI_DECLARATIONS
Returncode func(Array* argv);
#elif LUMI_STAGE == LUMI_FUNCTIONS
static char* _func_name_func = "func";
#define LUMI_FUNC_NAME _func_name_func
Returncode func(Array* argv) {
  /* parse input */
  CHECK(25, f_error_if(argv->length < 2, &(String){32, 31, "usage: lumi [Lumi file name]..."}) )
  if ((argv->length - 1) < 0 || (argv->length - 1) >= (argv)->length) RAISE(26)
  String* lumi_file = (&(((String*)((argv)->values))[argv->length - 1]));
  CHECK(27, f_error_if(lumi_file->length < 6, &(String){25, 24, "Lumi file name too short"}) )
  Bool _Bool1;
  CHECK(28, String_has(lumi_file, '"', &(_Bool1)) )
  CHECK(28, f_error_if(_Bool1, &(String){33, 32, "Illegal \" character in file name"}) )
  if ((0) < 0 || (lumi_file->length - 5) < 0 || (0) + (lumi_file->length - 5) > (lumi_file)->length) RAISE(31)
  String* prefix = (&(String){lumi_file->length - 5, lumi_file->length - 5, (lumi_file)->values + (0)});
  if ((lumi_file->length - 4) < 0 || (lumi_file->length - 4) >= (lumi_file)->length) RAISE(32)
  Char version = ((lumi_file)->values[lumi_file->length - 4]);
  CHECK(33, f_error_if(version < '0' || version > '3', &(String){23, 22, "Unsupported TL version"}) )
  CHECK(34, f_error_if(version < '2' && argv->length > 2, &(String){40, 39, "Multiple files not supported before TL2"}) )
  
  /* run Lumi compiler */
  String* command = &(String){1024, 0, (char[1024]){0}};
  CHECK(40, String_copy(command, &(String){3, 2, "tl"}) )
  CHECK(41, String_append(command, version) )
  CHECK(42, String_concat(command, &(String){10, 9, "-compiler"}) )
  {int index; for (index = (1); index < (argv->length); ++index) {
    CHECK(44, String_concat(command, &(String){3, 2, " \""}) )
    if ((index) < 0 || (index) >= (argv)->length) RAISE(45)
    CHECK(45, String_concat(command, (&(((String*)((argv)->values))[index]))) )
    CHECK(46, String_concat(command, &(String){2, 1, "\""}) )
  }}
  if (version < '2') {
    CHECK(48, String_concat(command, &(String){3, 2, " \""}) )
    CHECK(49, String_concat(command, prefix) )
    CHECK(50, String_concat(command, &(String){4, 3, ".c\""}) )
  }
  CHECK(51, f_run_command(command, &(String){21, 20, "Lumi compiler failed"}) )
  
  /* run C compiler */
  Bool _Bool2;
  CHECK(54, Sys_getenv(sys, &(String){3, 2, "CC"}, command, &(_Bool2)) )
  if (!_Bool2) {
    CHECK(55, String_copy(command, &(String){4, 3, "gcc"}) )
  }
  CHECK(56, String_concat(command, &(String){6, 5, " -g \""}) )
  CHECK(57, String_concat(command, prefix) )
  CHECK(58, String_concat(command, &(String){5, 4, ".c\" "}) )
  if (version == '0') {
    CHECK(60, String_concat(command, &(String){24, 23, "tl0-file.c tl0-string.c"}) )
  }
  else {
    CHECK(62, String_concat(command, &(String){6, 5, "lumi."}) )
    CHECK(63, String_append(command, version) )
    CHECK(64, String_concat(command, &(String){3, 2, ".c"}) )
  }
  CHECK(65, String_concat(command, &(String){6, 5, " -o \""}) )
  CHECK(66, String_concat(command, prefix) )
  CHECK(67, String_concat(command, &(String){2, 1, "\""}) )
  CHECK(68, f_run_command(command, &(String){18, 17, "C compiler failed"}) )
  return OK;
}
#undef LUMI_FUNC_NAME
#endif

#if LUMI_STAGE == LUMI_FUNCTIONS
MAIN_FUNC
#endif

#undef LUMI_FILE_NAME

#endif