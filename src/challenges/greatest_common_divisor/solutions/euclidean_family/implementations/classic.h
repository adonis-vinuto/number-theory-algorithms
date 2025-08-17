/**
 * @file classic.h
 * @brief Classic iterative Euclidean GCD algorithm implementations
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This header declares the classic iterative Euclidean GCD algorithms
 * and their implementation specifications.
 */

#ifndef CLASSIC_IMPLEMENTATIONS_H
#define CLASSIC_IMPLEMENTATIONS_H

#include "../../../../../core/interfaces/implementation_interface.h"
#include "../../../domain_types.h"

// ============================================================================
// ORIGINAL ALGORITHM DECLARATIONS
// ============================================================================

/**
 * @brief Classic Euclidean GCD using modulo operator
 *
 * @param a First operand
 * @param b Second operand
 * @return Greatest common divisor
 */
GcdInteger mdc_modulo(GcdInteger a, GcdInteger b);

/**
 * @brief Classic Euclidean GCD using subtraction
 *
 * @param a First operand
 * @param b Second operand
 * @return Greatest common divisor
 */
GcdInteger mdc_subtracao(GcdInteger a, GcdInteger b);

/**
 * @brief Classic Euclidean GCD using division
 *
 * @param a First operand
 * @param b Second operand
 * @return Greatest common divisor
 */
GcdInteger mdc_divisao(GcdInteger a, GcdInteger b);

// ============================================================================
// INTERFACE IMPLEMENTATIONS
// ============================================================================

/**
 * @brief Execute Euclidean modulo algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_modulo_compute(const MathBinaryInput *input);

/**
 * @brief Execute Euclidean subtraction algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_subtraction_compute(const MathBinaryInput *input);

/**
 * @brief Execute Euclidean division algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_division_compute(const MathBinaryInput *input);

// ============================================================================
// IMPLEMENTATION SPECIFICATIONS (EXTERN DECLARATIONS)
// ============================================================================

/**
 * @brief Implementation specification for Euclidean modulo algorithm
 */
extern ImplementationSpec euclidean_modulo_spec;

/**
 * @brief Implementation specification for Euclidean subtraction algorithm
 */
extern ImplementationSpec euclidean_subtraction_spec;

/**
 * @brief Implementation specification for Euclidean division algorithm
 */
extern ImplementationSpec euclidean_division_spec;

// ============================================================================
// FAMILY INTEGRATION FUNCTIONS
// ============================================================================

/**
 * @brief Get implementation specification by variant
 *
 * @param variant Algorithm variant
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *classic_euclidean_get_implementation(GcdAlgorithmVariant variant);

/**
 * @brief Get all classic Euclidean implementations
 *
 * @param specs Array to store implementation specs
 * @param max_specs Maximum number of specs to return
 * @return Number of implementation specs returned
 */
MathNatural classic_euclidean_get_all_implementations(
    const ImplementationSpec **specs,
    MathNatural max_specs);

/**
 * @brief Check if variant is a classic Euclidean algorithm
 *
 * @param variant Algorithm variant to check
 * @return true if variant is classic Euclidean
 */
bool is_classic_euclidean_variant(GcdAlgorithmVariant variant);

/**
 * @brief Initialize all classic Euclidean specifications
 */
void classic_euclidean_init_specs(void);

#endif // CLASSIC_IMPLEMENTATIONS_H