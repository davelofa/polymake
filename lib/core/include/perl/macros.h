/* Copyright (c) 1997-2017
   Ewgenij Gawrilow, Michael Joswig (Technische Universitaet Berlin, Germany)
   http://www.polymake.org

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version: http://www.gnu.org/licenses/gpl.txt.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
--------------------------------------------------------------------------------
*/

#ifndef POLYMAKE_PERL_MACROS_H
#define POLYMAKE_PERL_MACROS_H

/* The following macros are designed to be used in the files automatically generated by polymake.
   If you use them in the manually written code, you are doing it on your own risk!

   The changes in syntax and contents must be concerted with the corresponding routines
   in the package Polymake::Core::CPlusPlus
*/

#define Class4perl(pkg, ...) \
   template<> polymake::perl_bindings::Class< __VA_ARGS__ > \
   StaticRegistrator4perl<polymake::perl_bindings::Class< __VA_ARGS__ >,__LINE__>::r(pkg,__FILE__,__LINE__)

#define Builtin4perl(pkg, ...) \
   template<> pm::perl::Builtin< __VA_ARGS__ > \
   StaticRegistrator4perl<pm::perl::Builtin< __VA_ARGS__ >,__LINE__>::r(pkg,__FILE__,__LINE__)

#define ClassTemplate4perl(pkg) \
   template<> pm::perl::ClassTemplate \
   StaticRegistrator4perl<pm::perl::ClassTemplate,__LINE__>::r(pkg)

#define RegisterFunctionInstance4perl(reg_arg, ...) \
   template<> __VA_ARGS__              \
   StaticRegistrator4perl<__VA_ARGS__,__LINE__>::r(__FILE__,__LINE__,reg_arg)

#define FirstArgAsString(first_arg_name,...) #first_arg_name

