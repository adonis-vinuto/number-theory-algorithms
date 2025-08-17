/**
 * @file classic.c
 * @brief Classic iterative Euclidean GCD algorithm implementations
 * @author Adonis G G Vinuto
 * @version 1.0
 *
 * This file implements the classic iterative Euclidean GCD algorithms
 * by wrapping your existing functions from iterativo.c in the standard interface.
 *
 * Maps to your functions: mdc_modulo, mdc_subtracao, mdc_divisao
 */

#include "../../../../../core/interfaces/implementation_interface.h"
#include "../../../domain_types.h"
#include "../solution_spec.h"
#include "../../../../../infrastructure/utilities/math_utils.h"

// ============================================================================
// ORIGINAL ALGORITHM IMPLEMENTATIONS
// ============================================================================
// These are your original functions from iterativo.c
// Included here to be wrapped in the interface

/**
 * @brief Classic Euclidean GCD using modulo operator
 *
 * Your original mdc_modulo implementation from iterativo.c
 */
GcdInteger mdc_modulo(GcdInteger a, GcdInteger b)
{
    if (a == 0 && b == 0)
        return 0;
    while (b != 0)
    {
        GcdInteger temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * @brief Classic Euclidean GCD using subtraction
 *
 * Your original mdc_subtracao implementation from iterativo.c
 */
GcdInteger mdc_subtracao(GcdInteger a, GcdInteger b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    if (a == 0 && b == 0)
        return 0;
    while (a != b)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}

/**
 * @brief Classic Euclidean GCD using division
 *
 * Your original mdc_divisao implementation from iterativo.c
 */
GcdInteger mdc_divisao(GcdInteger a, GcdInteger b)
{
    if (a == 0 && b == 0)
        return 0;
    GcdInteger quociente, resto;
    while (b != 0)
    {
        quociente = a / b;
        resto = a - b * quociente;
        a = b;
        b = resto;
    }
    return a;
}

// ============================================================================
// INTERFACE IMPLEMENTATIONS
// ============================================================================

/**
 * @brief Validate input for classic Euclidean algorithms
 *
 * @param input Input parameters
 * @return true if input is valid
 */
static bool classic_euclidean_validate(const MathBinaryInput *input)
{
    if (input == NULL)
    {
        return false;
    }

    // Euclidean algorithms can handle any integer inputs
    // No special restrictions needed
    return true;
}

/**
 * @brief Execute Euclidean modulo algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_modulo_compute(const MathBinaryInput *input)
{
    if (!classic_euclidean_validate(input))
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
    GcdInteger result = mdc_modulo(input->operand_a, input->operand_b);
    double end_time = math_get_time_ms();

    double execution_time = (end_time >= 0 && start_time >= 0) ? (end_time - start_time) : 0.0;

    return math_create_success_result(result, 0, execution_time);
}

/**
 * @brief Execute Euclidean subtraction algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_subtraction_compute(const MathBinaryInput *input)
{
    if (!classic_euclidean_validate(input))
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
    GcdInteger result = mdc_subtracao(input->operand_a, input->operand_b);
    double end_time = math_get_time_ms();

    double execution_time = (end_time >= 0 && start_time >= 0) ? (end_time - start_time) : 0.0;

    return math_create_success_result(result, 0, execution_time);
}

/**
 * @brief Execute Euclidean division algorithm with interface
 *
 * @param input Input parameters
 * @return MathResult with computation result and timing
 */
MathResult euclidean_division_compute(const MathBinaryInput *input)
{
    if (!classic_euclidean_validate(input))
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
    GcdInteger result = mdc_divisao(input->operand_a, input->operand_b);
    double end_time = math_get_time_ms();

    double execution_time = (end_time >= 0 && start_time >= 0) ? (end_time - start_time) : 0.0;

    return math_create_success_result(result, 0, execution_time);
}

// ============================================================================
// IMPLEMENTATION SPECIFICATIONS (Global Variables)
// ============================================================================

/**
 * @brief Implementation specification for Euclidean modulo algorithm
 */
ImplementationSpec euclidean_modulo_spec = {
    .metadata = IMPLEMENTATION_METADATA(
        "Euclidean Modulo",
        "Classic Euclidean algorithm using modulo operator (%)",
        ALGORITHM_FAMILY_EUCLIDEAN,
        COMPLEXITY_LOGARITHMIC,
        false),
    .compute = euclidean_modulo_compute,
    .validate = classic_euclidean_validate,
    .performance = MATH_PERFORMANCE_METRICS_INIT};

/**
 * @brief Implementation specification for Euclidean subtraction algorithm
 */
ImplementationSpec euclidean_subtraction_spec = {
    .metadata = IMPLEMENTATION_METADATA(
        "Euclidean Subtraction",
        "Classic Euclidean algorithm using repeated subtraction",
        ALGORITHM_FAMILY_EUCLIDEAN,
        COMPLEXITY_LINEAR,
        false),
    .compute = euclidean_subtraction_compute,
    .validate = classic_euclidean_validate,
    .performance = MATH_PERFORMANCE_METRICS_INIT};

/**
 * @brief Implementation specification for Euclidean division algorithm
 */
ImplementationSpec euclidean_division_spec = {
    .metadata = IMPLEMENTATION_METADATA(
        "Euclidean Division",
        "Classic Euclidean algorithm using integer division",
        ALGORITHM_FAMILY_EUCLIDEAN,
        COMPLEXITY_LOGARITHMIC,
        false),
    .compute = euclidean_division_compute,
    .validate = classic_euclidean_validate,
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
const ImplementationSpec *classic_euclidean_get_implementation(GcdAlgorithmVariant variant)
{
    switch (variant)
    {
    case GCD_EUCLIDEAN_MODULO:
        return &euclidean_modulo_spec;
    case GCD_EUCLIDEAN_SUBTRACTION:
        return &euclidean_subtraction_spec;
    case GCD_EUCLIDEAN_DIVISION:
        return &euclidean_division_spec;
    default:
        return NULL;
    }
}

/**
 * @brief Get all classic Euclidean implementations
 *
 * @param specs Array to store implementation specs
 * @param max_specs Maximum number of specs to return
 * @return Number of implementation specs returned
 */
MathNatural classic_euclidean_get_all_implementations(
    const ImplementationSpec **specs,
    MathNatural max_specs)
{
    if (specs == NULL || max_specs == 0)
    {
        return 0;
    }

    MathNatural count = 0;

    if (count < max_specs)
        specs[count++] = &euclidean_modulo_spec;
    if (count < max_specs)
        specs[count++] = &euclidean_subtraction_spec;
    if (count < max_specs)
        specs[count++] = &euclidean_division_spec;

    return count;
}

/**
 * @brief Check if variant is a classic Euclidean algorithm
 *
 * @param variant Algorithm variant to check
 * @return true if variant is classic Euclidean
 */
bool is_classic_euclidean_variant(GcdAlgorithmVariant variant)
{
    return (variant == GCD_EUCLIDEAN_MODULO ||
            variant == GCD_EUCLIDEAN_SUBTRACTION ||
            variant == GCD_EUCLIDEAN_DIVISION);
}

/**
 * @brief Initialize all classic Euclidean specifications
 *
 * Call this function to ensure all specs are properly initialized.
 * This is automatically called by the registry system.
 */
void classic_euclidean_init_specs(void)
{
    // Specs are already initialized as global variables with static data
    // This function exists for consistency with the interface pattern
    // but no additional initialization is needed for these implementations
}