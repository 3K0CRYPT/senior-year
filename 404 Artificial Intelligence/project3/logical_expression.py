#!/usr/bin/env python

import sys
from copy import copy

#-------------------------------------------------------------------------------
# Begin code that is ported from code provided by Dr. Athitsos
class logical_expression:
    """A logical statement/sentence/expression class"""
    # All types need to be mutable, so we don't have to pass in the whole class.
    # We can just pass, for example, the symbol variable to a function, and the
    # function's changes will actually alter the class variable. Thus, lists.
    def __init__(self):
        self.symbol = ['']
        self.connective = ['']
        self.subexpressions = []
    
    # def __contains__(self, x):

def extract_symbols(kb, s):
    if kb.symbol[0]:
        sm = kb.symbol[0]
        if sm not in s:
            s.append(sm)
        return s
    else:
        for se in kb.subexpressions:
            s = extract_symbols(se,s)
    return s
    
def print_to_file(result):
    text_file = open("result.txt", "w")
    text_file.write(result)
    text_file.close()
    
def check_true_false(knowledge_base, statement, values):
        # definitely true:  kb |= statement && kb !|= !statement
        # definitely false: kb |= !statement && kb !|= statement
        # maybe true        kb !|= statement && kb !|= !statement
        #both: kb |= statement && kb |= !statement -----> kb is bad
        test1 = logical_expression()
        test2 = logical_expression()
        not_statement = logical_expression()
                
        test1.connective = ['and']
        test2.connective = ['and']
        not_statement.connective = ['not']
        
        test1.subexpressions = [statement, knowledge_base]
        not_statement.subexpressions = [statement]
        test2.subexpressions = [not_statement, knowledge_base]
        
        test1 = evaluate_statement(test1, values)
        test2 = evaluate_statement(test2, values)
        
        if test1 == 'false':
            if test2 == 'false': # kb !|= statement && kb !|= !statement
                return 'possibly true, possibly false'
            else: # kb |= !statement && kb !|= statement
                return 'definitely false'
        else:
            if test2 == 'false': 
                return 'definitely true' # kb |= statement && kb !|= !statement
            else: #  kb |= statement && kb |= !statement -----> kb is bad
                return 'both true and false'
    
def evaluate_statement(statement, values):
    # sys.stdout.write('EVAL: ')
    # print_expression(statement, '')
    # print   

    if (statement.symbol[0] != ''):
        if values[statement.symbol[0]] == 'false':
            return 'false'         
        elif values[statement.symbol[0]] == 'true':
            return 'true'
        else:
            return statement.symbol[0]
       

    if (statement.connective[0] == "and"):
        if not statement.subexpressions:
            return 'true'
        else:
            for exp in statement.subexpressions:
                if evaluate_statement(exp, values) == 'false':
                    return 'false'
            return 'true'

    if (statement.connective[0] == "or") :

        if not statement.subexpressions:
            return 'false'
        else:
            for exp in statement.subexpressions:
                if evaluate_statement(exp, values) == 'true':
                    return 'true'
            return 'false'

    if (statement.connective[0] == "xor"):

        if not statement.subexpressions:
            return 'false'
        else:
            result_list = []
            for exp in statement.subexpressions:
                result_list.append(evaluate_statement(exp, values))
            if result_list.count("true") == 1:
                return 'true'
            else:
                return 'false'

    if (statement.connective[0] == "not"): 

        if not statement.subexpressions:
            exit()            
        else:
            value = evaluate_statement(statement.subexpressions[0], values)
            if value == 'true':
                return 'false'
            if value == 'false':
                return 'true'
            else:
                if not isinstance(value, basestring):
                    return '(not' + value.symbol[0] + ')'
                else:
                    return '(not' + value + ')'

    if (statement.connective == "if"):

        if (len(statement.subexpressions) != 2):
            exit()
        else:
            result1 = evaluate_statement(statement.subexpressions[0], values)
            if result1 == 'true':
                result1 = 'false'
            elif result1 == 'false':
                result1 = 'true'
            else:
                result1 = '(not '+result1+')'
                
            result2 = evaluate_statement(statement.subexpressions[1], values)
            
            if result1 == 'true' or result2 == 'true':
                return 'true'
            else:
                return 'false'

    if (statement.connective == "iff"):

        if (len(statement.subexpressions) != 2):
            exit()
        else:
            result1 = evaluate_statement(statement.subexpressions[0], values)
            result2 = evaluate_statement(statement.subexpressions[1], values)
            if result1 == result2:
                return 'true'
            else:
                return 'false'
    
    return '?'


