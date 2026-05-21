# MIT License
#
# Copyright (c) 2026 ケイト
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to do so, subject to the
# following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

###############################################################
# 0. Càrrega segura de llibreries necessàries
# (només s’instal·len si no estan disponibles)
###############################################################
if (!requireNamespace("ggplot2", quietly = TRUE)) {
  install.packages("ggplot2")
}

if (!requireNamespace("reshape2", quietly = TRUE)) {
  install.packages("reshape2")
}

library(ggplot2)
library(reshape2)

# =========================================================
# Llegir dades dels benchmarks
# =========================================================

data_0 <- read.csv(
  "report_0.csv",
  check.names = FALSE,
  stringsAsFactors = FALSE
)

data_1 <- read.csv(
  "report_1.csv",
  check.names = FALSE,
  stringsAsFactors = FALSE
)

data_2 <- read.csv(
  "report_2.csv",
  check.names = FALSE,
  stringsAsFactors = FALSE
)

data_3 <- read.csv(
  "report_3.csv",
  check.names = FALSE,
  stringsAsFactors = FALSE
)

data_4 <- read.csv(
  "report_4.csv",
  check.names = FALSE,
  stringsAsFactors = FALSE
)

# =========================================================
# Funció auxiliar per detectar columnes
# =========================================================

find_col <- function(pattern, data) {

  cols <- colnames(data)

  m <- grep(
    pattern,
    cols,
    ignore.case = TRUE
  )

  if (length(m) == 0) {
    stop(paste("Columna no trobada:", pattern))
  }

  cols[m[1]]
}

# =========================================================
# Detectar columnes
# =========================================================

graph_name_col <- find_col("Graph Name", data_0)
density_col    <- find_col("Density", data_0)
nodes_col      <- find_col("Node Count", data_0)
edges_col      <- find_col("Edge Count", data_0)
start_node_col <- find_col("Start Node", data_0)

bfs_col <- find_col("BFS Time", data_0)
dfs_col <- find_col("DFS Time", data_0)

# =========================================================
# Construir matrius de temps
# Cada columna = una execució
# =========================================================

bfs_times <- cbind(
  data_0[[bfs_col]],
  data_1[[bfs_col]],
  data_2[[bfs_col]],
  data_3[[bfs_col]],
  data_4[[bfs_col]]
)

dfs_times <- cbind(
  data_0[[dfs_col]],
  data_1[[dfs_col]],
  data_2[[dfs_col]],
  data_3[[dfs_col]],
  data_4[[dfs_col]]
)

# =========================================================
# Calcular mitjanes. Per reduir soroll de dades i suavitzar
# variabilitat
# =========================================================

bfs_mean <- rowMeans(
  bfs_times,
  na.rm = TRUE
)

dfs_mean <- rowMeans(
  dfs_times,
  na.rm = TRUE
)

# =========================================================
# Crear dataset final
# =========================================================

paired <- data_0

paired$BFS_Mean <- bfs_mean
paired$DFS_Mean <- dfs_mean

# =========================================================
# Diferència directa
# Negatiu -> DFS més ràpid
# =========================================================

paired$Diff <-
  paired$DFS_Mean -
  paired$BFS_Mean

# =========================================================
# Diferència de logaritmes
# =========================================================

paired$Log_Diff <-
  log(paired$DFS_Mean) -
  log(paired$BFS_Mean)

# =========================================================
# Logaritme del ratio
# =========================================================

paired$Log_Ratio <-
  log(
    paired$DFS_Mean /
    paired$BFS_Mean
  )

# =========================================================
# Ratio original
# < 1 -> DFS més ràpid
# =========================================================

paired$Ratio <-
  paired$DFS_Mean /
  paired$BFS_Mean

# =========================================================
# Eliminar files amb NA
# =========================================================

paired <- paired[
  !is.na(paired$BFS_Mean) &
  !is.na(paired$DFS_Mean),
]

cat(
  "Observacions aparellades:",
  nrow(paired),
  "\n"
)

# =========================================================
# Estadística descriptiva
# =========================================================

paired$Mean_Time <-
  (
    paired$DFS_Mean +
    paired$BFS_Mean
  ) / 2

paired$Diff_Time <-
  paired$DFS_Mean -
  paired$BFS_Mean

mean_diff <- mean(paired$Diff_Time)
sd_diff <- sd(paired$Diff_Time)

upper_limit <- mean_diff + 1.96 * sd_diff
lower_limit <- mean_diff - 1.96 * sd_diff

cat("\n=============================\n")
cat("MITJANES GLOBALS\n")
cat("=============================\n")

cat(
  "DFS Mean:",
  mean(paired$DFS_Mean),
  "ms\n"
)

cat(
  "BFS Mean:",
  mean(paired$BFS_Mean),
  "ms\n"
)

cat(
  "Diff Mean:",
  mean(paired$Diff),
  "ms\n"
)

cat(
  "DFS SD:",
  sd(paired$DFS_Mean),
  "ms\n"
)

cat(
  "BFS SD:",
  sd(paired$BFS_Mean),
  "ms\n"
)

cat(
  "Diff SD:",
  sd(paired$Diff),
  "ms\n"
)

cat(
  "Mean Ratio DFS/BFS:",
  mean(paired$Ratio),
  "\n"
)

# =========================================================
# T-TESTS
# =========================================================

cat("\n=============================\n")
cat("PAIRED T-TEST\n")
cat("=============================\n")

