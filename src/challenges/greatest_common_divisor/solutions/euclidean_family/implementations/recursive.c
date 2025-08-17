/**
 * @file recursive.c
 * @brief Recursive Euclidean GCD algorithm implementations
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file implements the recursive Euclidean GCD algorithms
 * by wrapping your existing functions from recursivo.c in the standard interface.
 *
 * Maps to your functions: mdc_mod, mdc_sub, mdc_ext
 */

#include "../../../../../core/interfaces/implementation_interface.h"
#include "../../../domain_types.h"
#include "../solution_spec.h"
#include "../../../../../infrastructure/utilities/math_utils.h"

// ============================================================================
// ORIGINAL ALGORITHM IMPLEMENTATIONS
// ============================================================================
// These are your original functions from recursivo.c
// Included here to be wrapped in the interface

/**
 * @brief Recursive Euclidean GCD using modulo
 *
 * Your original mdc_mod implementation from recursivo.c
 */
GcdInteger mdc_mod(GcdInteger a, GcdInteger b)
{
    if (b == 0)
        return a;
    return mdc_mod(b, a % b);
}

/**
 * @brief Recursive Euclidean GCD using subtraction
 *
 * Your original mdc_sub implementation from recursivo.c
 */
GcdInteger mdc_sub(GcdInteger a, GcdInteger b)
{
    if (a == b)
        return a;
    if (a > b)
        return mdc_sub(a - b, b);
    return mdc_sub(a, b - a);
}

/**
 * @brief Extended Euclidean algorithm (recursive)
 *
 * Your original mdc_ext implementation from recursivo.c
 */
