#include <math.h>

#include "../header/Interpreter.hpp"
#include "../header/Opcodes.hpp"
#include "../header/ClassLoaderSubsystem.hpp"

Interpreter::Interpreter(Runtime * runtime){
    this->ConstructTable();

    this->runtime = runtime;
}

Interpreter::~Interpreter(){
    
}

void Interpreter::ExecuteInterpreter(){
    ClassLoaderSubsystem::Resolve(Runtime::main_class_name, this->runtime);    
    Interpreter::ExecuteFrame();
}

void Interpreter::ExecuteFrame(){
    cout << this->runtime->stack.size() << endl;
    // Aqui devemos executar o code.    
    while(this->runtime->stack.size() > 0){
        Frame *current_frame = this->runtime->GetCurrentFrame();
        Code_attribute current_code = current_frame->code;

        int current_pc = current_frame->pc;
        u1 bytecode = current_code.code[current_pc];

        // executa o método indicado pelo bytecode
        // não esquecer de verificar se o método existe.
        PointerFunction method_func = this->instruction_table[bytecode];
        (this->*method_func)();
    }
    // Para isso precisamos saber quantas casas de PC andar a cada função (Fazer isso dentro da própria função)

    // ( não precisa, vai desempilhar e basta colocar ) Colocar invoker_frame dentro das funções de invoke, para sinalizar para quem deve atribuir os return.

    // ( dentro do proprio return, desempilhar ) Pensar em como faremos para o return cancelar o frame atual e cancelar essa função.
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

void Interpreter::i_nop(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    topFrame->pc += 1;
}

void Interpreter::i_aconst_null(){    
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = OBJECT_VALUE;
    value.data.object_value = nullptr;

    topFrame->AddOperandStack(value);
    topFrame->pc += 1;
}

void Interpreter::i_iconst_m1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = -1;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iconst_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 0;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iconst_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 1;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iconst_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 2;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iconst_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 3;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iconst_4(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 4;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iconst_5(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 5;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_lconst_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    // Value padding;
    // padding.type = ValueType::PADDING;

    Value value;
    value.type = LONG_VALUE;
    value.data.long_value = 0;

    // topFrame->PushOperandStack(padding);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_lconst_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    // Value padding;
    // padding.type = ValueType::PADDING;

    Value value;
    value.type = LONG_VALUE;
    value.data.long_value = 1;

    // topFrame->PushOperandStack(padding);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_fconst_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = FLOAT_VALUE;
    value.data.float_value = 0;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_fconst_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = FLOAT_VALUE;
    value.data.float_value = 1;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_fconst_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = FLOAT_VALUE;
    value.data.float_value = 2;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_dconst_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    // Value padding;
    // padding.type = ValueType::PADDING;

    Value value;
    value.type = DOUBLE_VALUE;
    value.data.double_value = 0;

    // topFrame->PushOperandStack(padding);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_dconst_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    // Value padding;
    // padding.type = ValueType::PADDING;

    Value value;
    value.type = DOUBLE_VALUE;
    value.data.double_value = 1;

    // topFrame->PushOperandStack(padding);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_bipush(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
     
    u1 byte = topFrame->code.code[topFrame->pc+1];

    Value value;
    // value.printType = ValueType::BYTE;
    value.type = INT_VALUE;
    value.data.int_value = (int32_t) (int8_t) byte; // convertendo para inteiro e estendendo o sinal

    topFrame->AddOperandStack(value);

    topFrame->pc += 2;
}

void Interpreter::i_sipush(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    // u1 byte1 = topFrame->code.code[topFrame->pc+1];
    //u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t short_value = (byte1 << 8) | byte2;
    Value value;
    // value.printType = SHORT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = (int32_t) (int16_t) short_value; // convertendo para inteiro e estendendo o sinal

    topFrame->AddOperandStack(value);

    topFrame->pc += 3;
}

void Interpreter::i_ldc(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    u1 index = topFrame->code.code[topFrame->pc+1];
    // u1 index = topFrame->code.code[============================];
    
    vector<CpInfo *>constant_pool = topFrame->constant_pool;
    CpInfo *entry = constant_pool[index-1];

    Value value;
    
    if (entry->tag == CONSTANT_String) {
        CpInfo *utf8_entry = constant_pool[entry->info.String.string_index-1];
        // assert(utf8_entry.tag == CONSTANT_Utf8);
        
        u1* bytes = utf8_entry->info.Utf8.bytes;
        char utf8_string[utf8_entry->info.Utf8.length+1];
        int i;
        for (i = 0; i < utf8_entry->info.Utf8.length; i++) {
            utf8_string[i] = bytes[i];
        }
        utf8_string[i] = '\0';
        
        value.type = OBJECT_VALUE;
        // value.data.object = new StringObject(utf8_string);
    } else if (entry->tag == CONSTANT_Integer) {
        // value.printType = INT_VALUE;
        value.type = INT_VALUE;
        value.data.int_value = (int32_t) entry->info.Integer.bytes;
    } else if (entry->tag == CONSTANT_Float) {
        u4 float_bytes = entry->info.Float.bytes;
        int s = ((float_bytes >> 31) == 0) ? 1 : -1;
        int e = ((float_bytes >> 23) & 0xff);
        int m = (e == 0) ? (float_bytes & 0x7fffff) << 1 : (float_bytes & 0x7fffff) | 0x800000;
        
        float number = s*m*pow(2, e-150);
        value.type = FLOAT_VALUE;
        value.data.float_value = number;
    } else {
        // cerr << "ldc tentando acessar um elemento da CP invalido: " << entry->tag << endl;
        exit(1);
    }
    
    topFrame->AddOperandStack(value);
    topFrame->pc += 2;
}

void Interpreter::i_ldc_w(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    u2 index = (byte1 << 8) | byte2;
    
    vector<CpInfo *> constant_pool = topFrame->constant_pool;
    CpInfo *entry = constant_pool[index-1];
    
    Value value;
    
    if (entry->tag == CONSTANT_String) {
        CpInfo *utf8_entry = constant_pool[entry->info.String.string_index-1];
        // assert(utf8Entry.tag == CONSTANT_Utf8);
        
        u1* bytes = utf8_entry->info.Utf8.bytes;
        char utf8_string[utf8_entry->info.Utf8.length+1];
        int i;
        for (i = 0; i < utf8_entry->info.Utf8.length; i++) {
            utf8_string[i] = bytes[i];
        }
        utf8_string[i] = '\0';
        
        value.type = OBJECT_VALUE;
        // value.data.object = new StringObject(utf8_string);
    } else if (entry->tag == CONSTANT_Integer) {
        // value.printType = INT_VALUE;
        value.type = INT_VALUE;
        value.data.int_value = entry->info.Integer.bytes;
    } else if (entry->tag == CONSTANT_Float) {
        u4 float_bytes = entry->info.Float.bytes;
        int s = ((float_bytes >> 31) == 0) ? 1 : -1;
        int e = ((float_bytes >> 23) & 0xff);
        int m = (e == 0) ? (float_bytes & 0x7fffff) << 1 : (float_bytes & 0x7fffff) | 0x800000;
        
        float number = s*m*pow(2, e-150);
        value.type = FLOAT_VALUE;
        value.data.float_value = number;
    } else {
        // cerr << "ldc_w tentando acessar um elemento da CP invalido: " << entry.tag << endl;
        exit(1);
    }
    
    topFrame->AddOperandStack(value);
    topFrame->pc += 3;
}

void Interpreter::i_ldc2_w(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];
    
    u2 index = (byte1 << 8) | byte2;
    
    vector<CpInfo *> class_file = topFrame->constant_pool;
    CpInfo *entry = class_file[index-1];
    
    Value value;
    
    if (entry->tag == CONSTANT_Long) {
        u4 highBytes = entry->info.Long.high_bytes;
        u4 lowBytes = entry->info.Long.low_bytes;
        
        int64_t long_number = ((int64_t) highBytes << 32) + lowBytes;
        value.type = LONG_VALUE;
        value.data.long_value = long_number;
        
        // Value padding;
        // padding.type = ValueType::PADDING;
        
        // topFrame->PushOperandStack(padding);
    } else if (entry->tag == CONSTANT_Double) {
        u4 highBytes = entry->info.Double.high_bytes;
        u4 lowBytes = entry->info.Double.low_bytes;
        
        int64_t long_number = ((int64_t) highBytes << 32) + lowBytes;
        
        int32_t s = ((long_number >> 63) == 0) ? 1 : -1;
        int32_t e = (int32_t)((long_number >> 52) & 0x7ffL);
        int64_t m = (e == 0) ? (long_number & 0xfffffffffffffL) << 1 : (long_number & 0xfffffffffffffL) | 0x10000000000000L;
        
        double double_number = s*m*pow(2, e-1075);
        value.type = DOUBLE_VALUE;
        value.data.double_value = double_number;
        
        // Value padding;
        // padding.type = ValueType::PADDING;
        
        // topFrame->PushOperandStack(padding);
    } else {
        cerr << "ldc2_w tentando acessar um elemento da CP invalido: " << entry->tag << endl;
        exit(1);
    }
    
    topFrame->AddOperandStack(value);
    topFrame->pc += 3;
}

void Interpreter::i_iload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	
	int16_t index = (int16_t)byte1;

	if (wide) {
        u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	}
	else {
		topFrame->pc += 2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->GetLocalVariable(index);
	// assert(value.type == INT_VALUE);

	topFrame->AddOperandStack(value);
}

void Interpreter::i_lload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	u1 byte1 = topFrame->code.code[topFrame->pc+1];
    
	int16_t index = (int16_t)byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	}
	else {
		topFrame->pc += 2;
	}

	Value value = topFrame->GetLocalVariable(index);
	
    // assert(value.type == LONG_VALUE);

	// Value padding;
	// padding.type = ValueType::PADDING;

	// topFrame->pushIntoOperandStack(padding);
	topFrame->AddOperandStack(value);
}

