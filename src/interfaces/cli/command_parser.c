/**
 * @file command_parser.c
 * @brief Command line interface parser for GCD algorithm analysis
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file implements a simple and practical command-line interface
 * for the GCD algorithm analysis system. Provides easy access to all
 * system features without over-complicated command structures.
 */

// ✅ CORRECTED: Include headers instead of .c files
#include "command_parser.h"
#include "../../core/orchestration/system_coordinator.h"
#include "../../challenges/greatest_common_divisor/challenge_services/mdc_analyzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ============================================================================
// COMMAND PARSING IMPLEMENTATION
// ============================================================================

/**
 * @brief Parse command from string
 *
 * @param command_str Command string
 * @return Parsed command type
 */
CliCommand parse_command(const char *command_str)
{
    if (command_str == NULL)
    {
        return CMD_UNKNOWN;
    }

    if (strcmp(command_str, "help") == 0 || strcmp(command_str, "-h") == 0 || strcmp(command_str, "--help") == 0)
    {
        return CMD_HELP;
    }
    if (strcmp(command_str, "list") == 0 || strcmp(command_str, "ls") == 0)
    {
        return CMD_LIST;
    }
    if (strcmp(command_str, "execute") == 0 || strcmp(command_str, "exec") == 0 || strcmp(command_str, "run") == 0)
    {
        return CMD_EXECUTE;
    }
    if (strcmp(command_str, "compare") == 0 || strcmp(command_str, "comp") == 0)
    {
        return CMD_COMPARE;
    }
    if (strcmp(command_str, "benchmark") == 0 || strcmp(command_str, "bench") == 0)
    {
        return CMD_BENCHMARK;
    }
    if (strcmp(command_str, "extended") == 0 || strcmp(command_str, "ext") == 0)
    {
        return CMD_EXTENDED;
    }
    if (strcmp(command_str, "fastest") == 0 || strcmp(command_str, "fast") == 0)
    {
        return CMD_FASTEST;
    }
    if (strcmp(command_str, "status") == 0 || strcmp(command_str, "stat") == 0)
    {
        return CMD_STATUS;
    }
    if (strcmp(command_str, "test") == 0 || strcmp(command_str, "selftest") == 0)
    {
        return CMD_TEST;
    }
    if (strcmp(command_str, "interactive") == 0 || strcmp(command_str, "i") == 0)
    {
        return CMD_INTERACTIVE;
    }

    return CMD_UNKNOWN;
}

/**
 * @brief Parse algorithm variant from string
 *
 * @param variant_str Variant string
 * @return Parsed algorithm variant
 */
GcdAlgorithmVariant parse_algorithm_variant(const char *variant_str)
{
    if (variant_str == NULL)
    {
        return GCD_EUCLIDEAN_MODULO; // Default
    }

    if (strcmp(variant_str, "modulo") == 0 || strcmp(variant_str, "mod") == 0)
    {
        return GCD_EUCLIDEAN_MODULO;
    }
    if (strcmp(variant_str, "subtraction") == 0 || strcmp(variant_str, "sub") == 0)
    {
        return GCD_EUCLIDEAN_SUBTRACTION;
    }
    if (strcmp(variant_str, "division") == 0 || strcmp(variant_str, "div") == 0)
    {
        return GCD_EUCLIDEAN_DIVISION;
    }
    if (strcmp(variant_str, "recursive_modulo") == 0 || strcmp(variant_str, "rec_mod") == 0)
    {
        return GCD_RECURSIVE_MODULO;
    }
    if (strcmp(variant_str, "recursive_subtraction") == 0 || strcmp(variant_str, "rec_sub") == 0)
    {
        return GCD_RECURSIVE_SUBTRACTION;
    }
    if (strcmp(variant_str, "extended") == 0 || strcmp(variant_str, "ext") == 0)
    {
        return GCD_EXTENDED_EUCLIDEAN;
    }
    if (strcmp(variant_str, "stein") == 0 || strcmp(variant_str, "binary") == 0)
    {
        return GCD_BINARY_STEIN;
    }

    return GCD_EUCLIDEAN_MODULO; // Default fallback
}

