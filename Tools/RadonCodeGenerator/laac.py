import re
import sys
from pathlib import Path
#from enum import Enum

class Stack:

    def __init__(self):
        self.stack = []

    def push(self, value):
        if value not in self.stack:
            self.stack.append(value)
        
    def pop(self):
        if len(self.stack) > 0:
            return self.stack.pop()

        else:
            return None

    def peek(self):     
	    return self.stack[-1]

class Logger:

    @staticmethod
    def format(verbosity:str, message:str) -> str:
        return '{0} {1}> {2}'.format(Config.LAACPrefix, verbosity, message)

    @staticmethod
    def log(message:str) -> str:
        formatted = Logger.format('Log', message)
        print(formatted)

        return formatted

    @staticmethod
    def raw(message:str) -> None:
        print(message)

    @staticmethod
    def error(errorType:str, errorMessage:str) -> str:
        formatted = Logger.format('Error', '[{0}] {1}'.format(errorType, errorMessage))
        print(formatted)

        return formatted

    @staticmethod
    def fatal(errorType:str, errorMessage:str) -> str:
        formatted = Logger.format('Fatal', '[{0}] {1}'.format(errorType, errorMessage))
        print(formatted)

        return formatted

    @staticmethod
    def parseError(fileName:str, lineNumber:str, line:str, errorMessage:str, errorTokenIndex=-1) -> None:
        formatted = Logger.fatal('Parse Error', '{0} in {1}({2}): {3}'.format(errorMessage, fileName, lineNumber, line))

        if errorTokenIndex != -1:
            lineStartIndex = formatted.find(line)
            Logger.raw((lineStartIndex + errorTokenIndex) * ' ' + '^')

    @staticmethod
    def suggest(message:str) -> None:
        Logger.raw('    -Suggestion> {0}'.format(message))

class Command:

    @staticmethod
    def getShorthand():
        raise NotImplementedError

    @staticmethod
    def getFullSpec():
        raise NotImplementedError

    @staticmethod
    def getUsage():
        raise NotImplementedError

    @staticmethod
    def process(arguments:list):
        raise NotImplementedError

    @staticmethod
    def isShorthandCommand(commandLine:str):
        return commandLine.startsWith('-')

    @staticmethod
    def isFullSpecCommand(commandLine:str):
        return commandLine.startsWith('--')

    @staticmethod
    def isCommand(commandLine:str):
        return isShorthandCommand(commandLine) or isFullSpecCommand(commandLine)

class CommandDefinition(Command):
    
    @staticmethod
    def getShorthand():
        return 'd'

    @staticmethod
    def getFullSpec():
        return 'definition'

    @staticmethod
    def getUsage():
        return '<definitionFile1> [definitionFIle2] ... # one or more definition files are allowed'

    @staticmethod
    def process(arguments:list):
        if len(arguments) == 0:
            Logger.error('Invalid Arguments', 'Definition file not specified')
            return False

        for arg in arguments:
            Config.DefinitionFiles.append(arg)

        arguments.clear()

        return True

class CommandTemplate(Command):

    @staticmethod
    def getShorthand():
        return 't'

    @staticmethod
    def getFullSpec():
        return 'template'

    @staticmethod
    def getUsage():
        return '<templateFile>'

    @staticmethod
    def process(arguments:list):
        numArgs = len(arguments)
        if numArgs == 0:
            Logger.error('Invalid Arguments', 'Template file not specified')
            return False

        elif numArgs > 1:
            Logger.error('Invalid Arguments', 'Too many template files')
            return False

        Config.TemplateFileName = arguments[0]
        return True

class CommandOutput(Command):

    @staticmethod
    def getShorthand():
        return 'o'

    @staticmethod
    def getFullSpec():
        return 'output'

    @staticmethod
    def getUsage():
        return '<outputFile>'

    @staticmethod
    def process(arguments:list):
        numArgs = len(arguments)
        if numArgs == 0:
            Logger.error('Invalid Arguments', 'Template file not specified')
            return False

        elif numArgs > 1:
            Logger.error('Invalid Arguments', 'Too many template files')
            return False

        Config.TemplateFileName = arguments[0]
        return True