void Interpreter::i_fload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	int16_t index = (int16_t)byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	}
	else {
		topFrame->pc += 2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->GetLocalVariable(index);
	// assert(value.type == FLOAT_VALUE);
	topFrame->AddOperandStack(value);
}

void Interpreter::i_dload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	int16_t index = (int16_t) byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	}
	else {
		topFrame->pc += 2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > (index + 1)));

	Value value = topFrame->GetLocalVariable(index);
	// assert(value.type == DOUBLE_VALUE);

	// Value padding;
	// padding.type = ValueType::PADDING;

	// topFrame->pushIntoOperandStack(padding);
	topFrame->AddOperandStack(value);
}

void Interpreter::i_aload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	int16_t index = (int16_t) byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	}
	else {
		topFrame->pc += 2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->GetLocalVariable(index);
	// assert(value.type == ValueType::REFERENCE);
	topFrame->AddOperandStack(value);
}

void Interpreter::i_iload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(0);
    // assert(value.type == ValueType::INT);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(1);
    // assert(value.type == ValueType::INT);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(2);
    // assert(value.type == ValueType::INT);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(3);
    // assert(value.type == ValueType::INT);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_lload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(1);
    // assert(value.type == ValueType::PADDING);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(0);
    // assert(value.type == LONG_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_lload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(2);
    // assert(value.type == ValueType::PADDING);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(1);
    // assert(value.type == LONG_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_lload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(3);
    // assert(value.type == ValueType::PADDING);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(2);
    // assert(value.type == LONG_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_lload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(4);
    // assert(value.type == ValueType::PADDING);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(3);
    // assert(value.type == LONG_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_fload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(0);
    // assert(value.type == FLOAT_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_fload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(1);
    // assert(value.type == FLOAT_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_fload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(2);
    // assert(value.type == FLOAT_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_fload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(3);
    // assert(value.type == FLOAT_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_dload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(1);
    // assert(value.type == ValueType::PADDING);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(0);
    // assert(value.type == DOUBLE_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_dload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(2);
    // assert(value.type == ValueType::PADDING);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(1);
    // assert(value.type == DOUBLE_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_dload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(3);
    // assert(value.type == ValueType::PADDING);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(2);
    // assert(value.type == DOUBLE_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_dload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(4);
    // assert(value.type == ValueType::PADDING);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(3);
    // assert(value.type == DOUBLE_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_aload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(0);
    // assert(value.type == ValueType::REFERENCE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_aload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(1);
    // assert(value.type == ValueType::REFERENCE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_aload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(2);
    // assert(value.type == ValueType::REFERENCE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_aload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(3);
    // assert(value.type == ValueType::REFERENCE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}

void Interpreter::i_iaload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	// ArrayObject *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    // array = (ArrayObject *) arrayref.data.object;

    // if (array == NULL) {
    //     cerr << "NullPointerException" << endl;
    //     exit(1);
    // }
    // if (index.data.intValue > array->getSize() || index.data.intValue < 0) {
    //     cerr << "ArrayIndexOutOfBoundsException" << endl;
    //     exit(2);
    // }

    // topFrame->AddOperandStack(array->getValue(index.data.int_value));
    topFrame->pc += 1;
}

void Interpreter::i_laload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	// ArrayObject *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    // array = (ArrayObject *) arrayref.data.object;

    // if (array == NULL) {
    //     cerr << "NullPointerException" << endl;
    //     exit(1);
    // }
    // if (index.data.intValue > array->getSize() || index.data.intValue < 0) {
    //     cerr << "ArrayIndexOutOfBoundsException" << endl;
    //     exit(2);
    // }

    // Value padding;
    // padding.type = ValueType::PADDING;
    
    // topFrame->pushIntoOperandStack(padding);
    // topFrame->AddOperandStack(array->getValue(index.data.intValue));
    topFrame->pc += 1;
}

void Interpreter::i_faload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	// ArrayObject *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    // array = (ArrayObject *) arrayref.data.object;

    // if (array == NULL) {
    //     cerr << "NullPointerException" << endl;
    //     exit(1);
    // }
    // if (index.data.intValue > array->getSize() || index.data.intValue < 0) {
    //     cerr << "ArrayIndexOutOfBoundsException" << endl;
    //     exit(2);
    // }

    // topFrame->AddOperandStack(array->getValue(index.data.intValue));
    topFrame->pc += 1;
}

void Interpreter::i_daload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	// ArrayObject *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    // array = (ArrayObject *) arrayref.data.object;

    // if (array == NULL) {
    //     cerr << "NullPointerException" << endl;
    //     exit(1);
    // }
    // if (index.data.intValue > array->getSize() || index.data.intValue < 0) {
    //     cerr << "ArrayIndexOutOfBoundsException" << endl;
    //     exit(2);
    // }

    // Value padding;
    // padding.type = ValueType::PADDING;
    
    // topFrame->pushIntoOperandStack(padding);
    // topFrame->AddOperandStack(array->getValue(index.data.intValue));
    topFrame->pc += 1;
}

void Interpreter::i_aaload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	// ArrayObject *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    // array = (ArrayObject *) arrayref.data.object;

    // if (array == NULL) {
    //     cerr << "NullPointerException" << endl;
    //     exit(1);
    // }
    // if (index.data.intValue > array->getSize() || index.data.intValue < 0) {
    //     cerr << "ArrayIndexOutOfBoundsException" << endl;
    //     exit(2);
    // }

    // topFrame->AddOperandStack(array->getValue(index.data.intValue));
    topFrame->pc += 1;
}

void Interpreter::i_baload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	// ArrayObject *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    // array = (ArrayObject *) arrayref.data.object;

    // if (array == NULL) {
    //     cerr << "NullPointerException" << endl;
    //     exit(1);
    // }
    // if (index.data.intValue > array->getSize() || index.data.intValue < 0) {
    //     cerr << "ArrayIndexOutOfBoundsException" << endl;
    //     exit(2);
    // }

    // Value value = array->getValue(index.data.intValue);
    // assert(value.type == ValueType::BOOLEAN || value.type == ValueType::BYTE);
    
    // if (value.type == ValueType::BOOLEAN) {
    //     value.data.intValue = (uint32_t) value.data.booleanValue;
    //     value.printType = ValueType::BOOLEAN;
    // } else {
    //     value.data.intValue = (int32_t) value.data.byteValue;
    //     value.printType = ValueType::BYTE;
    // }
    // value.type = ValueType::INT;

    // topFrame->AddOperandStack(value);
    topFrame->pc += 1;
}

void Interpreter::i_caload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	// ArrayObject *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    // array = (ArrayObject *) arrayref.data.object;

    // if (array == NULL) {
    //     cerr << "NullPointerException" << endl;
    //     exit(1);
    // }
    // if (index.data.intValue > array->getSize() || index.data.intValue < 0) {
    //     cerr << "ArrayIndexOutOfBoundsException" << endl;
    //     exit(2);
    // }

    // Value charValue = array->getValue(index.data.intValue);
    // charValue.data.intValue = (uint32_t) charValue.data.charValue;
    // charValue.printType = CHAR_VALUE;
    // charValue.type = ValueType::INT;
    
    // topFrame->AddOperandStack(charValue);
    topFrame->pc += 1;
}

void Interpreter::i_saload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	// ArrayObject *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    // array = (ArrayObject *) arrayref.data.object;

    // if (array == NULL) {
    //     cerr << "NullPointerException" << endl;
    //     exit(1);
    // }
    // if (index.data.intValue > array->getSize() || index.data.intValue < 0) {
    //     cerr << "ArrayIndexOutOfBoundsException" << endl;
    //     exit(2);
    // }
    
    // Value short_value = array->getValue(index.data.intValue);
    // short_value.data.intValue = (int32_t) short_value.data.short_value;
    // short_value.printType = SHORT_VALUE;
    // short_value.type = ValueType::INT;
    
    // topFrame->AddOperandStack(short_value);
    topFrame->pc += 1;
}

void Interpreter::i_istore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value = topFrame->PopOperandStack();
	// assert(value.type == ValueType::INT);

	u1 byte1 = topFrame->code.code[topFrame->pc+1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	} else {
		topFrame->pc += 2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	topFrame->ChangeLocalVariable(index, value);
}

void Interpreter::i_lstore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value = topFrame->PopOperandStack();
	// assert(value.type == ValueType::LONG);
	topFrame->PopOperandStack(); //padding

	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	int16_t index = (int16_t)byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	} else {
		topFrame->pc += 2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > (index + 1)));
	topFrame->ChangeLocalVariable(index, value);
	// Value padding;
	// padding.type = ValueType::PADDING;
	// topFrame->ChangeLocalVariable(index + 1, padding);
}

void Interpreter::i_fstore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value = topFrame->PopOperandStack();
	// assert(value.type == ValueType::FLOAT);

	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	int16_t index = (int16_t)byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	} else {
		topFrame->pc += 2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	topFrame->ChangeLocalVariable(index, value);
}

void Interpreter::i_dstore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value = topFrame->PopOperandStack();
	// assert(value.type == ValueType::DOUBLE);
	topFrame->PopOperandStack(); //padding

	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	int16_t index = (int16_t)byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	} else {
		topFrame->pc += 2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > (index + 1)));
	topFrame->ChangeLocalVariable(index, value);
	// Value padding;
	// padding.type = ValueType::PADDING;
	// topFrame->ChangeLocalVariable(index + 1, padding);
}