def print_expression(expression, separator):
    """Prints the given expression using the given separator"""
    if expression == 0 or expression == None or expression == '':
        print '\nINVALID\n'

    elif expression.symbol[0]: # If it is a base case (symbol)
        sys.stdout.write('%s' % expression.symbol[0])

    else: # Otherwise it is a subexpression
        sys.stdout.write('(%s' % expression.connective[0])
        for subexpression in expression.subexpressions:
            sys.stdout.write(' ')
            print_expression(subexpression, '')
            sys.stdout.write('%s' % separator)
        sys.stdout.write(')')


def read_expression(input_string, counter=[0]):
    """Reads the next logical expression in input_string"""
    # Note: counter is a list because it needs to be a mutable object so the
    # recursive calls can change it, since we can't pass the address in Python.
    result = logical_expression()
    length = len(input_string)
    while True:
        if counter[0] >= length:
            break

        if input_string[counter[0]] == ' ':    # Skip whitespace
            counter[0] += 1
            continue

        elif input_string[counter[0]] == '(':  # It's the beginning of a connective
            counter[0] += 1
            read_word(input_string, counter, result.connective)
            read_subexpressions(input_string, counter, result.subexpressions)
            break

        else:  # It is a word
            read_word(input_string, counter, result.symbol)
            break
    return result


def read_subexpressions(input_string, counter, subexpressions):
    """Reads a subexpression from input_string"""
    length = len(input_string)
    while True:
        if counter[0] >= length:
            print '\nUnexpected end of input.\n'
            return 0

        if input_string[counter[0]] == ' ':     # Skip whitespace
            counter[0] += 1
            continue

        if input_string[counter[0]] == ')':     # We are done
            counter[0] += 1
            return 1

        else:
            expression = read_expression(input_string, counter)
            subexpressions.append(expression)


def read_word(input_string, counter, target):
    """Reads the next word of an input string and stores it in target"""
    word = ''
    while True:
        if counter[0] >= len(input_string):
            break

        if input_string[counter[0]].isalnum() or input_string[counter[0]] == '_':
            target[0] += input_string[counter[0]]
            counter[0] += 1

        elif input_string[counter[0]] == ')' or input_string[counter[0]] == ' ':
            break

        else:
            print('Unexpected character %s.' % input_string[counter[0]])
            sys.exit(1)


def valid_expression(expression):
    """Determines if the given expression is valid according to our rules"""
    if expression.symbol[0]:
        return valid_symbol(expression.symbol[0])

    if expression.connective[0].lower() == 'if' or expression.connective[0].lower() == 'iff':
        if len(expression.subexpressions) != 2:
            print('Error: connective "%s" with %d arguments.' %
                        (expression.connective[0], len(expression.subexpressions)))
            return 0

    elif expression.connective[0].lower() == 'not':
        if len(expression.subexpressions) != 1:
            print('Error: connective "%s" with %d arguments.' %
                        (expression.connective[0], len(expression.subexpressions)))
            return 0

    elif expression.connective[0].lower() != 'and' and \
         expression.connective[0].lower() != 'or' and \
         expression.connective[0].lower() != 'xor':
        print('Error: unknown connective %s.' % expression.connective[0])
        return 0

    for subexpression in expression.subexpressions:
        if not valid_expression(subexpression):
            return 0
    return 1


def valid_symbol(symbol):
    """Returns whether the given symbol is valid according to our rules."""
    if not symbol:
        return 0

    for s in symbol:
        if not s.isalnum() and s != '_':
            return 0
    return 1

# End of ported code
#-------------------------------------------------------------------------------

# Add all your functions here