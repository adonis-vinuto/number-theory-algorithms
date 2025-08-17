/**
 * @file mdc_analyzer.c
 * @brief GCD algorithm analyzer and comparison service
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file implements analysis and comparison services for GCD algorithms.
 * Provides simple ways to execute, compare, and validate your GCD implementations.
 *
 * Focused on practical analysis without over-engineering.
 */

#include "../challenge_definition.h"
#include "../solutions/euclidean_family/implementations/classic.h"
#include "../solutions/euclidean_family/implementations/recursive.h"
#include "../solutions/binary_family/implementations/stein.h"
#include "../../../infrastructure/utilities/math_utils.h"
#include "../../../infrastructure/utilities/memory_utils.h"
#include <stdio.h>

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
MathResult mdc_analyzer_execute_algorithm(GcdAlgorithmVariant variant, GcdInteger a, GcdInteger b)
{
    MathBinaryInput input = {.operand_a = a, .operand_b = b};

    // Get implementation based on variant
    const ImplementationSpec *spec = NULL;

    // Try classic Euclidean implementations
    if (is_classic_euclidean_variant(variant))
    {
        spec = classic_euclidean_get_implementation(variant);
    }
    // Try recursive Euclidean implementations
    else if (is_recursive_euclidean_variant(variant))
    {
        spec = recursive_euclidean_get_implementation(variant);
    }
    // Try binary implementations
    else if (is_stein_variant(variant))
    {
        spec = stein_get_implementation(variant);
    }

    if (spec == NULL)
    {
        return math_create_error_result(MATH_ERROR_NOT_IMPLEMENTED, 0, 0.0);
    }

    // Execute the algorithm
    return spec->compute(&input);
}

/**
 * @brief Execute all available GCD algorithms and compare results
 *
 * @param a First operand
 * @param b Second operand
 * @param results Array to store results (must have space for all algorithms)
 * @param max_results Maximum number of results to store
 * @return Number of algorithms executed
 */
MathNatural mdc_analyzer_execute_all(GcdInteger a, GcdInteger b, MathResult *results, MathNatural max_results)
{
    if (results == NULL || max_results == 0)
    {
        return 0;
    }

    MathNatural count = 0;

    // All available algorithm variants
    GcdAlgorithmVariant variants[] = {
        GCD_EUCLIDEAN_MODULO,
        GCD_EUCLIDEAN_SUBTRACTION,
        GCD_EUCLIDEAN_DIVISION,
        GCD_RECURSIVE_MODULO,
        GCD_RECURSIVE_SUBTRACTION,
        GCD_EXTENDED_EUCLIDEAN,
        GCD_BINARY_STEIN};

    MathNatural variant_count = sizeof(variants) / sizeof(variants[0]);

    // Execute each algorithm
    for (MathNatural i = 0; i < variant_count && count < max_results; i++)
    {
        results[count] = mdc_analyzer_execute_algorithm(variants[i], a, b);
        count++;
    }

    return count;
}

/**
 * @brief Execute Extended Euclidean algorithm with full result
 *
 * @param a First operand
 * @param b Second operand
 * @param x Pointer to store coefficient for a
 * @param y Pointer to store coefficient for b
 * @return ExtendedGcdResult with GCD and coefficients
 */
ExtendedGcdResult mdc_analyzer_execute_extended(GcdInteger a, GcdInteger b, GcdInteger *x, GcdInteger *y)
{
    return euclidean_extended_compute_full(a, b, x, y);
}

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
bool mdc_analyzer_validate_result(GcdInteger a, GcdInteger b, GcdInteger result)
{
    return gcd_validate_result(a, b, result);
}

/**
 * @brief Compare all algorithm results for consistency
 *
 * @param a First operand
 * @param b Second operand
 * @param results Array of results from different algorithms
 * @param result_count Number of results
 * @return true if all results are consistent
 */
bool mdc_analyzer_validate_consistency(GcdInteger a, GcdInteger b, const MathResult *results, MathNatural result_count)
{
    if (results == NULL || result_count == 0)
    {
        return false;
    }

    // Find first valid result as reference
    GcdInteger reference_value = MATH_INVALID_VALUE;
    for (MathNatural i = 0; i < result_count; i++)
    {
        if (MATH_IS_VALID_RESULT(results[i]))
        {
            reference_value = results[i].value;
            break;
        }
    }

    if (reference_value == MATH_INVALID_VALUE)
    {
        return false; // No valid results found
    }

    // Check all valid results match the reference
    for (MathNatural i = 0; i < result_count; i++)
    {
        if (MATH_IS_VALID_RESULT(results[i]))
        {
            if (results[i].value != reference_value)
            {
                return false; // Inconsistent result found
            }
        }
    }

    return true;
}

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
double mdc_analyzer_find_fastest(GcdInteger a, GcdInteger b, GcdAlgorithmVariant *fastest_variant)
{
    if (fastest_variant == NULL)
    {
        return -1.0;
    }

    MathResult results[10]; // Space for all algorithms
    MathNatural count = mdc_analyzer_execute_all(a, b, results, 10);

    if (count == 0)
    {
        return -1.0;
    }

    // Find algorithm with minimum execution time
    double min_time = -1.0;
    GcdAlgorithmVariant variants[] = {
        GCD_EUCLIDEAN_MODULO,
        GCD_EUCLIDEAN_SUBTRACTION,
        GCD_EUCLIDEAN_DIVISION,
        GCD_RECURSIVE_MODULO,
        GCD_RECURSIVE_SUBTRACTION,
        GCD_EXTENDED_EUCLIDEAN,
        GCD_BINARY_STEIN};

    for (MathNatural i = 0; i < count; i++)
    {
        if (MATH_IS_VALID_RESULT(results[i]) && results[i].execution_time_ms >= 0)
        {
            if (min_time < 0 || results[i].execution_time_ms < min_time)
            {
                min_time = results[i].execution_time_ms;
                *fastest_variant = variants[i];
            }
        }
    }

    return min_time;
}

