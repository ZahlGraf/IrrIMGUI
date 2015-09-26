import getopt
import sys
import os
import re
import time
from datetime import date

def usage():
  print ""
  print "merge_release_notes.py -b <binary-list-file> -e <extra-release-notes-file> -o <output-file>"
  print ""
  print " Merges the binary list, the extra release notes into the version section of the output file together with the upcomming version notes."
  print ""

LatestVersionHeadlinePattern               = re.compile("^## .*Latest Version.*$")
UpcommingVersionPattern                    = re.compile("^### .*Upcomming:.*$");
UpcommingVersionHighlightsHeadlinePattern  = re.compile("^#### .*Highlights.*$");
UpcommingVersionFixesHeadlinePattern       = re.compile("^#### .*Fixes.*$");
UpcommingVersionDependencysHeadlinePattern = re.compile("^#### .*Dependency Versions.*$");
UpcommingVersionTestedHeadlinePattern      = re.compile("^#### .*Tested Build Variants.*$");
PostVersionHeadlinePattern                 = re.compile("^## .*$");
LastVersionHeadlinePattern                 = re.compile("^### .*Version.*$");
NothingPlannedPattern                      = re.compile("^\*.*nothing planned[ ]*$");
NonePattern                                = re.compile("^\*.*none[ ]*$");
ButtetPointPattern                         = re.compile("^[ ]*[*]+[ ]+.*$");
VersionHistoryHeadlinePattern              = re.compile("^## .*Version History.*$")
def readOutputFile(FileName, VersionString):
  CurrentVersionHeadlinePattern            = re.compile("^### .*Version "+VersionString+".*$");  

  FileContent = {
    "PreVersionText": [],
    "UpcommingHighlights": [],
    "UpcommingFixes": [],
    "UpcommingDependencies": [],
    "UpcommingTests": [],
    "LastVersionText": [],    
    "PostVersionText": [],
    "VersionHistory": [],
    "PostVersionHistory": []
  }
  
  CurrentState = "PreVersionText"
  SecondState = "None"
  
  print "[Note] Start parsing file "+FileName
  File = open(FileName, "r")
  for i, Line in enumerate(File):
    if CurrentState == "PreVersionText":
      FileContent["PreVersionText"].append(Line)
      if re.match(LatestVersionHeadlinePattern, Line):
        CurrentState = "LatestVersion"
        print "[Note] Found Latest Version Headline at line "+str(i)

    elif CurrentState == "LatestVersion":     
      if re.match(PostVersionHeadlinePattern, Line):
        CurrentState = "PostVersion"
        FileContent["PostVersionText"].append(Line)
        print "[Note] Found Next Chapter Headline at line "+str(i)

      elif re.match(CurrentVersionHeadlinePattern, Line):
        print "[Error] Found Current Version Headline at line "+str(i)
        sys.exit(1)
                
      elif re.match(LastVersionHeadlinePattern, Line):
        CurrentState = "LastVersion"
        FileContent["LastVersionText"].append(Line)
        print "[Note] Found Last Version Headline at line "+str(i)
      
      elif re.match(UpcommingVersionPattern, Line):
        CurrentState = "UpcommingVersion"
        print "[Note] Found Upcomming Version Headline at line "+str(i)

      else:
        FileContent["PreVersionText"].append(Line)
              
    elif CurrentState == "UpcommingVersion":
      if re.match(PostVersionHeadlinePattern, Line):
        CurrentState = "PostVersion"
        FileContent["PostVersionText"].append(Line)
        print "[Note] Found Next Chapter Headline at line "+str(i)

      elif re.match(CurrentVersionHeadlinePattern, Line):
        print "[Error] Found Current Version Headline at line "+str(i)
        sys.exit(1)
                              
      elif re.match(LastVersionHeadlinePattern, Line):
        CurrentState = "LastVersion"
        FileContent["LastVersionText"].append(Line)
        print "[Note] Found Last Version Headline at line "+str(i)
              
      elif re.match(UpcommingVersionHighlightsHeadlinePattern, Line):
        SecondState = "Highlights"
        print "[Note] Found Highlights at line "+str(i)

      elif re.match(UpcommingVersionFixesHeadlinePattern, Line):
        SecondState = "Fixes"
        print "[Note] Found Fixes at line "+str(i)
        
      elif re.match(UpcommingVersionDependencysHeadlinePattern, Line):
        SecondState = "Dependency"
        print "[Note] Found Dependency Versions at line "+str(i)
        
      elif re.match(UpcommingVersionTestedHeadlinePattern, Line):
        SecondState = "Compilers"
        print "[Note] Found Tested Compilers at line "+str(i)
        
      else:
      
        if SecondState == "Highlights":
          if not ( re.match(NonePattern, Line) or re.match(NothingPlannedPattern, Line) ):
            if re.match(ButtetPointPattern, Line):
              FileContent["UpcommingHighlights"].append(Line)

        if SecondState == "Fixes":
          if not ( re.match(NonePattern, Line) or re.match(NothingPlannedPattern, Line) ):
            if re.match(ButtetPointPattern, Line):
              FileContent["UpcommingFixes"].append(Line)

        if SecondState == "Dependency":
          if not ( re.match(NonePattern, Line) or re.match(NothingPlannedPattern, Line) ):
            if re.match(ButtetPointPattern, Line):
              FileContent["UpcommingDependencies"].append(Line)

        if SecondState == "Compilers":
          if not ( re.match(NonePattern, Line) or re.match(NothingPlannedPattern, Line) ):
            if re.match(ButtetPointPattern, Line):
              FileContent["UpcommingTests"].append(Line)

    elif CurrentState == "LastVersion":
      if re.match(PostVersionHeadlinePattern, Line):
        CurrentState = "PostVersion"
        FileContent["PostVersionText"].append(Line)
        print "[Note] Found Next Chapter Headline at line "+str(i)
        
      else:
        FileContent["LastVersionText"].append(Line)
              
    elif CurrentState == "PostVersion":
      FileContent["PostVersionText"].append(Line)
      if re.match(VersionHistoryHeadlinePattern, Line):
        CurrentState = "VersionHistory"
        print "[Note] Found Version History Headline at line "+str(i)
    
    elif CurrentState == "VersionHistory":
      if re.match(PostVersionHeadlinePattern, Line):
        CurrentState = "PostVersionHistory"
        FileContent["PostVersionHistory"].append(Line)
        print "[Note] Found Next Chapter Headline at line "+str(i)
      
      else:
        FileContent["VersionHistory"].append(Line)

    elif CurrentState == "PostVersionHistory":
      FileContent["PostVersionHistory"].append(Line)

    else:
      print "ERROR: Unknown Parsing state while parsing output file!"
      sys.exit(1)
      
  File.close()
    
  #print FileContent["LastVersionText"]
    
  return FileContent
  
