/**
 * @file stein.c
 * @brief Stein's binary GCD algorithm implementation
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file implements Stein's binary GCD algorithm by wrapping your existing
 * mdc_stein function from iterativo.c in the standard interface.
 *
 * Maps to your function: mdc_stein (binary GCD algorithm)
 */

#include "../../core/interfaces/implementation_interface.h"
#include "../../domain_types.h"
#include "../solution_spec.h"
#include "../../../infrastructure/utilities/math_utils.c"
#include "../../../infrastructure/utilities/memory_utils.c"

// ============================================================================
// ORIGINAL ALGORITHM IMPLEMENTATION
// ============================================================================
// This is your original function from iterativo.c
// Included here to be wrapped in the interface

/**
 * @brief Stein's binary GCD algorithm
 *
 * Your original mdc_stein implementation from iterativo.c
 * Uses binary operations (shifts and subtraction) instead of division/modulo
 */
GcdInteger mdc_stein(GcdInteger a, GcdInteger b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    int shift = 0;

    // Factor out common factors of 2
    while (((a | b) & 1) == 0)
    {
        a >>= 1;
        b >>= 1;
        shift++;
    }

    // Remove all factors of 2 from a
    while ((a & 1) == 0)
        a >>= 1;

    // From here on, a is always odd
    while (b != 0)
    {
        // Remove all factors of 2 from b
        while ((b & 1) == 0)
            b >>= 1;

        // Now a and b are both odd. Swap if necessary so a <= b,
        // then set b = b - a (which is even)
        if (a > b)
        {
            a = a - b;
        }
        else
        {
            b = b - a;
        }
    }

    // Restore common factors of 2
    return a << shift;
}

// ============================================================================
// INTERFACE IMPLEMENTATION
// ============================================================================

/**
 * @brief Validate input for Stein's binary algorithm
 *
 * @param input Input parameters
 * @return true if input is valid
 */
static bool stein_validate(const MathBinaryInput *input)
{
    if (input == NULL)
    {
        return false;
    }

    // Stein's algorithm can handle any integer inputs
    // It's particularly efficient with large numbers
    return true;
}

/**
 * @brief Execute Stein's binary GCD algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult stein_binary_compute(const MathBinaryInput *input)
{
    if (!stein_validate(input))
    {
        return math_create_error_result(MATH_ERROR_INVALID_INPUT, 0, 0.0);
    }

    // Handle special cases first
    MathResult special_result;
    if (math_handle_gcd_special_cases(input->operand_a, input->operand_b, &special_result))
    {
        return special_result;
    }

    // Execute algorithm with timing
    double start_time = math_get_time_ms();
    GcdInteger result = mdc_stein(input->operand_a, input->operand_b);
    double end_time = math_get_time_ms();

    double execution_time = (end_time >= 0 && start_time >= 0) ? (end_time - start_time) : 0.0;

    return math_create_success_result(result, 0, execution_time);
}

// ============================================================================
// IMPLEMENTATION SPECIFICATION (Global Variable)
// ============================================================================

/**
 * @brief Implementation specification for Stein's binary GCD algorithm
 */
ImplementationSpec stein_binary_spec = {
    .metadata = IMPLEMENTATION_METADATA(
        "Stein Binary GCD",
        "Stein's binary GCD algorithm using bit operations instead of division",
        ALGORITHM_FAMILY_BINARY,
        COMPLEXITY_LOGARITHMIC,
        false),
    .compute = stein_binary_compute,
    .validate = stein_validate,
    .performance = MATH_PERFORMANCE_METRICS_INIT};

// ============================================================================
// BINARY ALGORITHM CHARACTERISTICS
// ============================================================================

/**
 * @brief Check if inputs are suitable for binary algorithms
 *
 * Binary algorithms work with any inputs, but may have performance
 * characteristics different from Euclidean algorithms.
 *
 * @param a First operand
 * @param b Second operand
 * @return true if inputs are suitable for binary algorithms
 */