class CommandHelp(Command):

    @staticmethod
    def getShorthand():
        return 'h'

    @staticmethod
    def getFullSpec():
        return 'help'

    @staticmethod
    def getUsage():
        return ''

    @staticmethod
    def process(arguments:list):
        Logger.raw('Commands:')

        for com in Config.Commands:
            Logger.raw(com.__name__ + ': -' + com.getShorthand() + ' or --' + com.getFullSpec() + ' ' + com.getUsage())

        return True

class CommandInlineDefinition(Command):
    
    @staticmethod
    def getShorthand():
        return 'D'

    @staticmethod
    def getFullSpec():
        return 'Definition'

    @staticmethod
    def getUsage():
        return '<definition1>=[value] <definition2>=[value] ... # one or more definitions are allowed'

    @staticmethod
    def process(arguments:list):


        for arg in arguments:
            Config.DefinitionFiles.append(arg)

        arguments.clear()

        return True

class CommandVerbose(Command):

    @staticmethod
    def getShorthand():
        return 'v'

    @staticmethod
    def getFullSpec():
        return 'verbose'

    @staticmethod
    def getUsage():
        return ''

    @staticmethod
    def process(arguments:list):
        Config.bVerbose = True

        return True

class Config:
    LAACVersion = "1.0.0"
    LAACPrefix = "LAAC"

    bVerbose = False

    DefinitionFiles = [ ]
    TemplateFileName = None
    OutputFileName = None
    Definitions = { }

    Commands = [ CommandHelp, CommandDefinition, CommandTemplate, CommandOutput, CommandInlineDefinition, CommandVerbose ]

class CommandParser:

    def __init__(self, arguments:list):
        self.arguments = arguments
        self.commandIndexes = [ ]
        self.parsedCommands = [ ]

    def parse(self):
        for i, arg in enumerate(self.arguments):
            if Command.isCommand(arg):
                self.commandIndexes.append(i)

        if len(self.commandIndexes) == 0:
            Logger.error('Invalid Arguments', 'No command to execute')
            Logger.log(CommandHelp.getUsage())

        else:
            for i in self.commandIndexes:
                arg = self.arguments[i]
                foundCommand = None

                for command in Config.Commands:
                    if Command.isShorthandCommand(arg):
                        if arg[1:] == command.getShorthand():
                            foundCommand = command

                    elif Command.isFullSpecCommand(arg):
                        if arg[2:] == command.getFullSpec():
                            foundCommand = command

                if foundCommand:
                    if foundCommand in self.parsedCommands:
                        Logger.fatal('Invalid Arguments', 'Duplicate command found: ' + arg)
                        return False
                    else:
                        self.parsedCommands.append(foundCommand)
                else:
                    Logger.error('Invalid Arguments', 'No such command: ' + arg)

        return True

    def execute(self):
        for i, c in enumerate(self.parsedCommands):
            if not c.process(self.arguments[self.commandIndexes[i]+1:self.commandIndexes[i+1]]):
                return False

        return True

class Definitions:
    __definitions = { }
    __importedModules = [ ]

    @staticmethod
    def set(newDefinitions:dict) -> None:
        _Definitions__definitions = newDefinitions

    @staticmethod
    def get() -> dict:
        return _Definitions__definitions

    @staticmethod
    def getImportedModules() -> list:
        return _Definitions__importedModules

