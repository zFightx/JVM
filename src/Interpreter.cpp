#include "../header/Interpreter.hpp"

Interpreter::Interpreter(Runtime * runtime){
    this->ConstructTable();

    this->runtime = runtime;
}

Interpreter::~Interpreter(){
    
}

void Interpreter::ExecuteInterpreter(){
    while(!this->runtime->stack.empty()){        
        Interpreter::ExecuteFrame();
    }
}

void Interpreter::ExecuteFrame(){
    Frame *current_frame = this->runtime->GetCurrentFrame();
    int current_pc = this->runtime->GetCurrentPC();
    Code_attribute *current_code = current_frame->GetCode();

    // Aqui devemos executar o code.

    // Para isso precisamos saber quantas casas de PC andar a cada função (Fazer isso dentro da própria função)

    // Colocar invoker_frame dentro das funções de invoke, para sinalizar para quem deve atribuir os return.

    // Pensar em como faremos para o return cancelar o frame atual e cancelar essa função.

    // As funções de code, chamarão ExecuteFrame, de tal forma que quando um ExecuteFrame for encerrado,
    // o ExecuteFrame do método invocador continuará rodando após isso.
}

void Interpreter::ConstructTable(){
    this->instruction_table[0x00] = &Interpreter::i_nop;
    this->instruction_table[0x01] = &Interpreter::i_aconst_null;
    this->instruction_table[0x02] = &Interpreter::i_iconst_m1;
    this->instruction_table[0x03] = &Interpreter::i_iconst_0;
    this->instruction_table[0x04] = &Interpreter::i_iconst_1;
    this->instruction_table[0x05] = &Interpreter::i_iconst_2;
    this->instruction_table[0x06] = &Interpreter::i_iconst_3;
    this->instruction_table[0x07] = &Interpreter::i_iconst_4;
    this->instruction_table[0x08] = &Interpreter::i_iconst_5;
    this->instruction_table[0x09] = &Interpreter::i_lconst_0;
    this->instruction_table[0x0a] = &Interpreter::i_lconst_1;
    this->instruction_table[0x0b] = &Interpreter::i_fconst_0;
    this->instruction_table[0x0c] = &Interpreter::i_fconst_1;
    this->instruction_table[0x0d] = &Interpreter::i_fconst_2;
    this->instruction_table[0x0e] = &Interpreter::i_dconst_0;
    this->instruction_table[0x0f] = &Interpreter::i_dconst_1;
    this->instruction_table[0x10] = &Interpreter::i_bipush;
    this->instruction_table[0x11] = &Interpreter::i_sipush;
    this->instruction_table[0x12] = &Interpreter::i_ldc;
    this->instruction_table[0x13] = &Interpreter::i_ldc_w;
    this->instruction_table[0x14] = &Interpreter::i_ldc2_w;
    this->instruction_table[0x15] = &Interpreter::i_iload;
    this->instruction_table[0x16] = &Interpreter::i_lload;
    this->instruction_table[0x17] = &Interpreter::i_fload;
    this->instruction_table[0x18] = &Interpreter::i_dload;
    this->instruction_table[0x19] = &Interpreter::i_aload;
    this->instruction_table[0x1a] = &Interpreter::i_iload_0;
    this->instruction_table[0x1b] = &Interpreter::i_iload_1;
    this->instruction_table[0x1c] = &Interpreter::i_iload_2;
    this->instruction_table[0x1d] = &Interpreter::i_iload_3;
    this->instruction_table[0x1e] = &Interpreter::i_lload_0;
    this->instruction_table[0x1f] = &Interpreter::i_lload_1;
    this->instruction_table[0x20] = &Interpreter::i_lload_2;
    this->instruction_table[0x21] = &Interpreter::i_lload_3;
    this->instruction_table[0x22] = &Interpreter::i_fload_0;
    this->instruction_table[0x23] = &Interpreter::i_fload_1;
    this->instruction_table[0x24] = &Interpreter::i_fload_2;
    this->instruction_table[0x25] = &Interpreter::i_fload_3;
    this->instruction_table[0x26] = &Interpreter::i_dload_0;
    this->instruction_table[0x27] = &Interpreter::i_dload_1;
    this->instruction_table[0x28] = &Interpreter::i_dload_2;
    this->instruction_table[0x29] = &Interpreter::i_dload_3;
    this->instruction_table[0x2a] = &Interpreter::i_aload_0;
    this->instruction_table[0x2b] = &Interpreter::i_aload_1;
    this->instruction_table[0x2c] = &Interpreter::i_aload_2;
    this->instruction_table[0x2d] = &Interpreter::i_aload_3;
    this->instruction_table[0x2e] = &Interpreter::i_iaload;
    this->instruction_table[0x2f] = &Interpreter::i_laload;
    this->instruction_table[0x30] = &Interpreter::i_faload;
    this->instruction_table[0x31] = &Interpreter::i_daload;
    this->instruction_table[0x32] = &Interpreter::i_aaload;
    this->instruction_table[0x33] = &Interpreter::i_baload;
    this->instruction_table[0x34] = &Interpreter::i_caload;
    this->instruction_table[0x35] = &Interpreter::i_saload;
    this->instruction_table[0x36] = &Interpreter::i_istore;
    this->instruction_table[0x37] = &Interpreter::i_lstore;
    this->instruction_table[0x38] = &Interpreter::i_fstore;
    this->instruction_table[0x39] = &Interpreter::i_dstore;
    this->instruction_table[0x3a] = &Interpreter::i_astore;
    this->instruction_table[0x3b] = &Interpreter::i_istore_0;
    this->instruction_table[0x3c] = &Interpreter::i_istore_1;
    this->instruction_table[0x3d] = &Interpreter::i_istore_2;
    this->instruction_table[0x3e] = &Interpreter::i_istore_3;
    this->instruction_table[0x3f] = &Interpreter::i_lstore_0;
    this->instruction_table[0x40] = &Interpreter::i_lstore_1;
    this->instruction_table[0x41] = &Interpreter::i_lstore_2;
    this->instruction_table[0x42] = &Interpreter::i_lstore_3;
    this->instruction_table[0x43] = &Interpreter::i_fstore_0;
    this->instruction_table[0x44] = &Interpreter::i_fstore_1;
    this->instruction_table[0x45] = &Interpreter::i_fstore_2;
    this->instruction_table[0x46] = &Interpreter::i_fstore_3;
    this->instruction_table[0x47] = &Interpreter::i_dstore_0;
    this->instruction_table[0x48] = &Interpreter::i_dstore_1;
    this->instruction_table[0x49] = &Interpreter::i_dstore_2;
    this->instruction_table[0x4a] = &Interpreter::i_dstore_3;
    this->instruction_table[0x4b] = &Interpreter::i_astore_0;
    this->instruction_table[0x4c] = &Interpreter::i_astore_1;
    this->instruction_table[0x4d] = &Interpreter::i_astore_2;
    this->instruction_table[0x4e] = &Interpreter::i_astore_3;
    this->instruction_table[0x4f] = &Interpreter::i_iastore;
    this->instruction_table[0x50] = &Interpreter::i_lastore;
    this->instruction_table[0x51] = &Interpreter::i_fastore;
    this->instruction_table[0x52] = &Interpreter::i_dastore;
    this->instruction_table[0x53] = &Interpreter::i_aastore;
    this->instruction_table[0x54] = &Interpreter::i_bastore;
    this->instruction_table[0x55] = &Interpreter::i_castore;
    this->instruction_table[0x56] = &Interpreter::i_sastore;
    this->instruction_table[0x57] = &Interpreter::i_pop;
    this->instruction_table[0x58] = &Interpreter::i_pop2;
    this->instruction_table[0x59] = &Interpreter::i_dup;
    this->instruction_table[0x5a] = &Interpreter::i_dup2_x1;
    this->instruction_table[0x5b] = &Interpreter::i_dup2_x2;
    this->instruction_table[0x5c] = &Interpreter::i_dup2;
    this->instruction_table[0x5d] = &Interpreter::i_dup2_x1;
    this->instruction_table[0x5e] = &Interpreter::i_dup2_x2;
    this->instruction_table[0x5f] = &Interpreter::i_swap;
    this->instruction_table[0x60] = &Interpreter::i_iadd;
    this->instruction_table[0x61] = &Interpreter::i_ladd;
    this->instruction_table[0x62] = &Interpreter::i_fadd;
    this->instruction_table[0x63] = &Interpreter::i_dadd;
    this->instruction_table[0x64] = &Interpreter::i_isub;
    this->instruction_table[0x65] = &Interpreter::i_lsub;
    this->instruction_table[0x66] = &Interpreter::i_fsub;
    this->instruction_table[0x67] = &Interpreter::i_dsub;
    this->instruction_table[0x68] = &Interpreter::i_imul;
    this->instruction_table[0x69] = &Interpreter::i_lmul;
    this->instruction_table[0x6a] = &Interpreter::i_fmul;
    this->instruction_table[0x6b] = &Interpreter::i_dmul;
    this->instruction_table[0x6c] = &Interpreter::i_idiv;
    this->instruction_table[0x6d] = &Interpreter::i_ldiv;
    this->instruction_table[0x6e] = &Interpreter::i_fdiv;
    this->instruction_table[0x6f] = &Interpreter::i_ddiv;
    this->instruction_table[0x70] = &Interpreter::i_irem;
    this->instruction_table[0x71] = &Interpreter::i_lrem;
    this->instruction_table[0x72] = &Interpreter::i_frem;
    this->instruction_table[0x73] = &Interpreter::i_drem;
    this->instruction_table[0x74] = &Interpreter::i_ineg;
    this->instruction_table[0x75] = &Interpreter::i_lneg;
    this->instruction_table[0x76] = &Interpreter::i_fneg;
    this->instruction_table[0x77] = &Interpreter::i_dneg;
    this->instruction_table[0x78] = &Interpreter::i_ishl;
    this->instruction_table[0x79] = &Interpreter::i_lshl;
    this->instruction_table[0x7a] = &Interpreter::i_ishr;
    this->instruction_table[0x7b] = &Interpreter::i_lshr;
    this->instruction_table[0x7c] = &Interpreter::i_iushr;
    this->instruction_table[0x7d] = &Interpreter::i_lushr;
    this->instruction_table[0x7e] = &Interpreter::i_iand;
    this->instruction_table[0x7f] = &Interpreter::i_land;
    this->instruction_table[0x80] = &Interpreter::i_ior;
    this->instruction_table[0x81] = &Interpreter::i_lor;
    this->instruction_table[0x82] = &Interpreter::i_ixor;
    this->instruction_table[0x83] = &Interpreter::i_lxor;
    this->instruction_table[0x84] = &Interpreter::i_iinc;
    this->instruction_table[0x85] = &Interpreter::i_i2l;
    this->instruction_table[0x86] = &Interpreter::i_i2f;
    this->instruction_table[0x87] = &Interpreter::i_i2d;
    this->instruction_table[0x88] = &Interpreter::i_l2i;
    this->instruction_table[0x89] = &Interpreter::i_l2f;
    this->instruction_table[0x8a] = &Interpreter::i_l2d;
    this->instruction_table[0x8b] = &Interpreter::i_f2i;
    this->instruction_table[0x8c] = &Interpreter::i_f2l;
    this->instruction_table[0x8d] = &Interpreter::i_f2d;
    this->instruction_table[0x8e] = &Interpreter::i_d2i;
    this->instruction_table[0x8f] = &Interpreter::i_d2l;
    this->instruction_table[0x90] = &Interpreter::i_d2f;
    this->instruction_table[0x91] = &Interpreter::i_i2b;
    this->instruction_table[0x92] = &Interpreter::i_i2c;
    this->instruction_table[0x93] = &Interpreter::i_i2s;
    this->instruction_table[0x94] = &Interpreter::i_lcmp;
    this->instruction_table[0x95] = &Interpreter::i_fcmpl;
    this->instruction_table[0x96] = &Interpreter::i_fcmpg;
    this->instruction_table[0x97] = &Interpreter::i_dcmpl;
    this->instruction_table[0x98] = &Interpreter::i_dcmpg;
    this->instruction_table[0x99] = &Interpreter::i_ifeq;
    this->instruction_table[0x9a] = &Interpreter::i_ifne;
    this->instruction_table[0x9b] = &Interpreter::i_iflt;
    this->instruction_table[0x9c] = &Interpreter::i_ifge;
    this->instruction_table[0x9d] = &Interpreter::i_ifgt;
    this->instruction_table[0x9e] = &Interpreter::i_ifle;
    this->instruction_table[0x9f] = &Interpreter::i_if_icmpeq;
    this->instruction_table[0xa0] = &Interpreter::i_if_icmpne;
    this->instruction_table[0xa1] = &Interpreter::i_if_icmplt;
    this->instruction_table[0xa2] = &Interpreter::i_if_icmpge;
    this->instruction_table[0xa3] = &Interpreter::i_if_icmpgt;
    this->instruction_table[0xa4] = &Interpreter::i_if_icmple;
    this->instruction_table[0xa5] = &Interpreter::i_if_acmpeq;
    this->instruction_table[0xa6] = &Interpreter::i_if_acmpne;
    this->instruction_table[0xa7] = &Interpreter::i_goto;
    this->instruction_table[0xa8] = &Interpreter::i_jsr;
    this->instruction_table[0xa9] = &Interpreter::i_ret;
    this->instruction_table[0xaa] = &Interpreter::i_tableswitch;
    this->instruction_table[0xab] = &Interpreter::i_lookupswitch;
    this->instruction_table[0xac] = &Interpreter::i_ireturn;
    this->instruction_table[0xad] = &Interpreter::i_lreturn;
    this->instruction_table[0xae] = &Interpreter::i_freturn;
    this->instruction_table[0xaf] = &Interpreter::i_dreturn;
    this->instruction_table[0xb0] = &Interpreter::i_areturn;
    this->instruction_table[0xb1] = &Interpreter::i_return;
    this->instruction_table[0xb2] = &Interpreter::i_getstatic;
    this->instruction_table[0xb3] = &Interpreter::i_putstatic;
    this->instruction_table[0xb4] = &Interpreter::i_getfield;
    this->instruction_table[0xb5] = &Interpreter::i_putfield;
    this->instruction_table[0xb6] = &Interpreter::i_invokevirtual;
    this->instruction_table[0xb7] = &Interpreter::i_invokespecial;
    this->instruction_table[0xb8] = &Interpreter::i_invokestatic;
    this->instruction_table[0xb9] = &Interpreter::i_invokeinterface;
    this->instruction_table[0xbb] = &Interpreter::i_new;
    this->instruction_table[0xbc] = &Interpreter::i_newarray;
    this->instruction_table[0xbd] = &Interpreter::i_anewarray;
    this->instruction_table[0xbe] = &Interpreter::i_arraylength;
    this->instruction_table[0xbf] = &Interpreter::i_athrow;
    this->instruction_table[0xc0] = &Interpreter::i_checkcast;
    this->instruction_table[0xc1] = &Interpreter::i_instanceof;
    this->instruction_table[0xc2] = &Interpreter::i_monitorenter;
    this->instruction_table[0xc3] = &Interpreter::i_monitorexit;
    this->instruction_table[0xc4] = &Interpreter::i_wide;
    this->instruction_table[0xc5] = &Interpreter::i_multianewarray;
    this->instruction_table[0xc6] = &Interpreter::i_ifnull;
    this->instruction_table[0xc7] = &Interpreter::i_ifnonnull;
    this->instruction_table[0xc8] = &Interpreter::i_goto_w;
    this->instruction_table[0xc9] = &Interpreter::i_jsr_w;
}