void Interpreter::i_astore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value = topFrame->PopOperandStack();
	// assert(value.type == ValueType::REFERENCE);

	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	int16_t index = (int16_t)byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		wide = false;
	} else {
		topFrame->pc += 2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	topFrame->ChangeLocalVariable(index, value);
}

void Interpreter::i_istore_0(){

}

void Interpreter::i_istore_1(){

}

void Interpreter::i_istore_2(){

}

void Interpreter::i_istore_3(){

}

void Interpreter::i_lstore_0(){

}

void Interpreter::i_lstore_1(){

}

void Interpreter::i_lstore_2(){

}

void Interpreter::i_lstore_3(){

}

void Interpreter::i_fstore_0(){

}

void Interpreter::i_fstore_1(){

}

void Interpreter::i_fstore_2(){

}

void Interpreter::i_fstore_3(){

}

void Interpreter::i_dstore_0(){

}

void Interpreter::i_dstore_1(){

}

void Interpreter::i_dstore_2(){

}

void Interpreter::i_dstore_3(){

}

void Interpreter::i_astore_0(){

}

void Interpreter::i_astore_1(){

}

void Interpreter::i_astore_2(){

}

void Interpreter::i_astore_3(){

}

void Interpreter::i_iastore(){

}

void Interpreter::i_lastore(){

}

void Interpreter::i_fastore(){

}

void Interpreter::i_dastore(){

}

void Interpreter::i_aastore(){

}

void Interpreter::i_bastore(){

}

void Interpreter::i_castore(){

}

void Interpreter::i_sastore(){

}

void Interpreter::i_pop(){

}

void Interpreter::i_pop2(){

}

void Interpreter::i_dup(){

}

void Interpreter::i_dup2_x1(){

}

void Interpreter::i_dup2_x2(){

}

void Interpreter::i_dup2(){

}

void Interpreter::i_swap(){

}

void Interpreter::i_iadd(){

}

void Interpreter::i_ladd(){

}

void Interpreter::i_fadd(){

}

void Interpreter::i_dadd(){

}
//  ALEXANDRE FAZENDO ATE AQUIIIIIIIIIIIIIIIIIIIIIIIII 

//###################################################################################################################################
//###################################################################################################################################
void Interpreter::i_isub(){
   
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
    
	value_1.data.int_value = value_1.data.int_value - (value_2.data.int_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;

}

void Interpreter::i_lsub(){
    
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);

	value_1.data.long_value = value_1.data.long_value - (value_2.data.long_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_fsub(){
    
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == FLOAT_VALUE);
	// assert(value_1.type == FLOAT_VALUE);

	value_1.data.float_value = value_1.data.float_value - (value_2.data.float_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_dsub(){
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == DOUBLE_VALUE);
	// assert(value_1.type == DOUBLE_VALUE);

	value_1.data.double_value = value_1.data.double_value - (value_2.data.double_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_imul(){
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
    
	value_1.data.int_value = value_1.data.int_value * (value_2.data.int_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_lmul(){
    
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);

	value_1.data.long_value = value_1.data.long_value * (value_2.data.long_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_fmul() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == FLOAT_VALUE);
	// assert(value_1.type == FLOAT_VALUE);

	value_1.data.float_value = value_1.data.float_value * (value_2.data.float_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_dmul() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == DOUBLE_VALUE);
	// assert(value_1.type == DOUBLE_VALUE);

	value_1.data.double_value = value_1.data.double_value * (value_2.data.double_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_idiv() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);
	if (value_2.data.int_value == 0) {
		cerr << "ArithmeticException" << endl;
		exit(2);
	}

    // value_1.printType = INT_VALUE;
	value_1.data.int_value = value_1.data.int_value / (value_2.data.int_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_ldiv() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);
	if (value_2.data.long_value == 0) {
		cerr << "ArithmeticException" << endl;
		exit(2);
	}

	value_1.data.long_value = value_1.data.long_value / (value_2.data.long_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_fdiv() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == FLOAT_VALUE);
	// assert(value_1.type == FLOAT_VALUE);
	if (value_2.data.float_value == 0) {
		cerr << "ArithmeticException" << endl;
		exit(2);
	}
	value_1.data.float_value = value_1.data.float_value / (value_2.data.float_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_ddiv() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == DOUBLE_VALUE);
	// assert(value_1.type == DOUBLE_VALUE);
	if (value_2.data.double_value == 0) {
		cerr << "ArithmeticException" << endl;
		exit(2);
	}
	value_1.data.double_value = value_1.data.double_value / (value_2.data.double_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_irem() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_2 = topFrame->PopOperandStack();
    Value value_1 = topFrame->PopOperandStack();

    // assert(value_2.type == INT_VALUE);
    // assert(value_1.type == INT_VALUE);
	if (value_2.data.int_value == 0) {
		cerr << "ArithmeticException" << endl;
        exit(2);
	}
	
    // value_1.printType = INT_VALUE;
	value_1.data.int_value = value_1.data.int_value - (value_1.data.int_value / value_2.data.int_value)*value_2.data.int_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_lrem() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_2 = topFrame->PopOperandStack();
    topFrame->PopOperandStack();
    Value value_1 = topFrame->PopOperandStack();
    // Sobra um padding na pilha que ficará abaixo do resultado

    // assert(value_2.type == LONG_VALUE);
    // assert(value_1.type == LONG_VALUE);
	if (value_2.data.long_value == 0) {
		cerr << "ArithmeticException" << endl;
        exit(2);
	}
	// value_1 negativo implica em resultado negativo
	value_1.data.long_value = value_1.data.long_value - (value_1.data.long_value / value_2.data.long_value)*value_2.data.long_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_frem() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_2 = topFrame->PopOperandStack();
    Value value_1 = topFrame->PopOperandStack();

    // assert(value_2.type == FLOAT_VALUE);
    // assert(value_1.type == FLOAT_VALUE);
	if (value_2.data.float_value == 0) {
		cerr << "ArithmeticException" << endl;
        exit(2);
	}
	// value_1 negativo implica em resultado negativo
	value_1.data.float_value = value_1.data.float_value - ((uint32_t)(value_1.data.float_value / value_2.data.float_value))*value_2.data.float_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_drem() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_2 = topFrame->PopOperandStack();
    topFrame->PopOperandStack(); // PADDING
    Value value_1 = topFrame->PopOperandStack();
    // Sobra um padding na pilha que ficará abaixo do resultado

    // assert(value_2.type == DOUBLE_VALUE);
    // assert(value_1.type == DOUBLE_VALUE);
	if (value_2.data.double_value == 0) {
		cerr << "ArithmeticException" << endl;
        exit(2);
	}
	// value_1 negativo implica em resultado negativo
	value_1.data.double_value = value_1.data.double_value - ((uint64_t)(value_1.data.double_value / value_2.data.double_value))*value_2.data.double_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_ineg() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    // assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.data.int_value = -value_1.data.int_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_lneg() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	// Não precisa tirar o padding
    Value value_1 = topFrame->PopOperandStack();
    // assert(value_1.type == LONG_VALUE);

	value_1.data.long_value = -value_1.data.long_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_fneg() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    // assert(value_1.type == FLOAT_VALUE);

	value_1.data.float_value = -value_1.data.float_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_dneg() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	// Não precisa tirar o padding
    Value value_1 = topFrame->PopOperandStack();
    // assert(value_1.type == DOUBLE_VALUE);

	value_1.data.double_value = -value_1.data.double_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_ishl() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_2 = topFrame->PopOperandStack();
    Value value_1 = topFrame->PopOperandStack();
    // assert(value_2.type == INT_VALUE);
    // assert(value_1.type == INT_VALUE);

	// value_2 armazena seus 5 primeiros bits
	value_2.data.int_value = 0x1f & value_2.data.int_value;
	value_1.data.int_value = value_1.data.int_value << value_2.data.int_value;
    // value_1.printType = INT_VALUE;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_lshl() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_2 = topFrame->PopOperandStack();
    Value value_1 = topFrame->PopOperandStack();
    // Sobra um padding na pilha que ficará abaixo do resultado

    // assert(value_2.type == INT_VALUE);
    // assert(value_1.type == LONG_VALUE);

    value_2.data.long_value = 0x3f & value_2.data.long_value;
    value_1.data.long_value = (value_1.data.long_value) << value_2.data.int_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_ishr() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_2 = topFrame->PopOperandStack();
    Value value_1 = topFrame->PopOperandStack();
    // assert(value_2.type == INT_VALUE);
    // assert(value_1.type == INT_VALUE);

	// value_2 armazena seus 5 primeiros bits
	value_2.data.int_value = 0x1f & value_2.data.int_value;
	value_1.data.int_value = value_1.data.int_value >> value_2.data.int_value;
    // value_1.printType = INT_VALUE;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_lshr() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

    Value value_2 = topFrame->PopOperandStack();
    Value value_1 = topFrame->PopOperandStack();
    // Sobra um padding na pilha que ficará abaixo do resultado

    // assert(value_2.type == INT_VALUE);
    // assert(value_1.type == LONG_VALUE);

	// value_2 armazena seus 6 primeiros bits
	value_2.data.long_value = 0x3f & value_2.data.long_value;
	value_1.data.long_value = value_1.data.long_value >> value_2.data.long_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}

void Interpreter::i_iushr() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

	value_2.data.int_value = 0x1f & value_2.data.int_value;
	value_1.data.int_value = value_1.data.int_value >> value_2.data.int_value;
	if (value_1.data.int_value < 0) {
		value_1.data.int_value = value_1.data.int_value + (2<<~(value_2.data.int_value));
	}
    // value_1.printType = INT_VALUE;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_lushr() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == LONG_VALUE);

	value_2.data.int_value = 0x3f & value_2.data.int_value;
	value_1.data.long_value = value_1.data.long_value >> value_2.data.int_value;
	if (value_1.data.long_value < 0) {
		value_1.data.long_value = value_1.data.long_value + ((int64_t)2 << ~(value_2.data.int_value));
	}
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_iand() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.data.int_value = value_1.data.int_value & value_2.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_land() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); // PADDING
	Value value_1 = topFrame->PopOperandStack();
	// Sobra um padding na pilha que ficará abaixo do resultado

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);

	// value_2 armazena seus 6 primeiros bits
	value_1.data.long_value = value_1.data.long_value & value_2.data.long_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_ior() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.data.int_value = value_1.data.int_value | value_2.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_lor() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); // PADDING
	Value value_1 = topFrame->PopOperandStack();
	// Sobra um padding na pilha que ficará abaixo do resultado

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);

	value_1.data.long_value = value_1.data.long_value | value_2.data.long_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_ixor() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.data.int_value = value_1.data.int_value ^ value_2.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_lxor() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); // PADDING
	Value value_1 = topFrame->PopOperandStack();
	// Sobra um padding na pilha que ficará abaixo do resultado

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);

	value_1.data.long_value = value_1.data.long_value ^ value_2.data.long_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_iinc() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    
    
    u2 index = 0;
    if (wide) {
        u1 byte2 = topFrame->code.code[topFrame->pc+2];
    } else {
        index += topFrame->code.code[topFrame->pc+1];
    }
    
    Value localVariable = topFrame->GetLocalVariable(index);
    // assert(localVariable.type == INT_VALUE);
    
    int32_t inc;
    if (wide) {
        uint16_t constant = (topFrame->code.code[topFrame->pc+3] << 8) | code[4];
        inc = (int32_t) (int16_t) constant;
    } else {
        u1 byte2 = topFrame->code.code[topFrame->pc+2];
    }
    
    localVariable.data.int_value += inc;
    topFrame->changeLocalVariable(localVariable, index);
    
    topFrame->pc += wide ? 5 : 3;
    wide = false;
}

