Tokens = []

#@Get Token List
def make_token():
    tokenode = []
    file = open("../Lexer2.0/data.txt")
    tmp = 0
    for line in file:
        tokenode.append(line.split(' ',1)[0])
        tokenode.append(line.split(' ',1)[1].split('<',1)[1].split(',',1)[0])       
        Tokens.append(tokenode)
        tokenode=[]
        
    for t in Tokens:            
        #//print(t)
        pass




Mark = [] # non-terminal 
Grammar = {} 
Grammar2 = {} 

#@Get Grammar List
def make_grammar():
    file = open("grammar.txt")
    for line in file:
        #//line = line.partition(' -> ')
        if line.split('-> ')[0].split('.')[1].strip() not in Mark:
                Mark.append(line.split('-> ')[0].split('.')[1].strip())
                
        if Grammar.get(line.split('-> ')[0].split('.')[1].strip()) is not None:
            Grammar[line.split('-> ')[0].split('.')[1].strip()].append(line.split('-> ')[1].strip('\n'))
        else:
            Grammar[line.split('-> ')[0].split('.')[1].strip()] = [line.split('-> ')[1].strip('\n')]
        
        # For Parsing Table:
        #@ When Creating Parsing Table, distinct key is needed 
        Grammar2[(line.split('-> ')[0].split('.')[1].strip(), line.split('-> ')[0].split('.')[0]) ] = line.split('-> ')[1].strip('\n')
    file.close()

    for a in Grammar.items():
        #//print(a)
        pass
    
    
    
    
    
    
    
    
    
    
    
# //// ###########################    
# A Context free grammar (CFG) consists of
# - A set of terminals
# - A set of non-terminals
# - A Start symbol
# - A set of productions
# //// ###########################  

# Parse tree shows the association of operations 

# Abstract syntax tree






















FIRST_LIST = {}
FOLLOW_LIST = {}

# Get FIRST SET and FOLLOW SET  
#@ First (terminals) = {terminals}
#@ For Non-Terminals:
#@ - First (NonTerminals) += {A | Nonterminals => *A...}
#@ - First (Non) += First(B) if Nonterminals => $ B [ Nonterminals => $ || (Nonterminals => C, C => $)]
def make_FIRST():
    # In Mark, non-terminals
    for m in Mark: 
        FIRST_LIST[m] = []

    flag = True # 判断first集是否有变化 #*
    
    while flag:
        flag = False #*
        
        for key, values in Grammar.items():
            tmp = len(FIRST_LIST.get(key)) #*
            
            for vals in values:
                vals = vals.split(' ')
                #//print(vals)
                for i, val in enumerate(vals):
                    # val is a non-terminal
                    #//print(i, val)
                    #//print(vals)
                    if val in Mark:
                        list1 = FIRST_LIST.get(key)
                        list2 = FIRST_LIST.get(val).copy()
                        
                        # 该非终止符不在最后的位置$就不能算
                        if '$' in list2 and i != len(vals) - 1:
                            list2.remove('$')
                        
                        FIRST_LIST[key] = list(set(list1+list2))
                        
                        # 作为一个没有$的非终止符
                        if '$' not in FIRST_LIST[val]:
                            break
                        
                    # val is terminal
                    else:
                        if val not in FIRST_LIST[key]:
                            FIRST_LIST[key].append(val)
                            # 终止符 FIRST岂能没有她
                        break
            
            # when all key FIRST not changed    
            if tmp != len(FIRST_LIST.get(key)): #*
                flag = True #*
        # While ends and make_FIRST done
    
    for a in FIRST_LIST.items():
    #//    print(a)
        pass


