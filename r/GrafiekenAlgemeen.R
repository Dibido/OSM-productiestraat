csvData <- read.csv(file="../linux/Exe1/result.csv", header=TRUE)

nrOfBuffers <- 4
nrOfMachines <- 10

buffers <- c(0,1,2,3,4,5,6,7,8,9,10,11,12,101,102,103,104,105,106,107,108,109)
firstBuffers <- c(0,12,100,109)
lastBuffers <- c(11,108)


#genereren grafieken aantal onderdelen in buffers
for (bufferID in buffers) 
{
  newdata <- subset(csvData, MACHINE.BUFFER == 'B' & ID == bufferID)
  plot(newdata$MILLISECONDS_FROM_SIM_START, xlab="time (milliseconds)", newdata$CURRENT_MACHINE_AMOUNT_OF_WORK, ylab="items", type="s", col.axis = "navy blue")
  e <- "number of parts in buffer"
  e <- paste(e, bufferID)
  title(e, cex.main = 2, col.main= "navy blue")
  print(e)
}

#genereren grafieken aantal onderdelen in machines
for (machineID in 0:nrOfMachines) 
{
  newdata <- subset(csvData, MACHINE.BUFFER == 'M' & ID == machineID)
  plot(newdata$MILLISECONDS_FROM_SIM_START, xlab="time (milliseconds)", newdata$CURRENT_MACHINE_AMOUNT_OF_WORK, ylab="items", type="s", col.axis = "navy blue")
  e <- "number of parts in machine"
  e <- paste(e, machineID)
  title(e, cex.main = 2, col.main= "navy blue")
  print(paste("machine", machineID, ":"))
  
  brokendata <- subset(newdata, STATE == "ISBROKEN")
  print(paste("nr of times broken: ", nrow(brokendata)))
  
  nrThrownAway <- 0
  for (row in 1:nrow(brokendata)) {
    price <- brokendata[row, "CURRENT_MACHINE_AMOUNT_OF_WORK"]
    nrThrownAway <- nrThrownAway + price
  }
  if (length(nrThrownAway) > 0){
    print(paste("nr of parts broken: ", nrThrownAway))
  }
}

for(i in buffers){
  newdata <- subset(csvData, MACHINE.BUFFER == 'B' & ID == i)
  print(paste("items in buffer", i, ":", tail(newdata, n=1)["CURRENT_MACHINE_AMOUNT_OF_WORK"]))
}

for(i in firstBuffers){
  newdata <- subset(csvData, MACHINE.BUFFER == 'B' & ID == i & MACHINE_NAME == 'SET')
  price <- 0
  for (row in 1:nrow(newdata)) {
    price <- price + newdata[row, "CURRENT_MACHINE_AMOUNT_OF_WORK"]
  }

  print(paste("items used from first buffer", i, ":", price))
}

print("Items in last buffers:")
for(i in lastBuffers){
  newdata <- subset(csvData, MACHINE.BUFFER == 'B' & ID == i & MACHINE_NAME == 'ADD')
  
  price <- 0
  for (row in 1:nrow(newdata)) {
    price <- price + as.numeric(newdata[row, "STATE"])
  }
  print(paste("items in buffer", i, ":", price))
  
}


#-----
#HKKLFA-211 Gemiddelde bezettingsgraad van buffers aantonen

#put all buffernumbers in a vector(needed for graph below)
newdata <- csvData[order(csvData[,"ID"]),]
newdata1 <- subset(newdata, MACHINE.BUFFER == 'B')
buffers1 <- newdata[!duplicated(newdata[c("ID")]),]
BufferNr <- vector(mode='numeric')
for(row in 1:nrow(buffers1)){
  sort(buffers1[row, "ID"])
  BufferNr[row] <- buffers1[row, "ID"]
  print(paste("Buffer: ", row, ", Nr: ", BufferNr[row], "buffers1", buffers1[row, "ID"]))
}
#calculate average and plot bar graph
print("Items in buffers:")
gemVector <- vector(mode='numeric')
for(i in BufferNr){
  newdata <- subset(csvData, MACHINE.BUFFER == 'B')
  buffersPerDay <- newdata[!duplicated(newdata[,c("SIM_DAY", "ID")]),]
  total <- 0
  count <- 0
  for (row in 1:nrow(buffersPerDay)) {
    if(buffersPerDay[row, "ID"]==i){
      total <- total + (buffersPerDay[row, "CURRENT_MACHINE_AMOUNT_OF_WORK"])
      count <- count + 1
    }
  }
  gem <- 0
  gem <- total/count
  gemVector[i+1] <- gem
  print(paste("Buffer: ", i, ", Total: ", total, ", Count: ",count, ", Gem: ", gem))
}
maxGem <- max(gemVector, na.rm = TRUE)
procentVector <- vector(mode='numeric')
for(i in BufferNr){
  procentVector[i+1] <- gemVector[i+1]/maxGem*100
}
procentVector <- procentVector[!is.na(procentVector)]
barplot(procentVector, main = "Gemiddelde buffer bezetting", xlab = "Buffer nummers", ylab = "bezetting in % ", names.arg = BufferNr)


