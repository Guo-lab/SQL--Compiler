# SQL--Compiler

### Reference:
http://osdev.foofun.cn/index.php?title=Making_a_Compiler

## 前端
- 首先，前端通常包括某种用户接口，以便可以接受文件和编译选项。 然后，有几个阶段的处理。
对于类似C的语言，会有一个 pre-processor 预处理器 从头文件中复制并粘贴代码，删除注释执行宏扩展并执行其他相对简单的任务。  
- 然后，一个 scanner 扫描器 (或 tokenizer 分词器) 将源文件分解为一系列分词令牌，代表一种语言的基本单词 (即标识符，数字和字符串常量，诸如 “if” 和 “when” 的关键字，标点符号和分号)
- 然后，parser解析器 读取令牌流并构造 parse tree解析树，这是一种树状结构，表示源代码的结构。 就语言制作而言，每个源代码文件都是该语言的 “sentence 句子”，并且每个句子 (如果有效) 都遵循特定的语法。
- 接下来，semantic analyzer 语义分析器 遍历解析树，并确定该 “句子” 每个部分的特定含义。 例如，如果是声明语句，则它将条目添加到符号表中，并且如果它是涉及变量的表达式，则它将符号表中已知变量的地址替换为表达式中的变量。
- 最后，前端生成一个 Intermediate Representation 中间层表达，它捕获程序源代码特定的所有信息。 一个好的IR可以说明源代码所表达的所有内容甚至更多，还可以捕获该语言对程序的其他要求。 它可以是 parse tree 解析树 、 abstract syntax tree 抽象语法树 、 three address code 三地址代码 或更奇特的东西。  


值得注意的是，这种划分纯粹是为了方便编译器开发人员。 大多数类型的 parsers 解析器 可以轻松读取字符流，而不是分词令牌流，因此不需要单独的扫描器。 一些非常强大的解析器类甚至可以 “在阅读完成之前” 确定语句的语义含义，因此不需要语义分析器。 不过，它们可能会更难理解和使用。

# `Lexer` is what I have done.
# `Lexer2.0` is fixed one which could pass all other tests. 
# `Parser` python one

Lexer2.0 and Parser. Learn them from Xv Zihan.