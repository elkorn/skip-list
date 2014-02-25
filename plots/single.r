setwd("/home/helluin/Documents/Git/skip-list/results/O2");
elements <- read.table("./elements.csv", header=FALSE, sep="\n")[,"V1"];
insert <- read.table("./inserting.csv", header=FALSE, sep="\n")[,"V1"];
find <- read.table("./finding.csv", header=FALSE, sep="\n")[,"V1"];
erase <- read.table("./erasing.csv", header=FALSE, sep="\n")[,"V1"];
col1="blue";
col2="red";
col3="orange";
xDiv=1000;

elements = elements/xDiv;
drawLine <- function (y, col, opName) {
  yMax=ceiling(max(y));
  plot(elements, insert, ylim=c(0, yMax), yaxt = "n", type="l", col=col, lwd = 2, xlab="Liczba elementów (w tysiącach)",  ylab="Czas wykonywania [s]", main=paste("Operacja '", opName, "' dla <int>", sep=""));
  lines(elements, y, type="l", col=col, lwd = 2);
  axis(2, at=seq(0,yMax,0.5));
  grid();
}

drawLine(insert, col1, "Insert")
