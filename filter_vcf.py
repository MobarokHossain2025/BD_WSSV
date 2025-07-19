import sys
from argparse import ArgumentParser

def print_author_info():
    author_banner = """
    ===============================================
    VCF Filtration Script
    Author: MD MOBAROK HOSSAIN
    PhD Candidate, University of Tasmania
    ===============================================
    """
    print(author_banner)

def parse_args():
    "Parse the input arguments, use '-h' for help"
    commands = ArgumentParser(description='VCF Filtration.')
    commands.add_argument('--vcf', type=str, required=True,
                          help='Mapped raw VCF file, with DP4 scores. (Required)')
    commands.add_argument('--phr', type=int, required=False, default=20,
                          help='Minimum Phred-Score. Default 20.')
    commands.add_argument('--depth', type=int, required=False, default=10,
                          help='Minimum read depth. Default 10.')
    commands.add_argument('--output', type=str, required=False, default='Filtered_for_phylo.vcf',
                          help='Output file.')
    return commands.parse_args()

# Show author info
print_author_info()

# Parse arguments
args = parse_args()
phrdQ = float(args.phr)

# Filtering the VCF file
with open(args.output, 'w') as output:
    for line in open(args.vcf, 'r'):
        if line.startswith("#"):
            output.write(line)
        else:
            element = line.strip().split("\t")
            phrd = float(element[5])
            info = element[7]

            try:
                hqread = info.split('DP4=')[1].split(';')[0].split(',')
                readALTf = int(hqread[2])
                readALTr = int(hqread[3])
                read_total = sum(map(int, hqread))
                read = float((readALTf + readALTr) / read_total) if read_total > 0 else 0
            except:
                read = 0

            try:
                FMT_read_dep = int(element[9].split(':')[2])
            except:
                FMT_read_dep = 0

            if (len(element[4]) == 1) and (phrd > phrdQ) and (FMT_read_dep >= args.depth):
                output.write(line)

output.close()

