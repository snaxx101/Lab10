import matplotlib.pyplot as plt

# Example: Replace these with your actual simulator results
# You can run the simulator for each trace and record the numbers
traces = ["Sequential", "Random", "Localized"]

cpu_cycles = [10, 12, 15]    # CPU cycles from each trace
tlb_hits = [7, 5, 9]         # TLB hits
tlb_misses = [3, 7, 1]       # TLB misses
page_faults = [3, 5, 2]      # Page faults

# --- CPU Cycles Graph ---
plt.figure(figsize=(10,5))
plt.plot(traces, cpu_cycles, marker='o', color='blue', label="CPU Cycles")
plt.plot(traces, tlb_hits, marker='s', color='green', label="TLB Hits")
plt.plot(traces, tlb_misses, marker='^', color='red', label="TLB Misses")
plt.plot(traces, page_faults, marker='x', color='orange', label="Page Faults")
plt.title("Memory Access Simulation Metrics")
plt.xlabel("Trace Pattern")
plt.ylabel("Count")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
