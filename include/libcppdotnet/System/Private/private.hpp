#pragma once

// For marking unused expressions (and keeping compilers quieter)
#define UNUSED(expr) do { (void)expr; } while (0)

#define ASSERT(expr)

#define PRECONDITION(expr) ASSERT(expr)
#define POSTCONDITION(expr) ASSERT(expr)
#define INVARIANT(expr) ASSERT(expr)

#define IMPLIES(a, b) (!(a) || (b))