class Preprocessor:

    @staticmethod
    def getKeyword() -> str:
        raise NotImplementedError

    @staticmethod
    def getParameters() -> list:
        raise NotImplementedError

    @staticmethod
    def hasReplacement() -> bool:
        raise NotImplementedError

    @staticmethod
    def process(parser, params:list):
        raise NotImplementedError

    class Parameter:
        
        @staticmethod
        def getType() -> type:
            raise NotImplementedError

        @staticmethod
        def getPattern() -> str:
            raise NotImplementedError

        @staticmethod
        def convert(paramString:str):
            raise NotImplementedError

    class IntParameter(Parameter):

        @staticmethod
        def getType() -> type:
            return int

        @staticmethod
        def getPattern() -> str:
            return r'\d+'

        @staticmethod
        def convert(paramString:str) -> int:
            return int(paramString)

    class FloatParameter(Parameter):

        @staticmethod
        def getType() -> type:
            return float

        @staticmethod
        def getPattern() -> str:
            return r'[-+]?(?:(?:\d*\.\d+)|(?:\d+\.?))(?:[Ee][+-]?\d+)?'

        @staticmethod
        def convert(paramString:str) -> float:
            return float(paramString)

    class CharParameter(Parameter):

        @staticmethod
        def getType() -> type:
            return str

        @staticmethod
        def getPattern() -> str:
            return r'(?:\"(.)\")|' + r"(?:\'(.)\')"

        @staticmethod
        def convert(paramString:str):
            match = re.match(Preprocessor.CharParameter.getPattern(), paramString)
            if match.group(1):
                result = match.group(1)
            else:
                result = match.group(2)

            return result

    class StringParameter(Parameter):

        @staticmethod
        def getType() -> type:
            return str

        @staticmethod
        def getPattern() -> str:
            return r"(?:\'(.*)\')|" + r'(?:\"(.*)\")'

        @staticmethod
        def convert(paramString:str):
            match = re.match(Preprocessor.StringParameter.getPattern(), paramString)
            if match.group(1):
                result = match.group(1)
            else:
                result = match.group(2)

            return result

class ProcRequire(Preprocessor):
    
    @staticmethod
    def getKeyword() -> str:
        return 'require'

    @staticmethod
    def getParameters() -> list:
        return [ Preprocessor.StringParameter ]

    @staticmethod
    def hasReplacement() -> bool:
        return False

    @staticmethod
    def process(parser, params:list) -> None:
        requiredFileName = params[0]

        if requiredFileName == parser.workingFileStack.peek():
            return

        if requiredFileName in parser.filesIncludedOnce and (requiredFileName in parser.definitionFiles or requiredFileName in parser.importedFiles):
            return

        parser.workingFileStack.push(requiredFileName)

        bSuccess, parsed = parser.parseFile(requiredFileName)
        if bSuccess:
            parser.parsedDefinitions.update(parsed)
            parser.importedFiles.append(requiredFileName)

        parser.workingFileStack.pop()

class ProcIncludeOnce(Preprocessor):

    @staticmethod
    def getKeyword() -> str:
        return 'include_once'

    @staticmethod
    def getParameters() -> list:
        return [ ]

    @staticmethod
    def hasReplacement() -> bool:
        return False

    @staticmethod
    def process(parser, params:list) -> None:
        parser.filesIncludedOnce.add(parser.workingFileStack.peek())

class ProcUndef(Preprocessor):

    @staticmethod
    def getKeyword() -> str:
        return 'undef'

    @staticmethod
    def getParameters() -> list:
        return [ Preprocessor.StringParameter ]

    @staticmethod
    def hasReplacement() -> bool:
        return False

    @staticmethod
    def process(parser, params:list) -> None:
        keyToUndef = params[0]

        try:
            del parser.parsedDefinitions[keyToUndef]
        except KeyError:
            pass

class ProcToChar(Preprocessor):

    @staticmethod
    def getKeyword() -> str:
        return 'to_char'

    @staticmethod
    def getParameters() -> list:
        return [ Preprocessor.IntParameter ]

    @staticmethod
    def hasReplacement() -> bool:
        return True

    @staticmethod
    def process(parser, params:list) -> str:
        return chr(params[0])

class ProcCharCode(Preprocessor):

    @staticmethod
    def getKeyword() -> str:
        return 'char_code'

    @staticmethod
    def getParameters() -> list:
        return [ Preprocessor.CharParameter ]

    @staticmethod
    def hasReplacement() -> bool:
        return True

    @staticmethod
    def process(parser, params:list) -> str:
        return ord(params[0])

