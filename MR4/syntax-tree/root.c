#ifndef MR_MAINFILE
#define MR_MAINFILE "syntax-tree/root.c"
#define DEPTH 5
#include "mr.3.h"
#else

#if MR_STAGE == MR_TYPEDEFS
static char* _mr_file21_name = "syntax-tree/root.3.mr";
#endif
#define MR_FILE_NAME _mr_file21_name

/* MR4 compiler - Syntax tree root */

/* The syntax tree root */
#if MR_STAGE == MR_TYPEDEFS
typedef struct SyntaxTreeRoot SyntaxTreeRoot;
#elif MR_STAGE == MR_TYPES(3)
struct SyntaxTreeRoot {
  SyntaxTreeNamespace _base;
  List* types;
  String* output_file_name;
  SyntaxTreeMainFunction* main_function;
  GlobalInit* global_init;
  Bool is_library;
/*  write C file in this order:
  1. type declarations
  2. type structs (ordered by depth)
  3. function declarations
  4. global variables
  5. function bodies
  6. main function
   */};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_init(SyntaxTreeRoot* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_init = "SyntaxTreeRoot.init";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_init
Returncode SyntaxTreeRoot_init(SyntaxTreeRoot* self) {
  CHECK(12, SyntaxTreeNamespace_init(&(self->_base)) )
  self->types = malloc(sizeof(List));
  if (self->types == NULL) RAISE(13)
  *self->types = (List){NULL, NULL};
  self->global_init = malloc(sizeof(GlobalInit));
  if (self->global_init == NULL) RAISE(14)
  *self->global_init = (GlobalInit){GlobalInit__dtl, NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, false, NULL, NULL, NULL, NULL, NULL, NULL, 0, false};
  self->global_init->_base._base._base._base._dtl = GlobalInit__dtl;
  CHECK(15, GlobalInit_init(self->global_init) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_parse(SyntaxTreeRoot* self, Array* argv);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_parse = "SyntaxTreeRoot.parse";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_parse
Returncode SyntaxTreeRoot_parse(SyntaxTreeRoot* self, Array* argv) {
  if (argv->length < 3) {
    CHECK(19, print(&(String){58, 57, "usage: mr-4compiler OUTPUT-C-FILE-NAME INPUT-MR3-FILES..."}) )
    RAISE(20)
  }
  
  if ((1) < 0 || (1) >= (argv)->length) RAISE(22)
  self->output_file_name = (&(((String*)((argv)->values))[1]));
  {int n; for (n = (2); n < (argv->length); ++n) {
    if ((n) < 0 || (n) >= (argv)->length) RAISE(24)
    glob->input_file_name = (&(((String*)((argv)->values))[n]));
    glob->line_number = 1;
    CHECK(26, file_open(glob->input_file_name, true, &(glob->input_file)) )
    
    Char _Char93;
    CHECK(28, SyntaxTreeBranch_parse_children(&(self->_base._base), NULL, NULL, &(_Char93)) )
    
    if (glob->input_buffer->length > 0 || glob->input_spaces > 0) {
      CHECK(31, SyntaxTreeNode_set_location(&(self->_base._base._base)) )
      CHECK(32, SyntaxTreeNode_m_syntax_error_msg(&(self->_base._base._base), &(String){28, 27, "no new-line before file end"}) )
    }
    
    CHECK(34, file_close(glob->input_file) )
  }}
  
  if ((2) < 0 || (2) >= (argv)->length) RAISE(36)
  self->_base._base._base.input_file_name = (&(((String*)((argv)->values))[2]));
  self->_base._base._base.line_number = 0;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_parse_child(SyntaxTreeRoot* self, String* keyword, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_parse_child = "SyntaxTreeRoot.parse-child";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_parse_child
Returncode SyntaxTreeRoot_parse_child(SyntaxTreeRoot* self, String* keyword, Char* end) {
  Bool _Bool94;
  CHECK(40, SyntaxTreeNamespace_parse_if_function(&(self->_base), keyword, NULL, &((*end)), &(_Bool94)) )
  if (_Bool94) {
    return OK;
  }
  
  Bool _Bool95;
  CHECK(43, String_equal(keyword, &(String){7, 6, "struct"}, &(_Bool95)) )
  if (_Bool95) {
    if ((*end) != ' ') {
      CHECK(45, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){35, 34, "expected space after \"struct\", got"}, (*end)) )
    }
    TypeData* _TypeData96;
    CHECK(47, TypeData_parse_new(NULL, false, &((*end)), &(_TypeData96)) )
    CHECK(47, List_add(self->types, _TypeData96) )
    
  }
  else {
    Bool _Bool97;
    CHECK(50, String_equal(keyword, &(String){6, 5, "class"}, &(_Bool97)) )
    if (_Bool97) {
      if ((*end) != ' ') {
        CHECK(52, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){34, 33, "expected space after \"class\", got"}, (*end)) )
      }
      TypeData* _TypeData98;
      CHECK(54, TypeData_parse_new(NULL, true, &((*end)), &(_TypeData98)) )
      CHECK(54, List_add(self->types, _TypeData98) )
      
    }
    else {
      Bool _Bool99;
      CHECK(57, String_equal(keyword, &(String){5, 4, "main"}, &(_Bool99)) )
      if (_Bool99) {
        if ((*end) != '\n') {
          CHECK(59, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){36, 35, "expected new-line after \"main\", got"}, (*end)) )
        }
        CHECK(61, SyntaxTreeMainFunction_parse_new(NULL, &((*end)), &(self->main_function)) )
        
      }
      else {
        Bool _Bool100;
        CHECK(64, String_equal(keyword, &(String){7, 6, "native"}, &(_Bool100)) )
        if (_Bool100) {
          if ((*end) != ' ') {
            CHECK(66, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){35, 34, "expected space after \"native\", got"}, (*end)) )
          }
          CHECK(68, parse_native(self, &((*end))) )
          
        }
        else {
          Bool _Bool101;
          CHECK(70, String_equal(keyword, &(String){5, 4, "test"}, &(_Bool101)) )
          if (_Bool101) {
            if ((*end) != ' ') {
              CHECK(72, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){33, 32, "expected space after \"test\", got"}, (*end)) )
            }
            SyntaxTreeTestFunction* _SyntaxTreeTestFunction102;
            CHECK(74, SyntaxTreeTestFunction_parse_new(NULL, &((*end)), &(_SyntaxTreeTestFunction102)) )
            CHECK(74, List_add(self->_base.functions, &(_SyntaxTreeTestFunction102->_base)) )
            
          }
          else {
            Bool _Bool103;
            CHECK(77, String_equal(keyword, &(String){5, 4, "mock"}, &(_Bool103)) )
            if (_Bool103) {
              if ((*end) != ' ') {
                CHECK(79, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){33, 32, "expected space after \"mock\", got"}, (*end)) )
              }
              SyntaxTreeMockFunction* _SyntaxTreeMockFunction104;
              CHECK(81, SyntaxTreeMockFunction_parse_new(NULL, &((*end)), &(_SyntaxTreeMockFunction104)) )
              CHECK(81, List_add(self->_base.functions, &(_SyntaxTreeMockFunction104->_base)) )
              
            }
            else {
              CHECK(85, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){16, 15, "unknown keyword"}, keyword) )
            }
          }
        }
      }
    }
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_link_types(SyntaxTreeRoot* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_link_types = "SyntaxTreeRoot.link-types";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_link_types
Returncode SyntaxTreeRoot_link_types(SyntaxTreeRoot* self) {
  RAISE(88)
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_analyze(SyntaxTreeRoot* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_analyze = "SyntaxTreeRoot.analyze";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_analyze
Returncode SyntaxTreeRoot_analyze(SyntaxTreeRoot* self) {
  CHECK(91, SyntaxTreeRoot_m_order_types(self) )
  CHECK(92, SyntaxTreeNamespace_link_types(&(self->_base)) )
  CHECK(93, SyntaxTreeNode_link_children_types(&(self->_base._base._base), self->types) )
  CHECK(94, (self->global_init)->_base._base._base._base._dtl[1](self->global_init) )
  if (NULL != self->main_function) {
    CHECK(96, (self->main_function)->_base._base._base._base._dtl[1](self->main_function) )
  }
  CHECK(97, SyntaxTreeNamespace_analyze(&(self->_base)) )
  CHECK(98, SyntaxTreeNode_analyze_children(&(self->_base._base._base), self->types) )
  CHECK(99, (self->global_init)->_base._base._base._base._dtl[2](self->global_init) )
  if (NULL != self->main_function) {
    CHECK(101, (self->main_function)->_base._base._base._base._dtl[2](self->main_function) )
  }
  else {
    if (!(NULL != glob->test_functions->first) &&  ! self->is_library) {
      CHECK(103, print(&(String){46, 45, "General code error: no main or test functions"}) )
      RAISE(104)
    }
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_m_order_types(SyntaxTreeRoot* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_m_order_types = "SyntaxTreeRoot.m-order-types";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_m_order_types
Returncode SyntaxTreeRoot_m_order_types(SyntaxTreeRoot* self) {
  List* ordered_list = malloc(sizeof(List));
  if (ordered_list == NULL) RAISE(107)
  *ordered_list = (List){NULL, NULL};
  while (true) {
    TypeData* type_data = NULL;
    CHECK(110, List_pop(self->types, (void**)&(type_data)) )
    if (!(NULL != type_data)) break;
    CHECK(112, TypeData_m_order_bases(type_data, ordered_list) )
  }
  free(self->types);
  self->types = ordered_list;
  return OK;
}
#undef MR_FUNC_NAME
#endif/*  write C file in this order:
  1. type declarations
  2. type structs (ordered by depth)
  3. function declarations
  4. global variables
  5. function bodies
  6. main function
   */
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_write(SyntaxTreeRoot* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_write = "SyntaxTreeRoot.write";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_write
Returncode SyntaxTreeRoot_write(SyntaxTreeRoot* self) {
  CHECK(125, file_open(self->output_file_name, false, &(glob->output_file)) )
  
  CHECK(127, write_global(&(String){19, 18, "#include \"mr.4.h\"\n"}) )
  
  CHECK(129, write_global(&(String){27, 26, "\n\n/* types declaration */\n"}) )
  TypeDeclarationWriter* type_declaration_writer = &(TypeDeclarationWriter){TypeDeclarationWriter__dtl};
  type_declaration_writer->_base._dtl = TypeDeclarationWriter__dtl;
  CHECK(131, SyntaxTreeRoot_write_for_type(self, &(type_declaration_writer->_base)) )
  
  /* will write type structures */
  CHECK(134, write_global(&(String){22, 21, "\n\n/* types struct */\n"}) )
  CHECK(135, SyntaxTreeNode_write_children(&(self->_base._base._base), self->types) )
  
  CHECK(137, write_global(&(String){35, 34, "\n\n/* types methods declaration */\n"}) )
  TypeMethodsDeclarationWriter* type_methods_declaration_writer = &(TypeMethodsDeclarationWriter){TypeMethodsDeclarationWriter__dtl};
  type_methods_declaration_writer->_base._dtl = TypeMethodsDeclarationWriter__dtl;
  CHECK(139, SyntaxTreeRoot_write_for_type(self, &(type_methods_declaration_writer->_base)) )
  
  CHECK(141, write_global(&(String){32, 31, "\n\n/* types global variables */\n"}) )
  TypeGlobalWriter* type_global_writer = &(TypeGlobalWriter){TypeGlobalWriter__dtl};
  type_global_writer->_base._dtl = TypeGlobalWriter__dtl;
  CHECK(143, SyntaxTreeRoot_write_for_type(self, &(type_global_writer->_base)) )
  
  /* will write global variables */
  CHECK(146, write_global(&(String){26, 25, "\n\n/* global variables */\n"}) )
  CHECK(147, SyntaxTreeNode_write_children(&(self->_base._base._base), self->_base._base.variables) )
  
  CHECK(149, write_global(&(String){38, 37, "\n\n/* global functions declaration */\n"}) )
  CHECK(150, SyntaxTreeNamespace_write_functions_declaration(&(self->_base)) )
  
  CHECK(152, write_global(&(String){28, 27, "\n\n/* types methods body */\n"}) )
  TypeMethodsBodyWriter* type_methods_body_writer = &(TypeMethodsBodyWriter){TypeMethodsBodyWriter__dtl};
  type_methods_body_writer->_base._dtl = TypeMethodsBodyWriter__dtl;
  CHECK(154, SyntaxTreeRoot_write_for_type(self, &(type_methods_body_writer->_base)) )
  
  /* will write global functions bodies */
  CHECK(157, write_global(&(String){31, 30, "\n\n/* global functions body */\n"}) )
  CHECK(158, SyntaxTreeNode_write_children(&(self->_base._base._base), self->_base.functions) )
  
  /* write main function */
  if (!glob->is_delete_mocked && (NULL != glob->test_functions->first ||  NULL !=  self->main_function)) {
    CHECK(163, write(&(String){32, 31, "\n\nvoid Mock_delete(Ref self) {}"}) )
  }
  if (NULL != glob->test_functions->first) {
    CHECK(165, SyntaxTreeRoot_write_test_main(self) )
  }
  else {
    if (NULL != self->main_function) {
      CHECK(167, write_global(&(String){23, 22, "\n\n/* main function */\n"}) )
      CHECK(168, (self->main_function)->_base._base._base._base._dtl[3](self->main_function) )
    }
  }
  
  CHECK(170, file_close(glob->output_file) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_write_for_type(SyntaxTreeRoot* self, TypeWriter* type_writer);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_write_for_type = "SyntaxTreeRoot.write-for-type";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_write_for_type
Returncode SyntaxTreeRoot_write_for_type(SyntaxTreeRoot* self, TypeWriter* type_writer) {
  ListNode* child = self->types->first;
  while (true) {
    if (!(NULL != child)) break;
    CHECK(176, (((TypeData*)(child->item)))->_base._base._base._dtl[10](((TypeData*)(child->item)), type_writer) )
    child = child->next;
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_write_test_main(SyntaxTreeRoot* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_write_test_main = "SyntaxTreeRoot.write-test-main";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_write_test_main
Returncode SyntaxTreeRoot_write_test_main(SyntaxTreeRoot* self) {
  CHECK(180, write(&(String){21, 20, "\nUSER_MAIN_HEADER {\n"}) )
  CHECK(181, write(&(String){27, 26, "  Bool MR_success = true;\n"}) )
  CHECK(182, (self->global_init)->_base._base._base._base._dtl[3](self->global_init) )
  CHECK(183, write(&(String){2, 1, "\n"}) )
  NameMapNode* node = glob->test_functions->first;
  while (true) {
    CHECK(186, write(&(String){12, 11, "  RUN_TEST("}) )
    CHECK(187, SyntaxTreeFunction_write_cname(&(((SyntaxTreeTestFunction*)(node->value))->_base)) )
    CHECK(188, write(&(String){4, 3, ");\n"}) )
    node = node->next;
    if (!(NULL != node)) break;
  }
  CHECK(191, write(&(String){33, 32, "  return MR_success? OK : FAIL;\n"}) )
  CHECK(192, write(&(String){3, 2, "}\n"}) )
  CHECK(193, write(&(String){17, 16, "\nTEST_MAIN_FUNC\n"}) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func SyntaxTreeRoot__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func SyntaxTreeRoot__dtl[] = {(void*)SyntaxTreeNode_get_parent_type, (void*)SyntaxTreeRoot_link_types, (void*)SyntaxTreeRoot_analyze, (void*)SyntaxTreeRoot_write, (void*)SyntaxTreeRoot_parse_child, (void*)SyntaxTreeBranch_find_variable};
#endif


/* Main function node in the syntax tree */
#if MR_STAGE == MR_TYPEDEFS
typedef struct SyntaxTreeMainFunction SyntaxTreeMainFunction;
#elif MR_STAGE == MR_TYPES(4)
struct SyntaxTreeMainFunction {
  SyntaxTreeFunction _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeMainFunction_parse_new(SyntaxTreeMainFunction* self, Char* end, SyntaxTreeMainFunction** new_node);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeMainFunction_parse_new = "SyntaxTreeMainFunction.parse-new";
#define MR_FUNC_NAME _func_name_SyntaxTreeMainFunction_parse_new
Returncode SyntaxTreeMainFunction_parse_new(SyntaxTreeMainFunction* self, Char* end, SyntaxTreeMainFunction** new_node) {
  (*new_node) = malloc(sizeof(SyntaxTreeMainFunction));
  if ((*new_node) == NULL) RAISE(199)
  *(*new_node) = (SyntaxTreeMainFunction){SyntaxTreeMainFunction__dtl, NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, false, NULL, NULL, NULL, NULL, NULL, NULL, 0, false};
  (*new_node)->_base._base._base._base._dtl = SyntaxTreeMainFunction__dtl;
  CHECK(200, SyntaxTreeMainFunction_parse((*new_node), &((*end))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeMainFunction_parse(SyntaxTreeMainFunction* self, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeMainFunction_parse = "SyntaxTreeMainFunction.parse";
#define MR_FUNC_NAME _func_name_SyntaxTreeMainFunction_parse
Returncode SyntaxTreeMainFunction_parse(SyntaxTreeMainFunction* self, Char* end) {
  CHECK(203, SyntaxTreeFunction_init(&(self->_base)) )
  CHECK(204, string_new_copy(&(String){5, 4, "main"}, &(self->_base.name)) )
  self->_base.arguments = malloc(sizeof(FunctionArguments));
  if (self->_base.arguments == NULL) RAISE(205)
  *self->_base.arguments = (FunctionArguments){FunctionArguments__dtl, NULL, 0, NULL, NULL};
  self->_base.arguments->_base._dtl = FunctionArguments__dtl;
  CHECK(206, FunctionArguments_init(self->_base.arguments) )
  CHECK(207, SyntaxTreeFunction_parse_body(&(self->_base), &((*end))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeMainFunction_write(SyntaxTreeMainFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeMainFunction_write = "SyntaxTreeMainFunction.write";
#define MR_FUNC_NAME _func_name_SyntaxTreeMainFunction_write
Returncode SyntaxTreeMainFunction_write(SyntaxTreeMainFunction* self) {
  /* USER_MAIN_HEADER { */
  /*   `block...` */
  /* } */
  /* MAIN_FUNC */
  CHECK(214, write(&(String){18, 17, "\nUSER_MAIN_HEADER"}) )
  CHECK(215, SyntaxTreeFunction_write_block(&(self->_base)) )
  CHECK(216, write_post_func() )
  CHECK(217, write(&(String){12, 11, "\nMAIN_FUNC\n"}) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeMainFunction_write_block_body(SyntaxTreeMainFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeMainFunction_write_block_body = "SyntaxTreeMainFunction.write-block-body";
#define MR_FUNC_NAME _func_name_SyntaxTreeMainFunction_write_block_body
Returncode SyntaxTreeMainFunction_write_block_body(SyntaxTreeMainFunction* self) {
  CHECK(220, (glob->root->global_init)->_base._base._base._base._dtl[3](glob->root->global_init) )
  CHECK(221, write_pre_func(&(self->_base)) )
  CHECK(222, write(&(String){2, 1, "\n"}) )
  CHECK(223, SyntaxTreeBlock_write_block_body(&(self->_base._base)) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func SyntaxTreeMainFunction__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func SyntaxTreeMainFunction__dtl[] = {(void*)SyntaxTreeFunction_get_parent_type, (void*)SyntaxTreeFunction_link_types, (void*)SyntaxTreeFunction_analyze, (void*)SyntaxTreeMainFunction_write, (void*)SyntaxTreeBlock_parse_child, (void*)SyntaxTreeFunction_find_variable, (void*)SyntaxTreeFunction_get_function, (void*)SyntaxTreeMainFunction_write_block_body, (void*)SyntaxTreeFunction_check_name, (void*)SyntaxTreeFunction_write_declaration};
#endif


#if MR_STAGE == MR_TYPEDEFS
typedef struct GlobalInit GlobalInit;
#elif MR_STAGE == MR_TYPES(4)
struct GlobalInit {
  SyntaxTreeFunction _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode GlobalInit_init(GlobalInit* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_GlobalInit_init = "GlobalInit.init";
#define MR_FUNC_NAME _func_name_GlobalInit_init
Returncode GlobalInit_init(GlobalInit* self) {
  CHECK(228, SyntaxTreeFunction_init(&(self->_base)) )
  self->_base._base.code_nodes = malloc(sizeof(List));
  if (self->_base._base.code_nodes == NULL) RAISE(229)
  *self->_base._base.code_nodes = (List){NULL, NULL};
  self->_base._base._base.variables = malloc(sizeof(List));
  if (self->_base._base._base.variables == NULL) RAISE(230)
  *self->_base._base._base.variables = (List){NULL, NULL};
  self->_base.arguments = malloc(sizeof(FunctionArguments));
  if (self->_base.arguments == NULL) RAISE(231)
  *self->_base.arguments = (FunctionArguments){FunctionArguments__dtl, NULL, 0, NULL, NULL};
  self->_base.arguments->_base._dtl = FunctionArguments__dtl;
  CHECK(232, FunctionArguments_init(self->_base.arguments) )
  self->_base._base._base.indentation_spaces = 2;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode GlobalInit_write(GlobalInit* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_GlobalInit_write = "GlobalInit.write";
#define MR_FUNC_NAME _func_name_GlobalInit_write
Returncode GlobalInit_write(GlobalInit* self) {
  if (!(NULL != self->_base._base.code_nodes->first)) {
    return OK;
  }
  CHECK(238, SyntaxTreeNode_write_children(&(self->_base._base._base._base), self->_base._base._base.variables) )
  CHECK(239, write(&(String){21, 20, "#undef RETURN_ERROR\n"}) )
  CHECK(240, write(&(String){43, 42, "#define RETURN_ERROR(value) return value;\n"}) )
  CHECK(241, write(&(String){55, 54, "#define MR_FUNC_NAME \"global variable initialization\"\n"}) )
  CHECK(242, (self)->_base._base._base._base._dtl[7](self) )
  CHECK(243, write(&(String){21, 20, "#undef MR_FUNC_NAME\n"}) )
  CHECK(244, write(&(String){21, 20, "#undef RETURN_ERROR\n"}) )
  CHECK(245, write(&(String){60, 59, "#define RETURN_ERROR(value) MR_err = value; goto MR_cleanup"}) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func GlobalInit__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func GlobalInit__dtl[] = {(void*)SyntaxTreeFunction_get_parent_type, (void*)SyntaxTreeFunction_link_types, (void*)SyntaxTreeFunction_analyze, (void*)GlobalInit_write, (void*)SyntaxTreeBlock_parse_child, (void*)SyntaxTreeFunction_find_variable, (void*)SyntaxTreeFunction_get_function, (void*)SyntaxTreeBlock_write_block_body, (void*)SyntaxTreeFunction_check_name, (void*)SyntaxTreeFunction_write_declaration};
#endif


/* proxy write function to be mocked on unit-tests */
#if MR_STAGE == MR_DECLARATIONS
Returncode write_global(String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_write_global = "write-global";
#define MR_FUNC_NAME _func_name_write_global
Returncode write_global(String* text) {
  CHECK(250, write(text) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

#undef MR_FILE_NAME

#ifndef MR_INCLUDES
#define MR_INCLUDES
#include "global/argument.c"
#include "global/common.c"
#include "global/file-io.c"
#include "global/global.c"
#include "global/list.c"
#include "global/map.c"
#include "global/type-instance.c"
#include "expression/base-type.c"
#include "expression/call.c"
#include "expression/constant.c"
#include "expression/container.c"
#include "expression/expression.c"
#include "expression/initialize.c"
#include "expression/slice.c"
#include "expression/symbol.c"
#include "syntax-tree/block.c"
#include "syntax-tree/branch.c"
#include "syntax-tree/code.c"
#include "syntax-tree/code-flow.c"
#include "syntax-tree/node.c"
#include "statement/error.c"
#include "statement/for.c"
#include "statement/function.c"
#include "statement/native.c"
#include "statement/test.c"
#include "statement/type.c"
#include "statement/variable.c"
#include "mr4-compiler.c"
#if MR_STAGE == MR_TYPES(1)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(2)
#elif MR_STAGE == MR_TYPES(2)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(3)
#elif MR_STAGE == MR_TYPES(3)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(4)
#elif MR_STAGE == MR_TYPES(4)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(5)
#endif
#undef MR_INCLUDES
#endif

#endif