#define FunctionInstance4perl(f_class, ...) \
   RegisterFunctionInstance4perl(0,                                    Wrapper4perl_##f_class< __VA_ARGS__ >)
#define OperatorInstance4perl(op_class, ...) \
   RegisterFunctionInstance4perl(0,                                    pm::perl::Operator_##op_class< __VA_ARGS__ >)
#define FunctionCrossAppInstance4perl(f_class, app_list, ...) \
   RegisterFunctionInstance4perl(pm::perl::make_string_array app_list, Wrapper4perl_##f_class< __VA_ARGS__ >)
#define OperatorCrossAppInstance4perl(op_class, app_list, ...) \
   RegisterFunctionInstance4perl(pm::perl::make_string_array app_list, pm::perl::Operator_##op_class< __VA_ARGS__ >)

// not supported any longer
#define DisabledFunction4perl(name, ...) ObsoleteWrapper(DisabledFunction not supported: name(__VA_ARGS__))

#define WrapperStart(name, perlname, ...)                       \
struct name {                                                   \
   typedef pm::list arg_list(__VA_ARGS__);                      \
   template <typename first_arg_type>                \
   name(const AnyString& file, int line, first_arg_type arg0) { pm::perl::WrapperBase<name>::register_it(perlname, file, line, arg0); } \
   static SV* call(SV **stack __attribute__((unused)))

#define FunctionInterface4perl(name, ...) WrapperStart(Wrapper4perl_##name, #name, __VA_ARGS__)

#define FunctionWrapper4perl(...) \
   template <>                    \
   SV* IndirectFunctionWrapper<__VA_ARGS__>::call(fptr_type func, SV **stack __attribute__((unused)))

#define FunctionWrapperInstance4perl(...) \
   template<> IndirectFunctionWrapper<__VA_ARGS__> \
   StaticRegistrator4perl<IndirectFunctionWrapper<__VA_ARGS__>,__LINE__>::r(__FILE__,__LINE__)

#define WrapperCloseFunction } enum { _unused }

// __VA_ARGS__ = anchors
#define WrapperBodyWithValue(pkg, expr, ...)                         \
   perl::Value Result_Value(pm::perl::value_allow_non_persistent | pm::perl::value_allow_store_ref); \
   pkg;                                                              \
   Result_Value.put(expr, Prescribed_Result_Pkg, ## __VA_ARGS__);      \
   return Result_Value.get_temp()

#define WrapperBodyWithLvalue(pkg, ownerType, expr, ...)    \
   perl::Value Result_Value(                      \
         (pm::attrib<typename pm::perl::access<ownerType>::type>::is_const ? pm::perl::value_read_only : pm::perl::value_mutable) | \
         pm::perl::value_expect_lval | pm::perl::value_allow_non_persistent | pm::perl::value_allow_store_ref); \
   pkg;                                                              \
   Result_Value.put_lvalue(expr, Prescribed_Result_Pkg, &arg0, (ownerType*)nullptr, ## __VA_ARGS__); \
   return Result_Value.get()

#define WrapperBodyWithoutValue(expr) \
   expr;                           \
   return nullptr

#define IndirectWrapperReturn(...)     WrapperBodyWithValue(int Prescribed_Result_Pkg=0, func(__VA_ARGS__))
#define IndirectWrapperReturnVoid(...) WrapperBodyWithoutValue(func(__VA_ARGS__))

// stack in the wrappers points to the first given argument = now it's the first empty slot

#define WrapperReturnList(expr)              \
   pm::perl::ListSlurp Result_List(stack-1);        \
   WrapperBodyWithoutValue(Result_List << (expr));  \
   WrapperCloseFunction

#define WrapperReturnPkg(...) \
   WrapperBodyWithValue(SV* Prescribed_Result_Pkg=stack[0], __VA_ARGS__);   WrapperCloseFunction
#define WrapperReturn(...) \
   WrapperBodyWithValue(int Prescribed_Result_Pkg=0,        __VA_ARGS__);   WrapperCloseFunction

#define WrapperReturnLvaluePkg(ownerType, ...) \
   WrapperBodyWithLvalue(SV* Prescribed_Result_Pkg=stack[0], ownerType, __VA_ARGS__);      WrapperCloseFunction
#define WrapperReturnLvalue(ownerType, ...) \
   WrapperBodyWithLvalue(int Prescribed_Result_Pkg=0,        ownerType, __VA_ARGS__);      WrapperCloseFunction

// deprecated:
#define WrapperReturnAnchPkg(n_anchors, anchors, expr)                    return nullptr; WrapperCloseFunction
#define WrapperReturnAnch(n_anchors, anchors, expr)                       return nullptr; WrapperCloseFunction
#define WrapperReturnLvalueAnchPkg(n_anchors, anchors, ownerType, expr)   return nullptr; WrapperCloseFunction
#define WrapperReturnLvalueAnch(n_anchors, anchors, ownerType, expr)      return nullptr; WrapperCloseFunction

#define WrapperReturnVoid(expr)    WrapperBodyWithoutValue(expr);  WrapperCloseFunction

#define WrapperReturnNew(Type, expr)                           \
   perl::Value Result_Value;                                   \
   SV* const Result_Proto=stack[0];                            \
   new(Result_Value.allocate<Type>(Result_Proto)) Type expr;   \
   return Result_Value.get_constructed_canned();               \
   WrapperCloseFunction

// the following macro calls can only be produced on the fly by the script guarded_compiler.pl

#define ThrowObsoleteWrapper(file, line, text) return pm::perl::complain_obsolete_wrapper(file,line,text); WrapperCloseFunction

#define ObsoleteWrapper(expr)                ThrowObsoleteWrapper(__FILE__, __LINE__, #expr)
#define ObsoleteWrapperLvalue(skip,...)      ThrowObsoleteWrapper(__FILE__, __LINE__, #__VA_ARGS__)
#define ObsoleteWrapperNew(Type,expr)        ThrowObsoleteWrapper(__FILE__, __LINE__, FirstArgAsString(new Type expr))

// ---

#define Wrapper4UnaryOperator(sign, name)                \
template <typename Arg0>                                 \
WrapperStart( Operator_Unary_##name, "." #name, Arg0 ) { \
   Value arg0(stack[0]);                                 \
   WrapperReturn( sign( arg0.get<Arg0>() ) );            \
}

#define Wrapper4UnaryAnchOperator(sign, name)                    \
template <typename Arg0>                                         \
WrapperStart( Operator_Unary_##name##a, "." #name "a" , Arg0 ) { \
   Value arg0(stack[0]);                                         \
   WrapperReturn( sign( arg0.get<Arg0>() ), arg0);        \
}

#define Wrapper4UnaryAssignOperator(sign, name)                \
template <typename Arg0>                                       \
WrapperStart( Operator_UnaryAssign_##name, "." #name, Arg0 ) { \
   Value arg0(stack[0]);                                       \
   WrapperReturnLvalue( Arg0, sign( arg0.get<Arg0>() ) );      \
}

#define Wrapper4BinaryOperator(sign, name)                     \
template <typename Arg0, typename Arg1>                        \
WrapperStart( Operator_Binary_##name, ":" #name, Arg0,Arg1 ) { \
   Value arg0(stack[0]), arg1(stack[1]);                       \
   WrapperReturn( arg0.get<Arg0>() sign arg1.get<Arg1>() );    \
}

#define Wrapper4BinaryAnchOperator(sign, name)                 \
template <typename Arg0, typename Arg1>                        \
WrapperStart( Operator_Binary_##name##a, ":" #name "a", Arg0,Arg1 ) { \
   Value arg0(stack[0]), arg1(stack[1]);                       \
   WrapperReturn( arg0.get<Arg0>() sign arg1.get<Arg1>(), arg0, arg1); \
}

#define Wrapper4BinaryAssignOperator(sign, name)                        \
template <typename Arg0, typename Arg1>                                 \
WrapperStart( Operator_BinaryAssign_##name, "=" #name, Arg0,Arg1 ) {    \
   Value arg0(stack[0]), arg1(stack[1]);                                \
   WrapperReturnLvalue( Arg0, arg0.get<Arg0>() sign arg1.get<Arg1>() ); \
}

#ifdef POLYMAKE_NO_EMBEDDED_RULES
// module with wrapper code only; proper definitions are located in core or another extension
# define DeclareEmbeddedFunction(...) namespace { }
# define InsertEmbeddedRule(...) namespace { }
#else

# define DeclareEmbeddedFunction(pre, fptr, decl) \
namespace {                                       \
   template<> pm::perl::Function                  \
   StaticRegistrator4perl<pm::perl::Function,__LINE__>::r(fptr,__FILE__,__LINE__, pre " " decl " : c++ (embedded=>%d);\n"); \
}

# define InsertEmbeddedRule(text)                                                      \
namespace {                                                                            \
   template<> pm::perl::EmbeddedRule                                                   \
   StaticRegistrator4perl<pm::perl::EmbeddedRule,__LINE__>::r(__FILE__,__LINE__,text); \
}

#endif

#define Function4perl(fptr, decl)                DeclareEmbeddedFunction(            "function",fptr,decl)
#define UserFunction4perl(help, fptr, decl)      DeclareEmbeddedFunction(help "\nuser_function",fptr,decl)

#define FunctionTemplate4perl(decl)                InsertEmbeddedRule("function " decl " : c++;\n")
#define UserFunctionTemplate4perl(help, decl)      InsertEmbeddedRule(help "\nuser_function " decl " : c++;\n")

#define FullPackage4perl(pkg, app) "Polymake::" FirstArgAsString(app) "::" pkg

#define OpaqueClass4perl(pkg, name, methods)                                        \
namespace {                                                                         \
  Class4perl(FullPackage4perl(pkg, POLYMAKE_APPNAME), name);                        \
}                                                                                   \
InsertEmbeddedRule("# @hide\n"                                                      \
                   "declare property_type " pkg " : c++ (special=>'" #name "') {\n" \
                   methods                                                          \
                   "}\n")

#define OpaqueMethod4perl(decl) "\nmethod " decl " : c++;\n"

#define RecognizeType4perl(name, typelist, ...) inline                                                  \
recognized<std::is_same<T, __VA_ARGS__ >::value>* recognize(pm::perl::type_infos& ti, bait*, T*, __VA_ARGS__*) \
{                                                                                                       \
   if (SV* proto=pm::perl::get_parameterized_type<pm::list typelist>(name, std::is_same<T, __VA_ARGS__ >())) \
      ti.set_proto(proto);                                              \
   return nullptr;                                                      \
}

// deprecated macros

#define CallPolymakeFunction(name, ...) \
polymake::call_function_deprecated(name, ## __VA_ARGS__)

#define CallPolymakeMethod(name, ...) \
call_method_deprecated(name, ## __VA_ARGS__)

#define ListCallPolymakeFunction(...) CallPolymakeFunction(__VA_ARGS__)
#define ListCallPolymakeMethod(...) CallPolymakeMethod(__VA_ARGS__)
#define VoidCallPolymakeFunction(...) CallPolymakeFunction(__VA_ARGS__)
#define VoidCallPolymakeMethod(...) CallPolymakeMethod(__VA_ARGS__)

#endif // POLYMAKE_MACROS_H

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
