"""
Converts valgrind output into suppression file.
For this you should run valgrind with --gen-suppressions=all option.
"""
def valgrind_to_suppressions(valgrind_output, suppressions_file):
    for line in valgrind_output:
        if line.startswith("=="):
            continue
        suppressions_file.write(line)

if __name__ == "__main__":
    import sys
    valgrind_output = sys.argv[1]
    suppressions_file = sys.argv[2]
    with open(valgrind_output, "r") as valgrind_output:
        with open(suppressions_file, "w") as suppressions_file:
            valgrind_to_suppressions(valgrind_output, suppressions_file)