/**
 * @brief Parse integer from string with error checking
 *
 * @param str String to parse
 * @param value Pointer to store parsed value
 * @return true if parsing successful
 */
bool parse_integer(const char *str, GcdInteger *value)
{
    if (str == NULL || value == NULL)
    {
        return false;
    }

    char *endptr;
    long long parsed = strtoll(str, &endptr, 10);

    if (*endptr != '\0' || endptr == str)
    {
        return false; // Invalid number
    }

    *value = (GcdInteger)parsed;
    return true;
}

/**
 * @brief Parse command line arguments
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @param args Pointer to store parsed arguments
 * @return Parsed command type
 */
CliCommand parse_arguments(int argc, char *argv[], CommandArgs *args)
{
    // Initialize args
    memset(args, 0, sizeof(CommandArgs));
    args->iterations = 1000; // Default iterations for benchmark

    if (argc < 2)
    {
        return CMD_HELP;
    }

    CliCommand command = parse_command(argv[1]);

    // Parse additional arguments based on command
    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
        {
            args->verbose = true;
        }
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--iterations") == 0)
        {
            if (i + 1 < argc)
            {
                args->iterations = (MathNatural)atoi(argv[++i]);
                args->has_iterations = true;
            }
        }
        else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--algorithm") == 0)
        {
            if (i + 1 < argc)
            {
                strncpy(args->algorithm_name, argv[++i], sizeof(args->algorithm_name) - 1);
                args->algorithm_name[sizeof(args->algorithm_name) - 1] = '\0';
                args->variant = parse_algorithm_variant(args->algorithm_name);
                args->has_algorithm = true;
            }
        }
        else if (!args->has_operands)
        {
            // Try to parse as operands
            if (i + 1 < argc)
            {
                if (parse_integer(argv[i], &args->operand_a) &&
                    parse_integer(argv[i + 1], &args->operand_b))
                {
                    args->has_operands = true;
                    i++; // Skip next argument since we used it
                }
            }
        }
    }

    return command;
}

// ============================================================================
// COMMAND EXECUTION IMPLEMENTATIONS
// ============================================================================

/**
 * @brief Execute help command
 */
void execute_help_command(void)
{
    printf("=== GCD Algorithm Analysis Tool ===\n\n");
    printf("Usage: %s <command> [options] [operands]\n\n", "gcd_analyzer");

    printf("Commands:\n");
    printf("  help, -h, --help          Show this help message\n");
    printf("  list, ls                  List all available algorithms\n");
    printf("  execute, exec, run        Execute specific algorithm\n");
    printf("  compare, comp             Compare all algorithms\n");
    printf("  benchmark, bench          Run performance benchmark\n");
    printf("  extended, ext             Execute Extended Euclidean algorithm\n");
    printf("  fastest, fast             Find fastest algorithm for input\n");
    printf("  status, stat              Show system status\n");
    printf("  test, selftest            Run system self-test\n");
    printf("  interactive, i            Enter interactive mode\n\n");

    printf("Options:\n");
    printf("  -a, --algorithm <name>    Specify algorithm (modulo, sub, stein, etc.)\n");
    printf("  -i, --iterations <num>    Number of iterations for benchmark\n");
    printf("  -v, --verbose             Verbose output\n\n");

    printf("Examples:\n");
    printf("  %s compare 48 18                    Compare all algorithms\n", "gcd_analyzer");
    printf("  %s execute -a modulo 48 18          Execute specific algorithm\n", "gcd_analyzer");
    printf("  %s benchmark -i 5000 48 18          Benchmark with 5000 iterations\n", "gcd_analyzer");
    printf("  %s extended 48 18                   Extended Euclidean algorithm\n", "gcd_analyzer");
    printf("  %s fastest 1000000 999999           Find fastest for large numbers\n\n", "gcd_analyzer");

    printf("Available Algorithms:\n");
    printf("  modulo, mod               Euclidean algorithm with modulo\n");
    printf("  subtraction, sub          Euclidean algorithm with subtraction\n");
    printf("  division, div             Euclidean algorithm with division\n");
    printf("  rec_mod                   Recursive Euclidean with modulo\n");
    printf("  rec_sub                   Recursive Euclidean with subtraction\n");
    printf("  extended, ext             Extended Euclidean algorithm\n");
    printf("  stein, binary             Stein's binary GCD algorithm\n\n");
}

