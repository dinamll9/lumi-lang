static char* _mr_file7_name = "func.2.mr";
#define MR_FILE_NAME _mr_file7_name
/* MR3 compiler - function */

static char* _func_name_f_get_access = "f-get-access";
#define MR_FUNC_NAME _func_name_f_get_access
Returncode f_get_access(String* access_text, Int* access) {
  Bool _Bool0;
  CHECK(4, String_equal(access_text, &(String){5, 4, "copy"}, &(_Bool0)))
  if (_Bool0) {
    (*access) = ACCESS_COPY;
  }
  else {
    Bool _Bool1;
    CHECK(6, String_equal(access_text, &(String){5, 4, "user"}, &(_Bool1)))
    if (_Bool1) {
      (*access) = ACCESS_USER;
    }
    else {
      Bool _Bool2;
      CHECK(8, String_equal(access_text, &(String){6, 5, "owner"}, &(_Bool2)))
      if (_Bool2) {
        (*access) = ACCESS_OWNER;
      }
      else {
        Bool _Bool3;
        CHECK(10, String_equal(access_text, &(String){4, 3, "var"}, &(_Bool3)))
        if (_Bool3) {
          (*access) = ACCESS_VAR;
        }
        else {
          CHECK(13, f_syntax_error(&(String){15, 14, "unknown access"}, access_text));
        }
      }
    }
  }
  return OK;
}
#undef MR_FUNC_NAME


typedef struct Dec_arg Dec_arg;

