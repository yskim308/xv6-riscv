import matplotlib.pyplot as plt
import pandas as pd

# 1. Load the data (make sure your file is named output.csv)
# If your columns have spaces after the commas, skipinitialspace fixes it
df = pd.read_csv("ticks.csv", skipinitialspace=True)

# 2. Setup the plot
plt.figure(figsize=(10, 6))

# 3. Loop through each unique PID and plot its line
for pid in df["pid"].unique():
    # Filter the data for just this one process
    pid_data = df[df["pid"] == pid]

    # Grab the ticket count to use in the legend label
    tickets = pid_data["tickets"].iloc[0]

    # Plot X (timestep) vs Y (ticks)
    plt.plot(
        pid_data["timestep"],
        pid_data["ticks"],
        marker="o",  # Adds little dots at each data point
        linewidth=2,  # Makes the line slightly thicker
        label=f"PID {pid} ({tickets} tickets)",
    )

# 4. Make it look professional for your assignment
plt.title(
    "Lottery Scheduler Performance (3:2:1 Ticket Ratio)", fontsize=14, fontweight="bold"
)
plt.xlabel("Time Step (Samples)", fontsize=12)
plt.ylabel("Accumulated CPU Ticks", fontsize=12)

# Start the Y-axis and X-axis at 0
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.legend(fontsize=12)
plt.grid(True, linestyle="--", alpha=0.7)

# 5. Save the graph to an image file and show it on screen
plt.savefig("lottery_graph.png", dpi=300, bbox_inches="tight")
print("Graph saved as 'lottery_graph.png'")
plt.show()
