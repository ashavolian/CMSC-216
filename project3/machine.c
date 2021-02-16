#include "machine.h"
#include <stdio.h>
#include <string.h>

unsigned int read_bits(unsigned int word, int type);

unsigned int replace_bits(unsigned int word, unsigned int value, int type);

void print_instruction(Hardware_word instruction){
  /*checks the opcode*/
  unsigned int temp = read_bits(instruction, 0);
  if(temp <= 14){
    Opcode opcode = temp;
    if(opcode == HALT) printf("%s ", "halt");
    else if(opcode == ADD) printf("%s ", "add");
    else if(opcode == SUB) printf("%s ", "sub");
    else if(opcode == MUL) printf("%s ", "mul");
    else if(opcode == DIV) printf("%s ", "div");
    else if(opcode == REM) printf("%s ", "rem");
    else if(opcode == INV) printf("%s ", "inv");
    else if(opcode == AND) printf("%s ", "and");
    else if(opcode == OR) printf("%s ", "or");
    else if(opcode == NOT) printf("%s ", "not");
    else if(opcode == CMP) printf("%s ", "cmp");
    else if(opcode == MV) printf("%s ", "mv");
    else if(opcode == LI) printf("%s ", "li");
    else if(opcode == LOAD) printf("%s ", "load");
    else if(opcode == STORE) printf("%s ", "store");
    /*when to check for register1 (for every opcode except for HALT)*/
    if(opcode >= 1 && opcode <= 14){
      /*reads bits at specified location*/
      temp = read_bits(instruction, 1);
      if(temp <= 19){
        /*prints the register number*/
        printf("%c%u ", 'R', temp);
      }
    }

    /*when to check for register2 (opcodes between 1-11)*/
    if(opcode >= 1 && opcode <= 11){
      /*reads bits at specified location*/
      temp = read_bits(instruction, 2);
      if(temp <= 19){
        /*prints the register number*/
        printf("%c%u ", 'R', temp);
      }
    }

    /*when to check for register3 (opcodes between 1-10 exluding INV and NOT)*/
    if(opcode >= 1 && opcode <= 10 && opcode != INV && opcode != NOT){
      /*reads bits at specified location*/
      temp = read_bits(instruction, 3);
      if(temp <= 11){
        /*prints the register number*/
        printf("%c%u ", 'R', temp);
      }
    }

    if(opcode == CMP || opcode == LI || opcode == LOAD || opcode == STORE){
      temp = read_bits(instruction, 4);
      if(opcode != LI){
	      printf("%04u ", temp);
      } else{
	      printf("%u ", temp);
      }
    }

  }
}

/*uses replace_bits() to modify our hw_word and stores it in result*/
unsigned int encode_instruction(unsigned short opcode, unsigned short reg1,
                                unsigned short reg2, unsigned short reg3,
                                unsigned int addr_or_constant,
                                Hardware_word *const hw_word){
  unsigned int result;
  /*returns 0 if hw_word is null, or if the given opcode is invalid*/
  if(hw_word == NULL || opcode < 0 || opcode > 14) return 0;
    /*checks required registers and addr_or_constant for each opcode*/
  if(((opcode >= 1 && opcode <= 14) && (reg1 < 0 || reg1 > 19)) ||
     ((opcode >= 1 && opcode <= 11) && (reg2 < 0 || reg2 > 19)) ||
     ((opcode >= 1 && opcode <= 10 && opcode != INV && opcode != NOT) &&
     (reg3 < 0 || reg3 > 19)) || ((opcode == CMP || opcode == LI || opcode  
     == LOAD || opcode == STORE) && (addr_or_constant > 2047))  ||
     ((opcode == CMP || opcode == LOAD || opcode == STORE) && (addr_or_constant % 4 != 0)) ||
     (opcode == LI && (addr_or_constant > 8191)) ||
     ((opcode != HALT && opcode != CMP && opcode != STORE) && (reg1 == 0 || reg1 == 1)) ||
     (opcode == CMP && reg3 > 5))
      return 0;
  /*creates an instruction with the result variable*/
  result = replace_bits(*hw_word, opcode, 0);
  result = replace_bits(result, reg1, 1);
  result = replace_bits(result, reg2, 2);
  result = replace_bits(result, reg3, 3);
  result = replace_bits(result, addr_or_constant, 4);
  /*modifies our pointer*/
  *hw_word = result;
  return 1;
}

