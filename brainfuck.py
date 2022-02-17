from inspect import ismemberdescriptor
import sys

def main():

    if len(sys.argv) < 2: # basic error handling
        print(f'No file to run')
        return
    
    elif len(sys.argv) > 2:
        print(f'Too many input arguments')
        return
    
    else:
        if not (sys.argv[1][~1:] == '.b' or sys.argv[1][~2:] == '.bf'):
            print(f'Wrong filetype')
            return
    

    number_of_instrunctions = 0
    instruction_pointer = 0
    data_pointer = 0
    instruction = {}
    data = {}


    with open(sys.argv[1], 'r') as f:
        for c in f.read():
            if c in '<>+-.,[]':
                instruction[number_of_instrunctions] = c
                number_of_instrunctions += 1


    while instruction_pointer < number_of_instrunctions:

        if instruction[instruction_pointer] == '>':
            data_pointer += 1
        elif instruction[instruction_pointer] == '<':
            data_pointer -= 1
        elif instruction[instruction_pointer] == '+':
            if data_pointer not in data: data[data_pointer] = 0
            data[data_pointer] += 1
        elif instruction[instruction_pointer] == '-':
            if data_pointer not in data: data[data_pointer] = 0
            data[data_pointer] -= 1
        elif instruction[instruction_pointer] == '.':
            print(chr(data[data_pointer]), end='')
        elif instruction[instruction_pointer] == ',':
            data[data_pointer] = ord(input())
        elif instruction[instruction_pointer] == '[':
            if data_pointer not in data or data[data_pointer] == 0:
                count = 1
                while count != 0:
                    instruction_pointer += 1
                    if instruction[instruction_pointer] == '[':
                        count += 1
                    elif instruction[instruction_pointer] == ']':
                        count -= 1
        elif instruction[instruction_pointer] == ']':
            if data_pointer in data and data[data_pointer] != 0:
                count = -1
                while count != 0:
                    instruction_pointer -= 1
                    if instruction[instruction_pointer] == '[':
                        count += 1
                    elif instruction[instruction_pointer] == ']':
                        count -= 1
        instruction_pointer += 1

if __name__ == '__main__':
    main()