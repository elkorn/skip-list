setwd("/home/helluin/Documents/Git/skip-list/results/O3");
opName="erasing";
dispName="Usuwanie";
elements <- read.table("./elements.csv", header=FALSE, sep="\n")[,"V1"];
sl <- read.table(paste("./", opName, ".csv",sep=""), header=FALSE, sep="\n")[,"V1"];
set <- read.table(paste("./", opName, "_set.csv",sep=""), header=FALSE, sep="\n")[,"V1"];
uset <- read.table(paste("./", opName, "_uset.csv",sep=""), header=FALSE, sep="\n")[,"V1"];

col1="blue";
col2="red";
col3="orange";
xDiv=1000;

elements = elements/xDiv;
yMax=round(max(sl, set, uset), 2);
drawLine <- function (y, col) {
  lines(elements, y, type="l", col=col, lwd = 2);
}

plot(elements, sl, ylim=c(0, yMax), yaxt = "n", type="l", col=col1, lwd = 2, xlab="Liczba elementów (w tys.)",  ylab="Czas wykonywania [s]", main=paste(dispName, " dla <int>", sep=""));
axis(2, at=seq(0,yMax,0.5))
drawLine(set, col2);
drawLine(uset, col3);
grid()

legend(x = "bottomright", legend = c("skip_list", "set", "unordered_set"), lty = 1, lwd = 2, col = c(col1, col2, col3))