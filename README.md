# VCF Filtration Script

Author: **MD MOBAROK HOSSAIN**  
PhD Candidate, University of Tasmania  

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
