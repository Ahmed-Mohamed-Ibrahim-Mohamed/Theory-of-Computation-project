import rstr
import re 
regex=input("Enter the regular expression :\n")
print("Examples for this regular expression are :\n",rstr.xeger(regex))
ch=input("do yo want to check specific string acceptance :Enter Y :\n")
if ch =='y' or ch=='Y':
        string=input("Enter string :\n")
        if re.fullmatch(regex,string):
            print("accepted ")
        else:
            print ("not accepted ")
