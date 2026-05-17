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

data <- read.csv("report.csv", check.names = FALSE, stringsAsFactors = FALSE)

cat("Files:", nrow(data), " Columnes:", ncol(data), "\n")
print(colnames(data))

# Funció auxiliar per detectar automàticament columnes
# segons un patró de text (sense modificar els noms originals)
find_col <- function(pattern) {
  cols <- colnames(data)
  m <- grep(pattern, cols, ignore.case = TRUE)
  if (length(m) == 0) stop(paste("Columna no trobada:", pattern))
  cols[m[1]]
}

graph_name        <- find_col("Graph Name")
density_col    <- find_col("Density")
nodes_col      <- find_col("Node Count")
edges_col      <- find_col("Edge Count")
bfs_col        <- find_col("BFS Time")
dfs_col        <- find_col("DFS Time")
start_node_col <- find_col("Start Node")

# Filtrar només observacions aparellades (files amb temps BFS i DFS disponibles)
paired <- data[!is.na(data[[dfs_col]]) & !is.na(data[[bfs_col]]), ]
print(paste("Observacions aparellades:", nrow(paired)))
print(paired)

# Diferència de temps entre DFS i BFS
# Valor negatiu -> DFS més ràpid
# Valor positiu -> BFS més ràpid
paired$Diff <- paired[[dfs_col]] - paired[[bfs_col]]

# Histogrames de totes les variables
# Exploració inicial de les distribucions per validar normalitat
png("histograms.png", width = 1200, height = 800)

par(mfrow = c(2, 4))

hist(paired[[dfs_col]],  col="#4C72B0", main="Temps DFS",  xlab="ms")
hist(paired[[bfs_col]],  col="#DD8452", main="Temps BFS",  xlab="ms")
hist(paired$Diff,        col="#55A868", main="DFS - BFS",  xlab="ms")

hist(paired[[nodes_col]],   col="#C44E52", main="Nodes",   xlab="")
hist(paired[[edges_col]],   col="#937860", main="Arestes", xlab="")
hist(paired[[density_col]], col="#8C8C8C", main="Densitat", xlab="")

dev.off()