void Interpreter::i_i2l() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

	Value padding;
	padding.type = ValueType::PADDING;

	topFrame->PushOperandStack(padding);

    value_1.data.long_value = (int64_t) value_1.data.int_value;
	value_1.type = LONG_VALUE;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_i2f() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

	value_1.type = FLOAT_VALUE;
	value_1.data.float_value = (float) value_1.data.int_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_i2d() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->PushOperandStack(padding);

	value_1.type = DOUBLE_VALUE;
	value_1.data.double_value = (double) value_1.data.int_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_l2i() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); //padding

	// assert(value_1.type == LONG_VALUE);

    value_1.data.int_value = (int32_t) value_1.data.int_value;
    // value_1.printType = INT_VALUE;
	value_1.type = INT_VALUE;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_l2f() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); //padding

	// assert(value_1.type == LONG_VALUE);

	value_1.type = FLOAT_VALUE;
	value_1.data.float_value = (float) value_1.data.long_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_l2d() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	//manter padding na pilha de operandos

	// assert(value_1.type == LONG_VALUE);

	value_1.type = DOUBLE_VALUE;
	value_1.data.double_value = (double) value_1.data.long_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_f2i() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == FLOAT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.type = INT_VALUE;
	value_1.data.int_value = (int32_t) value_1.data.float_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_f2l() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == FLOAT_VALUE);

	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->PushOperandStack(padding);

	value_1.type = LONG_VALUE;
	value_1.data.long_value = (uint64_t) value_1.data.float_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_f2d() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == FLOAT_VALUE);

	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->PushOperandStack(padding);

	value_1.type = DOUBLE_VALUE;
	value_1.data.double_value = (double) value_1.data.float_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_d2i() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); //padding

	// assert(value_1.type == DOUBLE_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.type = INT_VALUE;
	value_1.data.int_value = (int32_t) value_1.data.double_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_d2l() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	//manter padding na pilha de operandos

	// assert(value_1.type == DOUBLE_VALUE);

	value_1.type = LONG_VALUE;
	value_1.data.long_value = (int64_t) value_1.data.double_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_d2f() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); //padding

	// assert(value_1.type == DOUBLE_VALUE);

	value_1.type = FLOAT_VALUE;
	value_1.data.float_value = (float) value_1.data.double_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_i2b() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);
    
    value_1.printType = ValueType::BYTE;
    
    value_1.data.int_value = (int32_t) (int8_t) value_1.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_i2c() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

    value_1.printType = CHAR_VALUE;
    
    value_1.data.charValue = (uint32_t) (uint8_t) value_1.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_i2s() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

    value_1.printType = SHORT_VALUE;
    
    value_1.data.int_value = (int32_t) (int16_t) value_1.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}

void Interpreter::i_lcmp() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value resultado;
    resultado.printType = INT_VALUE;
	resultado.type = INT_VALUE;

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);

	if (value_1.data.long_value > value_2.data.long_value) {
		resultado.data.int_value = 1;
	} else if (value_1.data.long_value == value_2.data.long_value) {
		resultado.data.int_value = 0;
	} else {
		resultado.data.int_value = -1;
	}

	topFrame->PushOperandStack(resultado);

	topFrame->pc += 1;
}

void Interpreter::i_fcmpl() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	Value resultado;
    resultado.printType = INT_VALUE;
	resultado.type = INT_VALUE;

	// assert(value_2.type == FLOAT_VALUE);
	// assert(value_1.type == FLOAT_VALUE);

	if (isnan(value_1.data.float_value) || isnan(value_2.data.float_value)) {
		resultado.data.int_value = -1;
	} else if (value_1.data.float_value > value_2.data.float_value) {
		resultado.data.int_value = 1;
	} else if (value_1.data.float_value == value_2.data.float_value) {
		resultado.data.int_value = 0;
	} else {
		resultado.data.int_value = -1;
	}

	topFrame->PushOperandStack(resultado);

	topFrame->pc += 1;
}

void Interpreter::i_fcmpg() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	Value resultado;
    resultado.printType = INT_VALUE;
	resultado.type = INT_VALUE;

	// assert(value_2.type == FLOAT_VALUE);
	// assert(value_1.type == FLOAT_VALUE);

	if (isnan(value_1.data.float_value) || isnan(value_2.data.float_value)) {
		resultado.data.int_value = 1;
	} else if (value_1.data.float_value > value_2.data.float_value) {
		resultado.data.int_value = 1;
	} else if (value_1.data.float_value == value_2.data.float_value) {
		resultado.data.int_value = 0;
	} else {
		resultado.data.int_value = -1;
	}

	topFrame->PushOperandStack(resultado);

	topFrame->pc += 1;
}

void Interpreter::i_dcmpl() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value resultado;
    resultado.printType = INT_VALUE;
	resultado.type = INT_VALUE;

	// assert(value_2.type == DOUBLE_VALUE);
	// assert(value_1.type == DOUBLE_VALUE);

	if (isnan(value_1.data.double_value) || isnan(value_2.data.double_value)) {
		resultado.data.int_value = -1;
	} else if (value_1.data.double_value > value_2.data.double_value) {
		resultado.data.int_value = 1;
	} else if (value_1.data.double_value == value_2.data.double_value) {
		resultado.data.int_value = 0;
	} else {
		resultado.data.int_value = -1;
	}

	topFrame->PushOperandStack(resultado);

	topFrame->pc += 1;
}

void Interpreter::i_dcmpg() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value resultado;
    resultado.printType = INT_VALUE;
	resultado.type = INT_VALUE;

	// assert(value_2.type == DOUBLE_VALUE);
	// assert(value_1.type == DOUBLE_VALUE);

	if (isnan(value_1.data.double_value) || isnan(value_2.data.double_value)) {
		resultado.data.int_value = 1;
	} else if (value_1.data.double_value > value_2.data.double_value) {
		resultado.data.int_value = 1;
	} else if (value_1.data.double_value == value_2.data.double_value) {
		resultado.data.int_value = 0;
	} else {
		resultado.data.int_value = -1;
	}

	topFrame->PushOperandStack(resultado);

	topFrame->pc += 1;
}

void Interpreter::i_ifeq() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value value = topFrame->PopOperandStack();
    // assert(value.type == INT_VALUE);
    
    if (value.data.int_value == 0) {
        
        u1 byte1 = topFrame->code.code[topFrame->pc+1];
        u1 byte2 = topFrame->code.code[topFrame->pc+2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        topFrame->pc += branchOffset;
    } else {
        topFrame->pc += 3;
    }
}

