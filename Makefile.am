SUBDIRS = third_party . tests

AM_CXXFLAGS = $(PICKY_CXXFLAGS)
AM_CPPFLAGS = -isystem $(CLANG_DEV_LIBS)/include/
AM_LDFLAGS = -L $(CLANG_DEV_LIBS)/lib

# There are some strange circular deps within clang requiring us to list libraries twice
# https://github.com/eliben/llvm-clang-samples/blob/master/Makefile#L71
CLANG_LLVM_LIBS = -lclangAST -lclangAnalysis -lclangBasic -lclangDriver -lclangEdit -lclangFrontend -lclangFrontendTool -lclangLex -lclangParse -lclangSema -lclangSerialization\
                  -lclangAST -lclangAnalysis -lclangBasic -lclangDriver -lclangEdit -lclangFrontend -lclangFrontendTool -lclangLex -lclangParse -lclangSema -lclangSerialization\
                  -lLLVMOption  -lLLVMMCParser -lLLVMBitReader  -lLLVMMC -lLLVMSupport -lz -lpthread -ltermcap -ldl

common_source = clang_utility_functions.cc  clang_utility_functions.h unique_identifiers.h unique_identifiers.cc pkt_func_transform.h pkt_func_transform.cc graph.h expr_flattener_handler.cc expr_flattener_handler.h expr_prop.cc stateful_flanks.cc ssa.cc partitioning.cc if_conversion_handler.cc if_conversion_handler.h ssa.h partitioning.h stateful_flanks.h expr_prop.h pisa_code_generator.h pisa_code_generator.cc util.cc util.h pisa_atom.h pisa_atom.cc assert_exception.h desugar_compound_assignment.h desugar_compound_assignment.cc int_type_checker.h algebraic_simplifier.cc algebraic_simplifier.h array_validator.h redundancy_remover.cc redundancy_remover.h sketch_backend.cc sketch_backend.h csi.cc csi.h cse.cc cse.h gen_used_fields.cc gen_used_fields.h validator.h p4_backend.cc p4_backend.h p4_atom.cc p4_atom.h bool_to_int.h ast_visitor.cc ast_visitor.h

noinst_LIBRARIES = libdomino.a
bin_PROGRAMS = domino domino_to_p4

libdomino_a_SOURCES = $(common_source)

domino_CXXFLAGS = $(PICKY_CXXFLAGS) -fno-rtti
domino_SOURCES = domino.cc
domino_LDADD = $(CLANG_LLVM_LIBS) libdomino.a $(srcdir)/third_party/libmahimahi.a

domino_to_p4_CXXFLAGS = $(PICKY_CXXFLAGS) -fno-rtti
domino_to_p4_SOURCES = domino_to_p4.cc
domino_to_p4_LDADD = $(CLANG_LLVM_LIBS) libdomino.a $(srcdir)/third_party/libmahimahi.a