class DefinitionParser:
    
    CommentToken = '##'
    PreprocessorToken = '#'
    DefinitionDelimiter = ':='

    Preprocessors = [ ProcRequire, ProcIncludeOnce, ProcUndef, ProcToChar, ProcCharCode ]

    def __init__(self, definitionFiles:list, additionalDefinitions:list):
        self.definitionFiles = definitionFiles
        self.workingFileStack = Stack()
        self.additionalDefinitions = additionalDefinitions
        self.parsedDefinitions = { }
        self.filesIncludedOnce = set()
        self.importedFiles = [ ]

    def log(self):
        print("Definition Files: {0}".format(self.definitionFiles),
              "AdditionalDefinitions: {0}".format(self.additionalDefinitions),
              "ParsedDefinitions: {0}".format(self.parsedDefinitions),
              "FilesIncludedOnce: {0}".format(self.filesIncludedOnce),
              "ImportedFiles: {0}".format(self.importedFiles), sep = '\n')

    @staticmethod
    def loadFile(fileName:str) -> str:
        fileContent = None

        if Path(fileName).is_file():
            try:
                fpDefinition = open(fileName, 'rt')
                fileContent = fpDefinition.read()
                fpDefinition.close()

            except OSError as error:
                Logger.error('File Operation Failure', error.strerror)

        else:
            Logger.error('File Operation Failure', 'No such file: ' + fileName)

        return fileContent

    @staticmethod
    def restoreToken(string:str, token:str, bRemoveToken=False, bIgnoreEscapeSequence=True) -> str:
        result = string

        escTokenIndex = result.find('\\' + token)
        while escTokenIndex != -1:

            if not bIgnoreEscapeSequence:
                if escTokenIndex != 0 and string[escTokenIndex - 1] == '\\':
                    escTokenIndex = result.find('\\' + token, escTokenIndex + 2)
                    continue

            result = result[:escTokenIndex] + result[(escTokenIndex + 2 if bRemoveToken else escTokenIndex + 1):]
            escTokenIndex = result.find('\\' + token)

        return result

    @staticmethod
    def removeComments(content:str) -> str:
        result = content

        commentStartIndex = result.find(DefinitionParser.CommentToken)
        while commentStartIndex != -1:

            if commentStartIndex != 0 and result[commentStartIndex - 1] == '\\':
                commentStartIndex = result.find(DefinitionParser.CommentToken, commentStartIndex + len(CommentToken))
                continue

            commentEndIndex = result.find('\n', commentStartIndex)
            if commentEndIndex == -1:
                result = result[:commentStartIndex]

            else:
                result = result[:commentStartIndex] + result[commentEndIndex + 1:]

            commentStartIndex = result.find(DefinitionParser.CommentToken, commentStartIndex)

        return result

    @staticmethod
    def mergeLines(content:str) -> str:
        return DefinitionParser.restoreToken(content, '\n', True, False)

    @staticmethod
    def parseQuotes(line:str, start=0) -> (str, list):
        result = line
        quoteBlocks =  [ ]

        quoteBlockMatch = re.search(r"(?:(?P<QuoteBlock>\'.*\'))|(?:(?P<DoubleQuoteBlock>\".*\"))", line[start:])
        while quoteBlockMatch:

            quoteBlock = quoteBlockMatch.group('QuoteBlock')
            if quoteBlock:
                blockStart, blockEnd = quoteBlockMatch.span(1)
            else:
                quoteBlock = quoteBlockMatch.group('DoubleQuoteBlock')
                blockStart, blockEnd = quoteBlockMatch.span(2)

            quoteBlocks.append(quoteBlock)
            result = line[:blockStart] + '\0' + line[blockEnd:] #line[:blockStart - 1] + '\0' + line[blockEnd + 1:]
            quoteBlockMatch = re.search(r"(?:(?P<QuoteBlock>\'.*\'))|(?:(?P<DoubleQuoteBlock>\".*\"))", result)

        return (result, quoteBlocks)

    # preprocessors do not raise any error instead, they output error message and ignore the ones with problems
    def parsePreprocessors(self, fileName:str, content:str) -> str:
        lines = content.splitlines()
        for i, line in enumerate(lines):

            procStartIndex = line.find(DefinitionParser.PreprocessorToken)
            while procStartIndex != -1:
    
                if procStartIndex != 0 and line[procStartIndex - 1] == '\\':
                    procStartIndex = line.find(DefinitionParser.PreprocessorToken, procStartIndex + len(PreprocessorToken))
    
                else:
                    lines[i], quoteBlocks = self.parseQuotes(line, procStartIndex)
                    ogLine = line
                    line = lines[i]
                    lineEnd = len(line)

                    # preprocessor
                    #^ : current
                    current = procStartIndex + 1
                    whitespaceChars = [' ', '\t', '\r']

                    # skips any whitespace between the token '#' and the keyword
                    def skipIf(condition) -> int:
                        cursor = current
                        while cursor < lineEnd and condition(cursor):
                            cursor += 1
                        return cursor


                    current = skipIf(lambda p: line[p] in whitespaceChars)

                    parenStart = line.find('(', current)
                    if parenStart != -1:
                        parenEnd = line.find(')', parenStart + 1)
                        if parenEnd == -1:
                            Logger.parseError(fileName, i + 1, ogLine, "Unfinished preprocessor block: expected ')'")
                            break

                    if parenStart != -1:
                        procKeyword = line[current:parenStart].rstrip()
                        current = parenStart + 1
                        paramEnd = parenEnd
                        # require ( 'a.def')
                        #          ^
                    else:
                        procKeywordEnd = skipIf(lambda p: line[p] not in whitespaceChars)
                        procKeyword = line[current:procKeywordEnd]
                        current = procKeywordEnd
                        paramEnd = lineEnd
                        # require 'a.def'
                        #        ^

                    bParamError = False
                    numFoundQuoteBlocks = 0
                    parsedParams = [ ]
                    while current < paramEnd:
                        current = skipIf(lambda p: line[p] in whitespaceChars)
                        if current == paramEnd:
                            break

                        # if this is not the first parameter being parsed
                        if parsedParams:
                            if parenStart == -1:
                                Logger.parseError(fileName, i + 1, ogLine, "Ill-formed parameters: no more parameters are allowed")
                                Logger.suggest('Parenthesization is suggested for more than one params')
                                bParamError = True
                                break

                            else:
                                if line[current] == ',':
                                    current += 1
                                    current = skipIf(lambda p: line[p] in whitespaceChars)

                                else:
                                    Logger.parseError(fileName, i + 1, ogLine, "Ill-formed parameter: expected ','", current)
                                    bParamError = True
                                    break
                                
                        if line[current] == '\0':
                            parsedParams.append(quoteBlocks[numFoundQuoteBlocks])
                            numFoundQuoteBlocks += 1
                            current += 1

                        else:
                            if parenStart == -1:
                                currentEnd = skipIf(lambda p: line[p] not in whitespaceChars)
                            else:
                                currentEnd = skipIf(lambda p: p < parenEnd and line[p] not in whitespaceChars)

                            parsed = line[current:currentEnd]
                            if parsed:
                                parsedParams.append(parsed)

                            current = currentEnd

                    if bParamError:
                        break
    
                    currentProc = None
                    for proc in DefinitionParser.Preprocessors:
                        if proc.getKeyword() == procKeyword:
                            currentProc = proc
                            break
    
                    if currentProc:
                        protoParams = currentProc.getParameters()
                        numParams = len(protoParams)
                        numParsedParams = len(parsedParams)

                        if numParsedParams > numParams:
                            Logger.parseError(fileName, i + 1, ogLine, 'Too many parameters for preprocessor "{0}"'.format(procKeyword))
                            Logger.suggest('expected num of parameters: {0}'.format(numParams))

                        elif numParsedParams < numParams:
                            Logger.parseError(fileName, i + 1, ogLine, 'Not enough parameters for preprocessor "{0}"'.format(procKeyword))
                            Logger.suggest('expected num of parameters: {0}'.format(numParams))

                        else:
                            convertedParams = [ ]
                            bMatchError = False
                            for j, par in enumerate(parsedParams):
                                currentProtoParam = currentProc.getParameters()[j]

                                if re.match(currentProtoParam.getPattern(), par):
                                    convertedParams.append(currentProtoParam.convert(par))

                                else:
                                    bMatchError = True
                                    Logger.parseError(fileName, i + 1, ogLine, 'Invalid parameter "{1}" for preprocessor "{0}"'.format(procKeyword, par))
                                    break
                            
                            if not bMatchError:
                                repl = currentProc.process(self, convertedParams)

                                if currentProc.hasReplacement():
                                    lines[i] = line[:procStartIndex] + repl + line[procStartIndex:]
                                    line = lines[i]
                                    procStartIndex += len(repl)

                    break
            
            if procStartIndex != -1:
                lines[i] = line[:procStartIndex]
        
        return '\n'.join(lines)

    def preprocess(self, fileName:str, content:str) -> str:
        result = self.removeComments(content)
        result = self.mergeLines(result)
        result = self.parsePreprocessors(fileName, result)

        result = self.restoreToken(result, DefinitionParser.CommentToken)
        result = self.restoreToken(result, DefinitionParser.PreprocessorToken)

        return result

    @staticmethod
    def countNewLines(string:str, start:int = 0, end:int = -1):
        numNewLines = 0

        newLineIndex = str.find(string, '\n', start, end)
        while newLineIndex != -1:
            numNewLines += 1

            newLineIndex = str.find(string, '\n', newLineIndex + 1, end)

        return numNewLines

    @staticmethod
    def checkForError(fileName:str, content:str) -> bool:
        bError = False

        # checks for any escape sequence that was not properly parsed
        for i, line in enumerate(content.splitlines()):

            escIndex = line.find('\\')
            while escIndex != -1:

                if not bError:
                    bError = True

                Logger.parseError(fileName, i + 1, line, 'Unexpected symbol found', escIndex)
                escIndex = line.find('\\', escIndex + 1)

        return bError

    @staticmethod
    def parseDefinitions(fileName, lines:list) -> (bool, dict):
        bSuccess = True
        definitions = { }

        for i, line in enumerate(lines):

            # skip if it is an empty line or there are only whitespace characters in the line
            if line == '' or line.isspace():
                continue

            # find the first occurence of the definition delimiter
            currentPos = 0
            bFound = False
            delimiterLength = len(DefinitionParser.DefinitionDelimiter)
            while True:
                delimiterIndex = line.find(DefinitionParser.DefinitionDelimiter, currentPos)

                if delimiterIndex == -1:

                    if not bFound:
                        Logger.parseError(fileName, i + 1, line, 'Definition delimiter not found')
                        bSuccess = False

                    break

                elif delimiterIndex == 0 or line[delimiterIndex - 1] != '\\':
                    if bFound:
                        Logger.parseError(fileName, i + 1, line, 'Duplicate definition delimiter found', delimiterIndex)
                        bSuccess = False

                    else:
                        bFound = True
                        key = DefinitionParser.restoreToken(line[:delimiterIndex].strip(), DefinitionParser.DefinitionDelimiter)
                        value = DefinitionParser.restoreToken(line[delimiterIndex + delimiterLength:].strip(), DefinitionParser.DefinitionDelimiter)
    
                        definitions[key] = value

                currentPos = delimiterIndex + delimiterLength

        if not bSuccess:
            definitions = { }

        return (bSuccess, definitions)

    def parseFile(self, fileName:str) -> (bool, dict):
        content = self.loadFile(fileName)

        if not content:
            return (False, { })

        processed = self.preprocess(fileName, content)
        if self.checkForError(fileName, processed):
            return False

        lines = processed.splitlines()
        return self.parseDefinitions(fileName, lines)

    def parse(self):
        bSuccess = True

        for fileName in self.definitionFiles:
            self.workingFileStack.push(fileName)

            bSuccess, parsed = self.parseFile(fileName)
            if bSuccess:
                self.parsedDefinitions.update(parsed)

            self.workingFileStack.pop()

        self.parsedDefinitions.update(self.additionalDefinitions)

