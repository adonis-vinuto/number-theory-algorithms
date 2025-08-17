/**
 * @file recursive.h
 * @brief Recursive Euclidean GCD algorithm implementations
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This header declares the recursive Euclidean GCD algorithms
 * and their implementation specifications.
 */

#ifndef RECURSIVE_IMPLEMENTATIONS_H
#define RECURSIVE_IMPLEMENTATIONS_H

#include "../../../../../core/interfaces/implementation_interface.h"
#include "../../../domain_types.h"

// ============================================================================
// ORIGINAL ALGORITHM DECLARATIONS
// ============================================================================

/**
 * @brief Recursive Euclidean GCD using modulo
 *
 * @param a First operand
 * @param b Second operand
 * @return Greatest common divisor
 */
GcdInteger mdc_mod(GcdInteger a, GcdInteger b);

/**
 * @brief Recursive Euclidean GCD using subtraction
 *
 * @param a First operand
 * @param b Second operand
 * @return Greatest common divisor
 */
GcdInteger mdc_sub(GcdInteger a, GcdInteger b);

/**
 * @brief Extended Euclidean algorithm (recursive)
 *
 * @param a First operand
 * @param b Second operand
 * @param x Pointer to store coefficient for a
 * @param y Pointer to store coefficient for b
 * @return Greatest common divisor
 */
GcdInteger mdc_ext(GcdInteger a, GcdInteger b, GcdInteger *x, GcdInteger *y);

// ============================================================================
// INTERFACE IMPLEMENTATIONS
// ============================================================================

/**
 * @brief Execute recursive Euclidean modulo algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_recursive_modulo_compute(const MathBinaryInput *input);

/**
 * @brief Execute recursive Euclidean subtraction algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_recursive_subtraction_compute(const MathBinaryInput *input);

/**
 * @brief Execute extended Euclidean algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_extended_compute(const MathBinaryInput *input);

/**
 * @brief Execute extended Euclidean algorithm and return full result
 *
 * @param a First operand
 * @param b Second operand
 * @param x Pointer to store coefficient for a
 * @param y Pointer to store coefficient for b
 * @return ExtendedGcdResult with GCD and coefficients
 */
ExtendedGcdResult euclidean_extended_compute_full(GcdInteger a, GcdInteger b, GcdInteger *x, GcdInteger *y);

// ============================================================================
// IMPLEMENTATION SPECIFICATIONS (EXTERN DECLARATIONS)
// ============================================================================

/**
 * @brief Implementation specification for recursive Euclidean modulo algorithm
 */
extern ImplementationSpec euclidean_recursive_modulo_spec;

/**
 * @brief Implementation specification for recursive Euclidean subtraction algorithm
 */
extern ImplementationSpec euclidean_recursive_subtraction_spec;

/**
 * @brief Implementation specification for extended Euclidean algorithm
 */
extern ImplementationSpec euclidean_extended_spec;

// ============================================================================
// FAMILY INTEGRATION FUNCTIONS
// ============================================================================

/**
 * @brief Get implementation specification by variant
 *
 * @param variant Algorithm variant
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *recursive_euclidean_get_implementation(GcdAlgorithmVariant variant);

/**
 * @brief Get all recursive Euclidean implementations
 *
 * @param specs Array to store implementation specs
 * @param max_specs Maximum number of specs to return
 * @return Number of implementation specs returned
 */
MathNatural recursive_euclidean_get_all_implementations(
    const ImplementationSpec **specs,
    MathNatural max_specs);

/**
 * @brief Check if variant is a recursive Euclidean algorithm
 *
 * @param variant Algorithm variant to check
 * @return true if variant is recursive Euclidean
 */
bool is_recursive_euclidean_variant(GcdAlgorithmVariant variant);

/**
 * @brief Initialize all recursive Euclidean specifications
 */
void recursive_euclidean_init_specs(void);

#endif // RECURSIVE_IMPLEMENTATIONS_H