print(
  t.test(
    paired$DFS_Mean,
    paired$BFS_Mean,
    paired = TRUE,
    conf.level = 0.95
  )
)

cat("\n=============================\n")
cat("PAIRED T-TEST LOGS\n")
cat("=============================\n")

print(
  t.test(
    log(paired$DFS_Mean),
    log(paired$BFS_Mean),
    paired = TRUE,
    conf.level = 0.95
  )
)

# =========================================================
# HISTOGRAMES
# =========================================================

png(
  "histograms.png",
  width = 1800,
  height = 1200
)

par(mfrow = c(3, 4))

# =========================================================
# Temps originals
# =========================================================

hist(
  paired$DFS_Mean,
  col = "#4C72B0",
  main = "Temps DFS",
  xlab = "ms"
)

hist(
  paired$BFS_Mean,
  col = "#DD8452",
  main = "Temps BFS",
  xlab = "ms"
)

hist(
  paired$Diff,
  col = "#55A868",
  main = "DFS - BFS",
  xlab = "ms"
)

# =========================================================
# Característiques graf
# =========================================================

hist(
  paired[[nodes_col]],
  col = "#C44E52",
  main = "Nodes",
  xlab = ""
)

hist(
  paired[[edges_col]],
  col = "#937860",
  main = "Arestes",
  xlab = ""
)

hist(
  paired[[density_col]],
  col = "#8C8C8C",
  main = "Densitat",
  xlab = ""
)

# =========================================================
# Diferència logs
# =========================================================

hist(
  paired$Log_Diff,
  col = "#8172B2",
  main = "log(DFS)-log(BFS)",
  xlab = ""
)

hist(
  paired$Log_Ratio,
  col = "#64B5CD",
  main = "log(DFS/BFS)",
  xlab = ""
)

dev.off()

# =========================================================
# QQ Plots
# =========================================================

png(
  "qqplots.png",
  width = 3000,
  height = 1200,
  res = 300
)

par(mfrow = c(1, 3))

qqnorm(
  paired$Diff,
  main = "QQ Plot DFS - BFS",
  ylab = "Quantils mostra",
  xlab = "Quantils teòrics"
)

qqline(paired$Diff)

qqnorm(
  paired$Log_Diff,
  main = "QQ Log Diff",
  ylab = "Quantils mostra",
  xlab = "Quantils teòrics"
)

qqline(paired$Log_Diff)

qqnorm(
  paired$Log_Ratio,
  main = "QQ Log Ratio",
  ylab = "Quantils mostra",
  xlab = "Quantils teòrics"
)

qqline(paired$Log_Ratio)

dev.off()

# =========================================================
# Bland-Altman Plot with ggplot2
# =========================================================


png(
  "bland_altman.png",
  width = 1000,
  height = 700
)

ggplot(
  paired,
  aes(
    x = Mean_Time,
    y = Diff_Time
  )
) +

  # =====================================================
  # Scatter points
  # =====================================================

  geom_point(
    aes(color = "Observacions"),
    alpha = 0.7,
    size = 2
  ) +

  # =====================================================
  # Mean difference
  # =====================================================

  geom_hline(
    aes(
      yintercept = mean_diff,
      color = "Mitjana diferència"
    ),
    linewidth = 1.2
  ) +

  # =====================================================
  # Upper agreement limit
  # =====================================================

  geom_hline(
    aes(
      yintercept = upper_limit,
      color = "95% limits of agreement"
    ),
    linetype = "dashed",
    linewidth = 1
  ) +

  # =====================================================
  # Lower agreement limit
  # =====================================================

  geom_hline(
    aes(
      yintercept = lower_limit,
      color = "95% limits of agreement"
    ),
    linetype = "dashed",
    linewidth = 1
  ) +

  # =====================================================
  # Regression line
  # =====================================================

  geom_smooth(
    aes(color = "Tendència lineal"),
    method = "lm",
    se = FALSE,
    linewidth = 1.5
  ) +

  # =====================================================
  # Labels
  # =====================================================

  labs(
    title = "Bland-Altman Plot DFS vs BFS",
    x = "Mitjana DFS i BFS (ms)",
    y = "DFS - BFS (ms)",
    color = "Llegenda"
  ) +

  # =====================================================
  # Custom colors
  # =====================================================

  scale_color_manual(
    values = c(
      "Observacions" = "#4C72B0",
      "Mitjana diferència" = "red",
      "95% limits of agreement" = "darkgreen",
      "Tendència lineal" = "blue"
    )
  ) +

  # =====================================================
  # Theme
  # =====================================================

  theme_minimal(base_size = 14)

dev.off()

# =========================================================
# BOXPLOT
# =========================================================

plot_data <- data.frame(
  DFS = paired$DFS_Mean,
  BFS = paired$BFS_Mean
)

melted <- melt(plot_data)

png(
  "boxplot.png",
  width = 800,
  height = 600
)

ggplot(
  melted,
  aes(
    x = variable,
    y = value,
    fill = variable
  )
) +
  geom_boxplot() +
  labs(
    title = "Comparació DFS vs BFS",
    x = "Algorisme",
    y = "Temps (ms)"
  ) +
  theme_minimal()

dev.off()

# =========================================================
# Exportar resultats
# =========================================================

write.csv(
  paired,
  "paired_results.csv",
  row.names = FALSE
)

cat("\nFitxers generats:\n")
cat("- qqplots.png\n")
cat("- boxplot.png\n")
cat("- histograms.png\n")
cat("- bland_altman.png\n")
cat("- paired_results.csv\n")