import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("D:/source/bench_mark2/results.csv")

plt.figure(figsize=(8, 5.5))

markers = {"Merge sort": "o", "Quicksort": "s", "Heapsort": "^"}
colors = {"Merge sort": "#d62728", "Quicksort": "#1f77b4", "Heapsort": "#2ca02c"}

for algo in df["algorithm"].unique():
    sub = df[df["algorithm"] == algo].sort_values("n")
    plt.plot(sub["n"], sub["avg_time_ms"], marker=markers[algo],
              color=colors[algo], linewidth=2, markersize=7, label=algo)

plt.xlabel("Размер массива (n)", fontsize=12)
plt.ylabel("Среднее время выполнения (мс)", fontsize=12)
plt.title("Зависимость времени выполнения сортировок от размера массива", fontsize=12)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3)
plt.ticklabel_format(style='plain', axis='x')
plt.tight_layout()
plt.savefig("benchmark_plot.png", dpi=150)
plt.savefig("benchmark_plot.pdf")  # для латеха векторный вариант лучше
print("Сохранено: benchmark_plot.png и benchmark_plot.pdf")