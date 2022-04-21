#Jackson Esco
#CS-210 SNHU
#April 18th, 2022

import re
import string
import os.path
from os import path


#Function that returns a list of all unique items from "Test Inventory" and all their occurrances
def CountAll():
    #Open our test inventory file in read mode
    text = open("TestInventory.txt", "r")

    #Create an empty dictionary to store each word
    dictionary = dict()

    #Check each line of the input file
    for line in text:
        #format items in "TestInventory" for easier matching
        line = line.strip()
        word = line.lower()
        
        #Check if the word is in the dictionary
        if word in dictionary:
            #Increment number of times the word appears
            dictionary[word] = dictionary[word] + 1
        else:
            #If the word is not in the dictionary, add it to the dicitonary with a value of 1
            dictionary[word] = 1

    #Print dictionary
    for key in list (dictionary.keys()):
        print(key.capitalize(), ":", dictionary[key])

    #Close "TestInventory"
    text.close()

#This function returns the number of occurances of a specified item in "TestInventory"
def CountInstances(searchTerm):

    #Convert search term to lowercase for better matching
    searchTerm = searchTerm.lower()

    #Open "TestInventory" in read mode
    text = open("TestInventory.txt", "r")

    #Create variable to track the number of times a word is seen in the list
    wordCount = 0

    #Check each line of the input file
    for line in text:
        #format the list of word for easier matching
        line = line.strip()
        word = line.lower()
        
        #Check if the found word is equal to the user's input
        if word == searchTerm:
            #Increment number of times each word appears
            wordCount += 1

    #Return the number of times the search term was found
    return wordCount

    #Close "TestInventory" file
    text.close()

# A function that returns each item in "TestInventory" and the number of times it appears in the list represented as a historgram
def CollectData():
    #Open the "TestInventory" in read mode
    text = open("TestInventory.txt", "r")

    #Create and/or write the file frequency.dat
    frequency = open("frequency.dat", "w")

    #Create an empty dictionary to store words
    dictionary = dict()

    #Check each line of "TestInventory"
    for line in text:
        #format text for easier matching
        line = line.strip()
        word = line.lower()
        
        #Check if the word is already in the dictionary
        if word in dictionary:
            #Increment number of times each word appears
            dictionary[word] = dictionary[word] + 1
        else:
            #If the word is not in the dictionary, add it to the dicitonary with a value of 1
            dictionary[word] = 1

    #Write each key and value pair to frequency.dat
    for key in list (dictionary.keys()):
        #Format the key-value pair as strings followed by a newline.
        frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    #Close opened files
    text.close()
    frequency.close()
