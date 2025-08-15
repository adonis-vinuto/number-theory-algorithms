/**
 * @file system_coordinator.c
 * @brief Main system coordinator for the Number Theory Algorithm Analysis System
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file implements the main coordinator that ties together all components
 * of the GCD algorithm analysis system. Provides a simple, unified interface
 * for executing, comparing, and analyzing GCD algorithms.
 *
 * The coordinator manages the registry, analyzer, and provides high-level
 * convenience functions for common use cases.
 */

#include "../../challenges/greatest_common_divisor/challenge_services/solution_registry.c"
#include "../../challenges/greatest_common_divisor/challenge_services/mdc_analyzer.c"
#include "../../infrastructure/utilities/math_utils.c"
#include "../../infrastructure/utilities/memory_utils.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// SYSTEM STATE
// ============================================================================

/**
 * @brief System state and configuration
 */
typedef struct
{
    bool is_initialized;
    bool registry_ready;
    bool analyzer_ready;
    MathNatural total_executions;
    double total_execution_time;
} SystemState;

// Global system state
static SystemState g_system = {0};

// ============================================================================
// SYSTEM INITIALIZATION
// ============================================================================

/**
 * @brief Initialize the entire GCD algorithm analysis system
 *
 * @return MATH_SUCCESS if initialization successful
 */
MathStatus system_init(void)
{
    if (g_system.is_initialized)
    {
        return MATH_SUCCESS; // Already initialized
    }

    // Initialize registry (auto-registers all implementations)
    MathStatus registry_status = gcd_registry_init();
    if (registry_status != MATH_SUCCESS)
    {
        return registry_status;
    }
    g_system.registry_ready = true;

    // Analyzer doesn't need explicit initialization
    g_system.analyzer_ready = true;

    // Reset counters
    g_system.total_executions = 0;
    g_system.total_execution_time = 0.0;

    g_system.is_initialized = true;
    return MATH_SUCCESS;
}

/**
 * @brief Check if system is initialized and ready
 *
 * @return true if system is ready to use
 */
bool system_is_ready(void)
{
    return g_system.is_initialized && g_system.registry_ready && g_system.analyzer_ready;
}

/**
 * @brief Get system status information
 *
 * @param total_executions Pointer to store total execution count (optional)
 * @param total_time Pointer to store total execution time (optional)
 * @return true if system is ready
 */
bool system_get_status(MathNatural *total_executions, double *total_time)
{
    if (total_executions != NULL)
    {
        *total_executions = g_system.total_executions;
    }
    if (total_time != NULL)
    {
        *total_time = g_system.total_execution_time;
    }
    return system_is_ready();
}

// ============================================================================
// HIGH-LEVEL EXECUTION INTERFACE
// ============================================================================

/**
 * @brief Execute a GCD algorithm by variant (main interface)
 *
 * Automatically initializes system if needed and tracks usage statistics.
 *
 * @param variant Algorithm variant to execute
 * @param a First operand
 * @param b Second operand
 * @return MathResult with computation result and timing
 */
MathResult system_execute_gcd(GcdAlgorithmVariant variant, GcdInteger a, GcdInteger b)
{
    // Auto-initialize if needed
    if (!system_is_ready())
    {
        MathStatus init_status = system_init();
        if (init_status != MATH_SUCCESS)
        {
            return math_create_error_result(init_status, 0, 0.0);
        }
    }

    // Execute through registry
    MathResult result = gcd_registry_execute(variant, a, b);

    // Update statistics
    if (MATH_IS_VALID_RESULT(result))
    {
        g_system.total_executions++;
        if (result.execution_time_ms >= 0)
        {
            g_system.total_execution_time += result.execution_time_ms;
        }
    }

    return result;
}

/**
 * @brief Execute a GCD algorithm by name (convenient interface)
 *
 * @param algorithm_name Name of algorithm to execute
 * @param a First operand
 * @param b Second operand
 * @return MathResult with computation result and timing
 */
MathResult system_execute_gcd_by_name(const char *algorithm_name, GcdInteger a, GcdInteger b)
{
    // Auto-initialize if needed
    if (!system_is_ready())
    {
        MathStatus init_status = system_init();
        if (init_status != MATH_SUCCESS)
        {
            return math_create_error_result(init_status, 0, 0.0);
        }
    }

    // Execute through registry
    MathResult result = gcd_registry_execute_by_name(algorithm_name, a, b);

    // Update statistics
    if (MATH_IS_VALID_RESULT(result))
    {
        g_system.total_executions++;
        if (result.execution_time_ms >= 0)
        {
            g_system.total_execution_time += result.execution_time_ms;
        }
    }

    return result;
}