bool stein_is_suitable_input(GcdInteger a, GcdInteger b)
{
    // Stein's algorithm works with any integer inputs
    // It can be particularly efficient for large numbers or when
    // division/modulo operations are expensive

    // For very small numbers, Euclidean might be faster due to simplicity
    // For large numbers, Stein's can be faster due to avoiding division
    return true;
}

/**
 * @brief Estimate performance advantage of Stein's over Euclidean
 *
 * Simple heuristic to estimate when Stein's algorithm might be faster.
 *
 * @param a First operand
 * @param b Second operand
 * @return true if Stein's algorithm likely to be faster
 */
bool stein_likely_faster(GcdInteger a, GcdInteger b)
{
    // Simple heuristic: Stein's may be faster for larger numbers
    // where division/modulo operations become expensive

    GcdInteger max_operand = MATH_MAX(MATH_ABS(a), MATH_ABS(b));

    // Arbitrary threshold - in practice, this depends on the specific
    // system and compiler optimizations
    const GcdInteger THRESHOLD = 1000000; // 1 million

    return max_operand > THRESHOLD;
}

/**
 * @brief Count the number of iterations Stein's algorithm would perform
 *
 * Estimates the number of iterations for complexity analysis.
 *
 * @param a First operand
 * @param b Second operand
 * @return Estimated number of iterations
 */
MathNatural stein_estimate_iterations(GcdInteger a, GcdInteger b)
{
    // Stein's algorithm typically performs approximately 2 * log2(max(a,b)) iterations
    // This is a rough estimate for analysis purposes

    if (a == 0 || b == 0)
    {
        return 0;
    }

    GcdInteger max_operand = MATH_MAX(MATH_ABS(a), MATH_ABS(b));
    MathNatural bit_count = 0;

    // Count bits in larger operand
    while (max_operand > 0)
    {
        max_operand >>= 1;
        bit_count++;
    }

    // Conservative estimate: 2 * number of bits
    return 2 * bit_count;
}

// ============================================================================
// FAMILY INTEGRATION FUNCTIONS
// ============================================================================

/**
 * @brief Get implementation specification by variant
 *
 * @param variant Algorithm variant
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *stein_get_implementation(GcdAlgorithmVariant variant)
{
    if (variant == GCD_BINARY_STEIN)
    {
        return &stein_binary_spec;
    }
    return NULL;
}

/**
 * @brief Get all Stein (binary) implementations
 *
 * @param specs Array to store implementation specs
 * @param max_specs Maximum number of specs to return
 * @return Number of implementation specs returned
 */
MathNatural stein_get_all_implementations(
    const ImplementationSpec **specs,
    MathNatural max_specs)
{
    if (specs == NULL || max_specs == 0)
    {
        return 0;
    }

    specs[0] = &stein_binary_spec;
    return 1;
}

/**
 * @brief Check if variant is Stein's binary algorithm
 *
 * @param variant Algorithm variant to check
 * @return true if variant is Stein's binary algorithm
 */
bool is_stein_variant(GcdAlgorithmVariant variant)
{
    return (variant == GCD_BINARY_STEIN);
}

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
GcdInteger stein_compute_direct(GcdInteger a, GcdInteger b)
{
    // Handle overflow cases
    if (a == LLONG_MIN || b == LLONG_MIN)
    {
        return MATH_INVALID_VALUE;
    }

    return mdc_stein(a, b);
}

/**
 * @brief Get algorithm information for Stein's binary GCD
 *
 * @return Pointer to implementation specification
 */
const ImplementationSpec *stein_get_algorithm_info(void)
{
    return &stein_binary_spec;
}

/**
 * @brief Initialize Stein binary specification
 *
 * Call this function to ensure the spec is properly initialized.
 * This is automatically called by the registry system.
 */
void stein_binary_init_spec(void)
{
    // Spec is already initialized as global variable with static data
    // This function exists for consistency with the interface pattern
    // but no additional initialization is needed for this implementation
}