typedef struct Arg_node Arg_node; struct Arg_node {
  Func* _dtl;
  Arg_node* next;
};
static char* _func_name_Arg_node_parse = "Arg-node.parse";
#define MR_FUNC_NAME _func_name_Arg_node_parse
Returncode Arg_node_parse(Arg_node* self, Bool is_out, Int access, Char* end) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_node_analyze = "Arg-node.analyze";
#define MR_FUNC_NAME _func_name_Arg_node_analyze
Returncode Arg_node_analyze(Arg_node* self, Arg_node* arg, Mtype* prev_mtype, Mtype* prev_sub_mtype) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_node_write_intro = "Arg-node.write-intro";
#define MR_FUNC_NAME _func_name_Arg_node_write_intro
Returncode Arg_node_write_intro(Arg_node* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_node_write_final = "Arg-node.write-final";
#define MR_FUNC_NAME _func_name_Arg_node_write_final
Returncode Arg_node_write_final(Arg_node* self, Bool is_out) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_node_get_dec = "Arg-node.get-dec";
#define MR_FUNC_NAME _func_name_Arg_node_get_dec
Returncode Arg_node_get_dec(Arg_node* self, Dec_arg** arg) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_node_get_call_value = "Arg-node.get-call-value";
#define MR_FUNC_NAME _func_name_Arg_node_get_call_value
Returncode Arg_node_get_call_value(Arg_node* self, Mexp** exp) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
Func Arg_node__dtl[] = {Arg_node_parse, Arg_node_analyze, Arg_node_write_intro, Arg_node_write_final, Arg_node_get_dec, Arg_node_get_call_value};

typedef struct Dec_arg Dec_arg; struct Dec_arg {
  Arg_node _base;
  Mvar* mvar;
};
static char* _func_name_Dec_arg_init = "Dec-arg.init";
#define MR_FUNC_NAME _func_name_Dec_arg_init
Returncode Dec_arg_init(Dec_arg* self, Int access, Mtype* mtype, String* name) {
  CHECK(38, init_new_var(mtype, &(self->mvar)));
  self->mvar->access = access;
  CHECK(40, f_new_copy(name, &(self->mvar->name)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Dec_arg_parse = "Dec-arg.parse";
#define MR_FUNC_NAME _func_name_Dec_arg_parse
Returncode Dec_arg_parse(Dec_arg* self, Bool is_out, Int access, Char* end) {
  CHECK(43, init_new_var(NULL, &(self->mvar)));
  self->mvar->is_ref = is_out;
  self->mvar->access = access;
  CHECK(46, read_new(&(String){3, 2, " {"}, &(self->mvar->typename), &((*end))))
  if ((*end) == '{') {
    CHECK(47, read_new(&(String){2, 1, "}"}, &(self->mvar->sub_typename), &((*end))));
    CHECK(48, read_c(&((*end))));
  }
  CHECK(49, read_new(&(String){3, 2, ",)"}, &(self->mvar->name), &((*end))));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Dec_arg_analyze = "Dec-arg.analyze";
#define MR_FUNC_NAME _func_name_Dec_arg_analyze
Returncode Dec_arg_analyze(Dec_arg* self, Arg_node* arg, Mtype* prev_mtype, Mtype* prev_sub_mtype) {
  CHECK(52, Mvar_analyze(self->mvar));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Dec_arg_write_intro = "Dec-arg.write-intro";
#define MR_FUNC_NAME _func_name_Dec_arg_write_intro
Returncode Dec_arg_write_intro(Dec_arg* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Dec_arg_write_final = "Dec-arg.write-final";
#define MR_FUNC_NAME _func_name_Dec_arg_write_final
Returncode Dec_arg_write_final(Dec_arg* self, Bool is_out) {
  CHECK(58, write_cstyle(self->mvar->mtype->name));
  if (is_out) {
    CHECK(60, write(&(String){2, 1, "*"}));
  }
  if (self->mvar->access == ACCESS_USER || self->mvar->access == ACCESS_OWNER) {
    CHECK(62, write(&(String){2, 1, "*"}));
  }
  else {
    if (self->mvar->access == ACCESS_VAR && !self->mvar->mtype->is_primitive) {
      CHECK(64, write(&(String){2, 1, "*"}));
    }
  }
  CHECK(65, write(&(String){2, 1, " "}));
  CHECK(66, write_cstyle(self->mvar->name));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Dec_arg_get_dec = "Dec-arg.get-dec";
#define MR_FUNC_NAME _func_name_Dec_arg_get_dec
Returncode Dec_arg_get_dec(Dec_arg* self, Dec_arg** arg) {
  (*arg) = self;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Dec_arg_get_call_value = "Dec-arg.get-call-value";
#define MR_FUNC_NAME _func_name_Dec_arg_get_call_value
Returncode Dec_arg_get_call_value(Dec_arg* self, Mexp** exp) {
  RAISE(72)
}
#undef MR_FUNC_NAME
Func Dec_arg__dtl[] = {Dec_arg_parse, Dec_arg_analyze, Dec_arg_write_intro, Dec_arg_write_final, Dec_arg_get_dec, Dec_arg_get_call_value};

typedef struct Call_arg Call_arg; struct Call_arg {
  Arg_node _base;
  Int access;
  Mtype* generic_mtype;
  Mexp* value;
};
static char* _func_name_Call_arg_parse = "Call-arg.parse";
#define MR_FUNC_NAME _func_name_Call_arg_parse
Returncode Call_arg_parse(Call_arg* self, Bool is_out, Int access, Char* end) {
  self->access = access;
  self->generic_mtype = NULL;
  CHECK(82, parse_new_exp(&(String){3, 2, ",)"}, &(self->value), &((*end))));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_arg_analyze = "Call-arg.analyze";
#define MR_FUNC_NAME _func_name_Call_arg_analyze
Returncode Call_arg_analyze(Call_arg* self, Arg_node* arg, Mtype* prev_mtype, Mtype* prev_sub_mtype) {
  Dec_arg* dec_arg;
  CHECK(86, (*((Func**)(arg)))[4](arg, &(dec_arg)));
  if (self->access != dec_arg->mvar->access) {
    CHECK(88, f_syntax_error(&(String){25, 24, "invalid access for param"}, dec_arg->mvar->name));
  }
  Mtype* mtype = dec_arg->mvar->mtype;
  Mtype* sub_mtype = dec_arg->mvar->sub_mtype;
  if (mtype == prev_mtype->generic_mtype) {
    mtype = prev_sub_mtype;
    sub_mtype = NULL;
    self->generic_mtype = prev_mtype->generic_mtype;
  }
  else {
    if (sub_mtype == prev_mtype->generic_mtype) {
      sub_mtype = prev_sub_mtype;
    }
  }
  CHECK(97, Mexp_analyze(self->value, &(mtype), &(sub_mtype)));
  if (!self->value->is_used) {
    self->generic_mtype = mtype;
    self->value->is_used = true;
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_arg_write_intro = "Call-arg.write-intro";
#define MR_FUNC_NAME _func_name_Call_arg_write_intro
Returncode Call_arg_write_intro(Call_arg* self) {
  CHECK(103, Mexp_write_intro(self->value));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_arg_write_final = "Call-arg.write-final";
#define MR_FUNC_NAME _func_name_Call_arg_write_final
Returncode Call_arg_write_final(Call_arg* self, Bool is_out) {
  if (is_out) {
    if (NULL != self->generic_mtype) {
      CHECK(108, write(&(String){2, 1, "("}));
      CHECK(109, write_cstyle(self->generic_mtype->name));
      CHECK(110, write(&(String){4, 3, "**)"}));
    }
    CHECK(111, write(&(String){3, 2, "&("}));
  }
  CHECK(112, Mexp_write_final(self->value));
  if (is_out) {
    CHECK(114, write(&(String){2, 1, ")"}));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_arg_get_dec = "Call-arg.get-dec";
#define MR_FUNC_NAME _func_name_Call_arg_get_dec
Returncode Call_arg_get_dec(Call_arg* self, Dec_arg** arg) {
  RAISE(117)
}
#undef MR_FUNC_NAME
static char* _func_name_Call_arg_get_call_value = "Call-arg.get-call-value";
#define MR_FUNC_NAME _func_name_Call_arg_get_call_value
Returncode Call_arg_get_call_value(Call_arg* self, Mexp** exp) {
  (*exp) = self->value;
  return OK;
}
#undef MR_FUNC_NAME
Func Call_arg__dtl[] = {Call_arg_parse, Call_arg_analyze, Call_arg_write_intro, Call_arg_write_final, Call_arg_get_dec, Call_arg_get_call_value};

typedef struct Arg_list Arg_list; struct Arg_list {
  Arg_node* first_param;
  Arg_node* first_out;
  Bool is_dec;
};
static char* _func_name_Arg_list_init = "Arg-list.init";
#define MR_FUNC_NAME _func_name_Arg_list_init
Returncode Arg_list_init(Arg_list* self, Bool is_dec) {
  self->first_param = NULL;
  self->first_out = NULL;
  self->is_dec = is_dec;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_parse_args = "Arg-list.parse-args";
#define MR_FUNC_NAME _func_name_Arg_list_parse_args
Returncode Arg_list_parse_args(Arg_list* self, Bool is_out) {
  Arg_node* prev = NULL;
  Char end;
  while (true) {
    String* access_text = &(String){128, 0, (char[128]){0}};
    CHECK(137, read(&(String){3, 2, " )"}, access_text, &(end)));
    if (!(end == ' ')) break;
    Int access;
    CHECK(140, f_get_access(access_text, &(access)));
    Type arg_type;
    if (self->is_dec) {
      arg_type = (Type){sizeof(Dec_arg), Dec_arg__dtl};
    }
    else {
      arg_type = (Type){sizeof(Call_arg), Call_arg__dtl};
    }
    if (arg_type.size <= 0) RAISE(146)
    Arg_node* arg = malloc(arg_type.size);
    if (arg == NULL) RAISE(146)
    if (arg_type.dtl != NULL) { *((Func**)(arg)) = arg_type.dtl; }
    CHECK(147, (*((Func**)(arg)))[0](arg, is_out, access, &(end)));
    arg->next = NULL;
    if (NULL != prev) {
      prev->next = arg;
    }
    else {
      if (is_out) {
        self->first_out = arg;
      }
      else {
        self->first_param = arg;
      }
    }
    prev = arg;
    if (!(end == ',')) break;
    CHECK(157, read_c(&(end)));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_parse = "Arg-list.parse";
#define MR_FUNC_NAME _func_name_Arg_list_parse
Returncode Arg_list_parse(Arg_list* self, Bool is_dec, Char* end) {
  self->is_dec = is_dec;
  CHECK(161, Arg_list_parse_args(self, false));
  CHECK(162, read_c(&((*end))))
  if ((*end) == ':') {
    Char _Char4;
    CHECK(163, read_c(&(_Char4)))
    if (_Char4 != '(') {
      CHECK(164, f_syntax_error_c(&(String){17, 16, "expeted '(', got"}, (*end)));
    }
    CHECK(165, Arg_list_parse_args(self, true));
    CHECK(166, read_c(&((*end))));
  }
  else {
    self->first_out = NULL;
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_analyze_args = "Arg-list.analyze-args";
#define MR_FUNC_NAME _func_name_Arg_list_analyze_args
Returncode Arg_list_analyze_args(Arg_list* self, Arg_node* first) {
  Arg_node* node = first;
  while (true) {
    if (!(NULL != node)) break;
    CHECK(174, (*((Func**)(node)))[1](node, NULL, NULL, NULL));
    node = node->next;
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_analyze = "Arg-list.analyze";
#define MR_FUNC_NAME _func_name_Arg_list_analyze
Returncode Arg_list_analyze(Arg_list* self) {
  CHECK(178, Arg_list_analyze_args(self, self->first_param));
  CHECK(179, Arg_list_analyze_args(self, self->first_out));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_write_args_intro = "Arg-list.write-args-intro";
#define MR_FUNC_NAME _func_name_Arg_list_write_args_intro
Returncode Arg_list_write_args_intro(Arg_list* self, Arg_node* first) {
  Arg_node* node = first;
  while (true) {
    if (!(NULL != node)) break;
    CHECK(185, (*((Func**)(node)))[2](node));
    node = node->next;
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_write_args_final = "Arg-list.write-args-final";
#define MR_FUNC_NAME _func_name_Arg_list_write_args_final
Returncode Arg_list_write_args_final(Arg_list* self, Bool is_out, Arg_node* first) {
  Arg_node* node = first;
  Bool has_more = !is_out && NULL != self->first_out;
  while (true) {
    if (!(NULL != node)) break;
    CHECK(193, (*((Func**)(node)))[3](node, is_out));
    node = node->next;
    if (has_more || NULL != node) {
      CHECK(196, write(&(String){3, 2, ", "}));
    }
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_write_intro = "Arg-list.write-intro";
#define MR_FUNC_NAME _func_name_Arg_list_write_intro
Returncode Arg_list_write_intro(Arg_list* self) {
  CHECK(199, Arg_list_write_args_intro(self, self->first_param));
  CHECK(200, Arg_list_write_args_intro(self, self->first_out));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_write_final = "Arg-list.write-final";
#define MR_FUNC_NAME _func_name_Arg_list_write_final
Returncode Arg_list_write_final(Arg_list* self) {
  CHECK(203, write(&(String){2, 1, "("}));
  CHECK(204, Arg_list_write_args_final(self, false, self->first_param));
  CHECK(205, Arg_list_write_args_final(self, true, self->first_out));
  CHECK(206, write(&(String){2, 1, ")"}));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_add_arg = "Arg-list.add-arg";
#define MR_FUNC_NAME _func_name_Arg_list_add_arg
Returncode Arg_list_add_arg(Arg_list* self, Int access, Mtype* mtype, String* name, Arg_node** first) {
  Dec_arg* arg = malloc(sizeof(Dec_arg));
  if (arg == NULL) RAISE(209)
  *((Func**)(arg)) = Dec_arg__dtl;
  CHECK(210, Dec_arg_init(arg, access, mtype, name));
  arg->_base.next = (*first);
  (*first) = &(arg->_base);
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_add_param = "Arg-list.add-param";
#define MR_FUNC_NAME _func_name_Arg_list_add_param
Returncode Arg_list_add_param(Arg_list* self, Int access, Mtype* mtype, String* name) {
  CHECK(215, Arg_list_add_arg(self, access, mtype, name, &(self->first_param)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_add_out = "Arg-list.add-out";
#define MR_FUNC_NAME _func_name_Arg_list_add_out
Returncode Arg_list_add_out(Arg_list* self, Int access, Mtype* mtype, String* name) {
  CHECK(218, Arg_list_add_arg(self, access, mtype, name, &(self->first_out)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Arg_list_add_self_call = "Arg-list.add-self-call";
#define MR_FUNC_NAME _func_name_Arg_list_add_self_call
Returncode Arg_list_add_self_call(Arg_list* self, Mexp* value) {
  Call_arg* arg = malloc(sizeof(Call_arg));
  if (arg == NULL) RAISE(221)
  *((Func**)(arg)) = Call_arg__dtl;
  arg->access = ACCESS_VAR;
  arg->value = value;
  arg->_base.next = self->first_param;
  self->first_param = &(arg->_base);
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_parse_new_args = "parse-new-args";
#define MR_FUNC_NAME _func_name_parse_new_args
Returncode parse_new_args(Arg_list** new_args) {
  Arg_list* args = malloc(sizeof(Arg_list));
  if (args == NULL) RAISE(228)
  CHECK(229, Arg_list_init(args, true));
  Char _Char5;
  CHECK(230, Arg_list_parse(args, true, &(_Char5)));
  (*new_args) = args;
  return OK;
}
#undef MR_FUNC_NAME


typedef struct Mfunc Mfunc; struct Mfunc {
  String* name;
  Arg_list* args;
  Mtype* mclass;
  Bool is_dynamic;
  Int dynamic_index;
};
static char* _func_name_Mfunc_init = "Mfunc.init";
#define MR_FUNC_NAME _func_name_Mfunc_init
Returncode Mfunc_init(Mfunc* self, String* name) {
  CHECK(242, f_new_copy(name, &(self->name)));
  Arg_list* args = malloc(sizeof(Arg_list));
  if (args == NULL) RAISE(243)
  self->args = args;
  CHECK(245, Arg_list_init(self->args, true));
  self->mclass = NULL;
  self->is_dynamic = false;
  self->dynamic_index = 0;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mfunc_parse = "Mfunc.parse";
#define MR_FUNC_NAME _func_name_Mfunc_parse
Returncode Mfunc_parse(Mfunc* self) {
  self->mclass = glob->mclass;
  if (NULL != self->mclass) {
    String* meth_type = &(String){64, 0, (char[64]){0}};
    Char _Char6;
    CHECK(254, read(&(String){2, 1, " "}, meth_type, &(_Char6)));
    Bool _Bool7;
    CHECK(255, String_equal(meth_type, &(String){8, 7, "dynamic"}, &(_Bool7)))
    self->is_dynamic = _Bool7;
  }
  else {
    self->is_dynamic = false;
  }
  self->dynamic_index = 0;
  Char _Char8;
  CHECK(259, read_new(&(String){2, 1, "("}, &(self->name), &(_Char8)));
  CHECK(260, parse_new_args(&(self->args)));
  if (NULL != self->mclass) {
    CHECK(262, Arg_list_add_param(self->args, ACCESS_VAR, self->mclass, &(String){5, 4, "self"}));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mfunc_analyze = "Mfunc.analyze";
#define MR_FUNC_NAME _func_name_Mfunc_analyze
Returncode Mfunc_analyze(Mfunc* self) {
  CHECK(265, Arg_list_analyze(self->args));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mfunc_write_name = "Mfunc.write-name";
#define MR_FUNC_NAME _func_name_Mfunc_write_name
Returncode Mfunc_write_name(Mfunc* self) {
  if (self->mclass) {
    CHECK(269, write_cstyle(self->mclass->name));
    CHECK(270, write(&(String){2, 1, "_"}));
  }
  CHECK(271, write_cstyle(self->name));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mfunc_write = "Mfunc.write";
#define MR_FUNC_NAME _func_name_Mfunc_write
Returncode Mfunc_write(Mfunc* self) {
  CHECK(274, write(&(String){12, 11, "Returncode "}));
  CHECK(275, Mfunc_write_name(self));
  CHECK(276, Arg_list_write_final(self->args));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mfunc_m_new_var = "Mfunc.m-new-var";
#define MR_FUNC_NAME _func_name_Mfunc_m_new_var
Returncode Mfunc_m_new_var(Mfunc* self, Mvar** mvar) {
  CHECK(279, init_new_var(glob->type_func, &((*mvar))));
  CHECK(280, f_new_copy(self->name, &((*mvar)->name)));
  (*mvar)->func_dec = self;
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_parse_new_mfunc = "parse-new-mfunc";
#define MR_FUNC_NAME _func_name_parse_new_mfunc
Returncode parse_new_mfunc(Mfunc** new_mfunc) {
  Mfunc* mfunc = malloc(sizeof(Mfunc));
  if (mfunc == NULL) RAISE(284)
  CHECK(285, Mfunc_parse(mfunc));
  (*new_mfunc) = mfunc;
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_f_is_func_dynamic = "f-is-func-dynamic";
#define MR_FUNC_NAME _func_name_f_is_func_dynamic
Returncode f_is_func_dynamic(Mfunc* mfunc, Bool* is_dynamic) {
  (*is_dynamic) = mfunc->is_dynamic;
  return OK;
}
#undef MR_FUNC_NAME


typedef struct Call_operand Call_operand; struct Call_operand {
  Operand _base;
  Arg_list* args;
  Operand* func_opr;
  Operand* dynamic_opr;
  Int dynamic_index;
  Int dynamic_base_count;
  Bool is_used;
  Mtype* res_mtype;
  Mexp* res_exp;
  String* res_name;
};
static char* _func_name_Call_operand_parse = "Call-operand.parse";
#define MR_FUNC_NAME _func_name_Call_operand_parse
Returncode Call_operand_parse(Call_operand* self, String* text, String* ends, Char* end) {
  Arg_list* args = malloc(sizeof(Arg_list));
  if (args == NULL) RAISE(304)
  self->args = args;
  CHECK(306, Arg_list_init(self->args, false));
  CHECK(307, Arg_list_parse(args, false, &((*end))));
  self->func_opr = NULL;
  self->dynamic_opr = NULL;
  self->dynamic_index = 0;
  self->dynamic_base_count = 0;
  self->res_mtype = NULL;
  self->res_name = NULL;
  self->res_exp = NULL;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_operand_analyze_args = "Call-operand.analyze-args";
#define MR_FUNC_NAME _func_name_Call_operand_analyze_args
Returncode Call_operand_analyze_args(Call_operand* self, Mfunc* mfunc, Bool is_method, Mtype** mtype, Mtype** sub_mtype) {
  Arg_node* dec_param = mfunc->args->first_param;
  Arg_node* call_param = self->args->first_param;
  Bool not_self = !is_method;
  while (true) {
    if (!(NULL != dec_param)) break;
    if (!(NULL != call_param)) {
      CHECK(323, f_syntax_error(&(String){23, 22, "too few parameters for"}, mfunc->name));
    }
    if (not_self) {
      CHECK(325, (*((Func**)(call_param)))[1](call_param, dec_param, (*mtype), (*sub_mtype)));
    }
    else {
      not_self = true;
    }
    dec_param = dec_param->next;
    call_param = call_param->next;
  }
  if (NULL != call_param) {
    CHECK(331, f_syntax_error(&(String){24, 23, "too many parameters for"}, mfunc->name));
  }
  
  Arg_node* dec_out = mfunc->args->first_out;
  Arg_node* call_out = self->args->first_out;
  if (!(NULL != dec_out)) {
    if (self->is_used) {
      CHECK(337, f_syntax_error(&(String){20, 19, "no return value for"}, mfunc->name));
    }
    if (call_out) {
      CHECK(339, f_syntax_error(&(String){21, 20, "too many outputs for"}, mfunc->name));
    }
    (*mtype) = NULL;
    (*sub_mtype) = NULL;
    return OK;
  }
  
  if (NULL != call_out) {
    CHECK(345, (*((Func**)(call_out)))[1](call_out, dec_out, (*mtype), (*sub_mtype)));
    while (true) {
      if (!(NULL != call_out->next)) break;
      call_out = call_out->next;
      dec_out = dec_out->next;
      if (!(NULL != dec_out)) {
        CHECK(351, f_syntax_error(&(String){21, 20, "too many outputs for"}, mfunc->name));
      }
      CHECK(352, (*((Func**)(call_out)))[1](call_out, dec_out, (*mtype), (*sub_mtype)));
    }
  }
  
  Bool fill_out = NULL != dec_out->next || !(NULL != call_out);
  if (NULL != dec_out->next) {
    dec_out = dec_out->next;
    if (NULL != dec_out->next || !(NULL != call_out)) {
      CHECK(358, f_syntax_error(&(String){20, 19, "too few outputs for"}, mfunc->name));
    }
  }
  Dec_arg* dec_res;
  CHECK(360, (*((Func**)(dec_out)))[4](dec_out, &(dec_res)));
  Mtype* generic_mtype = NULL;
  if (dec_res->mvar->mtype == (*mtype)->generic_mtype) {
    generic_mtype = (*mtype)->generic_mtype;
    (*mtype) = (*sub_mtype);
    (*sub_mtype) = NULL;
  }
  else {
    if (dec_res->mvar->sub_mtype == (*mtype)->generic_mtype) {
      (*mtype) = dec_res->mvar->mtype;
      /* sub-mtype is the same */
    }
    else {
      (*mtype) = dec_res->mvar->mtype;
      (*sub_mtype) = dec_res->mvar->sub_mtype;
    }
  }
  self->res_mtype = (*mtype);
  if (fill_out) {
    String* res_count = &(String){64, 0, (char[64]){0}};
    CHECK(375, Int_str(glob->res_count, res_count));
    glob->res_count = glob->res_count + 1;
    String* res_name = new_string(self->res_mtype->name->length + res_count->length + 2);
    if (res_name == NULL) RAISE(377)
    self->res_name = res_name;
    CHECK(379, String_append(self->res_name, '-'));
    CHECK(380, String_concat(self->res_name, self->res_mtype->name));
    CHECK(381, String_concat(self->res_name, res_count));
    Var_operand* var_opr = malloc(sizeof(Var_operand));
    if (var_opr == NULL) RAISE(382)
    *((Func**)(var_opr)) = Var_operand__dtl;
    CHECK(383, f_new_copy(self->res_name, &(var_opr->name)));
    CHECK(384, init_new_var((*mtype), &(var_opr->mvar)));
    CHECK(385, f_new_copy(self->res_name, &(var_opr->mvar->name)));
    if (NULL != (*sub_mtype)) {
      CHECK(387, f_new_copy((*sub_mtype)->name, &(var_opr->mvar->sub_typename)));
    }
    var_opr->mvar->sub_mtype = (*sub_mtype);
    var_opr->mvar->func_dec = dec_res->mvar->func_dec;
    var_opr->mvar->access = dec_res->mvar->access;
    var_opr->_base.next = NULL;
    Mexp* exp = malloc(sizeof(Mexp));
    if (exp == NULL) RAISE(392)
    CHECK(393, Mexp_init(exp));
    exp->operand = &(var_opr->_base);
    Call_arg* arg = malloc(sizeof(Call_arg));
    if (arg == NULL) RAISE(395)
    *((Func**)(arg)) = Call_arg__dtl;
    arg->access = dec_res->mvar->access;
    arg->generic_mtype = generic_mtype;
    arg->value = exp;
    arg->_base.next = NULL;
    if (NULL != call_out) {
      call_out->next = &(arg->_base);
    }
    else {
      self->args->first_out = &(arg->_base);
    }
  }
  else {
    CHECK(405, (*((Func**)(call_out)))[5](call_out, &(self->res_exp)));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_operand_analyze_func_pointer = "Call-operand.analyze-func-pointer";
#define MR_FUNC_NAME _func_name_Call_operand_analyze_func_pointer
Returncode Call_operand_analyze_func_pointer(Call_operand* self, Mtype** mtype, Mtype** sub_mtype) {
  Arg_node* arg = self->args->first_param;
  Bool first = true;
  while (true) {
    if (!(NULL != arg)) break;
    Mexp* exp;
    CHECK(413, (*((Func**)(arg)))[5](arg, &(exp)));
    Mtype* param_mtype = NULL;
    Mtype* param_sub_mtype = NULL;
    CHECK(416, Mexp_analyze(exp, &(param_mtype), &(param_sub_mtype)));
  }
  arg = self->args->first_out;
  (*mtype) = NULL;
  (*sub_mtype) = NULL;
  while (true) {
    if (!(NULL != arg)) break;
    Mexp* exp;
    CHECK(423, (*((Func**)(arg)))[5](arg, &(exp)));
    (*mtype) = NULL;
    (*sub_mtype) = NULL;
    CHECK(426, Mexp_analyze(exp, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_operand_analyze = "Call-operand.analyze";
#define MR_FUNC_NAME _func_name_Call_operand_analyze
Returncode Call_operand_analyze(Call_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  self->is_used = exp->is_used || NULL != self->_base.next || NULL != exp->next || NULL != exp->operator;
  if (!self->is_used) {
    exp->is_used = true;
  }
  
  member->next = NULL;
  Operand* method_opr;
  method_opr = &(method->_base);
  Bool is_method = NULL != method && method_opr != member;
  if (is_method) {
    method->_base.next = NULL;
    self->func_opr = &(method->_base);
    if (method->mvar->func_dec->is_dynamic && method->allow_dynamic) {
      self->dynamic_opr = exp->operand;
      self->dynamic_index = method->mvar->func_dec->dynamic_index;
      self->dynamic_base_count = method->base_count;
      method->base_count = 0;
    }
    Mexp* new_exp = malloc(sizeof(Mexp));
    if (new_exp == NULL) RAISE(445)
    CHECK(446, Mexp_init(new_exp));
    new_exp->operand = exp->operand;
    new_exp->base_count = method->base_count;
    CHECK(449, Arg_list_add_self_call(self->args, new_exp));
  }
  else {
    self->func_opr = exp->operand;
  }
  exp->operand = &(self->_base);
  
  if (NULL != method && NULL != method->mvar->func_dec) {
    CHECK(455, Call_operand_analyze_args(self, method->mvar->func_dec, is_method, &((*mtype)), &((*sub_mtype))));
  }
  else {
    CHECK(457, Call_operand_analyze_func_pointer(self, &((*mtype)), &((*sub_mtype))));
  }
  
  if (NULL != self->_base.next) {
    CHECK(460, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, &(self->_base), NULL, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_operand_write_call = "Call-operand.write-call";
#define MR_FUNC_NAME _func_name_Call_operand_write_call
Returncode Call_operand_write_call(Call_operand* self) {
  CHECK(463, write_tb_check());
  if (NULL != self->dynamic_opr) {
    /* (opr)->[_base.]_dtl[index] */
    CHECK(466, write(&(String){2, 1, "("}));
    CHECK(467, Operand_write_all_final(self->dynamic_opr));
    CHECK(468, write(&(String){4, 3, ")->"}));
    Int n; for (n = 0; n < self->dynamic_base_count; ++n) {
      CHECK(470, write(&(String){7, 6, "_base."}));
    }
    CHECK(471, write(&(String){6, 5, "_dtl["}));
    CHECK(472, write_int(self->dynamic_index));
    CHECK(473, write(&(String){2, 1, "]"}));
  }
  else {
    CHECK(475, Operand_write_all_final(self->func_opr));
  }
  CHECK(476, Arg_list_write_final(self->args));
  CHECK(477, write(&(String){3, 2, " )"}));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_operand_write_intro = "Call-operand.write-intro";
#define MR_FUNC_NAME _func_name_Call_operand_write_intro
Returncode Call_operand_write_intro(Call_operand* self) {
  CHECK(480, Operand_write_all_intro(self->func_opr));
  CHECK(481, Arg_list_write_intro(self->args));
  if (NULL != self->res_exp) {
    CHECK(483, Mexp_write_intro(self->res_exp));
  }
  else {
    if (NULL != self->res_name) {
      CHECK(485, write_cstyle(self->res_mtype->name));
      if (!self->res_mtype->is_primitive) {
        CHECK(487, write(&(String){2, 1, "*"}));
      }
      CHECK(488, write(&(String){2, 1, " "}));
      CHECK(489, write_cstyle(self->res_name));
      CHECK(490, write(&(String){3, 2, ";\n"}));
      CHECK(491, write_spaces());
    }
  }
  if (self->is_used) {
    CHECK(493, Call_operand_write_call(self));
    CHECK(494, write_new_indent_line());
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Call_operand_write_final = "Call-operand.write-final";
#define MR_FUNC_NAME _func_name_Call_operand_write_final
Returncode Call_operand_write_final(Call_operand* self) {
  if (self->is_used) {
    if (NULL != self->res_exp) {
      CHECK(499, Mexp_write_final(self->res_exp));
    }
    else {
      if (self->res_name) {
        CHECK(501, write_cstyle(self->res_name));
      }
    }
  }
  else {
    CHECK(503, Call_operand_write_call(self));
  }
  return OK;
}
#undef MR_FUNC_NAME
Func Call_operand__dtl[] = {Call_operand_parse, Call_operand_analyze, Call_operand_write_intro, Call_operand_write_final};


static char* _func_name_parse_new_operand = "parse-new-operand";
#define MR_FUNC_NAME _func_name_parse_new_operand
Returncode parse_new_operand(Type opr_type, String* text, String* ends, Operand** new_opr, Char* end) {
  if (opr_type.size <= 0) RAISE(507)
  Operand* opr = malloc(opr_type.size);
  if (opr == NULL) RAISE(507)
  if (opr_type.dtl != NULL) { *((Func**)(opr)) = opr_type.dtl; }
  (*new_opr) = opr;
  CHECK(509, (*((Func**)(opr)))[0](opr, text, ends, &((*end))));
  Type next_type;
  if ((*end) == '.') {
    next_type = (Type){sizeof(Member_operand), Member_operand__dtl};
  }
  else {
    if ((*end) == '[') {
      next_type = (Type){sizeof(Slice_operand), Slice_operand__dtl};
    }
    else {
      if ((*end) == '(') {
        next_type = (Type){sizeof(Call_operand), Call_operand__dtl};
      }
      else {
        opr->next = NULL;
        return OK;
      }
    }
  }
  CHECK(520, parse_new_operand(next_type, NULL, ends, &(opr->next), &((*end))));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_parse_new_operands = "parse-new-operands";
#define MR_FUNC_NAME _func_name_parse_new_operands
Returncode parse_new_operands(String* text, String* ends, Operand** new_opr, Char* end) {
  Type opr_type;
  if (text->length == 0) {
    if ((*end) == '(') {
      opr_type = (Type){sizeof(Block_operand), Block_operand__dtl};
    }
    else {
      CHECK(528, f_syntax_error_c(&(String){11, 10, "unexpected"}, (*end)));
    }
  }
  else {
    if ((0) < 0 || (0) >= text->length) RAISE(530)
    Char first = text->chars[0];
    if (first == '\'') {
      opr_type = (Type){sizeof(Char_operand), Char_operand__dtl};
    }
    else {
      if (first == '"') {
        opr_type = (Type){sizeof(String_operand), String_operand__dtl};
      }
      else {
        if (first >= '0' && first <= '9') {
          opr_type = (Type){sizeof(Int_operand), Int_operand__dtl};
        }
        else {
          if (first >= 'A' && first <= 'Z') {
            opr_type = (Type){sizeof(Type_operand), Type_operand__dtl};
          }
          else {
            if (text->length == 1 && first == '_') {
              opr_type = (Type){sizeof(Empty_operand), Empty_operand__dtl};
            }
            else {
              Bool _Bool9;
              CHECK(541, String_equal(text, &(String){5, 4, "base"}, &(_Bool9)))
              if (_Bool9) {
                opr_type = (Type){sizeof(Base_meth_operand), Base_meth_operand__dtl};
              }
              else {
                opr_type = (Type){sizeof(Var_operand), Var_operand__dtl};
              }
            }
          }
        }
      }
    }
  }
  CHECK(545, parse_new_operand(opr_type, text, ends, &((*new_opr)), &((*end))));
  return OK;
}
#undef MR_FUNC_NAME


typedef struct St_func St_func; struct St_func {
  St_node _base;
  Mfunc* mfunc;
};
static char* _func_name_St_func_add_args_vars = "St-func.add-args-vars";
#define MR_FUNC_NAME _func_name_St_func_add_args_vars
Returncode St_func_add_args_vars(St_func* self, Arg_node* fisrt_arg) {
  Arg_node* arg = fisrt_arg;
  while (true) {
    if (!(NULL != arg)) break;
    Dec_arg* dec_arg;
    CHECK(556, (*((Func**)(arg)))[4](arg, &(dec_arg)));
    if (!(NULL != dec_arg)) break;
    CHECK(558, add_var(self->_base._base.sons_var_map, dec_arg->mvar));
    arg = arg->next;
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_func_parse = "St-func.parse";
#define MR_FUNC_NAME _func_name_St_func_parse
Returncode St_func_parse(St_func* self) {
  CHECK(562, parse_new_mfunc(&(self->mfunc)));
  Mvar* _Mvar10;
  CHECK(563, Mfunc_m_new_var(self->mfunc, &(_Mvar10)))
  CHECK(563, St_add_var(&(self->_base._base), _Mvar10));
  CHECK(564, f_copy_new_var_map(NULL, &(self->_base._base.sons_var_map)));
  CHECK(565, St_func_add_args_vars(self, self->mfunc->args->first_param));
  CHECK(566, St_func_add_args_vars(self, self->mfunc->args->first_out));
  CHECK(567, St_node_parse(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_func_analyze_first = "St-func.analyze-first";
#define MR_FUNC_NAME _func_name_St_func_analyze_first
Returncode St_func_analyze_first(St_func* self) {
  CHECK(570, Mfunc_analyze(self->mfunc));
  CHECK(571, St_node_analyze_first(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_func_analyze = "St-func.analyze";
#define MR_FUNC_NAME _func_name_St_func_analyze
Returncode St_func_analyze(St_func* self) {
  St_return* st_return = malloc(sizeof(St_return));
  if (st_return == NULL) RAISE(574)
  *((Func**)(st_return)) = St_return__dtl;
  CHECK(575, St_init(&(st_return->_base), &(self->_base._base)));
  CHECK(576, St_node_analyze(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_func_write = "St-func.write";
#define MR_FUNC_NAME _func_name_St_func_write
Returncode St_func_write(St_func* self) {
  if (NULL != glob->mclass) {
    if (!glob->methods) {
      return OK;
    }
    CHECK(582, write_new_indent_line());
  }
  CHECK(583, write(&(String){33, 32, "#if MR_STAGE == MR_DECLARATIONS\n"}));
  CHECK(584, write_spaces());
  CHECK(585, Mfunc_write(self->mfunc));
  CHECK(586, write(&(String){3, 2, ";\n"}));
  CHECK(587, write_spaces());
  CHECK(588, write(&(String){32, 31, "#elif MR_STAGE == MR_FUNCTIONS\n"}));
  CHECK(589, write_spaces());
  CHECK(590, write(&(String){25, 24, "static char* _func_name_"}));
  CHECK(591, Mfunc_write_name(self->mfunc));
  CHECK(592, write(&(String){5, 4, " = \""}));
  if (NULL != glob->mclass) {
    CHECK(594, write(glob->mclass->name));
    CHECK(595, write(&(String){2, 1, "."}));
  }
  CHECK(596, write(self->mfunc->name));
  CHECK(597, write(&(String){4, 3, "\";\n"}));
  CHECK(598, write_spaces());
  CHECK(599, write(&(String){33, 32, "#define MR_FUNC_NAME _func_name_"}));
  CHECK(600, Mfunc_write_name(self->mfunc));
  CHECK(601, write_new_indent_line());
  CHECK(602, Mfunc_write(self->mfunc));
  Mtype* mclass = glob->mclass;
  glob->mclass = NULL;
  CHECK(605, St_node_write(&(self->_base)));
  glob->mclass = mclass;
  CHECK(607, write_new_indent_line());
  CHECK(608, write(&(String){21, 20, "#undef MR_FUNC_NAME\n"}));
  CHECK(609, write_spaces());
  CHECK(610, write(&(String){7, 6, "#endif"}));
  return OK;
}
#undef MR_FUNC_NAME
Func St_func__dtl[] = {St_func_parse, St_func_analyze_first, St_func_analyze, St_func_write};


typedef struct St_main St_main; struct St_main {
  St_func _base;
};
static char* _func_name_St_main_parse = "St-main.parse";
#define MR_FUNC_NAME _func_name_St_main_parse
Returncode St_main_parse(St_main* self) {
  CHECK(615, St_func_parse(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_main_analyze_first = "St-main.analyze-first";
#define MR_FUNC_NAME _func_name_St_main_analyze_first
Returncode St_main_analyze_first(St_main* self) {
  CHECK(618, St_func_analyze_first(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_main_analyze = "St-main.analyze";
#define MR_FUNC_NAME _func_name_St_main_analyze
Returncode St_main_analyze(St_main* self) {
  CHECK(621, St_func_analyze(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_main_write = "St-main.write";
#define MR_FUNC_NAME _func_name_St_main_write
Returncode St_main_write(St_main* self) {
  CHECK(624, St_func_write(&(self->_base)));
  CHECK(625, write(&(String){32, 31, "\n\n#if MR_STAGE == MR_FUNCTIONS\n"}));
  CHECK(626, write(&(String){11, 10, "MAIN_FUNC\n"}));
  CHECK(627, write(&(String){7, 6, "#endif"}));
  return OK;
}
#undef MR_FUNC_NAME
Func St_main__dtl[] = {St_main_parse, St_main_analyze_first, St_main_analyze, St_main_write};


typedef struct St_format St_format; struct St_format {
  St_node _base;
  String* item_name;
  Mvar* item_mvar;
  String* func_name;
  String* format;
};
static char* _func_name_St_format_parse = "St-format.parse";
#define MR_FUNC_NAME _func_name_St_format_parse
Returncode St_format_parse(St_format* self) {
  self->item_name = NULL;
  self->item_mvar = NULL;
  Char _Char11;
  CHECK(639, read_new(&(String){3, 2, ".("}, &(self->func_name), &(_Char11)))
  if (_Char11 == '.') {
    self->item_name = self->func_name;
    Char _Char12;
    CHECK(641, read_new(&(String){2, 1, "("}, &(self->func_name), &(_Char12)));
  }
  String* format = &(String){256, 0, (char[256]){0}};
  Char _Char13;
  CHECK(643, read(&(String){2, 1, ")"}, format, &(_Char13)));
  if ((format->length - 1) < 0 || (format->length - 1) >= format->length) RAISE(644)
  if ((0) < 0 || (0) >= format->length) RAISE(644)
  if (format->length < 2 || format->chars[0] != '"' || format->chars[format->length - 1] != '"') {
    CHECK(645, f_syntax_error(&(String){22, 21, "illegal format string"}, format));
  }
  if ((1) < 0 || (format->length - 2) < 0 || (1) + (format->length - 2) > format->length) RAISE(646)
  CHECK(646, f_new_copy(&(String){format->length - 2, format->length - 2, format->chars + (1)}, &(self->format)));
  Char _Char14;
  CHECK(647, read_c(&(_Char14)));
  CHECK(648, St_node_parse(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_format_analyze_first = "St-format.analyze-first";
#define MR_FUNC_NAME _func_name_St_format_analyze_first
Returncode St_format_analyze_first(St_format* self) {
  CHECK(651, St_node_analyze_first(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_format_analyze = "St-format.analyze";
#define MR_FUNC_NAME _func_name_St_format_analyze
Returncode St_format_analyze(St_format* self) {
  Mvar* mvar;
  if (NULL != self->item_name) {
    CHECK(656, f_find_var(self->item_name, &(self->item_mvar)))
    if (!(NULL != self->item_mvar)) {
      CHECK(657, f_syntax_error(&(String){16, 15, "unknow variable"}, self->item_name));
    }
    CHECK(658, Var_map_find(self->item_mvar->mtype->members, self->func_name, &(mvar)))
    if (!(NULL != mvar)) {
      CHECK(659, f_syntax_error2(&(String){5, 4, "type"}, self->item_mvar->typename, &(String){14, 13, "has no method"}, self->func_name));
    }
  }
  else {
    CHECK(661, f_find_var(self->func_name, &(mvar)))
    if (!(NULL != mvar)) {
      CHECK(662, f_syntax_error(&(String){16, 15, "unknow function"}, self->func_name));
    }
  }
  if (!(NULL != mvar->func_dec)) {
    CHECK(664, f_syntax_error(&(String){22, 21, "non function variable"}, self->func_name));
  }
  if (!(NULL != mvar->func_dec->args->first_param)) {
    CHECK(666, f_syntax_error(&(String){26, 25, "no parameter for function"}, self->func_name));
  }
  if (NULL != mvar->func_dec->args->first_out) {
    CHECK(668, f_syntax_error(&(String){27, 26, "outputs exists in function"}, self->func_name));
  }
  Dec_arg* param_dec;
  if (NULL != self->item_name) {
    if (!(NULL != mvar->func_dec->args->first_param->next)) {
      CHECK(672, f_syntax_error(&(String){24, 23, "no parameter for method"}, self->func_name));
    }
    CHECK(673, (*((Func**)(mvar->func_dec->args->first_param->next)))[4](mvar->func_dec->args->first_param->next, &(param_dec)));
  }
  else {
    CHECK(675, (*((Func**)(mvar->func_dec->args->first_param)))[4](mvar->func_dec->args->first_param, &(param_dec)));
  }
  if (NULL != param_dec->_base.next) {
    CHECK(677, f_syntax_error(&(String){32, 31, "too many parameter for function"}, self->func_name));
  }
  if (param_dec->mvar->mtype != glob->type_string) {
    CHECK(679, f_syntax_error2(&(String){40, 39, "expected a string parameter in function"}, self->func_name, &(String){12, 11, " instead of"}, param_dec->mvar->typename));
  }
  if (param_dec->mvar->access != ACCESS_USER) {
    CHECK(681, f_syntax_error(&(String){48, 47, "expected parameter with user access in function"}, self->func_name));
  }
  CHECK(682, St_node_analyze(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_format_write = "St-format.write";
#define MR_FUNC_NAME _func_name_St_format_write
Returncode St_format_write(St_format* self) {
  Int index = 0;
  Int len = self->format->length;
  St* node = self->_base._base.first_son;
  while (true) {
    if (!(len > 0)) break;
    if (index > 0) {
      CHECK(691, write_new_indent_line());
    }
    
    if ((index) < 0 || (len) < 0 || (index) + (len) > self->format->length) RAISE(693)
    String* format = &(String){len, len, self->format->chars + (index)};
    Int _Int15;
    CHECK(694, String_find(format, &(String){3, 2, "{}"}, &(_Int15)))
    Int next = _Int15;
    if (next > 0) {
      CHECK(696, write_tb_check());
      if (NULL != self->item_mvar) {
        CHECK(698, write_cstyle(self->item_mvar->mtype->name));
        CHECK(699, write(&(String){2, 1, "_"}));
      }
      CHECK(700, write_cstyle(self->func_name));
      CHECK(701, write(&(String){2, 1, "("}));
      if (NULL != self->item_mvar) {
        if (self->item_mvar->is_ref) {
          CHECK(704, write(&(String){2, 1, "*"}));
        }
        CHECK(705, write_cstyle(self->item_mvar->name));
        CHECK(706, write(&(String){3, 2, ", "}));
      }
      CHECK(707, write(&(String){11, 10, "&(String){"}));
      CHECK(708, write_int(next + 1));
      CHECK(709, write(&(String){3, 2, ", "}));
      CHECK(710, write_int(next));
      CHECK(711, write(&(String){4, 3, ", \""}));
      if ((0) < 0 || (next) < 0 || (0) + (next) > format->length) RAISE(712)
      CHECK(712, write(&(String){next, next, format->chars + (0)}));
      CHECK(713, write(&(String){6, 5, "\"}) )"}));
    }
    else {
      if (!(NULL != node)) {
        CHECK(716, f_syntax_error(&(String){24, 23, "too few lines to format"}, self->func_name));
      }
      glob->line_num = node->line_num;
      CHECK(718, (*((Func**)(node)))[3](node));
      glob->line_num = self->_base._base.line_num;
      node = node->next_brother;
      next = 2;
    }
    index = index + next;
    len = len - next;
  }
  return OK;
}
#undef MR_FUNC_NAME
Func St_format__dtl[] = {St_format_parse, St_format_analyze_first, St_format_analyze, St_format_write};

#undef MR_FILE_NAME
