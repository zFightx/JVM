#include "../header/Opcodes.hpp"

void Opcodes::CreateOpcodes()
{
    map<int, pair<string, int>> opcodes_map = opcodes;

    opcodes_map[0x00] = make_pair("nop", 0);
    opcodes_map[0x01] = make_pair("aconst_null", 0);
    opcodes_map[0x02] = make_pair("iconst_m1", 0);
    opcodes_map[0x03] = make_pair("iconst_0", 0);
    opcodes_map[0x04] = make_pair("iconst_1", 0);
    opcodes_map[0x05] = make_pair("iconst_2", 0);
    opcodes_map[0x06] = make_pair("iconst_3", 0);
    opcodes_map[0x07] = make_pair("iconst_4", 0);
    opcodes_map[0x08] = make_pair("iconst_5", 0);
    opcodes_map[0x09] = make_pair("lconst_0", 0);
    opcodes_map[0x0a] = make_pair("lconst_1", 0);
    opcodes_map[0x0b] = make_pair("fconst_0", 0);
    opcodes_map[0x0c] = make_pair("fconst_1", 0);
    opcodes_map[0x0d] = make_pair("fconst_2", 0);
    opcodes_map[0x0e] = make_pair("dconst_0", 0);
    opcodes_map[0x0f] = make_pair("dconst_1", 0);
    opcodes_map[0x10] = make_pair("bipush", 1);
    opcodes_map[0x11] = make_pair("sipush", 2);
    opcodes_map[0x12] = make_pair("ldc", 1);
    opcodes_map[0x13] = make_pair("ldc_w", 2);
    opcodes_map[0x14] = make_pair("ldc2_w", 2);
    opcodes_map[0x15] = make_pair("iload", 1);
    opcodes_map[0x16] = make_pair("lload", 1);
    opcodes_map[0x17] = make_pair("fload", 1);
    opcodes_map[0x18] = make_pair("dload", 1);
    opcodes_map[0x19] = make_pair("aload", 1);
    opcodes_map[0x1a] = make_pair("iload_0", 0);
    opcodes_map[0x1b] = make_pair("iload_1", 0);
    opcodes_map[0x1c] = make_pair("iload_2", 0);
    opcodes_map[0x1d] = make_pair("iload_3", 0);
    opcodes_map[0x1e] = make_pair("lload_0", 0);
    opcodes_map[0x1f] = make_pair("lload_1", 0);
    opcodes_map[0x20] = make_pair("lload_2", 0);
    opcodes_map[0x21] = make_pair("lload_3", 0);
    opcodes_map[0x22] = make_pair("fload_0", 0);
    opcodes_map[0x23] = make_pair("fload_1", 0);
    opcodes_map[0x24] = make_pair("fload_2", 0);
    opcodes_map[0x25] = make_pair("fload_3", 0);
    opcodes_map[0x26] = make_pair("dload_0", 0);
    opcodes_map[0x27] = make_pair("dload_1", 0);
    opcodes_map[0x28] = make_pair("dload_2", 0);
    opcodes_map[0x29] = make_pair("dload_3", 0);
    opcodes_map[0x2a] = make_pair("aload_0", 0);
    opcodes_map[0x2b] = make_pair("aload_1", 0);
    opcodes_map[0x2c] = make_pair("aload_2", 0);
    opcodes_map[0x2d] = make_pair("aload_3", 0);
    opcodes_map[0x2e] = make_pair("iaload", 0);
    opcodes_map[0x2f] = make_pair("laload", 0);
    opcodes_map[0x30] = make_pair("faload", 0);
    opcodes_map[0x31] = make_pair("daload", 0);
    opcodes_map[0x32] = make_pair("aaload", 0);
    opcodes_map[0x33] = make_pair("baload", 0);
    opcodes_map[0x34] = make_pair("caload", 0);
    opcodes_map[0x35] = make_pair("saload", 0);
    opcodes_map[0x36] = make_pair("istore", 1);
    opcodes_map[0x37] = make_pair("lstore", 1);
    opcodes_map[0x38] = make_pair("fstore", 1);
    opcodes_map[0x39] = make_pair("dstore", 1);
    opcodes_map[0x3a] = make_pair("astore", 1);
    opcodes_map[0x3b] = make_pair("istore_0", 0);
    opcodes_map[0x3c] = make_pair("istore_1", 0);
    opcodes_map[0x3d] = make_pair("istore_2", 0);
    opcodes_map[0x3e] = make_pair("istore_3", 0);
    opcodes_map[0x3f] = make_pair("lstore_0", 0);
    opcodes_map[0x40] = make_pair("lstore_1", 0);
    opcodes_map[0x41] = make_pair("lstore_2", 0);
    opcodes_map[0x42] = make_pair("lstore_3", 0);
    opcodes_map[0x43] = make_pair("fstore_0", 0);
    opcodes_map[0x44] = make_pair("fstore_1", 0);
    opcodes_map[0x45] = make_pair("fstore_2", 0);
    opcodes_map[0x46] = make_pair("fstore_3", 0);
    opcodes_map[0x47] = make_pair("dstore_0", 0);
    opcodes_map[0x48] = make_pair("dstore_1", 0);
    opcodes_map[0x49] = make_pair("dstore_2", 0);
    opcodes_map[0x4a] = make_pair("dstore_3", 0);
    opcodes_map[0x4b] = make_pair("astore_0", 0);
    opcodes_map[0x4c] = make_pair("astore_1", 0);
    opcodes_map[0x4d] = make_pair("astore_2", 0);
    opcodes_map[0x4e] = make_pair("astore_3", 0);
    opcodes_map[0x4f] = make_pair("iastore", 0);
    opcodes_map[0x50] = make_pair("lastore", 0);
    opcodes_map[0x51] = make_pair("fastore", 0);
    opcodes_map[0x52] = make_pair("dastore", 0);
    opcodes_map[0x53] = make_pair("aastore", 0);
    opcodes_map[0x54] = make_pair("bastore", 0);
    opcodes_map[0x55] = make_pair("castore", 0);
    opcodes_map[0x56] = make_pair("sastore", 0);
    opcodes_map[0x57] = make_pair("pop", 0);
    opcodes_map[0x58] = make_pair("pop2", 0);
    opcodes_map[0x59] = make_pair("dup", 0);
    opcodes_map[0x5a] = make_pair("dup_x1", 0);
    opcodes_map[0x5b] = make_pair("dup_x2", 0);
    opcodes_map[0x5c] = make_pair("dup2", 0);
    opcodes_map[0x5d] = make_pair("dup2_x1", 0);
    opcodes_map[0x5e] = make_pair("dup2_x2", 0);
    opcodes_map[0x5f] = make_pair("swap", 0);
    opcodes_map[0x60] = make_pair("iadd", 0);
    opcodes_map[0x61] = make_pair("ladd", 0);
    opcodes_map[0x62] = make_pair("fadd", 0);
    opcodes_map[0x63] = make_pair("dadd", 0);
    opcodes_map[0x64] = make_pair("isub", 0);
    opcodes_map[0x65] = make_pair("lsub", 0);
    opcodes_map[0x66] = make_pair("fsub", 0);
    opcodes_map[0x67] = make_pair("dsub", 0);
    opcodes_map[0x68] = make_pair("imul", 0);
    opcodes_map[0x69] = make_pair("lmul", 0);
    opcodes_map[0x6a] = make_pair("fmul", 0);
    opcodes_map[0x6b] = make_pair("dmul", 0);
    opcodes_map[0x6c] = make_pair("idiv", 0);
    opcodes_map[0x6d] = make_pair("ldiv", 0);
    opcodes_map[0x6e] = make_pair("fdiv", 0);
    opcodes_map[0x6f] = make_pair("ddiv", 0);
    opcodes_map[0x70] = make_pair("irem", 0);
    opcodes_map[0x71] = make_pair("lrem", 0);
    opcodes_map[0x72] = make_pair("frem", 0);
    opcodes_map[0x73] = make_pair("drem", 0);
    opcodes_map[0x74] = make_pair("ineg", 0);
    opcodes_map[0x75] = make_pair("lneg", 0);
    opcodes_map[0x76] = make_pair("fneg", 0);
    opcodes_map[0x77] = make_pair("dneg", 0);
    opcodes_map[0x78] = make_pair("ishl", 0);
    opcodes_map[0x79] = make_pair("lshl", 0);
    opcodes_map[0x7a] = make_pair("ishr", 0);
    opcodes_map[0x7b] = make_pair("lshr", 0);
    opcodes_map[0x7c] = make_pair("iushr", 0);
    opcodes_map[0x7d] = make_pair("lushr", 0);
    opcodes_map[0x7e] = make_pair("iand", 0);
    opcodes_map[0x7f] = make_pair("land", 0);
    opcodes_map[0x80] = make_pair("ior", 0);
    opcodes_map[0x81] = make_pair("lor", 0);
    opcodes_map[0x82] = make_pair("ixor", 0);
    opcodes_map[0x83] = make_pair("lxor", 0);
    opcodes_map[0x84] = make_pair("iinc", 2);
    opcodes_map[0x85] = make_pair("i2l", 0);
    opcodes_map[0x86] = make_pair("i2f", 0);
    opcodes_map[0x87] = make_pair("i2d", 0);
    opcodes_map[0x88] = make_pair("l2i", 0);
    opcodes_map[0x89] = make_pair("l2f", 0);
    opcodes_map[0x8a] = make_pair("l2d", 0);
    opcodes_map[0x8b] = make_pair("f2i", 0);
    opcodes_map[0x8c] = make_pair("f2l", 0);
    opcodes_map[0x8d] = make_pair("f2d", 0);
    opcodes_map[0x8e] = make_pair("d2i", 0);
    opcodes_map[0x8f] = make_pair("d2l", 0);
    opcodes_map[0x90] = make_pair("d2f", 0);
    opcodes_map[0x91] = make_pair("i2b", 0);
    opcodes_map[0x92] = make_pair("i2c", 0);
    opcodes_map[0x93] = make_pair("i2s", 0);
    opcodes_map[0x94] = make_pair("lcmp", 0);
    opcodes_map[0x95] = make_pair("fcmpl", 0);
    opcodes_map[0x96] = make_pair("fcmpg", 0);
    opcodes_map[0x97] = make_pair("dcmpl", 0);
    opcodes_map[0x98] = make_pair("dcmpg", 0);
    opcodes_map[0x99] = make_pair("ifeq", 2);
    opcodes_map[0x9a] = make_pair("ifne", 2);
    opcodes_map[0x9b] = make_pair("iflt", 2);
    opcodes_map[0x9c] = make_pair("ifge", 2);
    opcodes_map[0x9d] = make_pair("ifgt", 2);
    opcodes_map[0x9e] = make_pair("ifle", 2);
    opcodes_map[0x9f] = make_pair("if_icmpeq", 2);
    opcodes_map[0xa0] = make_pair("if_icmpne", 2);
    opcodes_map[0xa1] = make_pair("if_icmplt", 2);
    opcodes_map[0xa2] = make_pair("if_icmpge", 2);
    opcodes_map[0xa3] = make_pair("if_icmpgt", 2);
    opcodes_map[0xa4] = make_pair("if_icmple", 2);
    opcodes_map[0xa5] = make_pair("if_acmpeq", 2);
    opcodes_map[0xa6] = make_pair("if_acmpne", 2);
    opcodes_map[0xa7] = make_pair("goto", 2);
    opcodes_map[0xa8] = make_pair("jsr", 2);
    opcodes_map[0xa9] = make_pair("ret", 1);
    opcodes_map[0xaa] = make_pair("tableswitch", -1);  // REVISAR
    opcodes_map[0xab] = make_pair("lookupswitch", -1); // REVISAR
    opcodes_map[0xac] = make_pair("ireturn", 0);
    opcodes_map[0xad] = make_pair("lreturn", 0);
    opcodes_map[0xae] = make_pair("freturn", 0);
    opcodes_map[0xaf] = make_pair("dreturn", 0);
    opcodes_map[0xb0] = make_pair("areturn", 0);
    opcodes_map[0xb1] = make_pair("return", 0);
    opcodes_map[0xb2] = make_pair("getstatic", 2);
    opcodes_map[0xb3] = make_pair("putstatic", 2);
    opcodes_map[0xb4] = make_pair("getfield", 2);
    opcodes_map[0xb5] = make_pair("putfield", 2);
    opcodes_map[0xb6] = make_pair("invokevirtual", 2);
    opcodes_map[0xb7] = make_pair("invokespecial", 2);
    opcodes_map[0xb8] = make_pair("invokestatic", 2);
    opcodes_map[0xb9] = make_pair("invokeinterface", 3); // REVISAR
    // opcodes_map[0xba] = make_pair("invokedynamic", 4 );
    opcodes_map[0xbb] = make_pair("new", 1);
    opcodes_map[0xbc] = make_pair("newarray", 1);
    opcodes_map[0xbd] = make_pair("anewarray", 2);
    opcodes_map[0xbe] = make_pair("arraylength", 0);
    opcodes_map[0xbf] = make_pair("athrow", 0);
    // opcodes_map[0xc0] = make_pair("checkcast", 2 );
    // opcodes_map[0xc1] = make_pair("instanceof", 2 );
    // opcodes_map[0xc2] = make_pair("monitorenter", 0 );
    // opcodes_map[0xc3] = make_pair("monitorexit", 0 );
    opcodes_map[0xc4] = make_pair("wide", 1);           // REVISAR
    opcodes_map[0xc5] = make_pair("multianewarray", 3); // REVISAR
    opcodes_map[0xc6] = make_pair("ifnull", 2);
    opcodes_map[0xc7] = make_pair("ifnonnull", 2);
    opcodes_map[0xc8] = make_pair("goto_w", 4);
    opcodes_map[0xc9] = make_pair("jsr_w", 4);
}

