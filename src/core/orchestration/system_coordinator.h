/**
 * @file system_coordinator.h
 * @brief Main system coordinator for the Number Theory Algorithm Analysis System
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This header defines the main coordinator interface that ties together all
 * components of the GCD algorithm analysis system. Provides a unified
 * interface for executing, comparing, and analyzing GCD algorithms.
 */

#ifndef SYSTEM_COORDINATOR_H
#define SYSTEM_COORDINATOR_H

#include "../../core/domain/mathematical_types.h"
#include "../../challenges/greatest_common_divisor/domain_types.h"
#include "../../core/interfaces/implementation_interface.h"
#include <stdbool.h>

// ============================================================================
// SYSTEM INITIALIZATION
// ============================================================================

/**
 * @brief Initialize the entire GCD algorithm analysis system
 *
 * @return MATH_SUCCESS if initialization successful
 */
MathStatus system_init(void);

/**
 * @brief Check if system is initialized and ready
 *
 * @return true if system is ready to use
 */
bool system_is_ready(void);

/**
 * @brief Get system status information
 *
 * @param total_executions Pointer to store total execution count (optional)
 * @param total_time Pointer to store total execution time (optional)
 * @return true if system is ready
 */
bool system_get_status(MathNatural *total_executions, double *total_time);

// ============================================================================
// HIGH-LEVEL EXECUTION INTERFACE
// ============================================================================

/**
 * @brief Execute a GCD algorithm by variant (main interface)
 *
 * @param variant Algorithm variant to execute
 * @param a First operand
 * @param b Second operand
 * @return MathResult with computation result and timing
 */
MathResult system_execute_gcd(GcdAlgorithmVariant variant, GcdInteger a, GcdInteger b);

/**
 * @brief Execute a GCD algorithm by name (convenient interface)
 *
 * @param algorithm_name Name of algorithm to execute
 * @param a First operand
 * @param b Second operand
 * @return MathResult with computation result and timing
 */
MathResult system_execute_gcd_by_name(const char *algorithm_name, GcdInteger a, GcdInteger b);

/**
 * @brief Execute Extended Euclidean algorithm (convenience wrapper)
 *
 * @param a First operand
 * @param b Second operand
 * @param x Pointer to store coefficient for a
 * @param y Pointer to store coefficient for b
 * @return ExtendedGcdResult with GCD and coefficients
 */
ExtendedGcdResult system_execute_extended_gcd(GcdInteger a, GcdInteger b, GcdInteger *x, GcdInteger *y);

// ============================================================================
// COMPARISON AND ANALYSIS INTERFACE
// ============================================================================

/**
 * @brief Compare all available GCD algorithms (main comparison interface)
 *
 * @param a First operand
 * @param b Second operand
 * @param print_results Whether to print results to console
 * @return Number of algorithms compared
 */
MathNatural system_compare_all_algorithms(GcdInteger a, GcdInteger b, bool print_results);

/**
 * @brief Find the fastest algorithm for given input
 *
 * @param a First operand
 * @param b Second operand
 * @param print_results Whether to print results to console
 * @return The fastest algorithm variant
 */
GcdAlgorithmVariant system_find_fastest_algorithm(GcdInteger a, GcdInteger b, bool print_results);

/**
 * @brief Run simple benchmark comparing algorithms
 *
 * @param a First operand
 * @param b Second operand
 * @param iterations Number of iterations for each algorithm
 * @param print_results Whether to print results to console
 * @return Number of algorithms benchmarked
 */
MathNatural system_benchmark_algorithms(GcdInteger a, GcdInteger b, MathNatural iterations, bool print_results);

// ============================================================================
// INFORMATION AND LISTING INTERFACE
// ============================================================================

/**
 * @brief List all available algorithms
 *
 * @param print_details Whether to print detailed information
 */
void system_list_algorithms(bool print_details);

/**
 * @brief Get information about a specific algorithm
 *
 * @param variant Algorithm variant to describe
 * @param print_info Whether to print information to console
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *system_get_algorithm_info(GcdAlgorithmVariant variant, bool print_info);

// ============================================================================
// CONVENIENCE FUNCTIONS
// ============================================================================

/**
 * @brief Quick GCD computation using default algorithm (Euclidean Modulo)
 *
 * @param a First operand
 * @param b Second operand
 * @return GCD result, or MATH_INVALID_VALUE on error
 */
GcdInteger system_quick_gcd(GcdInteger a, GcdInteger b);

/**
 * @brief Validate that two algorithms produce the same result
 *
 * @param variant1 First algorithm variant
 * @param variant2 Second algorithm variant
 * @param a First operand
 * @param b Second operand
 * @return true if both algorithms produce the same result
 */
bool system_validate_algorithms(GcdAlgorithmVariant variant1, GcdAlgorithmVariant variant2, GcdInteger a, GcdInteger b);

// ============================================================================
// SYSTEM DIAGNOSTICS
// ============================================================================

/**
 * @brief Print system status and statistics
 */
void system_print_status(void);

/**
 * @brief Run system self-test
 *
 * @return true if all tests pass
 */
bool system_self_test(void);

#endif // SYSTEM_COORDINATOR_H