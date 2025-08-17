/**
 * @file main.c
 * @brief Main entry point for the GCD Algorithm Analysis Tool
 * @author Adonis G G vinuto
 * @version 1.0
 *
 * This is the main entry point for the command-line GCD algorithm analysis tool.
 * Provides a simple interface to execute, compare, and analyze GCD algorithms
 * implemented in your iterativo.c and recursivo.c files.
 *
 * Simple and focused - just processes command line arguments and calls
 * the appropriate system functions.
 */

#include "command_parser.c"
#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// PROGRAM INFORMATION
// ============================================================================

#define PROGRAM_NAME "GCD Algorithm Analyzer"
#define PROGRAM_VERSION "1.0"
#define PROGRAM_AUTHOR "Number Theory Algorithms Project"

/**
 * @brief Print program banner
 */
void print_banner(void)
{
    printf("╔════════════════════════════════════════╗\n");
    printf("║        %s        ║\n", PROGRAM_NAME);
    printf("║              Version %s               ║\n", PROGRAM_VERSION);
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
}

/**
 * @brief Print quick usage information
 */
void print_quick_usage(void)
{
    printf("Quick usage:\n");
    printf("  %s compare 48 18           # Compare all algorithms\n", "gcd_analyzer");
    printf("  %s execute -a stein 48 18  # Execute Stein's algorithm\n", "gcd_analyzer");
    printf("  %s help                    # Show detailed help\n", "gcd_analyzer");
    printf("  %s interactive             # Enter interactive mode\n\n", "gcd_analyzer");
}

// ============================================================================
// ERROR HANDLING
// ============================================================================

/**
 * @brief Handle system initialization errors
 *
 * @param status Error status from system initialization
 * @return Appropriate exit code
 */
int handle_init_error(MathStatus status)
{
    printf("Error: Failed to initialize GCD analysis system\n");

    switch (status)
    {
    case MATH_ERROR_MEMORY:
        printf("Cause: Memory allocation failed\n");
        printf("Solution: Ensure sufficient memory is available\n");
        return 2;

    case MATH_ERROR_INVALID_INPUT:
        printf("Cause: Invalid system configuration\n");
        printf("Solution: Check system setup and try again\n");
        return 3;

    default:
        printf("Cause: Unknown error (status: %d)\n", status);
        printf("Solution: Try running the self-test: %s test\n", "gcd_analyzer");
        return 1;
    }
}

/**
 * @brief Handle command line argument errors
 *
 * @param argc Argument count
 * @param argv Argument vector
 */
