/**
 * @file stein.h
 * @brief Stein's binary GCD algorithm implementation
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This header declares Stein's binary GCD algorithm and its implementation specification.
 */

#ifndef STEIN_IMPLEMENTATIONS_H
#define STEIN_IMPLEMENTATIONS_H

#include "../../../../../core/interfaces/implementation_interface.h"
#include "../../../domain_types.h"

// ============================================================================
// ORIGINAL ALGORITHM DECLARATION
// ============================================================================

/**
 * @brief Stein's binary GCD algorithm
 *
 * @param a First operand
 * @param b Second operand
 * @return Greatest common divisor
 */
GcdInteger mdc_stein(GcdInteger a, GcdInteger b);

// ============================================================================
// INTERFACE IMPLEMENTATION
// ============================================================================

/**
 * @brief Execute Stein's binary GCD algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult stein_binary_compute(const MathBinaryInput *input);

// ============================================================================
// IMPLEMENTATION SPECIFICATION (EXTERN DECLARATION)
// ============================================================================

/**
 * @brief Implementation specification for Stein's binary GCD algorithm
 */
extern ImplementationSpec stein_binary_spec;

// ============================================================================
// BINARY ALGORITHM CHARACTERISTICS
// ============================================================================

/**
 * @brief Check if inputs are suitable for binary algorithms
 *
 * @param a First operand
 * @param b Second operand
 * @return true if inputs are suitable for binary algorithms
 */
bool stein_is_suitable_input(GcdInteger a, GcdInteger b);

/**
 * @brief Estimate performance advantage of Stein's over Euclidean
 *
 * @param a First operand
 * @param b Second operand
 * @return true if Stein's algorithm likely to be faster
 */
bool stein_likely_faster(GcdInteger a, GcdInteger b);

/**
 * @brief Count the number of iterations Stein's algorithm would perform
 *
 * @param a First operand
 * @param b Second operand
 * @return Estimated number of iterations
 */
MathNatural stein_estimate_iterations(GcdInteger a, GcdInteger b);

// ============================================================================
// FAMILY INTEGRATION FUNCTIONS
// ============================================================================

/**
 * @brief Get implementation specification by variant
 *
 * @param variant Algorithm variant
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *stein_get_implementation(GcdAlgorithmVariant variant);

/**
 * @brief Get all Stein (binary) implementations
 *
 * @param specs Array to store implementation specs
 * @param max_specs Maximum number of specs to return
 * @return Number of implementation specs returned
 */
MathNatural stein_get_all_implementations(
    const ImplementationSpec **specs,
    MathNatural max_specs);

/**
 * @brief Check if variant is Stein's binary algorithm
 *
 * @param variant Algorithm variant to check
 * @return true if variant is Stein's binary algorithm
 */
bool is_stein_variant(GcdAlgorithmVariant variant);

// ============================================================================
// DIRECT INTERFACE FOR CONVENIENCE
// ============================================================================

/**
 * @brief Direct interface to Stein's algorithm with basic error handling
 *
 * @param a First operand
 * @param b Second operand
 * @return GCD result, or MATH_INVALID_VALUE on error
 */
GcdInteger stein_compute_direct(GcdInteger a, GcdInteger b);

/**
 * @brief Get algorithm information for Stein's binary GCD
 *
 * @return Pointer to implementation specification
 */
const ImplementationSpec *stein_get_algorithm_info(void);

/**
 * @brief Initialize Stein binary specification
 */
void stein_binary_init_spec(void);

#endif // STEIN_IMPLEMENTATIONS_H