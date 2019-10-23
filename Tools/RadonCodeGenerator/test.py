class Command:
    Commands = set()

    def getShorthand(self):
        raise NotImplementedError

    def getFullSpec(self):
        raise NotImplementedError

    def process(self, arguments:list):
        raise NotImplementedError

    @staticmethod
    def getShorthand2():
        raise NotImplementedError

class CommandDefinition(Command):

    def getShorthand(self):
        return 'd'

    def getShorthand2():
        return 'hi'

    def getFullSpec(self):
        return 'definition'

    def process(self, arguments):
        pass

Command.Commands.add(CommandDefinition)

list1 = [ CommandDefinition, CommandDefinition ]
import sys

#lines = """#require 'hello.def'
##require "hi.dd"
##require "he.
##require 'hel"
#""".splitlines()
#
#print(lines)
#
#import re
#
#quoteBlocks =  [ ]
#for i, line in enumerate(lines):
#
#    procStartIndex = line.find('#')
#
#    quoteBlockMatch = re.search("(?:'(?P<QuoteBlock>.*)')|(?:\"(?P<DoubleQuoteBlock>.*)\")", line[procStartIndex:])
#    while quoteBlockMatch:
#        quoteBlock = quoteBlockMatch.group('QuoteBlock')
#
#        blockStart = -1
#        blockEnd = -1
#        if quoteBlock:
#            blockStart, blockEnd = quoteBlockMatch.span(1)
#        else:
#            quoteBlock = quoteBlockMatch.group('DoubleQuoteBlock')
#            blockStart, blockEnd = quoteBlockMatch.span(2)
#
#        quoteBlocks.append(quoteBlock)
#        lines[i] = line[:blockStart - 1] + '%' + line[blockEnd + 1:]
#        quoteBlockMatch = re.search("(?:'(?P<QuoteBlock>.*)')|(?:\"(?P<DoubleQuoteBlock>.*)\")", line[blockStart:])
#
#print("lines: ")
#for l in lines:
#    print(l)
#
#print("blocks: ")
#for s in quoteBlocks:
#    print(s)
#
#print(re.match(r'(?:\"(?P<g1>.)\")|' + r"(?:\'(?P<g2>.)\')", "'c'").group(2))

import laac
parser = laac.DefinitionParser([ 'radon.def' ], { 'helo': 'hi' })
parser.parse()
parser.log()