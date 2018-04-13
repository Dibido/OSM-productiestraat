csvStatis <- read.csv(file="C:/Users/dhnus/git/productiestraat-spaanders-development/productiestraat-spaanders/mingw/Exe1/MachineRepairTime.csv", header=TRUE)





print('Totaal aantal verloren tijd door reparaties: ')

print(sum(csvStatis$X116))



print('Standaarddeviatie voor alle reparaties: ')

print(sd(csvStatis$X116))



out <- split( csvStatis , f = csvStatis$X4 )



for (i in 1:9){
  
  a <- c(i )
  
  print(' ')
  
  print('Tandaarddeviatie van de reparaties van deze machine')
  
  print (a)
  
  print(sd(out[[i]]$X116))
  
  print('Gemiddelde van de raparaties van deze machine')
  
  print(mean(out[[i]]$X116))  
  
  
  
  hist(out[[i]]$X116, breaks=40 , main=a , xlab="Standaarddeviatie Machine")
  
}