/**
 * @brief Execute Extended Euclidean algorithm (convenience wrapper)
 *
 * @param a First operand
 * @param b Second operand
 * @param x Pointer to store coefficient for a
 * @param y Pointer to store coefficient for b
 * @return ExtendedGcdResult with GCD and coefficients
 */
ExtendedGcdResult system_execute_extended_gcd(GcdInteger a, GcdInteger b, GcdInteger *x, GcdInteger *y)
{
    // Auto-initialize if needed
    if (!system_is_ready())
    {
        system_init();
    }

    ExtendedGcdResult result = mdc_analyzer_execute_extended(a, b, x, y);

    // Update statistics (count as one execution)
    if (result.is_valid)
    {
        g_system.total_executions++;
    }

    return result;
}

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
MathNatural system_compare_all_algorithms(GcdInteger a, GcdInteger b, bool print_results)
{
    // Auto-initialize if needed
    if (!system_is_ready())
    {
        system_init();
    }

    MathResult results[16]; // Space for all possible algorithms
    MathNatural count = mdc_analyzer_execute_all(a, b, results, 16);

    // Update statistics
    g_system.total_executions += count;
    for (MathNatural i = 0; i < count; i++)
    {
        if (MATH_IS_VALID_RESULT(results[i]) && results[i].execution_time_ms >= 0)
        {
            g_system.total_execution_time += results[i].execution_time_ms;
        }
    }

    // Print results if requested
    if (print_results)
    {
        mdc_analyzer_print_comparison(a, b, results, count);

        // Validate consistency
        bool consistent = mdc_analyzer_validate_consistency(a, b, results, count);
        if (consistent)
        {
            printf("✓ All algorithms produced consistent results\n");
        }
        else
        {
            printf("✗ WARNING: Inconsistent results detected!\n");
        }
        printf("\n");
    }

    return count;
}

/**
 * @brief Find the fastest algorithm for given input
 *
 * @param a First operand
 * @param b Second operand
 * @param print_results Whether to print results to console
 * @return The fastest algorithm variant
 */
GcdAlgorithmVariant system_find_fastest_algorithm(GcdInteger a, GcdInteger b, bool print_results)
{
    // Auto-initialize if needed
    if (!system_is_ready())
    {
        system_init();
    }

    GcdAlgorithmVariant fastest;
    double fastest_time = mdc_analyzer_find_fastest(a, b, &fastest);

    if (print_results)
    {
        if (fastest_time >= 0)
        {
            printf("=== Fastest Algorithm Analysis ===\n");
            printf("Input: gcd(%lld, %lld)\n", (long long)a, (long long)b);
            printf("Fastest: %s\n", mdc_analyzer_get_algorithm_name(fastest));
            printf("Time: %.6f ms\n\n", fastest_time);
        }
        else
        {
            printf("Error: Could not determine fastest algorithm\n\n");
        }
    }

    return fastest;
}

/**
 * @brief Run simple benchmark comparing algorithms
 *
 * @param a First operand
 * @param b Second operand
 * @param iterations Number of iterations for each algorithm
 * @param print_results Whether to print results to console
 * @return Number of algorithms benchmarked
 */
MathNatural system_benchmark_algorithms(GcdInteger a, GcdInteger b, MathNatural iterations, bool print_results)
{
    // Auto-initialize if needed
    if (!system_is_ready())
    {
        system_init();
    }

    MathResult benchmarks[16];
    MathNatural count = mdc_analyzer_benchmark(a, b, iterations, benchmarks, 16);

    // Update statistics (multiply by iterations since that's how many were actually run)
    g_system.total_executions += count * iterations;

    if (print_results)
    {
        printf("=== Algorithm Benchmark ===\n");
        printf("Input: gcd(%lld, %lld)\n", (long long)a, (long long)b);
        printf("Iterations per algorithm: %lu\n\n", (unsigned long)iterations);

        GcdAlgorithmVariant variants[] = {
            GCD_EUCLIDEAN_MODULO, GCD_EUCLIDEAN_SUBTRACTION, GCD_EUCLIDEAN_DIVISION,
            GCD_RECURSIVE_MODULO, GCD_RECURSIVE_SUBTRACTION, GCD_EXTENDED_EUCLIDEAN,
            GCD_BINARY_STEIN};

        for (MathNatural i = 0; i < count && i < 7; i++)
        {
            printf("%-20s: Avg Time: %.6f ms | Runs: %lu\n",
                   mdc_analyzer_get_algorithm_name(variants[i]),
                   benchmarks[i].execution_time_ms,
                   (unsigned long)benchmarks[i].iterations);
        }
        printf("\n");
    }

    return count;
}

// ============================================================================
// INFORMATION AND LISTING INTERFACE
// ============================================================================

