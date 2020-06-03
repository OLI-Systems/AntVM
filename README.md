# AntVM: A tiny project to learn how to write a virtual machine

AntVM is a simple project written in C++ to demonstrate the creation and use of a rudimentary stack-based virtual machine (VM). The entire source is just one header file and can be simply included into a cpp file with zero configuration. It currently supports a few basic operations but can be easily extended to allow for more complex use cases. 


## Why Virtual Machines are useful

C++ is an ahead-of-time compiled language, which means it is not straightforward to "add new code" at run time. This makes it difficult to extend your software without the entire code-compile-run cycle. Many scripting languages, such as Python, Lua, ChaiScript and Julia, can be easily embedded into your C/C++ application in order to give runtime code execution capabilities to your software. But sometimes, you may want to create your own "solution" for performance reasons or extensibility that may be required for your particular application.

## So how does a stack-based VM work?

Let's try to compute the expression  (1 + 2)*3

A stack-based VM stores these instructions like this: [1, 2, +, 3, *]
This is known as the reverse polish notation, which means '+' in (1 + 2) is written after the operands (1 & 2) in this manner: (1 2 +). The VM simply executes the instructions one at a time. The stack state is shown below as the VM iterates through the instructions.

 1. [1] 
 2. [1 2]
 3. [1 2 +] -> [3] **#since '+' is encountered, pop off the last two elements in the stack, add them and push the result back onto the stack**
 4. [3 3]
 5. [3 3 *] -> [9]
The only value in the stack now is the evaluated value of the expression, which is **9**

## Primitives in AntVM
Two basic primitives available:-
	

 - Constant: a number that cannot be changed, can only be used part of the RHS of an expression
 - Variable: can be used in both LHS and RHS of an expression

## Instruction Set!!

 1. LOAD_CONST
 2. LOAD_VAR
 3. SET
 4. ADD
 5. SUB
 6. MUL
 7. DIV

## Example

    //create an ant-vm instance
    AntVM myVM;

    //create a place-holder for the final solution
    Variable finalValue;

    //instructions for final_value = 1.0 - 2.0
    myVM.addInstruction(Ins(InsCode::LOAD_CONST, 1.0));
    myVM.addInstruction(Ins(InsCode::LOAD_CONST, 2.0));
    myVM.addInstruction(Ins(InsCode::SUB));
    myVM.addInstruction(Ins(InsCode::SET, finalValue));

    //run the virtual machine
    myVM.run();

    //display the results
    std::cout<<"Value of finalValue is "<<finalValue.get();
