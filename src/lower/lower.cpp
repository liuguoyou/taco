#include "taco/lower/lower.h"

#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "taco/index_notation/index_notation.h"
#include "taco/index_notation/index_notation_nodes.h"

#include "taco/ir/ir.h"
#include "taco/ir/simplify.h"
#include "ir/ir_generators.h"

#include "taco/lower/lowerer_impl.h"
#include "iterator.h"
#include "mode_access.h"
#include "merge_lattice.h"

#include "error/error_checks.h"
#include "taco/error/error_messages.h"
#include "taco/util/name_generator.h"
#include "taco/util/collections.h"
#include "taco/util/strings.h"

using namespace std;
using namespace taco::ir;

namespace taco {


// class Lowerer
Lowerer::Lowerer() : impl(new LowererImpl()) {
}

Lowerer::Lowerer(LowererImpl* impl) : impl(impl) {
}

std::shared_ptr<LowererImpl> Lowerer::getLowererImpl() {
  return impl;
}

ir::Stmt lower(IndexStmt stmt, std::string name, bool assemble, bool compute,
               Lowerer lowerer) {
  taco_iassert(isLowerable(stmt));
  return lowerer.getLowererImpl()->lower(stmt, name, assemble, compute);
}


bool isLowerable(IndexStmt stmt, std::string* reason) {
  INIT_REASON(reason);

  // Must be concrete index notation
  if (!isConcreteNotation(stmt)) {
    *reason = "The index statement is not in concrete index notation";
    return false;
  }

  // Check for transpositions
//  if (!error::containsTranspose(this->getFormat(), freeVars, indexExpr)) {
//    *reason = error::expr_transposition;
//  }

  return true;
}

}
