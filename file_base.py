import pickle

class Program:
    def __init__(self,name, txt, cost, protected, ext):
        self.name = name
        self.txt = txt
        self.cost = cost
        self.protected = protected
        self.exten = ext

try:
    f = open("soft.db", "rb+")
except FileNotFoundError:
    f = open("soft.db", "wb+")
    pickle.dump([], f)

data = pickle.load(f)
f.close()
while True:
    print("1. Add software\n2. View market\n3. Exit")
    ent = input("Select option: ")
    if ent == "1":
        name = input("Enter software name: ")
        fl = input("Enter file_path: ")
        with open(fl, "r") as fl:
            txt = fl.read()
        cost = int(input("Enter cost: "))
        prot = input("Do you want to hide your code(y/n)?: ")
        pro = True if prot.lower() == "y" else False
        ext = input("Enter file extension: ")
        pr = Program(name, txt, cost, pro, ext)
        data.append(pr)
        print("Program '{}' added".format(pr.name))
    elif ent == "2":
        while True:
            for nm,x in enumerate(data, start=1):
                print("{}. {} cost:{}$".format(nm,x.name, x.cost))
            ent = input("Type a number to view a program, 'e' - to exit: ")
            if ent == "e":
                break
            else:
                prog = data[int(ent)-1]
                code = prog.txt if not prog.protected else "The code is hidden"
                print("{}    cost:{}$".format(prog.name, prog.cost))
                print("Code:\n{}".format(code))
                print("\n1. Buy software\n2. Back")
                ent = input("Select: ")
                if ent == "1":
                    loc = input("Enter location to upload file: ")
                    loc += "/" + "purchased." + prog.exten
                    fl = open(loc, "w")
                    fl.write(prog.code)
                    fl.close()
                    print("Purchase succesfull.")
                    print("You can find the software at " + loc)                
                

    elif ent == "3":
        f = open("soft.db", "wb")
        pickle.dump(data, f)
        f.close()
    

