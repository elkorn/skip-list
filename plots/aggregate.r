setwd("/home/helluin/Documents/Git/skip-list/results/O3");
elements <- read.table("./elements.csv", header=FALSE, sep="\n")[,"V1"];
insert <- read.table("./inserting.csv", header=FALSE, sep="\n")[,"V1"];
find <- read.table("./finding.csv", header=FALSE, sep="\n")[,"V1"];
erase <- read.table("./erasing.csv", header=FALSE, sep="\n")[,"V1"];
col1="blue";
col2="red";
col3="orange";
xDiv=1000;
yMax=ceiling(max(find, erase, insert));

drawLine <- function (y, col) {
  lines(elements, y, type="l", col=col, lwd = 2);
}

elements = elements/xDiv;
plot(elements, insert, ylim=c(0, yMax), yaxt = "n", type="l", col=col1, lwd = 2, xlab="Liczba elementów (w tysiącach)",  ylab="Czas wykonywania [s]", main="Operacje dla <int>");
axis(2, at=seq(0,yMax,0.5))
drawLine(find, col2);
drawLine(erase, col3);
grid()

legend(x = "bottomright", legend = c("Insert", "Find", "Erase"), lty = 1, lwd = 2, col = c(col1, col2, col3))