#@ FOLLOW (Start Symbol) = {$}
#@ FOLLOW (A) += {t} when [ => ...At ]
#@ FOLLOW (A) += (FIRST(B) - {$}) when [ => ...AB ]
#@ FOLLOW (A) += FOLLOW(X) when [ X => ...AB AND First(B) has $] B can disappear which belongs to X also belongs to A
def make_FOLLOW():
    # In Mark, still non-terminals
    for m in Mark:
        FOLLOW_LIST[m] = []
    
    FOLLOW_LIST['root'] = ['#']
    
    flag = True # 判断FOLLOW集是否有变化 #*
    
    while flag:
        flag = False #*
        
        for key, values in Grammar.items():
            #@ [ => values ]
            for vals in values:
                #@ in values, it may be jointed like [A => 'B', 'B C']
                vals = vals.split(' ')
                enumlist = list(enumerate(vals))
                #@ [[B] [B, C]]
                for val in enumlist:
                    #//print(val) # like (5, 'updatedElementListRec')
                    #//print(val[1])
                    # Only if it is non-terminal
                    if val[1] in Mark:
                        tmp = len(FOLLOW_LIST.get(val[1])) #*
                        isp = True #%
                        
                        listN = []
                        list2 = FOLLOW_LIST.get(val[1])
                        #//print(list2)
                        list3 = []

                        #//print(val[0]+1, len(enumlist))
                        for i in range(val[0]+1, len(enumlist)):
                            #! check following terminals or non-terminals 
                            if enumlist[i][1] in Mark: 
                                
                                listN = list(set(listN + FIRST_LIST.get(enumlist[i][1])))
                                
                                if '$' not in FIRST_LIST.get(enumlist[i][1]):
                                    isp = False #%
                                    break
                                # NO $ in FOLLOW()
                                else:
                                    listN.remove('$')
                                    
                            else:
                                isp = False #%
                                # just put the terminal ones into FOLLOW 
                                listN = list(set(listN + [enumlist[i][1]]))
                                break

                        if val[0] == len(vals) - 1 or isp: #%
                            #% isp true means behind val[0] each has $
                            list3 = FOLLOW_LIST.get(key)
                            
                        FOLLOW_LIST[val[1]] = list(set(listN+list2+list3))
                        
                        # When FOLLOW not changed any more
                        if tmp != len(FOLLOW_LIST.get(val[1])): #*
                            flag = True #*
                        # compare tmp, if any changed like c in [A=>'B','BC'], continue
        # While ends and FOLLOW not changed

    for a in FOLLOW_LIST.items():
    #//    print(a)
        pass
      
        
        
        
        
        




















#@ A -> a
#@ - each terminal t in FIRST(a) T[A, t] = a WHEN A -a-> t      (1)

#@ - $ in FIRST(a); t in FOLLOW(A) T[A, t] = a WHEN A-$in(a)->t (2)
#@ - $ in FIRST(a); # in FOLLOW(A) T[A, $] = a                  (3)

#! a is one group set
Table = {}

def make_Parsing_Tables():
    for key, values in Grammar2.items():
        #//print(key)
        #//print(values)  
        vals = values.split(' ')
        #//print(vals)
        enumlist = list(enumerate(vals))
        #//print(enumlist) # like [(0, ','), (1, 'expressionOrDefault'), (2, 'expressionOrDefaultListRec')]
        listN = []
        isp = True
        
        for i in range(len(enumlist)):
            # if it is in non-terminal
            if enumlist[i][1] in Mark:
                listN = list(set(listN + FIRST_LIST.get(enumlist[i][1])))
                
                if '$' not in FIRST_LIST.get(enumlist[i][1]):
                    isp = False
                    break
                else:
                    listN.remove('$')
            
            # When it is a terminal #! (1)
            elif enumlist[i][1] != '$':
                isp = False
                listN = list(set(listN + [enumlist[i][1]]))
                break
        
        # Before it, all empty, so A => $     
        if isp:
            listN.append('$') #! (3)

        for node in listN:
            Table[(key[0], node)] = [key[1], values]
        
        #! (2)
        if isp:
            for node in list(FOLLOW_LIST.get(key[0])):
                Table[(key[0], node)] = [key[1], '$']
        
        
        for a in Table.items():
            #//print(a)
            pass
        
        
        
        
        
        
        
        
        
if __name__ == '__main__':
    # Get Tokens
    make_token()
    make_grammar()
    
    # In Both Function below we can only consider non-terminals
    make_FIRST()
    make_FOLLOW()
    
    print('Have Built FIRST and FOLLOW SET.')
    
    make_Parsing_Tables()
    print('Have Built Parsing Tables.')