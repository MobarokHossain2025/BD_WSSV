# VCF Filtration Script

Author: **MD MOBAROK HOSSAIN**  
PhD Candidate, University of Tasmania  

This repository contains scripts related to the analysis and data processing for the White Spot Syndrome Virus (WSSV) manuscript. These tools are designed to support genomic and bioinformatic workflows, including variant filtration, quality control, and downstream analysis. Feel free to use, cite, or modify these scripts for academic and research purposes.

## 🧬 Overview

This script performs filtration on a VCF (Variant Call Format) file using custom criteria to retain only high-confidence SNPs.  
Specifically, it filters variants based on:

- Minimum Phred quality score (`--phr`, default: 20)
- Minimum read depth (`--depth`, default: 10)
- Biallelic SNPs only (single alternate allele)

The script expects the `DP4` tag in the INFO field and FORMAT field to include `DP`.

## 🛠 Requirements

- Python 3.6 or higher
- No external libraries required (pure standard library)

## 🚀 How to Run

1. **Save the script** as `filter_vcf.py`.

2. **Make sure your VCF file** has `DP4` in the INFO field and depth (`DP`) in the FORMAT field for each sample.

3. Run the script via the command line:

```bash
python filter_vcf.py --vcf input.vcf --phr 25 --depth 12 --output filtered_output.vcf
```
## Alternative: C Version

An alternative implementation of the VCF filtration logic is also provided in C for performance-critical environments.  
This version is ideal for integrating into compiled pipelines or when using minimal system resources.

### 📄 Included Files:

- `vcf_filter.c` — The C version of the filtration script

### 🧪 How to Compile and Run

Compile the C source file:

```bash
gcc -o vcf_filter vcf_filter.c
```
Finaly run the codes:

```bash
./vcf_filter input.vcf output.vcf 25 12