/**
 * @brief Execute list command
 *
 * @param verbose Whether to show detailed information
 */
void execute_list_command(bool verbose)
{
    system_list_algorithms(verbose);
}

/**
 * @brief Execute algorithm execution command
 *
 * @param args Command arguments
 */
void execute_execute_command(const CommandArgs *args)
{
    if (!args->has_operands)
    {
        printf("Error: Two operands required for execution\n");
        printf("Usage: execute [-a algorithm] <operand1> <operand2>\n\n");
        return;
    }

    MathResult result;
    if (args->has_algorithm)
    {
        result = system_execute_gcd(args->variant, args->operand_a, args->operand_b);
        printf("Algorithm: %s\n", mdc_analyzer_get_algorithm_name(args->variant));
    }
    else
    {
        result = system_execute_gcd(GCD_EUCLIDEAN_MODULO, args->operand_a, args->operand_b);
        printf("Algorithm: %s (default)\n", mdc_analyzer_get_algorithm_name(GCD_EUCLIDEAN_MODULO));
    }

    printf("Input: gcd(%lld, %lld)\n", (long long)args->operand_a, (long long)args->operand_b);

    if (MATH_IS_VALID_RESULT(result))
    {
        printf("Result: %lld\n", (long long)result.value);
        if (args->verbose)
        {
            printf("Execution Time: %.6f ms\n", result.execution_time_ms);
            printf("Status: %s\n", (result.status == MATH_SUCCESS) ? "Success" : "Error");
        }
    }
    else
    {
        printf("Error: Computation failed (status: %d)\n", result.status);
    }
    printf("\n");
}

/**
 * @brief Execute comparison command
 *
 * @param args Command arguments
 */
void execute_compare_command(const CommandArgs *args)
{
    if (!args->has_operands)
    {
        printf("Error: Two operands required for comparison\n");
        printf("Usage: compare <operand1> <operand2>\n\n");
        return;
    }

    system_compare_all_algorithms(args->operand_a, args->operand_b, true);
}

/**
 * @brief Execute benchmark command
 *
 * @param args Command arguments
 */
void execute_benchmark_command(const CommandArgs *args)
{
    if (!args->has_operands)
    {
        printf("Error: Two operands required for benchmark\n");
        printf("Usage: benchmark [-i iterations] <operand1> <operand2>\n\n");
        return;
    }

    system_benchmark_algorithms(args->operand_a, args->operand_b, args->iterations, true);
}

/**
 * @brief Execute extended Euclidean command
 *
 * @param args Command arguments
 */
void execute_extended_command(const CommandArgs *args)
{
    if (!args->has_operands)
    {
        printf("Error: Two operands required for Extended Euclidean\n");
        printf("Usage: extended <operand1> <operand2>\n\n");
        return;
    }

    GcdInteger x, y;
    ExtendedGcdResult result = system_execute_extended_gcd(args->operand_a, args->operand_b, &x, &y);
    mdc_analyzer_print_extended_result(args->operand_a, args->operand_b, &result);
}

/**
 * @brief Execute fastest algorithm finding command
 *
 * @param args Command arguments
 */
void execute_fastest_command(const CommandArgs *args)
{
    if (!args->has_operands)
    {
        printf("Error: Two operands required for fastest algorithm analysis\n");
        printf("Usage: fastest <operand1> <operand2>\n\n");
        return;
    }

    system_find_fastest_algorithm(args->operand_a, args->operand_b, true);
}

/**
 * @brief Execute status command
 */
void execute_status_command(void)
{
    system_print_status();
}

/**
 * @brief Execute self-test command
 */
