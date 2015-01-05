#ifndef STRINGS_H
#define STRINGS_H

#define STR_USAGE_MSG "Usage: %s [-ebh] " \
         "[-i input_base] [-o output_base(s)] " \
         "-f input_file | numbers\n" \
         "\t-e -- print number in english\n" \
         "\t-b -- print floating point number (if floating point) in binary\n" \
         "\t-h -- this help/usage message\n"

#define STR_TAB "\t"
#define STR_NEWLINE "\n"

#define STR_FILE_TOK_SEPARATOR " \t\n"

#define STR_OUTBASE_TOK_SEPARATOR ", "

#define STR_MALLOC_ERR "malloc"

#define STR_REALLOC_ERR "realloc"

#define STR_INPUT_STR_FMT "\n%s\n"

#define STR_GETOPT_OPTIONS "ebhi:o:f:"

#define STR_INBASE_ENDPTR_ERR "\t%s (input base) is not an integer.\n"
#define STR_OUTBASE_ENDPTR_ERR "\t%s (output base) is not an integer.\n"
#define STR_INT_ENDPTR_ERR "\t%s is not a valid integer in base %d.\n"
#define STR_FLOAT_ENDPTR_ERR "\t%s is not a valid floating point number.\n"

#define STR_INBASE_BAD_RANGE "\t%ld - invalid input base; " \
                             "valid input base range [%d - %d]\n"
#define STR_OUTBASE_BAD_RANGE "\t%ld - invalid output base; " \
                              "valid output base range [%d - %d]\n"

#define STR_FILE_AND_ARGS_ERR "\tOnly one of -f input_file or numbers on " \
                              "the command line\n"
#define STR_NO_INPUT_ERR "\tMust specify numbers using either -f input_file " \
                         "or numbers on the command line\n"

#define STR_DOT "dot "
#define STR_ZERO "zero "
#define STR_MINUS "minus "
#define STR_NEG_PREFIX "-"
#define STR_OCT_PREFIX "0"
#define STR_HEX_PREFIX "0x"

#endif // STRINGS_H