unsigned int disassemble(const Hardware_word memory[],
                         unsigned int memory_size, unsigned int num_instrs){
    int i;
    unsigned int opcode, reg1, reg2, reg3, addr_or_constant;
    Hardware_word word = 1; 
    /*returns 0 if any of our parameters are invalid*/
    if(memory == NULL || memory_size <= 0 || num_instrs <= 0 ||
       num_instrs > memory_size || memory_size > 511)
    return 0;
                 
    for(i = 0; i < num_instrs; i++){
      /*deconstructs our current instruction so we can test is
      validity using encode_instruction()*/
      opcode = read_bits(memory[i], 0);
      reg1 = read_bits(memory[i], 1);
      reg2 = read_bits(memory[i], 2);
      reg3 = read_bits(memory[i], 3);
      addr_or_constant = read_bits(memory[i], 4);
      /*returns 0 if our current instruction is ever invalid*/
      if(!encode_instruction(opcode, reg1, reg2, reg3, addr_or_constant, &word))
	  return 0;
      /*prints content of our current instruction*/
      printf("%03x%s", i*4, ": ");
      print_instruction(memory[i]);
      printf("\n");
    }   
    /*prints data stored in memory starting from the num_instrs index*/
    for(i = num_instrs; i < memory_size; i++){
      printf("%03x%s", i*4, ": ");
      printf("%08x", memory[i]);
      printf("\n");
    }                   

  return 1;
}

unsigned int compare_instructions(Hardware_word instr1, Hardware_word instr2){
  unsigned int temp1, temp2, opcode;
    temp1 = read_bits(instr1, 0);
    temp2 = read_bits(instr2, 0);
    /*if the opcodes are the same*/
    if(temp1 == temp2){
      opcode = temp1;
      if(opcode != HALT){
        temp1 = read_bits(instr1, 1);
        temp2 = read_bits(instr2, 1);
        /*if both reg1 are the same*/
        if(temp1 == temp2){
          if(opcode >= 1 && opcode <= 11){
            temp1 = read_bits(instr1, 2);
            temp2 = read_bits(instr2, 2);
            /*if both reg2 are the same*/
            if(temp1 == temp2){
              if((opcode >= 1 && opcode <= 10) && opcode != INV && opcode != NOT){
                temp1 = read_bits(instr1, 3);
                temp2 = read_bits(instr2, 3);
                /*if both reg3 are the same*/
                if(temp1 == temp2){
                  if(opcode == CMP || opcode == LI || opcode == LOAD || opcode == STORE){
                        temp1 = read_bits(instr1, 4);
                        temp2 = read_bits(instr2, 4);
                        /*if both addr_or_constant are the same*/
                        if(temp1 == temp2){
                          return 1;
                        }
                  } else return 1;
                }
              } else return 1;
            }
          } else return 1; 
        }
      } else return 1;
    }
  return 0;
}

/*helper function that reads bits of an instruction at the specified location*/
unsigned int read_bits(unsigned int word, int type){
  /*type 0 = opcode, 1 = register1, 2 = register2, 3 = register3, 4 = address
    word_pos is the position to be read
    length is the amount of bits to check for*/
  int word_pos, length, mask;
  unsigned int temp, value = 0;
  if(type == 0){
    word_pos = 31;
    length = 4;
  } else if(type < 4 && type > 0){
    length = 5;
    if(type == 1){
      word_pos = 27;
    } else if(type == 2){
      word_pos = 22;
    } else if(type == 3){
      word_pos = 17;
    }
  } else if(type == 4){
    word_pos = 12;
    length = 13;
  }
  /*reads each bit and adds it value to the value variable*/
  while(length){
    mask=1<<word_pos;
    temp = word&mask;
    value += temp;
    length--;
    word_pos--;
  }

	return value >> (word_pos+1 - length);

}

/*helper function that takes and instruction and replaces bits at specified location
  with bits from value.*/
unsigned int replace_bits(unsigned int word, unsigned int value, int type){
  /*type 0 = opcode, 1 = register1, 2 = register2, 3 = register3, 4 = address
    word_pos is the position to be replaced in the word parameter
    value_pos is the position of our bit in value that we need to insert into word*/
  int word_pos, value_pos, mask;
  if(type == 0){
    word_pos = 31;
    value_pos = 3;
  } else if(type < 4 && type > 0){
    value_pos = 4;
    if(type == 1){
      word_pos = 27;
    } else if(type == 2){
      word_pos = 22;
    } else if(type == 3){
      word_pos = 17;
    }
  } else if(type == 4){
    word_pos = 12;
    value_pos = 12;
  }
  while(value_pos+1){
    /*collect corresponding bit of value*/
    mask=(value>>value_pos)&1;
    
    /*if bit at specified position is 1*/
    if(mask==1){
      mask=1<<word_pos;
      word|=mask;
    }else{
      /*if bit at specified position is 0*/
      mask=~(1<<word_pos);
      word&=mask;
    }
    value_pos--;
    word_pos--;
  }

	return word;

}
