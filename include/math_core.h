/* 
 * Built by:
 * Harshitapreet Kaur (https://github.com/Harshita1204) (harshitak1204@gmail.com)
 * Pranav Sinha (https://github.com/Penguin5681) (pranavsinha922@gmail.com)
 *
 * Licensed under the MIT License.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* ── Version ──────────────────────────────────────────────────── */
#define MATH_CORE_VERSION_MAJOR 1
#define MATH_CORE_VERSION_MINOR 0
#define MATH_CORE_VERSION_PATCH 0

/* ── Opaque context ───────────────────────────────────────────── */

/**
 * Opaque handle. Holds all internal state (parser tables, SymEngine
 * session, etc.). Create one per thread. Not thread-safe.
 */
typedef struct MathContext MathContext;

/* ── Lifecycle ────────────────────────────────────────────────── */

/** Create a new context. Returns NULL on failure. */
MathContext* mc_create_context(void);

/** Destroy a context and free all its memory. */
void mc_destroy_context(MathContext* ctx);

/* ── Core operations ──────────────────────────────────────────── */

/**
 * Evaluate a LaTeX expression numerically or symbolically.
 *
 * Examples:
 *   "2 + 3"               → "5"
 *   "\frac{1}{2}+\frac{1}{3}" → "5/6"
 *   "x^2 + 2x + 1"        → "x^2 + 2*x + 1"  (no simplification here)
 *
 * Returns: 0 on success, non-zero on error.
 * On success: *out_result is a heap-allocated string. Free with mc_free_string().
 * On error:   *out_error  is a heap-allocated error message. Free with mc_free_string().
 * The caller always receives exactly one non-NULL pointer; the other is NULL.
 */
int mc_evaluate_latex(
    MathContext* ctx,
    const char*  latex,
    char**       out_result,
    char**       out_error
);

/**
 * Simplify a LaTeX expression algebraically.
 *
 * Examples:
 *   "x^2 + 2*x + 1"  → "(x + 1)^2"
 *   "\frac{x^2-1}{x-1}" → "x + 1"
 *
 * Returns: 0 on success, non-zero on error.
 * Same memory contract as mc_evaluate_latex.
 */
int mc_simplify_latex(
    MathContext* ctx,
    const char*  latex,
    char**       out_result,
    char**       out_error
);

/**
 * Differentiate a LaTeX expression with respect to a variable.
 *
 * Examples:
 *   latex="x^3 + 2*x", variable="x"  → "3*x^2 + 2"
 *   latex="\sin(x)",   variable="x"  → "\cos(x)"
 *
 * Returns: 0 on success, non-zero on error.
 * Same memory contract as mc_evaluate_latex.
 */
int mc_differentiate(
    MathContext* ctx,
    const char*  latex,
    const char*  variable,
    char**       out_result,
    char**       out_error
);

/**
 * Solve a LaTeX equation for a variable.
 *
 * Examples:
 *   latex="2*x + 3 = 7", variable="x"  → "x = 2"
 *   latex="x^2 - 4 = 0", variable="x"  → "x = 2, x = -2"
 *
 * Returns: 0 on success, non-zero on error.
 * Same memory contract as mc_evaluate_latex.
 */
int mc_solve_latex(
    MathContext* ctx,
    const char*  latex,
    const char*  variable,
    char**       out_result,
    char**       out_error
);

/* ── Memory ───────────────────────────────────────────────────── */

/**
 * Free any string returned by this library.
 * Never pass a pointer not returned by this library.
 * Never call twice on the same pointer.
 */
void mc_free_string(char* str);

/* ── Versioning ───────────────────────────────────────────────── */

/** Fill in the version numbers. */
void mc_get_version(int* major, int* minor, int* patch);

#ifdef __cplusplus
}
#endif