/**
 * @brief List all available algorithms
 *
 * @param print_details Whether to print detailed information
 */
void system_list_algorithms(bool print_details)
{
    // Auto-initialize if needed
    if (!system_is_ready())
    {
        system_init();
    }

    if (print_details)
    {
        gcd_registry_print_all();
    }
    else
    {
        printf("Available GCD Algorithms:\n");

        GcdAlgorithmVariant variants[16];
        MathNatural count = gcd_registry_list_variants(variants, 16);

        for (MathNatural i = 0; i < count; i++)
        {
            printf("  %lu. %s\n", (unsigned long)(i + 1), gcd_registry_get_display_name(variants[i]));
        }
        printf("\nTotal: %lu algorithms\n\n", (unsigned long)count);
    }
}

/**
 * @brief Get information about a specific algorithm
 *
 * @param variant Algorithm variant to describe
 * @param print_info Whether to print information to console
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *system_get_algorithm_info(GcdAlgorithmVariant variant, bool print_info)
{
    // Auto-initialize if needed
    if (!system_is_ready())
    {
        system_init();
    }

    const ImplementationSpec *spec = gcd_registry_get_implementation(variant);

    if (print_info)
    {
        gcd_registry_print_implementation_info(variant);
    }

    return spec;
}

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
GcdInteger system_quick_gcd(GcdInteger a, GcdInteger b)
{
    MathResult result = system_execute_gcd(GCD_EUCLIDEAN_MODULO, a, b);
    return MATH_IS_VALID_RESULT(result) ? result.value : MATH_INVALID_VALUE;
}

/**
 * @brief Validate that two algorithms produce the same result
 *
 * @param variant1 First algorithm variant
 * @param variant2 Second algorithm variant
 * @param a First operand
 * @param b Second operand
 * @return true if both algorithms produce the same result
 */
bool system_validate_algorithms(GcdAlgorithmVariant variant1, GcdAlgorithmVariant variant2, GcdInteger a, GcdInteger b)
{
    MathResult result1 = system_execute_gcd(variant1, a, b);
    MathResult result2 = system_execute_gcd(variant2, a, b);

    if (!MATH_IS_VALID_RESULT(result1) || !MATH_IS_VALID_RESULT(result2))
    {
        return false;
    }

    return result1.value == result2.value;
}

// ============================================================================
// SYSTEM DIAGNOSTICS
// ============================================================================

/**
 * @brief Print system status and statistics
 */
void system_print_status(void)
{
    printf("=== System Status ===\n");
    printf("Initialized: %s\n", g_system.is_initialized ? "Yes" : "No");
    printf("Registry Ready: %s\n", g_system.registry_ready ? "Yes" : "No");
    printf("Analyzer Ready: %s\n", g_system.analyzer_ready ? "Yes" : "No");

    if (system_is_ready())
    {
        printf("Total Executions: %lu\n", (unsigned long)g_system.total_executions);
        printf("Total Execution Time: %.6f ms\n", g_system.total_execution_time);

        if (g_system.total_executions > 0)
        {
            double avg_time = g_system.total_execution_time / g_system.total_executions;
            printf("Average Execution Time: %.6f ms\n", avg_time);
        }

        printf("Available Algorithms: %lu\n", (unsigned long)gcd_registry_get_count());
    }

    printf("\n");
}

/**
 * @brief Run system self-test
 *
 * @return true if all tests pass
 */
bool system_self_test(void)
{
    printf("=== System Self-Test ===\n");

    // Initialize system
    if (system_init() != MATH_SUCCESS)
    {
        printf("✗ System initialization failed\n");
        return false;
    }
    printf("✓ System initialization successful\n");

    // Test registry
    MathNatural algorithm_count = gcd_registry_get_count();
    if (algorithm_count == 0)
    {
        printf("✗ No algorithms registered\n");
        return false;
    }
    printf("✓ Registry loaded %lu algorithms\n", (unsigned long)algorithm_count);

    // Test basic computation
    GcdInteger test_result = system_quick_gcd(48, 18);
    if (test_result != 6)
    {
        printf("✗ Basic computation failed: expected 6, got %lld\n", (long long)test_result);
        return false;
    }
    printf("✓ Basic computation successful: gcd(48, 18) = %lld\n", (long long)test_result);

    // Test consistency
    MathNatural comparison_count = system_compare_all_algorithms(48, 18, false);
    if (comparison_count == 0)
    {
        printf("✗ Algorithm comparison failed\n");
        return false;
    }
    printf("✓ Algorithm comparison successful: %lu algorithms tested\n", (unsigned long)comparison_count);

    printf("✓ All tests passed!\n\n");
    return true;
}