class TemplateParser:
    
    def removeComments(self):
        pass

    def processPythonCodeBlock(self):
        pass

    def preprocess(self):
        pass

    def parseDefinitions(self):
        pass

    def parse(self):
        pass

def run():
    params = sys.argv[1:]

    definitionsFileName = ''
    outputFileName = ''
    templateFileName = ''
    bError = False
    bShouldAddDefinitions = False
    bVerbose = False
    definitionMap = { }

    for i, p in enumerate(params):
        par:str = p.strip()

        if par == '-d' or par == '--definition':
            if definitionsFileName != '':
                bError = reportError('Invalid Arguments', 'Duplicate definitions file')
                break

            if len(params) < i + 2:
                bError = reportError('Invalid Arguments', 'Definitions file not specified')
                break

            definitionsFileName = params[i+1]

            if bShouldAddDefinitions:
                bShouldAddDefinitions = False

            continue

        elif par == '-o' or par == '--output':
            if outputFileName != '':
                bError = reportError('Invalid Arguments', 'Duplicate output file')
                break

            if len(params) < i + 2:
                bError = reportError('Invalid Arguments', 'Output file not specified')
                break

            outputFileName = params[i+1] 

            if bShouldAddDefinitions:
                bShouldAddDefinitions = False

            continue

        elif par == '-t' or par == '--template':
            if templateFileName != '':
                bError = reportError('Invalid Arguments', 'Duplicate template file')
                break

            if len(params) < i + 2:
                bError = reportError('Invalid Arguments', 'Template file not specified')
                break

            templateFileName = params[i+1]

            if bShouldAddDefinitions:
                bShouldAddDefinitions = False

            continue

        elif par == '-v' or par == '--verbose':
            if bShouldAddDefinitions:
                bShouldAddDefinitions = False

            bVerbose = True

            continue

        if bShouldAddDefinitions:
            kvlist = par.split('=', 1)
            if len(kvlist) != 2:
                bError = reportError('Invalid Arguments', 'Invalid key-value paired definition')
                break

            key = kvlist[0].strip()
            value = kvlist[1].strip()

            definitionMap[key] = value
        else:
            if par == '-D' or par == '--Definitions':
                bShouldAddDefinitions = True

    if definitionsFileName == '':
        bError = reportError('Invalid Arguments', 'Definitions filename required')
        
    if outputFileName == '':
        bError = reportError('Invalid Arguments', 'Output filename required')
        
    if templateFileName == '':
        bError = reportError('Invalid Arguments', 'Template filename required')

    if bError:
        return

    if bVerbose:
        print('-d: ' + definitionsFileName)
        print('-o: ' + outputFileName)
        print('-t: ' + templateFileName)
        print('-D:', definitionMap)

    bParseError, parsedDefinitions = readProjectDefinitions(definitionsFileName)
    if not bParseError:
        parsedDefinitions.update(definitionMap)

        if bVerbose:
            print(parsedDefinitions)

        fpOutput = open(outputFileName, 'wt')
        fpOutput.write(parseMatchingDefinitions(templateFileName, parsedDefinitions))
        fpOutput.close()

