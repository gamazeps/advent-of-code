import collections
import random

operations = {
        "inc": lambda x, y: x + y,
        "dec": lambda x, y: x - y,
        "<"  : lambda x, y: x < y,
        ">"  : lambda x, y: x > y,
        "<=" : lambda x, y: x <= y,
        ">=" : lambda x, y: x >= y,
        "==" : lambda x, y: x == y,
        "!=" : lambda x, y: x != y,
        }

def parse_input(fname):
    instructions = list()
    f = open(fname, 'r')
    lines = f.readlines()
    for line in lines:
        tokens = line.strip().split(" ")
        inst = {
                "register": tokens[0],
                "operation": tokens[1],
                "value": tokens[2],
                "cond_l": tokens[4],
                "cond_op": tokens[5],
                "cond_r": tokens[6]
                }
        instructions.append(inst)
    return instructions

def cond(regs, inst):
    return operations[inst["cond_op"]](
            regs[inst["cond_l"]],
            int(inst["cond_r"]))    

def apply_op(regs, inst):
    regs[inst["register"]] = operations[inst["operation"]](
            regs[inst["register"]],
            int(inst["value"])
            )

def part_1(insts):
    regs = collections.defaultdict(int)

    for inst in insts:
        if cond(regs, inst):
            apply_op(regs, inst)

    return max(regs.values())

def part_2(insts):
    regs = collections.defaultdict(int)
    highest = 0

    for inst in insts:
        if cond(regs, inst):
            apply_op(regs, inst)
        highest = max(highest, regs[inst["register"]])

    return highest

def main():
    insts = parse_input("data/p08.in")
    print(part_1(insts))
    print(part_2(insts))

if __name__ == "__main__":
    main()