void Interpreter::i_ifne() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value = topFrame->PopOperandStack();
	// assert(value.type == INT_VALUE);
	
	if (value.data.int_value != 0) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_iflt() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value = topFrame->PopOperandStack();
	// assert(value.type == INT_VALUE);
	
	if (value.data.int_value < 0) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_ifge() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value = topFrame->PopOperandStack();
	// assert(value.type == INT_VALUE);
	
	if (value.data.int_value >= 0) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_ifgt() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value = topFrame->PopOperandStack();
	// assert(value.type == INT_VALUE);
	
	if (value.data.int_value > 0) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_ifle() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value = topFrame->PopOperandStack();
	// assert(value.type == INT_VALUE);
	
	if (value.data.int_value <= 0) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_if_icmpeq() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == INT_VALUE);
	// assert(value2.type == INT_VALUE);
	
	if (value1.data.int_value == value2.data.int_value) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_if_icmpne() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == INT_VALUE);
	// assert(value2.type == INT_VALUE);
	
	if (value1.data.int_value != value2.data.int_value) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_if_icmplt() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == INT_VALUE);
	// assert(value2.type == INT_VALUE);
	
	if (value1.data.int_value < value2.data.int_value) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_if_icmpge() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == INT_VALUE);
	// assert(value2.type == INT_VALUE);
	
	if (value1.data.int_value >= value2.data.int_value) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_if_icmpgt() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == INT_VALUE);
	// assert(value2.type == INT_VALUE);
	
	if (value1.data.int_value > value2.data.int_value) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_if_icmple() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == INT_VALUE);
	// assert(value2.type == INT_VALUE);
	
	if (value1.data.int_value <= value2.data.int_value) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_if_acmpeq() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == ValueType::REFERENCE);
	// assert(value2.type == ValueType::REFERENCE);
	
	if (value1.data.object == value2.data.object) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_if_acmpne() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == ValueType::REFERENCE);
	// assert(value2.type == ValueType::REFERENCE);

	if (value1.data.object != value2.data.object) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Interpreter::i_goto() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	
	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	u1 byte2 = topFrame->code.code[topFrame->pc+2];
	int16_t branchOffset = (byte1 << 8) | byte2;
	topFrame->pc += branchOffset;
}

void Interpreter::i_jsr() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	
	
	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	u1 byte2 = topFrame->code.code[topFrame->pc+2];
	int16_t branchOffset = (byte1 << 8) | byte2;
	
	Value returnAddr;
	returnAddr.type = ValueType::RETURN_ADDR;
	returnAddr.data.returnAddress = topFrame->pc + 3; 
	topFrame->PushOperandStack(returnAddr);
	
	topFrame->pc += branchOffset;
}

// Pode ser modificado pelo wide
void Interpreter::i_ret() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	
	u1 byte1 = topFrame->code.code[topFrame->pc+1]; // índice do vetor de variáveis locais
	uint16_t index = (uint16_t) byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->GetLocalVariable(index);

	// assert(value.type == ValueType::RETURN_ADDR);
	topFrame->changeLocalVariable(value, index);

	topFrame->pc = value.data.returnAddress;
	wide = false;
}

void Interpreter::i_tableswitch() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    u1* code = topFrame->getCode(topFrame->pc);
    u1 padding = 4 - (topFrame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;
    
    u1 defaultbyte1 = code[padding + 1];
    u1 defaultbyte2 = code[padding + 2];
    u1 defaultbyte3 = code[padding + 3];
    u1 defaultbyte4 = code[padding + 4];
    int32_t defaultBytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;
    
    u1 lowbyte1 = code[padding + 5];
    u1 lowbyte2 = code[padding + 6];
    u1 lowbyte3 = code[padding + 7];
    u1 lowbyte4 = code[padding + 8];
    uint32_t lowbytes = (lowbyte1 << 24) | (lowbyte2 << 16) | (lowbyte3 << 8) | lowbyte4;
    
    u1 highbyte1 = code[padding + 9];
    u1 highbyte2 = code[padding + 10];
    u1 highbyte3 = code[padding + 11];
    u1 highbyte4 = code[padding + 12];
    uint32_t highbytes = (highbyte1 << 24) | (highbyte2 << 16) | (highbyte3 << 8) | highbyte4;
    
    Value keyValue = topFrame->PopOperandStack();
    // assert(keyValue.type == INT_VALUE);
    int32_t key = keyValue.data.int_value;
    
    uint32_t i;
    uint32_t baseIndex = padding + 13;
    int32_t offsets = highbytes - lowbytes + 1;
    bool matched = false;
    for (i = 0; i < offsets; i++) {
        if (key == lowbytes) {
            int32_t offset = (code[baseIndex] << 24) | (code[baseIndex+1] << 16) | (code[baseIndex+2] << 8) | code[baseIndex+3];
            topFrame->pc += offset;
            matched = true;
            break;
        }
        lowbytes++;
        baseIndex += 4;
    }
    
    if (!matched) {
        topFrame->pc += defaultBytes; // salto default
    }
}

void Interpreter::i_lookupswitch() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    u1* code = topFrame->getCode(topFrame->pc);
    u1 padding = 4 - (topFrame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;
    
    u1 defaultbyte1 = code[padding + 1];
    u1 defaultbyte2 = code[padding + 2];
    u1 defaultbyte3 = code[padding + 3];
    u1 defaultbyte4 = code[padding + 4];
    int32_t defaultBytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;
    
    u1 npairs1 = code[padding + 5];
    u1 npairs2 = code[padding + 6];
    u1 npairs3 = code[padding + 7];
    u1 npairs4 = code[padding + 8];
    uint32_t npairs = (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;

    Value keyValue = topFrame->PopOperandStack();
    // assert(keyValue.type == INT_VALUE);
    int32_t key = keyValue.data.int_value;
    
    uint32_t i;
    uint32_t baseIndex = padding + 9;
    bool matched = false;
    for (i = 0; i < npairs; i++) {
        int32_t match = (code[baseIndex] << 24) | (code[baseIndex+1] << 16) | (code[baseIndex+2] << 8) | code[baseIndex+3];
        
        if (key == match) {
            int32_t offset = (code[baseIndex+4] << 24) | (code[baseIndex+5] << 16) | (code[baseIndex+6] << 8) | code[baseIndex+7];
            topFrame->pc += offset;
            matched = true;
            break;
        }
        baseIndex += 8;
    }
    
    if (!matched) {
        topFrame->pc += defaultBytes; // salto default
    }
}

void Interpreter::i_ireturn() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == INT_VALUE);
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    newTopFrame->PushOperandStack(returnValue);
}

void Interpreter::i_lreturn() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == LONG_VALUE);
    // assert(topFrame->PopOperandStack();().type == ValueType::PADDING); // o debaixo precisa ser padding
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    Value padding;
    padding.type = ValueType::PADDING;
    newTopFrame->PushOperandStack(padding);
    newTopFrame->PushOperandStack(returnValue);
}

void Interpreter::i_freturn() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == FLOAT_VALUE);
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    newTopFrame->PushOperandStack(returnValue);
}

void Interpreter::i_dreturn() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == DOUBLE_VALUE);
    // assert(topFrame->PopOperandStack();().type == ValueType::PADDING); // o debaixo precisa ser padding
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    
    Value padding;
    padding.type = ValueType::PADDING;
    newTopFrame->PushOperandStack(padding);
    newTopFrame->PushOperandStack(returnValue);
}

void Interpreter::i_areturn() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == ValueType::REFERENCE);
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    newTopFrame->PushOperandStack(returnValue);
}

void Interpreter::i_return() {
    
    stackFrame.destroyTopFrame();
}

void Interpreter::i_getstatic() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    cp_info *constantPool = *(topFrame->getConstantPool());
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    cp_info fieldCP = constantPool[fieldIndex-1];
    // assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

    string className = getFormattedConstant(constantPool, fieldRef.class_index);

    cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    // assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

    string fieldName = getFormattedConstant(constantPool, fieldNameAndType.name_index);
    string fieldDescriptor = getFormattedConstant(constantPool, fieldNameAndType.descriptor_index);

    // caso especial
    if (className == "java/lang/System" && fieldDescriptor == "Ljava/io/PrintStream;" ) {
        topFrame->pc += 3;
        return;
    }
    // fim do caso especial
    
    MethodArea &methodArea = MethodArea::getInstance();
    ClassRuntime *classRuntime = methodArea.loadClassNamed(className);

    while (classRuntime != NULL) {
        if (classRuntime->fieldExists(fieldName) == false) {
            if (classRuntime->getClassFile()->super_class == 0) {
                classRuntime = NULL;
            } else {
                string superClassName = getFormattedConstant(classRuntime->getClassFile()->constant_pool, classRuntime->getClassFile()->super_class);
                classRuntime = methodArea.loadClassNamed(superClassName);
            }
        } else {
            break;
        }
    }

    if (classRuntime == NULL) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
    if (stackFrame.getTopFrame() != topFrame) return;
    
    Value staticValue = classRuntime->getValueFromField(fieldName);
    switch (staticValue.type) {
        case ValueType::BOOLEAN:
            staticValue.type = INT_VALUE;
            staticValue.printType = ValueType::BOOLEAN;
            break;
        case ValueType::BYTE:
            staticValue.type = INT_VALUE;
            staticValue.printType = ValueType::BYTE;
            break;
        case SHORT_VALUE:
            staticValue.type = INT_VALUE;
            staticValue.printType = SHORT_VALUE;
            break;
        case INT_VALUE:
            staticValue.type = INT_VALUE;
            staticValue.printType = INT_VALUE;
            break;
        default:
            break;
    }
    
    if (staticValue.type == DOUBLE_VALUE || staticValue.type == LONG_VALUE) {
        Value paddingValue;
        paddingValue.type = ValueType::PADDING;
        topFrame->PushOperandStack(paddingValue);
    }

    topFrame->PushOperandStack(staticValue);

    topFrame->pc += 3;
}