def readExtraFile(FileName):
  FileContent = {
    "UpcommingHighlights": [],
    "UpcommingFixes": [],
    "UpcommingDependencies": [],
    "UpcommingTests": [],
  }
  
  SecondState = "None"
  print "[Note] Start parsing file "+FileName
  File = open(FileName, "r")
  for i, Line in enumerate(File):
          
    if re.match(UpcommingVersionHighlightsHeadlinePattern, Line):
      SecondState = "Highlights"
      print "[Note] Found Highlights at line "+str(i)

    if re.match(UpcommingVersionFixesHeadlinePattern, Line):
      SecondState = "Fixes"
      print "[Note] Found Fixes at line "+str(i)
          
    if re.match(UpcommingVersionDependencysHeadlinePattern, Line):
      SecondState = "Dependency"
      print "[Note] Found Dependency Versions at line "+str(i)
          
    if re.match(UpcommingVersionTestedHeadlinePattern, Line):
      SecondState = "Compilers"
      print "[Note] Found Tested Compilers at line "+str(i)
          
    else:
        
      if SecondState == "Highlights":
        if not ( re.match(NonePattern, Line) or re.match(NothingPlannedPattern, Line) ):
          if re.match(ButtetPointPattern, Line):
            FileContent["UpcommingHighlights"].append(Line)

      if SecondState == "Fixes":
        if not ( re.match(NonePattern, Line) or re.match(NothingPlannedPattern, Line) ):
          if re.match(ButtetPointPattern, Line):
            FileContent["UpcommingFixes"].append(Line)

      if SecondState == "Dependency":
        if not ( re.match(NonePattern, Line) or re.match(NothingPlannedPattern, Line) ):
          if re.match(ButtetPointPattern, Line):
            FileContent["UpcommingDependencies"].append(Line)

      if SecondState == "Compilers":
        if not ( re.match(NonePattern, Line) or re.match(NothingPlannedPattern, Line) ):
          if re.match(ButtetPointPattern, Line):
            FileContent["UpcommingTests"].append(Line)
  
  File.close()
  
  #print FileContent["UpcommingHighlights"]
  #print FileContent["UpcommingFixes"]
  #print FileContent["UpcommingDependencies"]
  #print FileContent["UpcommingTests"]
      
  return FileContent
  
