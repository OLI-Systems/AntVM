#include <iostream>
#include "AntVM.h"

using namespace ant_vm;

int main() {

    //create an ant-vm instance
    AntVM myVM;

    //create a place-holder for the final solution
    Variable finalValue;

    //instructions for final_value = 1.0 + 2.0
    myVM.addInstruction(Ins(InsCode::LOAD_CONST, 1.0));
    myVM.addInstruction(Ins(InsCode::LOAD_CONST, 2.0));
    myVM.addInstruction(Ins(InsCode::SUB));
    myVM.addInstruction(Ins(InsCode::SET, finalValue));

    //run the virtual machine
    myVM.run();

    //display the results
    std::cout<<"Value of finalValue is "<<finalValue.get();

    return 0;
}
