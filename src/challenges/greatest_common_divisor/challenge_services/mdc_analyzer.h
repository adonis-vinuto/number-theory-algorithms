/**
 * @file mdc_analyzer.h
 * @brief GCD algorithm analyzer and comparison service
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This header defines analysis and comparison services for GCD algorithms.
 * Provides simple ways to execute, compare, and validate GCD implementations.
 */

#ifndef MDC_ANALYZER_H
#define MDC_ANALYZER_H

#include "../challenge_definition.h"
#include "../../../core/domain/mathematical_types.h"
#include "../domain_types.h"
#include <stdbool.h>

// ============================================================================
// ALGORITHM EXECUTION
// ============================================================================

/**
 * @brief Execute a specific GCD algorithm by variant
 *
 * @param variant Which algorithm to execute
 * @param a First operand
 * @param b Second operand
 * @return MathResult with timing and result
 */
MathResult mdc_analyzer_execute_algorithm(GcdAlgorithmVariant variant, GcdInteger a, GcdInteger b);

/**
 * @brief Execute all available GCD algorithms and compare results
 *
 * @param a First operand
 * @param b Second operand
 * @param results Array to store results (must have space for all algorithms)
 * @param max_results Maximum number of results to store
 * @return Number of algorithms executed
 */
MathNatural mdc_analyzer_execute_all(GcdInteger a, GcdInteger b, MathResult *results, MathNatural max_results);

/**
 * @brief Execute Extended Euclidean algorithm with full result
 *
 * @param a First operand
 * @param b Second operand
 * @param x Pointer to store coefficient for a
 * @param y Pointer to store coefficient for b
 * @return ExtendedGcdResult with GCD and coefficients
 */
ExtendedGcdResult mdc_analyzer_execute_extended(GcdInteger a, GcdInteger b, GcdInteger *x, GcdInteger *y);

// ============================================================================
// RESULT VALIDATION
// ============================================================================

/**
 * @brief Validate that a GCD result is mathematically correct
 *
 * @param a First operand
 * @param b Second operand
 * @param result Computed GCD result
 * @return true if result is correct
 */
bool mdc_analyzer_validate_result(GcdInteger a, GcdInteger b, GcdInteger result);

/**
 * @brief Compare all algorithm results for consistency
 *
 * @param a First operand
 * @param b Second operand
 * @param results Array of results from different algorithms
 * @param result_count Number of results
 * @return true if all results are consistent
 */
bool mdc_analyzer_validate_consistency(GcdInteger a, GcdInteger b, const MathResult *results, MathNatural result_count);

// ============================================================================
// PERFORMANCE ANALYSIS
// ============================================================================

/**
 * @brief Find the fastest algorithm for given input
 *
 * @param a First operand
 * @param b Second operand
 * @param fastest_variant Pointer to store the fastest variant
 * @return Execution time of fastest algorithm, or -1.0 on error
 */
double mdc_analyzer_find_fastest(GcdInteger a, GcdInteger b, GcdAlgorithmVariant *fastest_variant);

/**
 * @brief Get algorithm name from variant
 *
 * @param variant Algorithm variant
 * @return Human-readable algorithm name
 */
const char *mdc_analyzer_get_algorithm_name(GcdAlgorithmVariant variant);

// ============================================================================
// SIMPLE BENCHMARKING
// ============================================================================

/**
 * @brief Run simple benchmark comparing algorithm performance
 *
 * @param a First operand
 * @param b Second operand
 * @param iterations Number of times to run each algorithm
 * @param results Array to store benchmark results
 * @param max_results Maximum number of results
 * @return Number of algorithms benchmarked
 */
MathNatural mdc_analyzer_benchmark(GcdInteger a, GcdInteger b, MathNatural iterations, MathResult *results, MathNatural max_results);

// ============================================================================
// CONSOLE OUTPUT HELPERS
// ============================================================================

/**
 * @brief Print comparison results to console
 *
 * @param a First operand
 * @param b Second operand
 * @param results Array of results from different algorithms
 * @param result_count Number of results
 */
void mdc_analyzer_print_comparison(GcdInteger a, GcdInteger b, const MathResult *results, MathNatural result_count);

/**
 * @brief Print Extended GCD result to console
 *
 * @param a First operand
 * @param b Second operand
 * @param ext_result Extended GCD result
 */
void mdc_analyzer_print_extended_result(GcdInteger a, GcdInteger b, const ExtendedGcdResult *ext_result);

#endif // MDC_ANALYZER_H