def startMerge(OutputFile, BinaryFile, ExtraNotesFile):
  VersionFile = open("version.txt", "r")
  
  for Line in VersionFile:
    VersionString = Line.rstrip()
  
  VersionFile.close()
  
  Output     = readOutputFile(OutputFile, VersionString)
  BinaryList = readExtraFile(BinaryFile)
  ExtraNotes = readExtraFile(ExtraNotesFile)
  
  ReadmeFileContent = {
    "PreVersionText": [],
    "UpcommingHighlights": [],
    "UpcommingFixes": [],
    "UpcommingDependencies": [],
    "UpcommingTests": [],
    "LastVersionText": [],
    "PostVersionText": [],
    "VersionHistory": [],
    "PostVersionHistory": []
  }
  
  for Line in Output["PreVersionText"]:
    ReadmeFileContent["PreVersionText"].append(Line)

  for Line in Output["UpcommingHighlights"]:
    ReadmeFileContent["UpcommingHighlights"].append(Line)

  for Line in BinaryList["UpcommingHighlights"]:
    ReadmeFileContent["UpcommingHighlights"].append(Line)

  for Line in ExtraNotes["UpcommingHighlights"]:
    ReadmeFileContent["UpcommingHighlights"].append(Line)

  for Line in Output["UpcommingFixes"]:
    ReadmeFileContent["UpcommingFixes"].append(Line)
    
  for Line in BinaryList["UpcommingFixes"]:
    ReadmeFileContent["UpcommingFixes"].append(Line)

  for Line in ExtraNotes["UpcommingFixes"]:
    ReadmeFileContent["UpcommingFixes"].append(Line)

  for Line in Output["UpcommingDependencies"]:
    ReadmeFileContent["UpcommingDependencies"].append(Line)

  for Line in BinaryList["UpcommingDependencies"]:
    ReadmeFileContent["UpcommingDependencies"].append(Line)

  for Line in ExtraNotes["UpcommingDependencies"]:
    ReadmeFileContent["UpcommingDependencies"].append(Line)
    
  for Line in Output["UpcommingTests"]:
    ReadmeFileContent["UpcommingTests"].append(Line)

  for Line in BinaryList["UpcommingTests"]:
    ReadmeFileContent["UpcommingTests"].append(Line)

  for Line in ExtraNotes["UpcommingTests"]:
    ReadmeFileContent["UpcommingTests"].append(Line)
    
  for Line in Output["PostVersionText"]:
    ReadmeFileContent["PostVersionText"].append(Line)

  for Line in Output["LastVersionText"]:
    ReadmeFileContent["VersionHistory"].append(Line)
    
  for Line in Output["VersionHistory"]:
    ReadmeFileContent["VersionHistory"].append(Line)
    
  for Line in Output["PostVersionHistory"]:
    ReadmeFileContent["PostVersionHistory"].append(Line)
    
  writeToOutput(ReadmeFileContent, VersionString)
    