#-----
#HKKLFA-212 Gemiddelde doorlooptijd van een complete tafel

#totalProduction
print("Gemiddelde doorlooptijd tafel: ")
newdata <- subset(csvData, MACHINE.BUFFER == 'M' & MACHINE_NAME == 'INPAKKEN' & STATE == 'FINISHEDWORK')
totalProduction <- sum(newdata$CURRENT_MACHINE_AMOUNT_OF_WORK)

#calculate workhours
newdata1 <- subset(csvData, MACHINE.BUFFER == 'M' & MACHINE_NAME == 'INPAKKEN' & STATE == 'TURNON')
Time <- head(newdata1,1)
StartTime <- Time[1, c("TIME_OF_DAY..H.M.")]
newdata2 <- subset(csvData, MACHINE.BUFFER == 'M' & MACHINE_NAME == 'INPAKKEN' & STATE == 'TURNOFF')
Time <- tail(newdata2,1)
FinishTime <- Time[1, c("TIME_OF_DAY..H.M.")]
StartTime<-gsub(":.*","",StartTime)
FinishTime<-gsub(":.*","",FinishTime)
WorkHours <- (as.numeric(as.character(FinishTime)) - as.numeric(as.character(StartTime)))
maxDays <- max(newdata$SIM_DAY, na.rm = TRUE)
Time <- WorkHours*maxDays
GemiddeldeDoorloopTijd <- Time/totalProduction
print(paste("Totale productie: ", totalProduction))
print(paste("Werkuren in hele simulatie: ", Time))
print(paste("gemiddelde doorlooptijd van een complete tafel (in uren): ", GemiddeldeDoorloopTijd))


#-----
#Aantal reparaties per simulatietijd

newdata <- subset(csvData, MACHINE.BUFFER == 'M' & STATE == 'REPAIRED')
aantalReparaties <- nrow(newdata)
print(paste("Aantal reparaties per simulatie: ",aantalReparaties))


#-----
#HKKLFA-210 Gemiddelde aantal bewerkingen per uur van de diverse machines berekenen

#put all machinenumbers in a vector(needed for graph below)
newdata <- csvData[order(csvData[,"ID"]),]
newdata1 <- subset(newdata, MACHINE.BUFFER == 'M')
machines <- newdata1[!duplicated(newdata1[c("ID")]),]
machineNr <- vector(mode='numeric')
for(row in 1:nrow(machines)){
  sort(machines[row, "ID"])
  machineNr[row] <- machines[row, "ID"]
  print(paste("Machines: ", row, ", Nr: ", machineNr[row], "machines", machines[row, "ID"]))
}

#calculate nr and plot bar graph
print(" aantal bewerkingen per machine:")
gemVector <- vector(mode='numeric')
for(i in machineNr){
  newdata <- subset(csvData, MACHINE.BUFFER == 'M' & STATE == 'FINISHEDWORK')
  total <- 0
  for (row in 1:nrow(newdata)) {
    if(newdata[row, "ID"]==i){
      total <- total + (newdata[row, "CURRENT_MACHINE_AMOUNT_OF_WORK"])
    }
  }
  gem <- 0
  gem <- total/Time
  gemVector[i+1] <- gem
  print(paste("Machine: ", i, ", Total: ", total, ", Tijd in uren: ",Time, ", Gem: ", gem))
}
gemVector <- gemVector[!is.na(gemVector)]
barplot(gemVector, main = "Gemiddelde aantal bewerkingen per uur van de diverse machines", xlab = "Machine id", ylab = "Aantal bewerkingen", names.arg = machineNr)