void Interpreter::i_putstatic() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    cp_info *constantPool = *(topFrame->getConstantPool());
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    cp_info fieldCP = constantPool[fieldIndex-1];
    // assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

    string className = getFormattedConstant(constantPool, fieldRef.class_index);

    cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    // assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

    string fieldName = getFormattedConstant(constantPool, fieldNameAndType.name_index);
    string fieldDescriptor = getFormattedConstant(constantPool, fieldNameAndType.descriptor_index);

    MethodArea &methodArea = MethodArea::getInstance();
    ClassRuntime *classRuntime = methodArea.loadClassNamed(className);

    while (classRuntime != NULL) {
        if (classRuntime->fieldExists(fieldName) == false) {
            if (classRuntime->getClassFile()->super_class == 0) {
                classRuntime = NULL;
            } else {
                string superClassName = getFormattedConstant(classRuntime->getClassFile()->constant_pool, classRuntime->getClassFile()->super_class);
                classRuntime = methodArea.loadClassNamed(superClassName);
            }
        } else {
            break;
        }
    }

    if (classRuntime == NULL) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
    if (stackFrame.getTopFrame() != topFrame) return;
    
    Value topValue = topFrame->PopOperandStack();
    if (topValue.type == DOUBLE_VALUE || topValue.type == LONG_VALUE) {
        topFrame->PopOperandStack(); // removendo padding
    } else {
        switch (fieldDescriptor[0]) {
            case 'B':
                topValue.type = ValueType::BYTE;
                topValue.printType = ValueType::BYTE;
                break;
            case 'C':
                topValue.type = CHAR_VALUE;
                topValue.type = CHAR_VALUE;
                break;
            case 'S':
                topValue.type = SHORT_VALUE;
                topValue.type = SHORT_VALUE;
                break;
            case 'Z':
                topValue.type = ValueType::BOOLEAN;
                topValue.type = ValueType::BOOLEAN;
                break;
        }
    }

    classRuntime->putValueIntoField(topValue, fieldName);

    topFrame->pc += 3;
}

void Interpreter::i_getfield() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    cp_info *constantPool = *(topFrame->getConstantPool());
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    cp_info fieldCP = constantPool[fieldIndex-1];
    // assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

    string className = getFormattedConstant(constantPool, fieldRef.class_index);

    cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    // assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

    string fieldName = getFormattedConstant(constantPool, fieldNameAndType.name_index);
    string fieldDescriptor = getFormattedConstant(constantPool, fieldNameAndType.descriptor_index);

    Value objectValue = topFrame->PopOperandStack();
    // assert(objectValue.type == ValueType::REFERENCE);
    Object *object = objectValue.data.object;
    // assert(object->objectType() == ObjectType::CLASS_INSTANCE);
    ClassInstance *classInstance = (ClassInstance *) object;

    if (!classInstance->fieldExists(fieldName)) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    Value fieldValue = classInstance->getValueFromField(fieldName);
    switch (fieldValue.type) {
        case ValueType::BOOLEAN:
            fieldValue.type = INT_VALUE;
            fieldValue.printType = ValueType::BOOLEAN;
            break;
        case ValueType::BYTE:
            fieldValue.type = INT_VALUE;
            fieldValue.printType = ValueType::BYTE;
            break;
        case SHORT_VALUE:
            fieldValue.type = INT_VALUE;
            fieldValue.printType = SHORT_VALUE;
            break;
        case INT_VALUE:
            fieldValue.type = INT_VALUE;
            fieldValue.printType = INT_VALUE;
            break;
        default:
            break;
    }
    
    if (fieldValue.type == DOUBLE_VALUE || fieldValue.type == LONG_VALUE) {
        Value paddingValue;
        paddingValue.type = ValueType::PADDING;
        topFrame->PushOperandStack(paddingValue);
    }

    topFrame->PushOperandStack(fieldValue);

    topFrame->pc += 3;
}

void Interpreter::i_putfield() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    cp_info *constantPool = *(topFrame->getConstantPool());
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    cp_info fieldCP = constantPool[fieldIndex-1];
    // assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

    string className = getFormattedConstant(constantPool, fieldRef.class_index);

    cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    // assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

    string fieldName = getFormattedConstant(constantPool, fieldNameAndType.name_index);
    string fieldDescriptor = getFormattedConstant(constantPool, fieldNameAndType.descriptor_index);

    Value valueToBeInserted = topFrame->PopOperandStack();
    if (valueToBeInserted.type == DOUBLE_VALUE || valueToBeInserted.type == LONG_VALUE) {
        topFrame->PopOperandStack(); // removendo padding
    } else {
        switch (fieldDescriptor[0]) {
            case 'B':
                valueToBeInserted.type = ValueType::BYTE;
                valueToBeInserted.printType = ValueType::BYTE;
                break;
            case 'C':
                valueToBeInserted.type = CHAR_VALUE;
                valueToBeInserted.printType = CHAR_VALUE;
                break;
            case 'S':
                valueToBeInserted.type = SHORT_VALUE;
                valueToBeInserted.printType = SHORT_VALUE;
                break;
            case 'Z':
                valueToBeInserted.type = ValueType::BOOLEAN;
                valueToBeInserted.printType = ValueType::BOOLEAN;
                break;
        }
    }

    Value objectValue = topFrame->PopOperandStack();
    // assert(objectValue.type == ValueType::REFERENCE);
    Object *object = objectValue.data.object;
    // assert(object->objectType() == ObjectType::CLASS_INSTANCE);
    ClassInstance *classInstance = (ClassInstance *) object;

    classInstance->putValueIntoField(valueToBeInserted, fieldName);

    topFrame->pc += 3;
}

void Interpreter::i_invokevirtual() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    cp_info *constantPool = *(topFrame->getConstantPool());
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    cp_info methodCP = constantPool[methodIndex-1];
    // assert(methodCP.tag == CONSTANT_Methodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

    string className = getFormattedConstant(constantPool, methodInfo.class_index);

    cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    // assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

    string methodName = getFormattedConstant(constantPool, methodNameAndType.name_index);
    string methodDescriptor = getFormattedConstant(constantPool, methodNameAndType.descriptor_index);

    if (className.find("java/") != string::npos) {
        // simulando println ou print
        if (className == "java/io/PrintStream" && (methodName == "print" || methodName == "println")) {
            if (methodDescriptor != "()V") {
                Value print_value = topFrame->PopOperandStack();

                if (print_value.type == INT_VALUE) {
                    switch (print_value.printType) {
                        case ValueType::BOOLEAN:
                            printf("%s", print_value.data.booleanValue == 0 ? "false" : "true");
                            break;
                        case ValueType::BYTE:
                            printf("%d", print_value.data.byteValue);
                            break;
                        case CHAR_VALUE:
                            printf("%c", print_value.data.charValue);
                            break;
                        case SHORT_VALUE:
                            printf("%d", print_value.data.shortValue);
                            break;
                        default:
                            printf("%d", print_value.data.int_value);
                            break;
                    }
                } else {
                    switch (print_value.type) {
                        case DOUBLE_VALUE:
                            topFrame->PopOperandStack(); // removendo padding
                            printf("%f", print_value.data.double_value);
                            break;
                        case FLOAT_VALUE:
                            printf("%f", print_value.data.float_value);
                            break;
                        case LONG_VALUE:
                            topFrame->PopOperandStack(); // removendo padding
                            printf("%lld", print_value.data.long_value);
                            break;
                        case ValueType::REFERENCE:
                            // assert(print_value.data.object->objectType() == ObjectType::STRING_INSTANCE);
                            printf("%s", ((StringObject *) print_value.data.object)->getString().c_str());
                            break;
                        case ValueType::BOOLEAN:
                            printf("%s", print_value.data.booleanValue == 0 ? "false" : "true");
                            break;
                        case ValueType::BYTE:
                            printf("%d", print_value.data.byteValue);
                            break;
                        case CHAR_VALUE:
                            printf("%c", print_value.data.charValue);
                            break;
                        case SHORT_VALUE:
                            printf("%d", print_value.data.shortValue);
                            break;
                        default:
                            cerr << "Tentando printar tipo de dado invalido: " << print_value.type << endl;
                            exit(1);
                            break;
                    }
                }
            }

            if (methodName == "println") printf("\n");
        } else if (className == "java/lang/String" && methodName == "equals") {
            Value strValue1 = topFrame->PopOperandStack();
            Value strValue2 = topFrame->PopOperandStack();
            // assert(strValue1.type == ValueType::REFERENCE);
            // assert(strValue2.type == ValueType::REFERENCE);
            // assert(strValue1.data.object->objectType() == ObjectType::STRING_INSTANCE);
            // assert(strValue2.data.object->objectType() == ObjectType::STRING_INSTANCE);
            
            StringObject *str1 = (StringObject*) strValue1.data.object;
            StringObject *str2 = (StringObject*) strValue2.data.object;
            
            Value result;
            result.printType = INT_VALUE;
            result.type = INT_VALUE;
            if (str1->getString() == str2->getString()) {
                result.data.int_value = 1;
            } else {
                result.data.int_value = 0;
            }
            topFrame->PushOperandStack(result);
        } else if (className == "java/lang/String" && methodName == "length") {	
            Value strValue = topFrame->PopOperandStack();
            // assert(strValue.type == ValueType::REFERENCE);		
            // assert(strValue.data.object->objectType() == ObjectType::STRING_INSTANCE);		
                    
            StringObject *str = (StringObject*) strValue.data.object;		
                    
            Value result;
            result.printType = INT_VALUE;
            result.type = INT_VALUE;		
            result.data.int_value = (str->getString()).size();		
            topFrame->PushOperandStack(result);
        } else {
            cerr << "Tentando invocar metodo de instancia invalido: " << methodName << endl;
            exit(1);
        }
    } else {
        uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';');
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[');
                if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
            } else {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = topFrame->PopOperandStack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        Value objectValue = topFrame->PopOperandStack();
        // assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
        args.insert(args.begin(), objectValue);

        Object *object = objectValue.data.object;
        // assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
        ClassInstance *instance = (ClassInstance *) object;

        MethodArea &methodArea = MethodArea::getInstance();
        ClassRuntime *classRuntime = methodArea.loadClassNamed(className);
        
        Frame *newFrame = new Frame(instance, classRuntime, methodName, methodDescriptor, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        if (stackFrame.getTopFrame() != topFrame) {
            topFrame->setOperandStackFromBackup(operandStackBackup);
            delete newFrame;
            return;
        }

        stackFrame.addFrame(newFrame);
    }

    topFrame->pc += 3;
}

