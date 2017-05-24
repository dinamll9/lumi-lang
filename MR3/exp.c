static char* _mr_file4_name = "exp.2.mr";
#define MR_FILE_NAME _mr_file4_name
/* MR3 compiler - expression */

typedef struct Mexp Mexp;
typedef struct Var_operand Var_operand;

typedef struct Operand Operand; struct Operand {
  Func* _dtl;
  Operand* next;
};
static char* _func_name_Operand_parse = "Operand.parse";
#define MR_FUNC_NAME _func_name_Operand_parse
Returncode Operand_parse(Operand* self, String* text, String* ends, Char* end) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Operand_analyze = "Operand.analyze";
#define MR_FUNC_NAME _func_name_Operand_analyze
Returncode Operand_analyze(Operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Operand_write_intro = "Operand.write-intro";
#define MR_FUNC_NAME _func_name_Operand_write_intro
Returncode Operand_write_intro(Operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Operand_write_final = "Operand.write-final";
#define MR_FUNC_NAME _func_name_Operand_write_final
Returncode Operand_write_final(Operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Operand_write_all_intro = "Operand.write-all-intro";
#define MR_FUNC_NAME _func_name_Operand_write_all_intro
Returncode Operand_write_all_intro(Operand* self) {
  CHECK(19, (*((Func**)(self)))[2](self));
  if (NULL != self->next) {
    CHECK(21, Operand_write_all_intro(self->next));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Operand_write_all_final = "Operand.write-all-final";
#define MR_FUNC_NAME _func_name_Operand_write_all_final
Returncode Operand_write_all_final(Operand* self) {
  CHECK(24, (*((Func**)(self)))[3](self));
  if (NULL != self->next) {
    CHECK(26, Operand_write_all_final(self->next));
  }
  return OK;
}
#undef MR_FUNC_NAME
Func Operand__dtl[] = {Operand_parse, Operand_analyze, Operand_write_intro, Operand_write_final};


static char* _func_name_read_new_value = "read-new-value";
#define MR_FUNC_NAME _func_name_read_new_value
Returncode read_new_value(String* ends, String** out_text, Char* end) {
  String* all_ends = new_string(ends->length + 5);
  if (all_ends == NULL) RAISE(30)
  CHECK(31, String_copy(all_ends, &(String){5, 4, " .[("}));
  CHECK(32, String_concat(all_ends, ends));
  CHECK(33, read_new(all_ends, &((*out_text)), &((*end))));
  free(all_ends);
  return OK;
}
#undef MR_FUNC_NAME

Returncode parse_new_operands(String* text, String* ends, Operand** new_opr, Char* end);

typedef struct Mexp Mexp; struct Mexp {
  Operand* operand;
  String* operator;
  Mexp* next;
  Int base_count;
  Bool is_used;
};
static char* _func_name_Mexp_init = "Mexp.init";
#define MR_FUNC_NAME _func_name_Mexp_init
Returncode Mexp_init(Mexp* self) {
  self->operand = NULL;
  self->operator = NULL;
  self->next = NULL;
  self->is_used = true;
  self->base_count = 0;
  return OK;
}
#undef MR_FUNC_NAME
Returncode Mexp_parse(Mexp* self, String* text, String* ends, Char* end);
static char* _func_name_Mexp_parse_new_with_text = "Mexp.parse-new-with-text";
#define MR_FUNC_NAME _func_name_Mexp_parse_new_with_text
Returncode Mexp_parse_new_with_text(Mexp* self, String* text, String* ends, Mexp** new_exp, Char* end) {
  Mexp* exp = malloc(sizeof(Mexp));
  if (exp == NULL) RAISE(55)
  CHECK(56, Mexp_init(exp));
  CHECK(57, Mexp_parse(exp, text, ends, &((*end))));
  (*new_exp) = exp;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_parse_new = "Mexp.parse-new";
#define MR_FUNC_NAME _func_name_Mexp_parse_new
Returncode Mexp_parse_new(Mexp* self, String* ends, Mexp** new_exp, Char* end) {
  String* text;
  CHECK(62, read_new_value(ends, &(text), &((*end))));
  CHECK(63, Mexp_parse_new_with_text(self, text, ends, &((*new_exp)), &((*end))));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_parse_new_with_kw = "Mexp.parse-new-with-kw";
#define MR_FUNC_NAME _func_name_Mexp_parse_new_with_kw
Returncode Mexp_parse_new_with_kw(Mexp* self, String* ends, Mexp** new_exp, Char* end) {
  if (NULL != glob->key_word) {
    String* text;
    CHECK(68, f_new_copy(glob->key_word->text, &(text)));
    (*end) = glob->key_word->end;
    CHECK(70, Mexp_parse_new_with_text(self, text, ends, &((*new_exp)), &((*end))));
  }
  else {
    CHECK(72, Mexp_parse_new(self, ends, &((*new_exp)), &((*end))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_parse = "Mexp.parse";
#define MR_FUNC_NAME _func_name_Mexp_parse
Returncode Mexp_parse(Mexp* self, String* text, String* ends, Char* end) {
  String* _String0;
  CHECK(75, Op_map_find(glob->op_map, text, &(_String0)))
  if ((*end) == ' ' && NULL != _String0) {
    self->operator = text;
    CHECK(77, read_new_value(ends, &(text), &((*end))));
    
    String* _String1;
    CHECK(79, Op_map_find(glob->op_map, text, &(_String1)))
    if ((*end) == ' ' && NULL != _String1) {
      self->operand = NULL;
      CHECK(81, Mexp_parse_new_with_text(self, text, ends, &(self->next), &((*end))));
      return OK;
    }
  }
  
  CHECK(84, parse_new_operands(text, ends, &(self->operand), &((*end))));
  Bool _Bool2;
  CHECK(85, String_has(ends, ' ', &(_Bool2)))
  if ((*end) == ' ' && !_Bool2) {
    CHECK(86, Mexp_parse_new(self, ends, &(self->next), &((*end))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_f_count_bases = "Mexp.f-count-bases";
#define MR_FUNC_NAME _func_name_Mexp_f_count_bases
Returncode Mexp_f_count_bases(Mexp* self, Mtype* target_mtype, Mtype** mtype, Int* base_count) {
  if (!(NULL != target_mtype)) {
    return OK;
  }
  if (!(NULL != (*mtype))) {
    CHECK(92, f_syntax_error(&(String){23, 22, "got no value, expected"}, target_mtype->name));
  }
  (*base_count) = 0;
  if (target_mtype == glob->type_bool && (*mtype)->is_primitive) {
    (*mtype) = glob->type_bool;
    return OK;
  }
  if (target_mtype == glob->type_char && (*mtype) == glob->type_int) {
    (*mtype) = glob->type_char;
    return OK;
  }
  if (target_mtype == glob->type_int && (*mtype) == glob->type_char) {
    (*mtype) = glob->type_int;
    return OK;
  }
  Mtype* orig_mtype = (*mtype);
  while (true) {
    if (!((*mtype) != target_mtype)) break;
    (*mtype) = (*mtype)->base_mtype;
    if (!(NULL != (*mtype))) {
      CHECK(108, f_syntax_error2(&(String){4, 3, "got"}, orig_mtype->name, &(String){9, 8, "expected"}, target_mtype->name));
    }
    (*base_count) = (*base_count) + 1;
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_analyze = "Mexp.analyze";
#define MR_FUNC_NAME _func_name_Mexp_analyze
Returncode Mexp_analyze(Mexp* self, Mtype** mtype, Mtype** sub_mtype) {
  if (NULL != self->operand) {
    Mtype* target_mtype = (*mtype);
    Mtype* target_sub_mtype = (*sub_mtype);
    CHECK(115, (*((Func**)(self->operand)))[1](self->operand, self, NULL, NULL, &((*mtype)), &((*sub_mtype))));
    if (NULL != self->operator && NULL != (*mtype)) {
      Bool _Bool3;
      CHECK(117, String_equal(self->operator, &(String){2, 1, "?"}, &(_Bool3)))
      if (_Bool3) {
        if ((*mtype)->is_primitive) {
          CHECK(119, f_syntax_error(&(String){20, 19, "? on primitive type"}, (*mtype)->name));
        }
        (*mtype) = glob->type_bool;
        (*sub_mtype) = NULL;
      }
    }
    CHECK(122, Mexp_f_count_bases(self, target_mtype, &((*mtype)), &(self->base_count)));
    Int _Int4;
    CHECK(123, Mexp_f_count_bases(self, target_sub_mtype, &((*sub_mtype)), &(_Int4)));
  }
  
  if (NULL != self->next) {
    CHECK(126, Mexp_analyze(self->next, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_analyze_get_subtype = "Mexp.analyze-get-subtype";
#define MR_FUNC_NAME _func_name_Mexp_analyze_get_subtype
Returncode Mexp_analyze_get_subtype(Mexp* self, Mtype* target_mtype, Mtype** sub_mtype) {
  Mtype* mtype = target_mtype;
  CHECK(130, Mexp_analyze(self, &(mtype), &((*sub_mtype))));
  if (!(NULL != mtype)) {
    CHECK(132, f_syntax_error(&(String){23, 22, "got no value, expected"}, target_mtype->name));
  }
  if (mtype != target_mtype) {
    CHECK(134, f_syntax_error2(&(String){4, 3, "got"}, mtype->name, &(String){9, 8, "expected"}, target_mtype->name));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_analyze_types = "Mexp.analyze-types";
#define MR_FUNC_NAME _func_name_Mexp_analyze_types
Returncode Mexp_analyze_types(Mexp* self, Mtype* target_mtype, Mtype* target_sub_mtype) {
  Mtype* sub_mtype = target_sub_mtype;
  CHECK(138, Mexp_analyze_get_subtype(self, target_mtype, &(sub_mtype)));
  if (NULL != target_sub_mtype) {
    if (!(NULL != sub_mtype)) {
      CHECK(141, f_syntax_error(&(String){26, 25, "got no sub-type, expected"}, target_sub_mtype->name));
    }
    if (sub_mtype != target_sub_mtype) {
      CHECK(143, f_syntax_error2(&(String){13, 12, "got sub-type"}, sub_mtype->name, &(String){9, 8, "expected"}, target_sub_mtype->name));
    }
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_analyze_type = "Mexp.analyze-type";
#define MR_FUNC_NAME _func_name_Mexp_analyze_type
Returncode Mexp_analyze_type(Mexp* self, Mtype* target_mtype) {
  CHECK(146, Mexp_analyze_types(self, target_mtype, NULL));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_write_all_final = "Mexp.write-all-final";
#define MR_FUNC_NAME _func_name_Mexp_write_all_final
Returncode Mexp_write_all_final(Mexp* self, Bool is_binary) {
  if (NULL != self->operator) {
    String* op;
    CHECK(151, Op_map_find(glob->op_map, self->operator, &(op)))
    if (!(NULL != op)) {
      CHECK(152, f_syntax_error(&(String){16, 15, "unknow operator"}, self->operator));
    }
    if (is_binary) {
      CHECK(154, write(&(String){2, 1, " "}));
    }
    CHECK(155, write(op));
    if (is_binary) {
      CHECK(157, write(&(String){2, 1, " "}));
    }
  }
  if (NULL != self->operand) {
    if (self->base_count > 0) {
      CHECK(160, write(&(String){3, 2, "&("}));
    }
    CHECK(161, Operand_write_all_final(self->operand));
    if (self->base_count > 0) {
      CHECK(163, write(&(String){8, 7, "->_base"}));
      Int n; for (n = 1; n < self->base_count; ++n) {
        CHECK(165, write(&(String){7, 6, "._base"}));
      }
      CHECK(166, write(&(String){2, 1, ")"}));
    }
  }
  if (NULL != self->next) {
    CHECK(168, Mexp_write_all_final(self->next, true));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_write_intro = "Mexp.write-intro";
#define MR_FUNC_NAME _func_name_Mexp_write_intro
Returncode Mexp_write_intro(Mexp* self) {
  if (NULL != self->operand) {
    CHECK(172, Operand_write_all_intro(self->operand));
  }
  if (NULL != self->next) {
    CHECK(174, Mexp_write_intro(self->next));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Mexp_write_final = "Mexp.write-final";
#define MR_FUNC_NAME _func_name_Mexp_write_final
Returncode Mexp_write_final(Mexp* self) {
  CHECK(177, Mexp_write_all_final(self, false));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_parse_new_exp = "parse-new-exp";
#define MR_FUNC_NAME _func_name_parse_new_exp
Returncode parse_new_exp(String* ends, Mexp** exp, Char* end) {
  CHECK(180, Mexp_parse_new(NULL, ends, &((*exp)), &((*end))));
  return OK;
}
#undef MR_FUNC_NAME

static char* _func_name_parse_new_exp_with_kw = "parse-new-exp-with-kw";
#define MR_FUNC_NAME _func_name_parse_new_exp_with_kw
Returncode parse_new_exp_with_kw(String* ends, Mexp** exp, Char* end) {
  CHECK(183, Mexp_parse_new_with_kw(NULL, ends, &((*exp)), &((*end))));
  return OK;
}
#undef MR_FUNC_NAME


Returncode f_find_var(String* name, Mvar** mvar);

typedef struct Var_operand Var_operand; struct Var_operand {
  Operand _base;
  String* name;
  Mvar* mvar;
  Int base_count;
  Bool allow_dynamic;
};
static char* _func_name_Var_operand_parse = "Var-operand.parse";
#define MR_FUNC_NAME _func_name_Var_operand_parse
Returncode Var_operand_parse(Var_operand* self, String* text, String* ends, Char* end) {
  self->name = text;
  self->mvar = NULL;
  self->base_count = 0;
  self->allow_dynamic = true;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Var_operand_analyze = "Var-operand.analyze";
#define MR_FUNC_NAME _func_name_Var_operand_analyze
Returncode Var_operand_analyze(Var_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  CHECK(201, f_find_var(self->name, &(self->mvar)))
  if (!(NULL != self->mvar)) {
    CHECK(202, f_syntax_error(&(String){16, 15, "unknow variable"}, self->name));
  }
  (*mtype) = self->mvar->mtype;
  (*sub_mtype) = self->mvar->sub_mtype;
  if (NULL != self->_base.next) {
    CHECK(206, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, &(self->_base), self, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Var_operand_write_intro = "Var-operand.write-intro";
#define MR_FUNC_NAME _func_name_Var_operand_write_intro
Returncode Var_operand_write_intro(Var_operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Var_operand_write_final = "Var-operand.write-final";
#define MR_FUNC_NAME _func_name_Var_operand_write_final
Returncode Var_operand_write_final(Var_operand* self) {
  if (self->mvar->is_ref) {
    CHECK(213, write(&(String){3, 2, "(*"}));
  }
  CHECK(214, write_cstyle(self->name));
  if (self->mvar->is_ref) {
    CHECK(216, write(&(String){2, 1, ")"}));
  }
  return OK;
}
#undef MR_FUNC_NAME
Func Var_operand__dtl[] = {Var_operand_parse, Var_operand_analyze, Var_operand_write_intro, Var_operand_write_final};


typedef struct Char_operand Char_operand; struct Char_operand {
  Operand _base;
  String* text;
};
static char* _func_name_Char_operand_parse = "Char-operand.parse";
#define MR_FUNC_NAME _func_name_Char_operand_parse
Returncode Char_operand_parse(Char_operand* self, String* text, String* ends, Char* end) {
  Char ch;
  if (text->length == 3) {
    if ((1) < 0 || (1) >= text->length) RAISE(225)
    ch = text->chars[1];
    if (ch == '\'' || ch == '\\') {
      CHECK(227, f_syntax_error(&(String){27, 26, "illegal character constant"}, text));
    }
  }
  else {
    if (text->length == 4) {
      if ((1) < 0 || (1) >= text->length) RAISE(229)
      if (text->chars[1] != '\\') {
        CHECK(230, f_syntax_error(&(String){27, 26, "illegal character constant"}, text));
      }
      if ((2) < 0 || (2) >= text->length) RAISE(231)
      ch = text->chars[2];
    }
    else {
      CHECK(233, f_syntax_error(&(String){27, 26, "illegal character constant"}, text));
    }
  }
  if ((text->length - 1) < 0 || (text->length - 1) >= text->length) RAISE(234)
  if (text->chars[text->length - 1] != '\'') {
    CHECK(235, f_syntax_error(&(String){27, 26, "illegal character constant"}, text));
  }
  self->text = text;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Char_operand_analyze = "Char-operand.analyze";
#define MR_FUNC_NAME _func_name_Char_operand_analyze
Returncode Char_operand_analyze(Char_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  (*mtype) = glob->type_char;
  (*sub_mtype) = NULL;
  if (NULL != self->_base.next) {
    CHECK(242, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, &(self->_base), NULL, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Char_operand_write_intro = "Char-operand.write-intro";
#define MR_FUNC_NAME _func_name_Char_operand_write_intro
Returncode Char_operand_write_intro(Char_operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Char_operand_write_final = "Char-operand.write-final";
#define MR_FUNC_NAME _func_name_Char_operand_write_final
Returncode Char_operand_write_final(Char_operand* self) {
  CHECK(248, write(self->text));
  return OK;
}
#undef MR_FUNC_NAME
Func Char_operand__dtl[] = {Char_operand_parse, Char_operand_analyze, Char_operand_write_intro, Char_operand_write_final};


typedef struct String_operand String_operand; struct String_operand {
  Operand _base;
  String* text;
};
static char* _func_name_String_operand_parse = "String-operand.parse";
#define MR_FUNC_NAME _func_name_String_operand_parse
Returncode String_operand_parse(String_operand* self, String* text, String* ends, Char* end) {
  if ((text->length - 1) < 0 || (text->length - 1) >= text->length) RAISE(255)
  if (text->chars[text->length - 1] != '\"') {
    CHECK(256, f_syntax_error(&(String){24, 23, "illegal string constant"}, text));
  }
  self->text = text;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_String_operand_analyze = "String-operand.analyze";
#define MR_FUNC_NAME _func_name_String_operand_analyze
Returncode String_operand_analyze(String_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  (*mtype) = glob->type_string;
  (*sub_mtype) = NULL;
  if (NULL != self->_base.next) {
    CHECK(263, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, &(self->_base), NULL, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_String_operand_write_intro = "String-operand.write-intro";
#define MR_FUNC_NAME _func_name_String_operand_write_intro
Returncode String_operand_write_intro(String_operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_String_operand_write_final = "String-operand.write-final";
#define MR_FUNC_NAME _func_name_String_operand_write_final
Returncode String_operand_write_final(String_operand* self) {
  Int real_length = 1;
  Int index; for (index = 1; index < self->text->length - 1; ++index) {
    if ((index) < 0 || (index) >= self->text->length) RAISE(271)
    if (self->text->chars[index] == '\\') {
      index = index + 1;
    }
    real_length = real_length + 1;
  }
  CHECK(274, write(&(String){11, 10, "&(String){"}));
  CHECK(275, write_int(real_length));
  CHECK(276, write(&(String){3, 2, ", "}));
  CHECK(277, write_int(real_length - 1));
  CHECK(278, write(&(String){3, 2, ", "}));
  CHECK(279, write(self->text));
  CHECK(280, write(&(String){2, 1, "}"}));
  return OK;
}
#undef MR_FUNC_NAME
Func String_operand__dtl[] = {String_operand_parse, String_operand_analyze, String_operand_write_intro, String_operand_write_final};


typedef struct Int_operand Int_operand; struct Int_operand {
  Operand _base;
  String* text;
  Int value;
};
static char* _func_name_Int_operand_parse = "Int-operand.parse";
#define MR_FUNC_NAME _func_name_Int_operand_parse
Returncode Int_operand_parse(Int_operand* self, String* text, String* ends, Char* end) {
  self->value = 0;
  Int n; for (n = 0; n < text->length; ++n) {
    if ((n) < 0 || (n) >= text->length) RAISE(290)
    Char ch = text->chars[n];
    if (ch < '0' || ch > '9') {
      CHECK(292, f_syntax_error(&(String){15, 14, "illegal number"}, text));
    }
    self->value = self->value * 10 + ch - '0';
  }
  self->text = text;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Int_operand_analyze = "Int-operand.analyze";
#define MR_FUNC_NAME _func_name_Int_operand_analyze
Returncode Int_operand_analyze(Int_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  (*mtype) = glob->type_int;
  (*sub_mtype) = NULL;
  if (NULL != self->_base.next) {
    CHECK(300, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, &(self->_base), NULL, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Int_operand_write_intro = "Int-operand.write-intro";
#define MR_FUNC_NAME _func_name_Int_operand_write_intro
Returncode Int_operand_write_intro(Int_operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Int_operand_write_final = "Int-operand.write-final";
#define MR_FUNC_NAME _func_name_Int_operand_write_final
Returncode Int_operand_write_final(Int_operand* self) {
  CHECK(306, write(self->text));
  return OK;
}
#undef MR_FUNC_NAME
Func Int_operand__dtl[] = {Int_operand_parse, Int_operand_analyze, Int_operand_write_intro, Int_operand_write_final};


typedef struct Empty_operand Empty_operand; struct Empty_operand {
  Operand _base;
};
static char* _func_name_Empty_operand_parse = "Empty-operand.parse";
#define MR_FUNC_NAME _func_name_Empty_operand_parse
Returncode Empty_operand_parse(Empty_operand* self, String* text, String* ends, Char* end) {
  free(text);
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Empty_operand_analyze = "Empty-operand.analyze";
#define MR_FUNC_NAME _func_name_Empty_operand_analyze
Returncode Empty_operand_analyze(Empty_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  if (!(NULL != (*mtype)) || NULL != self->_base.next || (*mtype)->is_primitive) {
    CHECK(315, f_syntax_error_c(&(String){21, 20, "illegal use of value"}, '_'));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Empty_operand_write_intro = "Empty-operand.write-intro";
#define MR_FUNC_NAME _func_name_Empty_operand_write_intro
Returncode Empty_operand_write_intro(Empty_operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Empty_operand_write_final = "Empty-operand.write-final";
#define MR_FUNC_NAME _func_name_Empty_operand_write_final
Returncode Empty_operand_write_final(Empty_operand* self) {
  CHECK(321, write(&(String){5, 4, "NULL"}));
  return OK;
}
#undef MR_FUNC_NAME
Func Empty_operand__dtl[] = {Empty_operand_parse, Empty_operand_analyze, Empty_operand_write_intro, Empty_operand_write_final};


typedef struct Block_operand Block_operand; struct Block_operand {
  Operand _base;
  Mexp* exp;
};
static char* _func_name_Block_operand_parse = "Block-operand.parse";
#define MR_FUNC_NAME _func_name_Block_operand_parse
Returncode Block_operand_parse(Block_operand* self, String* text, String* ends, Char* end) {
  free(text);
  CHECK(329, parse_new_exp(&(String){2, 1, ")"}, &(self->exp), &((*end))));
  if ((*end) != ')') {
    CHECK(331, f_syntax_error(&(String){8, 7, "missing"}, &(String){2, 1, ")"}));
  }
  CHECK(332, read_c(&((*end))));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Block_operand_analyze = "Block-operand.analyze";
#define MR_FUNC_NAME _func_name_Block_operand_analyze
Returncode Block_operand_analyze(Block_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  CHECK(335, Mexp_analyze(self->exp, &((*mtype)), &((*sub_mtype))));
  if (NULL != self->_base.next) {
    CHECK(337, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, &(self->_base), NULL, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Block_operand_write_intro = "Block-operand.write-intro";
#define MR_FUNC_NAME _func_name_Block_operand_write_intro
Returncode Block_operand_write_intro(Block_operand* self) {
  CHECK(340, Mexp_write_intro(self->exp));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Block_operand_write_final = "Block-operand.write-final";
#define MR_FUNC_NAME _func_name_Block_operand_write_final
Returncode Block_operand_write_final(Block_operand* self) {
  CHECK(343, write(&(String){2, 1, "("}));
  CHECK(344, Mexp_write_final(self->exp));
  CHECK(345, write(&(String){2, 1, ")"}));
  return OK;
}
#undef MR_FUNC_NAME
Func Block_operand__dtl[] = {Block_operand_parse, Block_operand_analyze, Block_operand_write_intro, Block_operand_write_final};


Returncode f_is_func_dynamic(Mfunc* mfunc, Bool* is_dynamic);

typedef struct Cast_operand Cast_operand; struct Cast_operand {
  Operand _base;
  Mtype* mtype;
  Operand* operand;
};
static char* _func_name_Cast_operand_parse = "Cast-operand.parse";
#define MR_FUNC_NAME _func_name_Cast_operand_parse
Returncode Cast_operand_parse(Cast_operand* self, String* text, String* ends, Char* end) {
  RAISE(355)
}
#undef MR_FUNC_NAME
static char* _func_name_Cast_operand_analyze = "Cast-operand.analyze";
#define MR_FUNC_NAME _func_name_Cast_operand_analyze
Returncode Cast_operand_analyze(Cast_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  self->mtype = (*mtype);
  self->operand = exp->operand;
  exp->operand = &(self->_base);
  if (NULL != self->_base.next) {
    CHECK(362, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, &(self->_base), NULL, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Cast_operand_write_intro = "Cast-operand.write-intro";
#define MR_FUNC_NAME _func_name_Cast_operand_write_intro
Returncode Cast_operand_write_intro(Cast_operand* self) {
  CHECK(365, Operand_write_all_intro(self->operand));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Cast_operand_write_final = "Cast-operand.write-final";
#define MR_FUNC_NAME _func_name_Cast_operand_write_final
Returncode Cast_operand_write_final(Cast_operand* self) {
  /* ((Type*)(operand...)) */
  CHECK(369, write(&(String){3, 2, "(("}));
  CHECK(370, write_cstyle(self->mtype->name));
  CHECK(371, write(&(String){4, 3, "*)("}));
  CHECK(372, Operand_write_all_final(self->operand));
  CHECK(373, write(&(String){3, 2, "))"}));
  return OK;
}
#undef MR_FUNC_NAME
Func Cast_operand__dtl[] = {Cast_operand_parse, Cast_operand_analyze, Cast_operand_write_intro, Cast_operand_write_final};


typedef struct Member_operand Member_operand; struct Member_operand {
  Var_operand _base;
  Mtype* prev_mtype;
};
static char* _func_name_Member_operand_parse = "Member-operand.parse";
#define MR_FUNC_NAME _func_name_Member_operand_parse
Returncode Member_operand_parse(Member_operand* self, String* text, String* ends, Char* end) {
  self->_base.base_count = 0;
  self->_base.allow_dynamic = true;
  CHECK(382, read_new_value(ends, &(self->_base.name), &((*end))));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Member_operand_analyze = "Member-operand.analyze";
#define MR_FUNC_NAME _func_name_Member_operand_analyze
Returncode Member_operand_analyze(Member_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  if (!(NULL != (*mtype))) {
    CHECK(386, f_syntax_error(&(String){20, 19, "member with no type"}, self->_base.name));
  }
  self->prev_mtype = (*mtype);
  while (true) {
    CHECK(389, Var_map_find((*mtype)->members, self->_base.name, &(self->_base.mvar)))
    if (!(!(NULL != self->_base.mvar))) break;
    (*mtype) = (*mtype)->base_mtype;
    if (!(NULL != (*mtype))) {
      CHECK(392, f_syntax_error2(&(String){5, 4, "type"}, self->prev_mtype->name, &(String){14, 13, "has no member"}, self->_base.name));
    }
    self->_base.base_count = self->_base.base_count + 1;
  }
  self->prev_mtype = (*mtype);
  Mtype* prev_sub_mtype = (*sub_mtype);
  Mtype* basetype = (*mtype)->base_mtype;
  if ((*mtype)->generic_mtype == self->_base.mvar->mtype) {
    (*mtype) = (*sub_mtype);
    (*sub_mtype) = NULL;
    if ((NULL != exp->operator || NULL != self->_base._base.next) && (*mtype) != self->_base.mvar->mtype) {
      Cast_operand* cast = malloc(sizeof(Cast_operand));
      if (cast == NULL) RAISE(401)
      *((Func**)(cast)) = Cast_operand__dtl;
      cast->_base.next = self->_base._base.next;
      self->_base._base.next = NULL;
      CHECK(404, (*((Func**)(cast)))[1](cast, exp, NULL, NULL, &((*mtype)), &((*sub_mtype))));
    }
    else {
      if ((*mtype) != self->_base.mvar->mtype && !(NULL != self->_base._base.next)) {
        exp->is_used = false;
      }
    }
  }
  else {
    if ((*mtype)->generic_mtype == self->_base.mvar->sub_mtype) {
      (*mtype) = self->_base.mvar->mtype;
      /* sub-mtype is the same */
    }
    else {
      (*mtype) = self->_base.mvar->mtype;
      (*sub_mtype) = self->_base.mvar->sub_mtype;
    }
  }
  if (NULL != self->_base._base.next) {
    if (NULL != self->_base.mvar->func_dec && NULL != member) {
      Bool _Bool5;
      CHECK(415, f_is_func_dynamic(self->_base.mvar->func_dec, &(_Bool5)))
      if (_Bool5 && self->_base.allow_dynamic) {
        while (true) {
          if (!(NULL != basetype)) break;
          self->_base.base_count = self->_base.base_count + 1;
          basetype = basetype->base_mtype;
        }
      }
      (*mtype) = self->prev_mtype;
      (*sub_mtype) = prev_sub_mtype;
      CHECK(422, (*((Func**)(self->_base._base.next)))[1](self->_base._base.next, exp, member, &(self->_base), &((*mtype)), &((*sub_mtype))));
    }
    else {
      CHECK(424, (*((Func**)(self->_base._base.next)))[1](self->_base._base.next, exp, &(self->_base._base), &(self->_base), &((*mtype)), &((*sub_mtype))));
    }
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Member_operand_write_intro = "Member-operand.write-intro";
#define MR_FUNC_NAME _func_name_Member_operand_write_intro
Returncode Member_operand_write_intro(Member_operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Member_operand_write_final = "Member-operand.write-final";
#define MR_FUNC_NAME _func_name_Member_operand_write_final
Returncode Member_operand_write_final(Member_operand* self) {
  if (NULL != self->_base.mvar->func_dec) {
    CHECK(431, write_cstyle(self->prev_mtype->name));
    CHECK(432, write(&(String){2, 1, "_"}));
  }
  else {
    CHECK(434, write(&(String){3, 2, "->"}));
    Int n; for (n = 0; n < self->_base.base_count; ++n) {
      CHECK(436, write(&(String){7, 6, "_base."}));
    }
  }
  CHECK(437, Var_operand_write_final(&(self->_base)));
  return OK;
}
#undef MR_FUNC_NAME
Func Member_operand__dtl[] = {Member_operand_parse, Member_operand_analyze, Member_operand_write_intro, Member_operand_write_final};


typedef struct Base_meth_operand Base_meth_operand; struct Base_meth_operand {
  Operand _base;
  Member_operand* member;
  Bool first;
};
static char* _func_name_Base_meth_operand_parse = "Base-meth-operand.parse";
#define MR_FUNC_NAME _func_name_Base_meth_operand_parse
Returncode Base_meth_operand_parse(Base_meth_operand* self, String* text, String* ends, Char* end) {
  free(text);
  Member_operand* member = malloc(sizeof(Member_operand));
  if (member == NULL) RAISE(446)
  *((Func**)(member)) = Member_operand__dtl;
  self->member = member;
  CHECK(448, (*((Func**)(self->member)))[0](self->member, NULL, ends, &((*end))));
  self->member->_base._base.next = NULL;
  self->member->_base.allow_dynamic = false;
  if ((*end) != '(') {
    CHECK(452, f_syntax_error(&(String){13, 12, "not a method"}, self->member->_base.mvar->name));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Base_meth_operand_analyze = "Base-meth-operand.analyze";
#define MR_FUNC_NAME _func_name_Base_meth_operand_analyze
Returncode Base_meth_operand_analyze(Base_meth_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  (*sub_mtype) = NULL;
  self->first = !(NULL != member);
  if (self->first) {
    Mvar* mvar;
    CHECK(459, f_find_var(&(String){5, 4, "self"}, &(mvar)))
    if (!(NULL != mvar)) {
      CHECK(460, f_syntax_error(&(String){25, 24, "not a method, cannot use"}, &(String){5, 4, "base"}));
    }
    (*mtype) = mvar->mtype;
  }
  if (!(NULL != (*mtype)->base_mtype)) {
    CHECK(463, f_syntax_error(&(String){20, 19, "no subtype for type"}, (*mtype)->name));
  }
  (*mtype) = (*mtype)->base_mtype;
  CHECK(465, (*((Func**)(self->member)))[1](self->member, exp, &(self->_base), NULL, &((*mtype)), &((*sub_mtype))));
  self->member->_base.base_count = self->member->_base.base_count + 1;
  CHECK(467, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, &(self->_base), &(self->member->_base), &((*mtype)), &((*sub_mtype))));
  self->member = NULL;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Base_meth_operand_write_intro = "Base-meth-operand.write-intro";
#define MR_FUNC_NAME _func_name_Base_meth_operand_write_intro
Returncode Base_meth_operand_write_intro(Base_meth_operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Base_meth_operand_write_final = "Base-meth-operand.write-final";
#define MR_FUNC_NAME _func_name_Base_meth_operand_write_final
Returncode Base_meth_operand_write_final(Base_meth_operand* self) {
  if (self->first) {
    CHECK(475, write(&(String){5, 4, "self"}));
  }
  return OK;
}
#undef MR_FUNC_NAME
Func Base_meth_operand__dtl[] = {Base_meth_operand_parse, Base_meth_operand_analyze, Base_meth_operand_write_intro, Base_meth_operand_write_final};


typedef struct Type_operand Type_operand; struct Type_operand {
  Operand _base;
  String* name;
  Mtype* mtype;
};
static char* _func_name_Type_operand_parse = "Type-operand.parse";
#define MR_FUNC_NAME _func_name_Type_operand_parse
Returncode Type_operand_parse(Type_operand* self, String* text, String* ends, Char* end) {
  self->name = text;
  self->mtype = NULL;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Type_operand_analyze = "Type-operand.analyze";
#define MR_FUNC_NAME _func_name_Type_operand_analyze
Returncode Type_operand_analyze(Type_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  CHECK(487, f_find_type(self->name, &((*mtype))));
  if (NULL != self->_base.next) {
    (*sub_mtype) = NULL;
    exp->operand = self->_base.next;
    CHECK(491, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, member, method, &((*mtype)), &((*sub_mtype))));
    free(self);
  }
  else {
    self->mtype = (*mtype);
    (*mtype) = glob->type_type;
    (*sub_mtype) = self->mtype;
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Type_operand_write_intro = "Type-operand.write-intro";
#define MR_FUNC_NAME _func_name_Type_operand_write_intro
Returncode Type_operand_write_intro(Type_operand* self) {
  /* nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Type_operand_write_final = "Type-operand.write-final";
#define MR_FUNC_NAME _func_name_Type_operand_write_final
Returncode Type_operand_write_final(Type_operand* self) {
  /* (Type){sizeof(name), name__dtl} */
  CHECK(503, write(&(String){8, 7, "(Type){"}));
  CHECK(504, write_type_type_params(self->mtype));
  CHECK(505, write(&(String){2, 1, "}"}));
  return OK;
}
#undef MR_FUNC_NAME
Func Type_operand__dtl[] = {Type_operand_parse, Type_operand_analyze, Type_operand_write_intro, Type_operand_write_final};


typedef struct Slice_operand Slice_operand; struct Slice_operand {
  Operand _base;
  Mexp* index;
  Mexp* second_index;
  Operand* seq;
  Mtype* seq_type;
  Mtype* item_type;
};
static char* _func_name_Slice_operand_parse = "Slice-operand.parse";
#define MR_FUNC_NAME _func_name_Slice_operand_parse
Returncode Slice_operand_parse(Slice_operand* self, String* text, String* ends, Char* end) {
  CHECK(516, parse_new_exp(&(String){3, 2, ":]"}, &(self->index), &((*end))));
  if ((*end) == ':') {
    CHECK(518, parse_new_exp(&(String){3, 2, ":]"}, &(self->second_index), &((*end))));
  }
  else {
    self->second_index = NULL;
  }
  if ((*end) != ']') {
    CHECK(522, f_syntax_error(&(String){8, 7, "missing"}, &(String){2, 1, "]"}));
  }
  CHECK(523, read_c(&((*end))));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Slice_operand_analyze = "Slice-operand.analyze";
#define MR_FUNC_NAME _func_name_Slice_operand_analyze
Returncode Slice_operand_analyze(Slice_operand* self, Mexp* exp, Operand* member, Var_operand* method, Mtype** mtype, Mtype** sub_mtype) {
  self->seq_type = (*mtype);
  self->item_type = (*sub_mtype);
  if (self->seq_type != glob->type_array && self->seq_type != glob->type_string) {
    CHECK(529, f_syntax_error(&(String){19, 18, "non-sliceable type"}, self->seq_type->name));
  }
  if (!(NULL != self->second_index)) {
    (*sub_mtype) = NULL;
    if (self->seq_type == glob->type_string) {
      (*mtype) = glob->type_char;
    }
    else {
      if (NULL != self->item_type) {
        (*mtype) = self->item_type;
      }
      else {
        CHECK(537, f_syntax_error(&(String){27, 26, "missing sub-type for array"}, &(String){1, 0, ""}));
      }
    }
  }
  
  self->seq = exp->operand;
  exp->operand = &(self->_base);
  member->next = NULL;
  
  CHECK(543, Mexp_analyze_type(self->index, glob->type_int));
  if (NULL != self->second_index) {
    CHECK(545, Mexp_analyze_type(self->second_index, glob->type_int));
  }
  
  if (NULL != self->_base.next) {
    CHECK(548, (*((Func**)(self->_base.next)))[1](self->_base.next, exp, &(self->_base), NULL, &((*mtype)), &((*sub_mtype))));
  }
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Slice_operand_write_intro = "Slice-operand.write-intro";
#define MR_FUNC_NAME _func_name_Slice_operand_write_intro
Returncode Slice_operand_write_intro(Slice_operand* self) {
  CHECK(551, Mexp_write_intro(self->index));
  if (NULL != self->second_index) {
    CHECK(553, Mexp_write_intro(self->second_index));
  }
  CHECK(554, Operand_write_all_intro(self->seq));
  /* if ((index) < 0 || (index) >= (seq)->length) RAISE(line-num) */
  /* if ((index) < 0 || (second) < 0 || (index) + (second) > (seq)->length) RAISE(line-num) */
  CHECK(557, write(&(String){6, 5, "if (("}));
  CHECK(558, Mexp_write_final(self->index));
  CHECK(559, write(&(String){11, 10, ") < 0 || ("}));
  if (NULL != self->second_index) {
    CHECK(561, Mexp_write_final(self->second_index));
    CHECK(562, write(&(String){11, 10, ") < 0 || ("}));
  }
  CHECK(563, Mexp_write_final(self->index));
  CHECK(564, write(&(String){3, 2, ") "}));
  if (NULL != self->second_index) {
    CHECK(566, write(&(String){4, 3, "+ ("}));
    CHECK(567, Mexp_write_final(self->second_index));
    CHECK(568, write(&(String){4, 3, ") >"}));
  }
  else {
    CHECK(570, write(&(String){3, 2, ">="}));
  }
  CHECK(571, write(&(String){3, 2, " ("}));
  CHECK(572, Operand_write_all_final(self->seq));
  CHECK(573, write(&(String){12, 11, ")->length) "}));
  CHECK(574, write_tb_raise());
  CHECK(575, write_new_indent_line());
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_Slice_operand_write_final = "Slice-operand.write-final";
#define MR_FUNC_NAME _func_name_Slice_operand_write_final
Returncode Slice_operand_write_final(Slice_operand* self) {
  /* ((Prmitive*)((seq)->values))[index] */
  /* ((Complex*)((seq)->values)) + index */
  /* &(Array){second, ((Type*)((seq)->values)) + (index)} */
  /* &(String){second, second, (seq)->values + (index)} */
  CHECK(582, write(&(String){2, 1, "("}));
  if (NULL != self->second_index) {
    CHECK(584, write(&(String){3, 2, "&("}));
    CHECK(585, write_cstyle(self->seq_type->name));
    CHECK(586, write(&(String){3, 2, "){"}));
    CHECK(587, Mexp_write_final(self->second_index));
    CHECK(588, write(&(String){3, 2, ", "}));
    if (self->seq_type == glob->type_string) {
      CHECK(590, Mexp_write_final(self->second_index));
      CHECK(591, write(&(String){3, 2, ", "}));
    }
  }
  if (NULL != self->item_type) {
    CHECK(593, write(&(String){3, 2, "(("}));
    CHECK(594, write_cstyle(self->item_type->name));
    CHECK(595, write(&(String){4, 3, "*)("}));
  }
  CHECK(596, write(&(String){2, 1, "("}));
  CHECK(597, Operand_write_all_final(self->seq));
  CHECK(598, write(&(String){10, 9, ")->values"}));
  if (NULL != self->item_type) {
    CHECK(600, write(&(String){3, 2, "))"}));
  }
  if (NULL != self->second_index) {
    CHECK(602, write(&(String){5, 4, " + ("}));
    CHECK(603, Mexp_write_final(self->index));
    CHECK(604, write(&(String){3, 2, ")}"}));
  }
  else {
    if (NULL != self->item_type && !self->item_type->is_primitive) {
      CHECK(606, write(&(String){4, 3, " + "}));
      CHECK(607, Mexp_write_final(self->index));
    }
    else {
      CHECK(609, write(&(String){2, 1, "["}));
      CHECK(610, Mexp_write_final(self->index));
      CHECK(611, write(&(String){2, 1, "]"}));
    }
  }
  CHECK(612, write(&(String){2, 1, ")"}));
  return OK;
}
#undef MR_FUNC_NAME
Func Slice_operand__dtl[] = {Slice_operand_parse, Slice_operand_analyze, Slice_operand_write_intro, Slice_operand_write_final};


typedef struct St_exp St_exp; struct St_exp {
  St _base;
  Mexp* exp;
};
static char* _func_name_St_exp_parse = "St-exp.parse";
#define MR_FUNC_NAME _func_name_St_exp_parse
Returncode St_exp_parse(St_exp* self) {
  Char _Char6;
  CHECK(619, parse_new_exp_with_kw(&(String){1, 0, ""}, &(self->exp), &(_Char6)));
  self->exp->is_used = false;
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_exp_analyze_first = "St-exp.analyze-first";
#define MR_FUNC_NAME _func_name_St_exp_analyze_first
Returncode St_exp_analyze_first(St_exp* self) {
  /* do nothing */
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_exp_analyze = "St-exp.analyze";
#define MR_FUNC_NAME _func_name_St_exp_analyze
Returncode St_exp_analyze(St_exp* self) {
  Mtype* mtype = NULL;
  Mtype* sub_mtype = NULL;
  CHECK(628, Mexp_analyze(self->exp, &(mtype), &(sub_mtype)));
  return OK;
}
#undef MR_FUNC_NAME
static char* _func_name_St_exp_write = "St-exp.write";
#define MR_FUNC_NAME _func_name_St_exp_write
Returncode St_exp_write(St_exp* self) {
  CHECK(631, Mexp_write_intro(self->exp));
  CHECK(632, Mexp_write_final(self->exp));
  if (!self->exp->is_used) {
    CHECK(634, write(&(String){2, 1, ";"}));
  }
  return OK;
}
#undef MR_FUNC_NAME
Func St_exp__dtl[] = {St_exp_parse, St_exp_analyze_first, St_exp_analyze, St_exp_write};

#undef MR_FILE_NAME
