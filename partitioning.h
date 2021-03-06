#ifndef PARTITIONING_H_
#define PARTITIONING_H_

#include <vector>
#include <set>
#include <map>

#include "clang/AST/Expr.h"
#include "clang/AST/Decl.h"

#include "graph.h"

/// Typedef for a set of BinaryOperator's sequenced one after the other
typedef std::vector<const clang::BinaryOperator *> InstBlock;

/// Typedef for a data structure mapping
/// from stage_id + atom_id
/// to InstBlock
/// for diagramming them out in a dot file
typedef std::map<uint32_t, std::map<uint32_t, InstBlock>> PipelineDrawing;

/// Printer for an InstBlock
std::string inst_block_printer(const InstBlock & iblock);

/// Identify statements that read from and write to state
/// And create a back edge from the write back to the read.
/// This is really the crux of the compiler:
/// back edges from stateful writes to the next stateful read.
Graph<const clang::BinaryOperator *> handle_state_vars(const std::vector<const clang::BinaryOperator *> & stmt_vector, const Graph<const clang::BinaryOperator*> & dep_graph);

/// Does a particular operation read a variable
bool op_reads_var(const clang::BinaryOperator * op, const clang::Expr * var);

/// Is there a dependence from op1 to op2?
/// Requiring op1 to be executed before op2?
bool depends(const clang::BinaryOperator * op1, const clang::BinaryOperator * op2);

/// Print out dependency graph once Stongly Connected Components
/// have been condensed together to form a DAG.
/// Also partition the code based on the dependency graph
/// and generate a function declaration with a body for each partition
/// as a string for each timestamp
std::map<uint32_t, std::vector<InstBlock>> generate_partitions(const clang::CompoundStmt * function_body);

/// Return pipeline diagram as a dot file
std::string draw_pipeline(const PipelineDrawing & atoms_for_drawing, const Graph<InstBlock> & condensed_graph);

/// Entry point to partitioning logic, called by SinglePass
std::string partitioning_transform(const clang::TranslationUnitDecl * tu_decl, const uint32_t pipeline_depth, const uint32_t pipeline_width);

#endif  // PARTITIONING_H_