void execute_test_command(void)
{
    bool success = system_self_test();
    if (!success)
    {
        printf("Self-test failed!\n");
    }
}

// ============================================================================
// INTERACTIVE MODE
// ============================================================================

/**
 * @brief Run interactive mode
 */
void execute_interactive_mode(void)
{
    printf("=== Interactive GCD Analysis Mode ===\n");
    printf("Type 'help' for commands, 'quit' to exit\n\n");

    char input[256];
    char command[64];
    GcdInteger a, b;

    while (1)
    {
        printf("gcd> ");
        if (!fgets(input, sizeof(input), stdin))
        {
            break;
        }

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        // Parse input
        if (strlen(input) == 0)
        {
            continue;
        }

        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0)
        {
            break;
        }

        if (strcmp(input, "help") == 0)
        {
            printf("Interactive commands:\n");
            printf("  help                     Show this help\n");
            printf("  list                     List algorithms\n");
            printf("  <algorithm> <a> <b>      Execute algorithm\n");
            printf("  compare <a> <b>          Compare all algorithms\n");
            printf("  extended <a> <b>         Extended Euclidean\n");
            printf("  status                   Show system status\n");
            printf("  quit, exit               Exit interactive mode\n\n");
            continue;
        }

        if (strcmp(input, "list") == 0)
        {
            execute_list_command(false);
            continue;
        }

        if (strcmp(input, "status") == 0)
        {
            execute_status_command();
            continue;
        }

        // Try to parse as command with operands
        if (sscanf(input, "%63s %lld %lld", command, (long long *)&a, (long long *)&b) == 3)
        {
            if (strcmp(command, "compare") == 0)
            {
                system_compare_all_algorithms(a, b, true);
            }
            else if (strcmp(command, "extended") == 0)
            {
                GcdInteger x, y;
                ExtendedGcdResult result = system_execute_extended_gcd(a, b, &x, &y);
                mdc_analyzer_print_extended_result(a, b, &result);
            }
            else
            {
                // Try as algorithm name
                GcdAlgorithmVariant variant = parse_algorithm_variant(command);
                MathResult result = system_execute_gcd(variant, a, b);

                printf("Algorithm: %s\n", mdc_analyzer_get_algorithm_name(variant));
                printf("Input: gcd(%lld, %lld)\n", (long long)a, (long long)b);

                if (MATH_IS_VALID_RESULT(result))
                {
                    printf("Result: %lld\n", (long long)result.value);
                    printf("Time: %.6f ms\n", result.execution_time_ms);
                }
                else
                {
                    printf("Error: Computation failed\n");
                }
                printf("\n");
            }
        }
        else
        {
            printf("Invalid command. Type 'help' for available commands.\n\n");
        }
    }

    printf("Exiting interactive mode.\n");
}

// ============================================================================
// MAIN COMMAND DISPATCHER
// ============================================================================

/**
 * @brief Execute command based on parsed arguments
 *
 * @param command Command to execute
 * @param args Command arguments
 * @return Exit code (0 for success)
 */
int execute_command(CliCommand command, const CommandArgs *args)
{
    switch (command)
    {
    case CMD_HELP:
        execute_help_command();
        return 0;

    case CMD_LIST:
        execute_list_command(args->verbose);
        return 0;

    case CMD_EXECUTE:
        execute_execute_command(args);
        return 0;

    case CMD_COMPARE:
        execute_compare_command(args);
        return 0;

    case CMD_BENCHMARK:
        execute_benchmark_command(args);
        return 0;

    case CMD_EXTENDED:
        execute_extended_command(args);
        return 0;

    case CMD_FASTEST:
        execute_fastest_command(args);
        return 0;

    case CMD_STATUS:
        execute_status_command();
        return 0;

    case CMD_TEST:
        execute_test_command();
        return 0;

    case CMD_INTERACTIVE:
        execute_interactive_mode();
        return 0;

    case CMD_UNKNOWN:
    default:
        printf("Unknown command. Use 'help' for available commands.\n\n");
        return 1;
    }
}