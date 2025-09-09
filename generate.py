import pandas as pd
import matplotlib.pyplot as plt
import subprocess
import argparse
import os
import sys

# Argument parsing
parser = argparse.ArgumentParser(description="Generate benchmark graph.")
parser.add_argument("-rerun", action="store_true", help="Recompile and rerun benchmark before plotting.")
args = parser.parse_args()

# Rerun benchmark if requested
if args.rerun:
    print("Compiling and running benchmark...")
    os.makedirs("data", exist_ok=True)
    compile_result = subprocess.run(["g++", "-O2", "-std=c++17", "benchmark.cpp", "-o", "benchmark.out"])
    if compile_result.returncode != 0   :
        print("Compilation failed.")
        sys.exit(1)
    run_result = subprocess.run(["./benchmark.out"])
    if run_result.returncode != 0:
        print("Benchmark run failed.")
        sys.exit(1)

# Plot the CSV
csv_path = "data/benchmark_results.csv"
if not os.path.exists(csv_path):
    print("CSV file not found. Did you forget to run the benchmark?")
    sys.exit(1)

df = pd.read_csv(csv_path)

# Plotting
os.makedirs("images", exist_ok=True)
plt.figure(figsize=(10, 6))
plt.plot(df["InputSize"], df["BitFilterTime_ms"], marker='o', label="Bit Filter Solution")
plt.plot(df["InputSize"], df["StandardTime_ms"], marker='x', label="Standard nth_element Solution")
plt.xlabel("Input Size")
plt.ylabel("Execution Time (ms)")
plt.title("Performance Comparison")
plt.grid(True)
plt.legend()
output_file = "images/performance_comparison.png"
plt.savefig(output_file)
print(f"Saved graph to {output_file}")