def parseMatchingDefinitions(templateFileName:str, definitions:dict) -> str:
    fpTemplate = open(templateFileName, 'rt')
    fileContent = fpTemplate.read()

    print('\n---------------------------------------------------\n' + fileContent + '\n---------------------------------------------------\n')

    # Parses comments
    commentMatch = re.search(r"[^\\](?P<Comment>\$(?P<removingLeadingDashes>-*)#(?:.|\n)*?#(?P<removingTrailingDashes>-*)\$)", fileContent)
    while commentMatch:
        numLeadingCharsToRemove = len(commentMatch.group('removingLeadingDashes'))
        numTrailingCharsToRemove = len(commentMatch.group('removingTrailingDashes'))
        commentStart, commentEnd = commentMatch.span(1)
        fileContent = fileContent[:commentStart - numLeadingCharsToRemove] + fileContent[commentEnd + numTrailingCharsToRemove:]

        print('\n---------------------------------------------------\n' + fileContent + '\n---------------------------------------------------\n')

        commentMatch = re.search(r"[^\\](?P<Comment>\$(?P<removingLeadingDashes>-*)#(?:.|\n)*?#(?P<removingTrailingDashes>-*)\$)", fileContent)

    for key in definitions:
        numCharsToRemove = 0
        optionalChars = ''
        formatStr = r"(?P<DefinitionRepl>\$(?:(?P<removingDashesWhenDefExists>-*):(?P<removingDashesWhenDefNotExists>-*))?(\[(?P<optionalChars>.+)\])?\(" + key + "\))"

        match = re.search(formatStr, fileContent)
        while match:
            if not fileContent[match.start() - 1] == '\\':

                if definitions[key]:
                    numCharsToRemove = len(match.group('removingDashesWhenDefExists')) if match.group('removingDashesWhenDefExists') else 0
                else:
                    numCharsToRemove = len(match.group('removingDashesWhenDefNotExists')) if match.group('removingDashesWhenDefNotExists') else 0
    
                optionalChars = match.group('optionalChars')
                if optionalChars == None:
                    optionalChars = ''
    
                repl = optionalChars + definitions[key] if definitions[key] else definitions[key]
                replStart, replEnd = match.span(1)
                fileContent = fileContent[:replStart - numCharsToRemove] + repl + fileContent[replEnd:]

            match = re.search(formatStr, fileContent)