void Interpreter::i_invokespecial() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    cp_info *constantPool = *(topFrame->getConstantPool());
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    cp_info methodCP = constantPool[methodIndex-1];
    // assert(methodCP.tag == CONSTANT_Methodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

    string className = getFormattedConstant(constantPool, methodInfo.class_index);

    cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    // assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

    string methodName = getFormattedConstant(constantPool, methodNameAndType.name_index);
    string methodDescriptor = getFormattedConstant(constantPool, methodNameAndType.descriptor_index);
    
    // casos especiais
    if ((className == "java/lang/Object" || className == "java/lang/String") && methodName == "<init>") {
        if (className == "java/lang/String") {
            topFrame->PopOperandStack();
        }
        
        topFrame->pc += 3;
        return;
    }
    // fim dos casos especiais
    
    if (className.find("java/") != string::npos) {
        cerr << "Tentando invocar metodo especial invalido: " << methodName << endl;
        exit(1);
    } else {
        uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';');
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[');
                if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
            } else {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = topFrame->PopOperandStack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        Value objectValue = topFrame->PopOperandStack();
        // assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
        args.insert(args.begin(), objectValue);

        Object *object = objectValue.data.object;
        // assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
        ClassInstance *instance = (ClassInstance *) object;

        MethodArea &methodArea = MethodArea::getInstance();
        ClassRuntime *classRuntime = methodArea.loadClassNamed(className);
        
        Frame *newFrame = new Frame(instance, classRuntime, methodName, methodDescriptor, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        if (stackFrame.getTopFrame() != topFrame) {
            topFrame->setOperandStackFromBackup(operandStackBackup);
            delete newFrame;
            return;
        }

        stackFrame.addFrame(newFrame);
    }

    topFrame->pc += 3;
}

void Interpreter::i_invokestatic() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    cp_info *constantPool = *(topFrame->getConstantPool());
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    cp_info methodCP = constantPool[methodIndex-1];
    // assert(methodCP.tag == CONSTANT_Methodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

    string className = getFormattedConstant(constantPool, methodInfo.class_index);

    cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    // assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

    string methodName = getFormattedConstant(constantPool, methodNameAndType.name_index);
    string methodDescriptor = getFormattedConstant(constantPool, methodNameAndType.descriptor_index);

    if (className == "java/lang/Object" && methodName == "registerNatives") {
        topFrame->pc += 3;
        return;
    }
    
    if (className.find("java/") != string::npos) {
        cerr << "Tentando invocar metodo estatico invalido: " << methodName << endl;
        exit(1);
    } else {
        uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';');
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[');
                if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
            } else {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = topFrame->PopOperandStack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        MethodArea &methodArea = MethodArea::getInstance();
        ClassRuntime *classRuntime = methodArea.loadClassNamed(className);
        Frame *newFrame = new Frame(classRuntime, methodName, methodDescriptor, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        if (stackFrame.getTopFrame() != topFrame) {
            topFrame->setOperandStackFromBackup(operandStackBackup);
            delete newFrame;
            return;
        }

        stackFrame.addFrame(newFrame);
    }

    topFrame->pc += 3;
}

void Interpreter::i_invokeinterface() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    cp_info *constantPool = *(topFrame->getConstantPool());
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    cp_info methodCP = constantPool[methodIndex-1];
    // assert(methodCP.tag == CONSTANT_Methodref || methodCP.tag == CONSTANT_InterfaceMethodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

    string className = getFormattedConstant(constantPool, methodInfo.class_index);

    cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    // assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

    string methodName = getFormattedConstant(constantPool, methodNameAndType.name_index);
    string methodDescriptor = getFormattedConstant(constantPool, methodNameAndType.descriptor_index);

    if (className.find("java/") != string::npos) {
        cerr << "Tentando invocar metodo de interface invalido: " << methodName << endl;
        exit(1);
    } else {
        uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';');
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[');
                if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
            } else {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = topFrame->PopOperandStack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        Value objectValue = topFrame->PopOperandStack();
        // assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
        args.insert(args.begin(), objectValue);

        Object *object = objectValue.data.object;
        // assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
        ClassInstance *instance = (ClassInstance *) object;

        MethodArea &methodArea = MethodArea::getInstance();
        methodArea.loadClassNamed(className); // carregando a interface (caso ainda não foi carregada).
        
        Frame *newFrame = new Frame(instance, instance->getClassRuntime(), methodName, methodDescriptor, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        if (stackFrame.getTopFrame() != topFrame) {
            topFrame->setOperandStackFromBackup(operandStackBackup);
            delete newFrame;
            return;
        }

        stackFrame.addFrame(newFrame);
    }

    topFrame->pc += 5;
}

void Interpreter::i_new() {
           
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();     
    cp_info *constantPool = *(topFrame->getConstantPool());
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t classIndex = (byte1 << 8) | byte2;
    cp_info classCP = constantPool[classIndex-1];
    // assert(classCP.tag == CONSTANT_Class);
    
    CONSTANT_Class_info classInfo = classCP.info.class_info; // Formata nome da classe
    string className = getFormattedConstant(constantPool, classInfo.name_index);

    Object *object;
    if (className == "java/lang/String") {
        object = new StringObject();
    } else {
        MethodArea &methodArea = MethodArea::getInstance();
        ClassRuntime *classRuntime = methodArea.loadClassNamed(className);
        object = new ClassInstance(classRuntime); // Cria instancia da classe e coloca na heap
    }
    
    // Armazena referência na pilha
    Value objectref;
    objectref.data.object = object;
    objectref.type = ValueType::REFERENCE;
    topFrame->PushOperandStack(objectref);
    
    topFrame->pc += 3;
}

void Interpreter::i_newarray() {
           
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value count = topFrame->PopOperandStack(); // Número de elementos no array
    // assert(count.type == INT_VALUE);
    
    if (count.data.int_value < 0) {
        cerr << "NegativeArraySizeException" << endl;
        exit(1);
    }
    
    ArrayObject *array; // array que será criado
    Value value; // elemento que irá popular o array
    value.data.long_value = 0; // inicializando Value com 0s
    
    Value padding; // padding poderá ser usado
    padding.type = ValueType::PADDING;
    
    
    switch (topFrame->code.code[topFrame->pc+1]) { // argumento representa tipo do array
        case 4:
            array = new ArrayObject(ValueType::BOOLEAN);
            value.type = ValueType::BOOLEAN;
            value.printType = ValueType::BOOLEAN;
            for (int i = 0; i < count.data.int_value; i++) {
                array->pushValue(value);
            }
            break;
        case 5:
            array = new ArrayObject(CHAR_VALUE);
            value.type = CHAR_VALUE;
            value.printType = CHAR_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->pushValue(value);
            }
            break;
        case 6:
            array = new ArrayObject(FLOAT_VALUE);
            value.type = FLOAT_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->pushValue(value);
            }
            break;
        case 7:
            array = new ArrayObject(DOUBLE_VALUE);
            value.type = DOUBLE_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->pushValue(value);
            }
            break;
        case 8:
            array = new ArrayObject(ValueType::BYTE);
            value.type = ValueType::BYTE;
            value.printType = ValueType::BYTE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->pushValue(value);
            }
            break;
        case 9:
            array = new ArrayObject(SHORT_VALUE);
            value.type = SHORT_VALUE;
            value.printType = SHORT_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->pushValue(value);
            }
            break;
        case 10:
            array = new ArrayObject(INT_VALUE);
            value.type = INT_VALUE;
            value.printType = INT_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->pushValue(value);
            }
            break;
        case 11:
            array = new ArrayObject(LONG_VALUE);
            value.type = LONG_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->pushValue(value);
            }
            break;
    }
    
    Value arrayref; // Referencia pro array na pilha de operandos
    arrayref.type = ValueType::REFERENCE;
    arrayref.data.object = array;
    
    topFrame->PushOperandStack(arrayref);
    topFrame->pc += 2;
}

void Interpreter::i_anewarray() {
           
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value count = topFrame->PopOperandStack(); // Número de elementos no array
    // assert(count.type == INT_VALUE);
    if (count.data.int_value < 0) {
        cerr << "NegativeArraySizeException" << endl;
        exit(1);
    }
    
    cp_info *constantPool = *(topFrame->getConstantPool());
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t classIndex = (byte1 << 8) | byte2; // Índice na pool de constantes
    cp_info classCP = constantPool[classIndex-1];
    // assert(classCP.tag == CONSTANT_Class);
    
    CONSTANT_Class_info classInfo = classCP.info.class_info; // Formata nome da classe
    string className = getFormattedConstant(constantPool, classInfo.name_index);

    if (className != "java/lang/String") {
        int i = 0;
        while (className[i] == '[') i++;
        if (className[i] == 'L') {
            MethodArea &methodArea = MethodArea::getInstance();
            methodArea.loadClassNamed(className.substr(i+1, className.size()-i-2)); // carrega a classe de referência (se ainda não foi).
        }
    }

    // criando objeto da classe instanciada
    Value objectref;
    objectref.type = ValueType::REFERENCE;
    objectref.data.object = new ArrayObject(ValueType::REFERENCE);
    
    // populando array com NULL
    Value nullValue;
    nullValue.type = ValueType::REFERENCE;
    nullValue.data.object = NULL;
    for (int i = 0; i < count.data.int_value; i++) {
        ((ArrayObject *) objectref.data.object)->pushValue(nullValue);
    }

    topFrame->PushOperandStack(objectref);
    
    topFrame->pc += 3;
}