GcdInteger mdc_ext(GcdInteger a, GcdInteger b, GcdInteger *x, GcdInteger *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    GcdInteger x1, y1;
    GcdInteger gcd = mdc_ext(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

// ============================================================================
// INTERFACE IMPLEMENTATIONS
// ============================================================================

/**
 * @brief Validate input for recursive Euclidean algorithms
 *
 * @param input Input parameters
 * @return true if input is valid
 */
static bool recursive_euclidean_validate(const MathBinaryInput *input)
{
    if (input == NULL)
    {
        return false;
    }

    // Recursive algorithms can handle any integer inputs
    // But we should check for potential stack overflow with very large inputs
    // For now, accept all inputs (stack limits are system-dependent)
    return true;
}

/**
 * @brief Execute recursive Euclidean modulo algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_recursive_modulo_compute(const MathBinaryInput *input)
{
    if (!recursive_euclidean_validate(input))
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
    GcdInteger result = mdc_mod(input->operand_a, input->operand_b);
    double end_time = math_get_time_ms();

    double execution_time = (end_time >= 0 && start_time >= 0) ? (end_time - start_time) : 0.0;

    return math_create_success_result(result, 0, execution_time);
}

/**
 * @brief Execute recursive Euclidean subtraction algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_recursive_subtraction_compute(const MathBinaryInput *input)
{
    if (!recursive_euclidean_validate(input))
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
    GcdInteger result = mdc_sub(input->operand_a, input->operand_b);
    double end_time = math_get_time_ms();

    double execution_time = (end_time >= 0 && start_time >= 0) ? (end_time - start_time) : 0.0;

    return math_create_success_result(result, 0, execution_time);
}

/**
 * @brief Execute extended Euclidean algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_extended_compute(const MathBinaryInput *input)
{
    if (!recursive_euclidean_validate(input))
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
    GcdInteger x, y;
    GcdInteger result = mdc_ext(input->operand_a, input->operand_b, &x, &y);
    double end_time = math_get_time_ms();

    double execution_time = (end_time >= 0 && start_time >= 0) ? (end_time - start_time) : 0.0;

    // Note: Extended algorithm returns coefficients in x,y but our interface
    // only returns the GCD value. For full extended results, use the direct
    // mdc_ext function or create a separate extended interface.

    return math_create_success_result(result, 0, execution_time);
}

// ============================================================================
// EXTENDED GCD INTERFACE
// ============================================================================

/**
 * @brief Execute extended Euclidean algorithm and return full result
 *
 * @param a First operand
 * @param b Second operand
 * @param x Pointer to store coefficient for a
 * @param y Pointer to store coefficient for b
 * @return ExtendedGcdResult with GCD and coefficients
 */
ExtendedGcdResult euclidean_extended_compute_full(GcdInteger a, GcdInteger b, GcdInteger *x, GcdInteger *y)
{
    if (x == NULL || y == NULL)
    {
        return EXTENDED_GCD_INVALID;
    }

    // Handle special case: gcd(0,0)
    if (a == 0 && b == 0)
    {
        *x = 0;
        *y = 0;
        return EXTENDED_GCD_INIT(0, 0, 0);
    }

    // Execute extended algorithm
    GcdInteger gcd_result = mdc_ext(a, b, x, y);

    return EXTENDED_GCD_INIT(gcd_result, *x, *y);
}

// ============================================================================
// IMPLEMENTATION SPECIFICATIONS (Global Variables)
// ============================================================================

/**
 * @brief Implementation specification for recursive Euclidean modulo algorithm
 */
ImplementationSpec euclidean_recursive_modulo_spec = {
    .metadata = IMPLEMENTATION_METADATA(
        "Recursive Euclidean Modulo",
        "Recursive Euclidean algorithm using modulo operator (%)",
        ALGORITHM_FAMILY_EUCLIDEAN,
        COMPLEXITY_LOGARITHMIC,
        true),
    .compute = euclidean_recursive_modulo_compute,
    .validate = recursive_euclidean_validate,
    .performance = MATH_PERFORMANCE_METRICS_INIT};

/**
 * @brief Implementation specification for recursive Euclidean subtraction algorithm
 */
ImplementationSpec euclidean_recursive_subtraction_spec = {
    .metadata = IMPLEMENTATION_METADATA(
        "Recursive Euclidean Subtraction",
        "Recursive Euclidean algorithm using repeated subtraction",
        ALGORITHM_FAMILY_EUCLIDEAN,
        COMPLEXITY_LINEAR,
        true),
    .compute = euclidean_recursive_subtraction_compute,
    .validate = recursive_euclidean_validate,
    .performance = MATH_PERFORMANCE_METRICS_INIT};

/**
 * @brief Implementation specification for extended Euclidean algorithm
 */
ImplementationSpec euclidean_extended_spec = {
    .metadata = IMPLEMENTATION_METADATA(
        "Extended Euclidean",
        "Extended Euclidean algorithm computing GCD and Bezout coefficients",
        ALGORITHM_FAMILY_EUCLIDEAN,
        COMPLEXITY_LOGARITHMIC,
        true),
    .compute = euclidean_extended_compute,
    .validate = recursive_euclidean_validate,
    .performance = MATH_PERFORMANCE_METRICS_INIT};

// ============================================================================
// FAMILY INTEGRATION FUNCTIONS
// ============================================================================

/**
 * @brief Get implementation specification by variant
 *
 * @param variant Algorithm variant
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *recursive_euclidean_get_implementation(GcdAlgorithmVariant variant)
{
    switch (variant)
    {
    case GCD_RECURSIVE_MODULO:
        return &euclidean_recursive_modulo_spec;
    case GCD_RECURSIVE_SUBTRACTION:
        return &euclidean_recursive_subtraction_spec;
    case GCD_EXTENDED_EUCLIDEAN:
        return &euclidean_extended_spec;
    default:
        return NULL;
    }
}

/**
 * @brief Get all recursive Euclidean implementations
 *
 * @param specs Array to store implementation specs
 * @param max_specs Maximum number of specs to return
 * @return Number of implementation specs returned
 */
MathNatural recursive_euclidean_get_all_implementations(
    const ImplementationSpec **specs,
    MathNatural max_specs)
{
    if (specs == NULL || max_specs == 0)
    {
        return 0;
    }

    MathNatural count = 0;

    if (count < max_specs)
        specs[count++] = &euclidean_recursive_modulo_spec;
    if (count < max_specs)
        specs[count++] = &euclidean_recursive_subtraction_spec;
    if (count < max_specs)
        specs[count++] = &euclidean_extended_spec;

    return count;
}

/**
 * @brief Check if variant is a recursive Euclidean algorithm
 *
 * @param variant Algorithm variant to check
 * @return true if variant is recursive Euclidean
 */
bool is_recursive_euclidean_variant(GcdAlgorithmVariant variant)
{
    return (variant == GCD_RECURSIVE_MODULO ||
            variant == GCD_RECURSIVE_SUBTRACTION ||
            variant == GCD_EXTENDED_EUCLIDEAN);
}

/**
 * @brief Initialize all recursive Euclidean specifications
 *
 * Call this function to ensure all specs are properly initialized.
 * This is automatically called by the registry system.
 */
void recursive_euclidean_init_specs(void)
{
    // Specs are already initialized as global variables with static data
    // This function exists for consistency with the interface pattern
    // but no additional initialization is needed for these implementations
}