void Opcodes::PrintOpcodes(u1* code, int size){
    
    
    map<int, pair<string,int>> opcodes_map = opcodes;

    for (int i = 0; i < size; i++){
        u1 opcode = code[i];
        string opcode_mnemonic = opcodes_map[opcode].first;
        int opcode_argument_bytes = opcodes_map[opcode].second;
    

    switch(opcode_argument_bytes){
        

        case 2:
            switch(opcode){
                case 0x11:{ // sipush
                    u1 byte1 = code[i+1];
                    u1 byte2 = code[i+2];
                    int16_t value = (byte1 << 8) | byte2;
                    cout << opcode_mnemonic << " " << value << endl;
                    break;
                }
                case 0x13:
                case 0x14:{ // ldc2_w
                    u1 byte1 = code[i+1];
                    u1 byte2 = code[i+2];
                    uint16_t value = (byte1 << 8) | byte2;
                    cout << opcode_mnemonic << " " << value << endl;
                    break;
                } 
            

                    

                case 0x9f:
                case 0xa0:
                case 0xa1:
                case 0xa2:
                case 0xa3:
                case 0xa4:
                case 0xa5:
                case 0xa6:{
                    
                    u1 branchbyte1 = code[i+1];
                    u1 branchbyte2 = code[i+2];
                    int16_t offset = (branchbyte1 << 8) | branchbyte2;
                    cout << opcode_mnemonic << " " << offset << endl;
                    break;
                }
            
                    
                
            }
        

    }
    }

}