#        formatStr = (r"(?P<DefinitionRepl>(?:[^\$]){%d}[^\\]*\$(?:-*)(?:\[.+\])?\(" + key + "\))") % numCharsToRemove
#        repl = definitions[key]
#        if definitions[key] != '':
#            formatStr = r"[^\\]*(?P<DefinitionRepl>\$(?:-*)(?:\[.+\])?\(" + key + "\))"
#            repl = optionalChars + definitions[key]
#        
#        definitionMatch = re.search(formatStr, fileContent)
#        while definitionMatch:
#            replStart, replEnd = definitionMatch.span(1)
#            fileContent = fileContent[:replStart] + repl + fileContent[replEnd:]
#
#            definitionMatch = re.search(formatStr, fileContent)
        #fileContent = re.sub(formatStr, repl, fileContent)
        
        print('\n---------------------------------------------------\n' + fileContent + '\n---------------------------------------------------\n')
    
    fpTemplate.close()

    return fileContent

def readProjectDefinitions(definitionsFileName:str) -> (bool, dict):
    fpProjectDefinitions = open(definitionsFileName, 'rt')
    bError = False
    definitions = { }

    if fpProjectDefinitions.closed == False:
        bError, definitions = parseDefinitions(definitionsFileName, fpProjectDefinitions.readlines())

    fpProjectDefinitions.close()
    return (bError, definitions)

