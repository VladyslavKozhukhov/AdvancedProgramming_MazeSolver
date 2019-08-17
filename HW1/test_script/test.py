from os import listdir
from os.path import isfile, join
import subprocess

expectedOutput = "expected_output"
input = "input"
output = "output"


def strip(s):
    s = s.replace('\r\n', '\n')
    if s.endswith('\n'):
        s = s[:-1]
    return s


def getFilesInPath(path):
    return [f for f in listdir(path) if isfile(join(path, f))]


#os.system("make")
for file in getFilesInPath(input):

    inputFilePath = input + "/" + file
    outputFilePath = output + "/" + file
    expectedOutputFilePath = expectedOutput + "/" + file.replace("in", "out")

    commandRes = subprocess.Popen(['./ex1', inputFilePath, outputFilePath], stdout=subprocess.PIPE,
                                  stderr=subprocess.STDOUT)
    stdout = commandRes.communicate()[0].decode('UTF-8')

    with open(expectedOutputFilePath, "r") as expOutput:
        expOutputFileContent = strip(expOutput.read())
    if "FAIL" in file:
        outputContent = strip(stdout)
    else:
        with open(outputFilePath, "r") as outFile:
            outputContent = strip(outFile.read())
    if expOutputFileContent == outputContent:
        print("PASSED " + file + "\n")
    else:
        print("FAILED " + file)
        print("expected:\n" + expOutputFileContent)
        print("got:\n" + outputContent + "\n")
