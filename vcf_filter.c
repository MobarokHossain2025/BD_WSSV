#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 10000

void print_author_info() {
    printf("===============================================\n");
    printf("VCF Filtration Script (C version)\n");
    printf("Author: MD MOBAROK HOSSAIN\n");
    printf("PhD Candidate, University of Tasmania\n");
    printf("===============================================\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s input.vcf [output.vcf] [min_phred] [min_depth]\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    char *output_file = (argc > 2) ? argv[2] : "Filtered_for_phylo.vcf";
    float min_phred = (argc > 3) ? atof(argv[3]) : 20.0;
    int min_depth = (argc > 4) ? atoi(argv[4]) : 10;

    print_author_info();

    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");

    if (!in || !out) {
        perror("File error");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), in)) {
        if (line[0] == '#') {
            fprintf(out, "%s", line);
            continue;
        }

        char *fields[10];
        int i = 0;
        char *token = strtok(line, "\t");
        while (token && i < 10) {
            fields[i++] = token;
            token = strtok(NULL, "\t");
        }

        if (i < 10) continue;

        float qual = atof(fields[5]);
        char *alt = fields[4];
        if (strlen(alt) > 1) continue;

        // Check FORMAT and DP value
        char *format = strdup(fields[8]);
        char *sample = strdup(fields[9]);
        char *fmt_tok = strtok(format, ":");
        char *sample_tok = strtok(sample, ":");
        int depth = 0;

        while (fmt_tok && sample_tok) {
            if (strcmp(fmt_tok, "DP") == 0) {
                depth = atoi(sample_tok);
                break;
            }
            fmt_tok = strtok(NULL, ":");
            sample_tok = strtok(NULL, ":");
        }

        free(format);
        free(sample);

        if (qual >= min_phred && depth >= min_depth) {
            fprintf(out, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
                    fields[0], fields[1], fields[2], fields[3], alt,
                    fields[5], fields[6], fields[7], fields[8], fields[9]);
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