void Interpreter::i_arraylength() {
           
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value arrayref = topFrame->PopOperandStack();  
    // assert(arrayref.type == ValueType::REFERENCE);
    if (arrayref.data.object == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    
    Value length;
    length.type = INT_VALUE;
    length.data.int_value = ((ArrayObject *) arrayref.data.object)->getSize();
    
    topFrame->PushOperandStack(length);
    topFrame->pc += 1 ;
}

void Interpreter::i_athrow() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    topFrame->pc += 1;
}

void Interpreter::i_checkcast() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    MethodArea &methodArea = MethodArea::getInstance();
    
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];
    
    u2 cpIndex = (byte1 << 8) | byte2;
    cp_info *constantPool = *(topFrame->getConstantPool());
    cp_info cpElement = constantPool[cpIndex-1];
    // assert(cpElement.tag == CONSTANT_Class);
    string className = getFormattedConstant(constantPool, cpIndex);
    
    Value objectrefValue = topFrame->PopOperandStack();
    // assert(objectrefValue.type == ValueType::REFERENCE);
    
    Value resultValue;
    resultValue.type = INT_VALUE;
    
    if (objectrefValue.data.object == NULL) {
        cerr << "ClassCastException" << endl;
        exit(1);
    } else {
        Object *obj = objectrefValue.data.object;
        
        if (obj->objectType() == ObjectType::CLASS_INSTANCE) {
            ClassInstance *classInstance = (ClassInstance *) obj;
            ClassRuntime *classRuntime = classInstance->getClassRuntime();
            
            bool found = false;
            while (!found) {
                ClassFile *classFile = classRuntime->getClassFile();
                string currClassName = getFormattedConstant(classFile->constant_pool, classFile->this_class);
                
                if (currClassName == className) {
                    found = true;
                } else {
                    if (classFile->super_class == 0) {
                        break;
                    } else {
                        string superClassName = getFormattedConstant(classFile->constant_pool, classFile->this_class);
                        classRuntime = methodArea.loadClassNamed(superClassName);
                    }
                }
            }
            
            resultValue.data.int_value = found ? 1 : 0;
        } else if (obj->objectType() == ObjectType::STRING_INSTANCE) {
            resultValue.data.int_value = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
        } else {
            if (className == "java/lang/Object") {
                resultValue.data.int_value = 1;
            } else {
                resultValue.data.int_value = 0;
            }
        }
    }
    
    topFrame->PushOperandStack(resultValue);
    
    topFrame->pc += 3;
}

void Interpreter::i_instanceof() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    MethodArea &methodArea = MethodArea::getInstance();

    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];
    
    u2 cpIndex = (byte1 << 8) | byte2;
    cp_info *constantPool = *(topFrame->getConstantPool());
    cp_info cpElement = constantPool[cpIndex-1];
    // assert(cpElement.tag == CONSTANT_Class);
    string className = getFormattedConstant(constantPool, cpIndex);
    
    Value objectrefValue = topFrame->PopOperandStack();
    // assert(objectrefValue.type == ValueType::REFERENCE);
    
    Value resultValue;
    resultValue.type = INT_VALUE;

    if (objectrefValue.data.object == NULL) {
        resultValue.data.int_value = 0;
    } else {
        Object *obj = objectrefValue.data.object;
        
        if (obj->objectType() == ObjectType::CLASS_INSTANCE) {
            ClassInstance *classInstance = (ClassInstance *) obj;
            ClassRuntime *classRuntime = classInstance->getClassRuntime();
            
            bool found = false;
            while (!found) {
                ClassFile *classFile = classRuntime->getClassFile();
                string currClassName = getFormattedConstant(classFile->constant_pool, classFile->this_class);
                
                if (currClassName == className) {
                    found = true;
                } else {
                    if (classFile->super_class == 0) {
                        break;
                    } else {
                        string superClassName = getFormattedConstant(classFile->constant_pool, classFile->this_class);
                        classRuntime = methodArea.loadClassNamed(superClassName);
                    }
                }
            }
            
            resultValue.data.int_value = found ? 1 : 0;
        } else if (obj->objectType() == ObjectType::STRING_INSTANCE) {
            resultValue.data.int_value = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
        } else {
            if (className == "java/lang/Object") {
                resultValue.data.int_value = 1;
            } else {
                resultValue.data.int_value = 0;
            }
        }
    }
    
    topFrame->PushOperandStack(resultValue);
    
    topFrame->pc += 3;
}

void Interpreter::i_monitorenter() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    topFrame->pc += 1;
}

void Interpreter::i_monitorexit() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    topFrame->pc += 1;
}

void Interpreter::i_wide() {
	       
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
	wide = true;
	topFrame->pc += 1;
}

void Interpreter::i_multianewarray() {
           
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    cp_info *constantPool = *(topFrame->getConstantPool());
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];
    u1 dimensions = topFrame->code.code[topFrame->pc+3];
    // assert(dimensions >= 1);

    uint16_t classIndex = (byte1 << 8) | byte2;
    cp_info classCP = constantPool[classIndex-1];
    // assert(classCP.tag == CONSTANT_Class);
    
    CONSTANT_Class_info classInfo = classCP.info.class_info;
    string className = getFormattedConstant(constantPool, classInfo.name_index);
    
    // obter o tipo dentro de className:
    ValueType valueType;
    int i = 0;
    while (className[i] == '[') i++;
    
    string multiArrayType = className.substr(i+1, className.size()-i-2); // em caso de ser uma referência (e.g. [[[Ljava/lang/String;)
    
    switch (className[i]) {
        case 'L':
            if (multiArrayType != "java/lang/String") {
                MethodArea &methodArea = MethodArea::getInstance();
                methodArea.loadClassNamed(multiArrayType); // verifica se existe classe com esse nome
            }
            valueType = ValueType::REFERENCE;
            break;
        case 'B':
            valueType = ValueType::BYTE;
            break;
        case 'C':
            valueType = CHAR_VALUE;
            break;
        case 'D':
            valueType = DOUBLE_VALUE;
            break;
        case 'F':
            valueType = FLOAT_VALUE;
            break;
        case 'I':
            valueType = INT_VALUE;
            break;
        case 'J':
            valueType = LONG_VALUE;
            break;
        case 'S':
            valueType = SHORT_VALUE;
            break;
        case 'Z':
            valueType = ValueType::BOOLEAN;
            break;
        default:
            cerr << "Descritor invalido em multianewarray" << endl;
            exit(1);
    }
    
    stack<int> count;
    for (int i = 0; i < dimensions; i++) {
        Value dimLength = topFrame->PopOperandStack();
        // assert(dimLength.type == INT_VALUE);
        count.push(dimLength.data.int_value);
    }
    
    ArrayObject *array = new ArrayObject((dimensions > 1) ? ValueType::REFERENCE : valueType);
    populateMultiarray(array, valueType, count);
    
    Value arrayValue;
    arrayValue.type = ValueType::REFERENCE;
    arrayValue.data.object = array;
    
    topFrame->PushOperandStack(arrayValue);
    
    topFrame->pc += 4;
}

void Interpreter::i_ifnull() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value referenceValue = topFrame->PopOperandStack();
    // assert(referenceValue.type == ValueType::REFERENCE);
    
    if (referenceValue.data.object == NULL) {
        
        u1 byte1 = topFrame->code.code[topFrame->pc+1];
        u1 byte2 = topFrame->code.code[topFrame->pc+2];
        int16_t branch =  (byte1 << 8) | byte2;
        topFrame->pc += branch;
    } else {
        topFrame->pc += 3;
    }
}

void Interpreter::i_ifnonnull() {
    
    Frame *topFrame = Interpreter::runtime->GetCurrentFrame();
    
    Value referenceValue = topFrame->PopOperandStack();
    // assert(referenceValue.type == ValueType::REFERENCE);
    
    if (referenceValue.data.object != NULL) {
        
        u1 byte1 = topFrame->code.code[topFrame->pc+1];
        u1 byte2 = topFrame->code.code[topFrame->pc+2];
        int16_t branch =  (byte1 << 8) | byte2;
        topFrame->pc += branch;
    } else {
        topFrame->pc += 3;
    }
}

void Interpreter::i_goto_w() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	
	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	u1 byte2 = topFrame->code.code[topFrame->pc+2];
	u1 byte3 = topFrame->code.code[topFrame->pc+3];
	u1 byte4 = code[4];
	int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

	topFrame->pc += branchOffset;
	// assert(topFrame->pc < (int32_t)topFrame->sizeCode());
}

void Interpreter::i_jsr_w() {
	
	Frame *topFrame = Interpreter::runtime->GetCurrentFrame();

	
	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	u1 byte2 = topFrame->code.code[topFrame->pc+2];
	u1 byte3 = topFrame->code.code[topFrame->pc+3];
	u1 byte4 = code[4];
	int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8)| byte4;

	Value returnAddr;
	returnAddr.type = ValueType::RETURN_ADDR;
	returnAddr.data.returnAddress = topFrame->pc + 5;
	topFrame->PushOperandStack(returnAddr);

	topFrame->pc += branchOffset;
	// assert(topFrame->pc < (int32_t)topFrame->sizeCode());
}