def writeToOutput(ReadmeFileContent, VersionString):
  Today = date.today()
  Date = str(Today.day)+"."+str(Today.month)+"."+str(Today.year)

  File = open("README.md", "w")
    
  for Line in ReadmeFileContent["PreVersionText"]:
    File.write(Line)

  File.write("### Upcomming: master-branch (unstable not tested yet)\n")    
  File.write("\n")    
  File.write("#### Highlights\n")    
  File.write("* nothing planned\n")    
  File.write("\n")    
  File.write("#### Fixes\n")    
  File.write("* nothing planned\n")    
  File.write("\n")    
  File.write("#### Dependency Versions\n")    
  if len(ReadmeFileContent["UpcommingDependencies"]) == 0:
    File.write("* none")
  else:
    for Line in ReadmeFileContent["UpcommingDependencies"]:
      File.write(Line)
  File.write("\n")    
  File.write("\n")    
  File.write("### "+Date+": Version "+VersionString+" ([Download Source](https://github.com/ZahlGraf/IrrIMGUI/archive/v"+VersionString+".zip)) ([Download Binaries](https://irrimgui.netzeband.eu/binaries/irrimgui_v"+VersionString+".zip))\n")    
  File.write("\n")    

  for i, Line in enumerate(ReadmeFileContent["UpcommingHighlights"]):
    if i == 0:
      File.write("#### Highlights\n")
    File.write(Line)
    if i == len(ReadmeFileContent["UpcommingHighlights"])-1:
      File.write("\n")    
  
  for i, Line in enumerate(ReadmeFileContent["UpcommingFixes"]):
    if i == 0:
      File.write("#### Fixes\n")
    File.write(Line)
    if i == len(ReadmeFileContent["UpcommingFixes"])-1:
      File.write("\n")    
  
  for i, Line in enumerate(ReadmeFileContent["UpcommingDependencies"]):
    if i == 0:
      File.write("#### Dependency Versions\n")
    File.write(Line)
    if i == len(ReadmeFileContent["UpcommingDependencies"])-1:
      File.write("\n")    
  
  for i, Line in enumerate(ReadmeFileContent["UpcommingTests"]):
    if i == 0:
      File.write("#### Tested Build Variants\n")
    File.write(Line)
    if i == len(ReadmeFileContent["UpcommingTests"])-1:
      File.write("\n")    
  
  for Line in ReadmeFileContent["PostVersionText"]:
    File.write(Line)

  for Line in ReadmeFileContent["VersionHistory"]:
    File.write(Line)
    
  for Line in ReadmeFileContent["PostVersionHistory"]:
    File.write(Line)
  
  File.close()
  
if __name__ == "__main__":
  try:
    OptionList, Arguments = getopt.getopt(sys.argv[1:], "b:e:o:", ["--binary", "--extra-notes", "--output"])
    
  except getopt.GetoptError as Error:
    print str(Error)
    usage()
    sys.exit(1)
    
  BinaryFile=""
  ExtraNotesFile=""
  OutputFile=""
  for Option, Argument in OptionList:
    if Option in ["-b", "--binary"]:
      BinaryFile=Argument
      
    elif Option in ["-e", "--extra-notes"]:
      ExtraNotesFile=Argument

    elif Option in ["-o", "--output"]:
      OutputFile=Argument
      
  if not os.path.isfile(BinaryFile):
    print "ERROR: Binary list file "+BinaryFile+" is not a valid file..."
    sys.exit(1)
    
  if not os.path.isfile(ExtraNotesFile):
    print "ERROR: Extra notes file "+ExtraNotesFile+" is not a valid file..."    
    sys.exit(1)
    
  if not os.path.isfile(OutputFile):
    print "ERROR: Output file "+OutputFile+" is not a valid file..."    
    sys.exit(1)

  startMerge(OutputFile, BinaryFile, ExtraNotesFile)