/**
 * @brief Get algorithm name from variant
 *
 * @param variant Algorithm variant
 * @return Human-readable algorithm name
 */
const char *mdc_analyzer_get_algorithm_name(GcdAlgorithmVariant variant)
{
    switch (variant)
    {
    case GCD_EUCLIDEAN_MODULO:
        return "Euclidean Modulo";
    case GCD_EUCLIDEAN_SUBTRACTION:
        return "Euclidean Subtraction";
    case GCD_EUCLIDEAN_DIVISION:
        return "Euclidean Division";
    case GCD_RECURSIVE_MODULO:
        return "Recursive Modulo";
    case GCD_RECURSIVE_SUBTRACTION:
        return "Recursive Subtraction";
    case GCD_EXTENDED_EUCLIDEAN:
        return "Extended Euclidean";
    case GCD_BINARY_STEIN:
        return "Stein Binary";
    default:
        return "Unknown";
    }
}

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
MathNatural mdc_analyzer_benchmark(GcdInteger a, GcdInteger b, MathNatural iterations, MathResult *results, MathNatural max_results)
{
    if (results == NULL || max_results == 0 || iterations == 0)
    {
        return 0;
    }

    GcdAlgorithmVariant variants[] = {
        GCD_EUCLIDEAN_MODULO,
        GCD_EUCLIDEAN_SUBTRACTION,
        GCD_EUCLIDEAN_DIVISION,
        GCD_RECURSIVE_MODULO,
        GCD_RECURSIVE_SUBTRACTION,
        GCD_EXTENDED_EUCLIDEAN,
        GCD_BINARY_STEIN};

    MathNatural variant_count = sizeof(variants) / sizeof(variants[0]);
    MathNatural result_count = 0;

    // Benchmark each algorithm
    for (MathNatural i = 0; i < variant_count && result_count < max_results; i++)
    {
        double total_time = 0.0;
        MathNatural successful_runs = 0;

        // Run multiple iterations
        for (MathNatural j = 0; j < iterations; j++)
        {
            MathResult single_result = mdc_analyzer_execute_algorithm(variants[i], a, b);

            if (MATH_IS_VALID_RESULT(single_result) && single_result.execution_time_ms >= 0)
            {
                total_time += single_result.execution_time_ms;
                successful_runs++;
            }
        }

        // Store benchmark result
        if (successful_runs > 0)
        {
            results[result_count].value = 0; // Not relevant for benchmark
            results[result_count].status = MATH_SUCCESS;
            results[result_count].is_valid = true;
            results[result_count].iterations = successful_runs;
            results[result_count].execution_time_ms = total_time / successful_runs; // Average time
            result_count++;
        }
    }

    return result_count;
}

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
void mdc_analyzer_print_comparison(GcdInteger a, GcdInteger b, const MathResult *results, MathNatural result_count)
{
    printf("=== GCD Algorithm Comparison ===\n");
    printf("Input: gcd(%lld, %lld)\n\n", (long long)a, (long long)b);

    GcdAlgorithmVariant variants[] = {
        GCD_EUCLIDEAN_MODULO,
        GCD_EUCLIDEAN_SUBTRACTION,
        GCD_EUCLIDEAN_DIVISION,
        GCD_RECURSIVE_MODULO,
        GCD_RECURSIVE_SUBTRACTION,
        GCD_EXTENDED_EUCLIDEAN,
        GCD_BINARY_STEIN};

    for (MathNatural i = 0; i < result_count && i < 7; i++)
    {
        const char *name = mdc_analyzer_get_algorithm_name(variants[i]);

        if (MATH_IS_VALID_RESULT(results[i]))
        {
            printf("%-20s: GCD = %lld | Time: %.6f ms\n",
                   name,
                   (long long)results[i].value,
                   results[i].execution_time_ms);
        }
        else
        {
            printf("%-20s: ERROR (status: %d)\n", name, results[i].status);
        }
    }

    printf("\n");
}

/**
 * @brief Print Extended GCD result to console
 *
 * @param a First operand
 * @param b Second operand
 * @param ext_result Extended GCD result
 */
void mdc_analyzer_print_extended_result(GcdInteger a, GcdInteger b, const ExtendedGcdResult *ext_result)
{
    if (ext_result == NULL)
    {
        printf("Extended GCD: Invalid result\n");
        return;
    }

    printf("=== Extended Euclidean Algorithm ===\n");
    printf("Input: gcd(%lld, %lld)\n", (long long)a, (long long)b);

    if (ext_result->is_valid)
    {
        printf("GCD = %lld\n", (long long)ext_result->gcd);
        printf("Coefficients: x = %lld, y = %lld\n",
               (long long)ext_result->coefficient_x,
               (long long)ext_result->coefficient_y);
        printf("Verification: %lld*%lld + %lld*%lld = %lld\n",
               (long long)a, (long long)ext_result->coefficient_x,
               (long long)b, (long long)ext_result->coefficient_y,
               (long long)(a * ext_result->coefficient_x + b * ext_result->coefficient_y));
    }
    else
    {
        printf("Extended GCD: Invalid result\n");
    }

    printf("\n");
}