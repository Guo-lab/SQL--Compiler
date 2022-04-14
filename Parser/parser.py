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
            
    file.close()

    for a in Grammar.items():
        #//print(a)
        pass
    

 


FIRST_LIST = {}
FOLLOW_LIST = {}

# Get FIRST SET and FOLLOW SET     
def make_FIRST():
    pass  
def make_FOLLOW():
    pass
    
        
        
        
        
        
if __name__ == '__main__':
    # Get Tokens
    make_token()
    make_grammar()
    
    make_FIRST()
    make_FOLLOW()