def restoreSymbols(definitionsFileName:str, lineNumber:int, string:str, symbols:list) -> (bool, str):
    bErrorReported = False

    for symbol in symbols:
        symbolIndex = string.find(symbol)

        while(symbolIndex != -1):
            if string[symbolIndex - 1] != '\\':
                bErrorReported = reportParseError(definitionsFileName, lineNumber, string, symbolIndex, "Unresolved Symbol: '" + symbol + "'")
                break

            string = string[:symbolIndex - 1] + string[symbolIndex:]
            symbolIndex = string.find(symbol, symbolIndex)
    
    return (bErrorReported, string)

def preprocessString(string:str) -> str:
    result = string

    # remove comments (starting with #)
    commentStartIndex = str.find(string, '#')
    if commentStartIndex != -1:
        result = string[:commentStartIndex]

    return result

def parseDefinitions(definitionsFileName:str, linesToParse:list) -> (bool, dict):
    bErrorReported = False
    parsedDefinitions = { }

    for i, line in enumerate(linesToParse):
        if bErrorReported:
            break

        processed = preprocessString(line)

        delimiterIndex = processed.find('=')
        while (delimiterIndex != -1):
            if (processed[delimiterIndex - 1] != '\\'):
                break
            
            delimiterIndex = processed.find('=', delimiterIndex)

        if processed == '' or processed.isspace():
            continue

        if delimiterIndex == -1:
            bErrorReported = reportParseError(definitionsFileName, i+1, line, len(line) - 1, "Expected a key-value delimiter: '='")
            break

        key = processed[:delimiterIndex].strip()
        value = processed[delimiterIndex+1:].strip()

        bErrorReported, key = restoreSymbols(definitionsFileName, i+1, key, ['='])
        if bErrorReported:
            break

        bErrorReported, value = restoreSymbols(definitionsFileName, i+1, value, ['='])
        if bErrorReported:
            break

        parsedDefinitions[key] = value

        if bErrorReported:
            parsedDefinitions = { }

    return (bErrorReported, parsedDefinitions)

def reportParseError(fileName:str, lineNumber:int, line:str, errorSymbolIndex:int, errorMessage:str):
    global RCGPrefix

    initFormatString = '{0} Parse Error [{4}]> {1}({2}): {3}'.format(RCGPrefix, fileName, lineNumber, line, errorMessage)
    lineStart = initFormatString.find(line)
    print(initFormatString, (lineStart + errorSymbolIndex) * ' ' + '^', sep='\n')
    return True

def reportError(errorType:str, errorMessage:str):
    global RCGPrefix

    formatString = '{0} {1} Error [{2}]'.format(RCGPrefix, errorType, errorMessage)
    print(formatString)
    return True

if __name__ == "__main__":
    run()