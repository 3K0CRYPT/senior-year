#!/usr/bin/env python

import sys
import sets
from logical_expression import *

def main(argv):
    if len(argv) != 4:
        print('Usage: %s [wumpus-rules-file] [additional-knowledge-file] [input_file]' % argv[0])
        sys.exit(0)

    # Read wumpus rules file
    try:
        input_file = open(argv[1], 'rb')
    except:
        print('failed to open file %s' % argv[1])
        sys.exit(0)

    # Create the knowledge base with wumpus rules
    print '\nLoading wumpus rules...'
    knowledge_base = logical_expression()
    knowledge_base.connective = ['and']
    for line in input_file:
        # Skip comments and blank lines. Consider all line ending types.
        if line[0] == '#' or line == '\r\n' or line == '\n' or line == '\r':
            continue
        counter = [0]  # A mutable counter so recursive calls don't just make a copy
        subexpression = read_expression(line.rstrip('\r\n'), counter)
        knowledge_base.subexpressions.append(subexpression)
    input_file.close()

    # Read additional knowledge base information file
    try:
        input_file = open(argv[2], 'rb')
    except:
        print('failed to open file %s' % argv[2])
        sys.exit(0)

    # Add expressions to knowledge base
    print 'Loading additional knowledge...'
    for line in input_file:
        # Skip comments and blank lines. Consider all line ending types.
        if line[0] == '#' or line == '\r\n' or line == '\n' or line == '\r':
            continue
        counter = [0]  # a mutable counter
        subexpression = read_expression(line.rstrip('\r\n'), counter)
        knowledge_base.subexpressions.append(subexpression)
    input_file.close()

    # Verify it is a valid logical expression
    if not valid_expression(knowledge_base):
        sys.exit('invalid knowledge base')

    # I had left this line out of the original code. If things break, comment out.
    # print_expression(knowledgebase, '\n')

    # Read statement whose entailment we want to determine
    try:
        input_file = open(argv[3], 'rb')
    except:
        print('failed to open file %s' % argv[3])
        sys.exit(0)
    print 'Loading statement...'
    statement = input_file.readline().rstrip('\r\n')
    input_file.close()
    
    # Convert statement into a logical expression and verify it is valid
    statement = read_expression(statement)
    if not valid_expression(statement):
        sys.exit('invalid statement')

    # Show us what the statement is
    print '\nChecking statement: ',
    print_expression(statement, '')
    print
    
    unique_symbols = list(set().union(extract_symbols(knowledge_base, [])+extract_symbols(statement, [])))    
    values = dict.fromkeys(unique_symbols, '?')
    
    print 'Unique symbols:',  extract_symbols(knowledge_base, [])
    print
    
    for value in values:
        new_statement = logical_expression()
        new_statement.symbol = [value]        
        result = check_true_false(knowledge_base, new_statement, values)
        if result == 'definitely true':
            values[value] = 'true'
        elif result == 'definitely false':
            values[value] = 'false'
        elif result == 'both true and false':
            print result            
            print_to_file(result)
            exit()
        else: #no definitive conclusion
            values[value] = 'true'
            for value2 in values:
                new_statement2 = logical_expression()
                new_statement2.symbol = [value2]        
                result2 = check_true_false(knowledge_base, new_statement2, values)
                if result2 == 'both true and false':
                    values[value] = 'false'
                    break
        
    print values
    
    # Run the statement through the inference engine
    result = check_true_false(knowledge_base, statement, values)
    print result
    print_to_file(result)

    sys.exit(1)
    

if __name__ == '__main__':
    main(sys.argv)