void handle_argument_error(int argc, char *argv[])
{
    printf("Error: Invalid command line arguments\n\n");

    if (argc > 1)
    {
        printf("Unrecognized command: %s\n\n", argv[1]);
    }

    print_quick_usage();
    printf("Use '%s help' for detailed usage information.\n\n", "gcd_analyzer");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

/**
 * @brief Main entry point
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code (0 = success, non-zero = error)
 */
int main(int argc, char *argv[])
{
    // Parse command line arguments
    CommandArgs args;
    CliCommand command = parse_arguments(argc, argv, &args);

    // Handle special case: no arguments or just program name
    if (argc == 1)
    {
        print_banner();
        printf("Welcome to the GCD Algorithm Analysis Tool!\n\n");
        print_quick_usage();
        printf("This tool analyzes your GCD implementations from:\n");
        printf("  • iterativo.c (mdc_modulo, mdc_subtracao, mdc_divisao, mdc_stein)\n");
        printf("  • recursivo.c (mdc_mod, mdc_sub, mdc_ext)\n\n");
        printf("Use '%s help' for detailed information.\n\n", argv[0]);
        return 0;
    }

    // Handle unknown commands
    if (command == CMD_UNKNOWN)
    {
        handle_argument_error(argc, argv);
        return 1;
    }

    // Initialize system if needed (for commands that require it)
    if (command != CMD_HELP)
    {
        MathStatus init_status = system_init();
        if (init_status != MATH_SUCCESS)
        {
            return handle_init_error(init_status);
        }
    }

    // Execute the command
    int exit_code = execute_command(command, &args);

    // Print system status on verbose mode or for status command
    if (args.verbose && command != CMD_STATUS && command != CMD_HELP)
    {
        printf("=== Session Summary ===\n");
        MathNatural total_executions;
        double total_time;
        if (system_get_status(&total_executions, &total_time))
        {
            printf("Total executions this session: %lu\n", (unsigned long)total_executions);
            if (total_executions > 0)
            {
                printf("Total execution time: %.6f ms\n", total_time);
                printf("Average time per execution: %.6f ms\n", total_time / total_executions);
            }
        }
        printf("\n");
    }

    return exit_code;
}

// ============================================================================
// PROGRAM ENTRY POINT VALIDATION
// ============================================================================

/**
 * @brief Alternative main function for testing/validation
 *
 * This function can be used for basic validation when developing
 * or testing the system without command line arguments.
 */
int test_main(void)
{
    printf("=== GCD Algorithm Analysis Test ===\n\n");

    // Initialize system
    if (system_init() != MATH_SUCCESS)
    {
        printf("Failed to initialize system\n");
        return 1;
    }

    // Run self-test
    printf("Running system self-test...\n");
    if (!system_self_test())
    {
        printf("Self-test failed!\n");
        return 1;
    }

    // Quick demonstration
    printf("=== Quick Demonstration ===\n");
    printf("Computing gcd(48, 18) with different algorithms:\n\n");

    // Test a few algorithms
    GcdAlgorithmVariant variants[] = {
        GCD_EUCLIDEAN_MODULO,
        GCD_EUCLIDEAN_SUBTRACTION,
        GCD_BINARY_STEIN,
        GCD_EXTENDED_EUCLIDEAN};

    for (int i = 0; i < 4; i++)
    {
        MathResult result = system_execute_gcd(variants[i], 48, 18);
        printf("%-20s: ", mdc_analyzer_get_algorithm_name(variants[i]));

        if (MATH_IS_VALID_RESULT(result))
        {
            printf("GCD = %lld, Time = %.6f ms\n",
                   (long long)result.value, result.execution_time_ms);
        }
        else
        {
            printf("ERROR\n");
        }
    }

    printf("\n=== Test completed successfully ===\n");
    return 0;
}

// ============================================================================
// COMPILE-TIME CONFIGURATION
// ============================================================================

/*
 * Compilation instructions:
 *
 * Basic compilation:
 *   gcc main.c -o gcd_analyzer
 *
 * With optimization:
 *   gcc -O2 main.c -o gcd_analyzer
 *
 * Debug version:
 *   gcc -g -DDEBUG main.c -o gcd_analyzer_debug
 *
 * Windows (MinGW):
 *   gcc main.c -o gcd_analyzer.exe
 *
 * Force simple timing (maximum compatibility):
 *   gcc -DSIMPLE_TIMING main.c -o gcd_analyzer
 *
 * Test version (runs test_main instead of main):
 *   gcc -DTEST_MODE main.c -o gcd_test
 */

#ifdef TEST_MODE
/**
 * @brief Test mode entry point
 *
 * When compiled with -DTEST_MODE, runs test_main instead of main
 */
int main(int argc, char *argv[])
{
    (void)argc; // Suppress unused parameter warning
    (void)argv;
    return test_main();
}
#endif

// ============================================================================
// USAGE EXAMPLES AND DOCUMENTATION
// ============================================================================

/*
 * USAGE EXAMPLES:
 *
 * 1. Basic usage:
 *    ./gcd_analyzer compare 48 18
 *
 * 2. Execute specific algorithm:
 *    ./gcd_analyzer execute -a modulo 48 18
 *    ./gcd_analyzer execute -a stein 1000000 999999
 *
 * 3. Benchmark performance:
 *    ./gcd_analyzer benchmark -i 10000 48 18
 *
 * 4. Extended Euclidean:
 *    ./gcd_analyzer extended 48 18
 *
 * 5. Find fastest algorithm:
 *    ./gcd_analyzer fastest 48 18
 *
 * 6. Interactive mode:
 *    ./gcd_analyzer interactive
 *
 * 7. System information:
 *    ./gcd_analyzer list
 *    ./gcd_analyzer status
 *    ./gcd_analyzer test
 *
 * 8. Verbose output:
 *    ./gcd_analyzer compare -v 48 18
 *
 * The program automatically maps to your existing algorithms:
 * - mdc_modulo     -> "modulo" or "mod"
 * - mdc_subtracao  -> "subtraction" or "sub"
 * - mdc_divisao    -> "division" or "div"
 * - mdc_stein      -> "stein" or "binary"
 * - mdc_mod        -> "rec_mod"
 * - mdc_sub        -> "rec_sub"
 * - mdc_ext        -> "extended" or "ext"
 */