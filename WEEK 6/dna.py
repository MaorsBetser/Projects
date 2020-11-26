import csv
import sys
import re

if len(sys.argv) != 3:
    print("Incorrect usage : Python dna.py *required CSV* *DNA sequences*")
    sys.exit()

data = {}
                #dict for storing the CSVFile
with open(sys.argv[1], 'r') as csvfile:
    reader=csv.reader(csvfile, skipinitialspace=True, quotechar="'")
    for row in reader:
        data[row[0]]=row[1:]
                #Opens given CSV and loads in to dict [Name : :DNA" ]

    dnaSeq = open(sys.argv[2], "r")
    dnaSeqStr = str(dnaSeq.read())
                #Opens dna Sequence and loads in to String

    dataList = []
    matchesCnt = []
    dnaRepeatedList = []
                #Declarations for lists

    for value in data['name']:
        temp = [value]
        dataList.append(temp)
                #Get the DNA strings

    for i in range(len(dataList)):
        currentDna = str(dataList[i])
        if "[" in currentDna:
            currentDna = currentDna.replace('[', '')
        if "]" in currentDna:
            currentDna = currentDna.replace(']', '')
        if "'" in currentDna:
            currentDna = currentDna.replace("'", "")
                #Removes special characters in The current Dna
       

        dnaRepeated = 0
        mostRepeatedDna = len(max(re.findall('((?:' + re.escape(currentDna) + ')*)', dnaSeqStr), key = len))
                #finds the longest consecutive DNA string inside the DNA file

        timesRepeated = int(mostRepeatedDna / len(currentDna))
        matchesCnt.append(timesRepeated)
        matchesCntStr = str(matchesCnt)                          
                #Turns the list to a string in order to compare it later
    matchFound = False

    for key,value in data.items():
        valueStr = str(value)
        valueStr = valueStr.replace("'", "")
                #Removes special characters for correct string comparing

        if valueStr == matchesCntStr:
            print(f"The Match is {key}")
            matchFound = True
    
    if matchFound == False:
        print("No Matches Found")