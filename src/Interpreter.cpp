#include <math.h>

#include "../header/Interpreter.hpp"
#include "../header/Opcodes.hpp"
#include "../header/ClassLoaderSubsystem.hpp"
#include "../header/ReadFile.hpp"
#include "../header/MethodAreaSection.hpp"
#include "../header/ObjectRef.hpp"

Interpreter::Interpreter(Runtime * runtime){
    this->ConstructTable();

    this->runtime = runtime;
}

Interpreter::~Interpreter(){
    
}
//! Essa função representa a função ExecuteInterpreter da JVM
void Interpreter::ExecuteInterpreter(){
    ClassLoaderSubsystem::Resolve(Runtime::main_class_name, this->runtime);    
    Interpreter::ExecuteFrame();
}
//! Essa função representa a função ExecuteFrame da JVM
void Interpreter::ExecuteFrame(){
    cout << this->runtime->stack.size() << endl;
    Opcodes::CreateOpcodes();
    // Aqui devemos executar o code.    
    while(this->runtime->stack.size() > 0){
        // cout << "RODANDO STACK " << endl;
        Frame *current_frame = this->runtime->GetCurrentFrame();
        Code_attribute current_code = current_frame->code;
        // cout << "EXECUTE " << endl;
        int current_pc = current_frame->pc;
        u1 bytecode = current_code.code[current_pc];
        // cout << "EXECUTE 2" << endl;
        // executa o método indicado pelo bytecode
        // não esquecer de verificar se o método existe.
        PointerFunction method_func = this->instruction_table[bytecode];
        // cout << "EXECUTE 3" << endl;
        cout << "Executando: " << Opcodes::opcodes[bytecode].first << endl;

        (this->*method_func)();
    }
    // Para isso precisamos saber quantas casas de PC andar a cada função (Fazer isso dentro da própria função)

    // ( não precisa, vai desempilhar e basta colocar ) Colocar invoker_frame dentro das funções de invoke, para sinalizar para quem deve atribuir os return.

    // ( dentro do proprio return, desempilhar ) Pensar em como faremos para o return cancelar o frame atual e cancelar essa função.
}

//! Essa função representa a função ConstructTable da JVM
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
    this->instruction_table[0x5a] = &Interpreter::i_dup_x1;
    this->instruction_table[0x5b] = &Interpreter::i_dup_x2;
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
//! Essa função representa a função nop da JVM
void Interpreter::i_nop(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    topFrame->pc += 1;
}
//! Essa função representa a função aconst_null da JVM
void Interpreter::i_aconst_null(){    
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = OBJECT_VALUE;
    value.data.object_value = nullptr;

    topFrame->AddOperandStack(value);
    topFrame->pc += 1;
}
//! Essa função representa a função iconst_m1 da JVM
void Interpreter::i_iconst_m1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = -1;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função iconst_0 da JVM
void Interpreter::i_iconst_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 0;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função iconst_1 da JVM
void Interpreter::i_iconst_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 1;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função iconst_2 da JVM
void Interpreter::i_iconst_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 2;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função iconst_3 da JVM
void Interpreter::i_iconst_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 3;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função iconst_4 da JVM
void Interpreter::i_iconst_4(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 4;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função iconst_5 da JVM
void Interpreter::i_iconst_5(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    // value.printType = INT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = 5;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função lconst_0 da JVM
void Interpreter::i_lconst_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    // Value padding;
    // padding.type = PADDING_VALUE;

    Value value;
    value.type = LONG_VALUE;
    value.data.long_value = 0;

    // topFrame->PushOperandStack(padding);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função lconst_1 da JVM
void Interpreter::i_lconst_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    // Value padding;
    // padding.type = PADDING_VALUE;

    Value value;
    value.type = LONG_VALUE;
    value.data.long_value = 1;

    // topFrame->PushOperandStack(padding);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função fconst_0 da JVM
void Interpreter::i_fconst_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = FLOAT_VALUE;
    value.data.float_value = 0;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função fconst_1 da JVM
void Interpreter::i_fconst_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = FLOAT_VALUE;
    value.data.float_value = 1;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função fconst_2 da JVM
void Interpreter::i_fconst_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = FLOAT_VALUE;
    value.data.float_value = 2;

    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função dconst_0 da JVM
void Interpreter::i_dconst_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    // Value padding;
    // padding.type = PADDING_VALUE;

    Value value;
    value.type = DOUBLE_VALUE;
    value.data.double_value = 0;

    // topFrame->PushOperandStack(padding);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função dconst_1 da JVM
void Interpreter::i_dconst_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    // Value padding;
    // padding.type = PADDING_VALUE;

    Value value;
    value.type = DOUBLE_VALUE;
    value.data.double_value = 1;

    // topFrame->PushOperandStack(padding);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função bipush da JVM
void Interpreter::i_bipush(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    u1 byte = topFrame->code.code[topFrame->pc+1];

    Value value;
    // value.printType = BYTE_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = (int32_t) (int8_t) byte; // convertendo para inteiro e estendendo o sinal

    topFrame->AddOperandStack(value);

    topFrame->pc += 2;
}
//! Essa função representa a função sipush da JVM
void Interpreter::i_sipush(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t short_value = (byte1 << 8) | byte2;
    Value value;
    // value.printType = SHORT_VALUE;
    value.type = INT_VALUE;
    value.data.int_value = (int32_t) (int16_t) short_value; // convertendo para inteiro e estendendo o sinal

    topFrame->AddOperandStack(value);

    topFrame->pc += 3;
}
//! Essa função representa a função ldc da JVM
void Interpreter::i_ldc(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    u1 index = topFrame->code.code[topFrame->pc+1];
    
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
        
        value.type = STRING_VALUE;
        value.data.string_value = new string(utf8_string);
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
//! Essa função representa a função ldc_w da JVM
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
        
        value.type = STRING_VALUE;
        value.data.string_value = new string(utf8_string);
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
//! Essa função representa a função ldc2_w da JVM
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
        // padding.type = PADDING_VALUE;
        
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
        // padding.type = PADDING_VALUE;
        
        // topFrame->PushOperandStack(padding);
    } else {
        cerr << "ldc2_w tentando acessar um elemento da CP invalido: " << entry->tag << endl;
        exit(1);
    }
    
    topFrame->AddOperandStack(value);
    topFrame->pc += 3;
}
//! Essa função representa a função iload da JVM
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
//! Essa função representa a função lload da JVM
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
	// padding.type = PADDING_VALUE;

	// topFrame->pushIntoOperandStack(padding);
	topFrame->AddOperandStack(value);
}
//! Essa função representa a função fload da JVM
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
//! Essa função representa a função dload da JVM
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
	// padding.type = PADDING_VALUE;

	// topFrame->pushIntoOperandStack(padding);
	topFrame->AddOperandStack(value);
}
//! Essa função representa a função aload da JVM
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
//! Essa função representa a função iload_0 da JVM
void Interpreter::i_iload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(0);
    // assert(value.type == ValueType::INT);

    topFrame->AddOperandStack(value);


    topFrame->pc += 1;
}
//! Essa função representa a função iload_1 da JVM
void Interpreter::i_iload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(1);
    // assert(value.type == ValueType::INT);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função iload_2 da JVM
void Interpreter::i_iload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(2);
    // assert(value.type == ValueType::INT);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função iload_3 da JVM
void Interpreter::i_iload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(3);
    // assert(value.type == ValueType::INT);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função lload_0 da JVM
void Interpreter::i_lload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(1);
    // assert(value.type == PADDING_VALUE);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(0);
    // assert(value.type == LONG_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função lload_1 da JVM
void Interpreter::i_lload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(2);
    // assert(value.type == PADDING_VALUE);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(1);
    // assert(value.type == LONG_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função lload_2 da JVM
void Interpreter::i_lload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(3);
    // assert(value.type == PADDING_VALUE);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(2);
    // assert(value.type == LONG_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função lload_3 da JVM
void Interpreter::i_lload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(4);
    // assert(value.type == PADDING_VALUE);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(3);
    // assert(value.type == LONG_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função fload_0 da JVM
void Interpreter::i_fload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(0);
    // assert(value.type == FLOAT_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função fload_1 da JVM
void Interpreter::i_fload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(1);
    // assert(value.type == FLOAT_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função fload_2 da JVM
void Interpreter::i_fload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(2);
    // assert(value.type == FLOAT_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função fload_3 da JVM
void Interpreter::i_fload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(3);
    // assert(value.type == FLOAT_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função dload_0 da JVM
void Interpreter::i_dload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(1);
    // assert(value.type == PADDING_VALUE);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(0);
    // assert(value.type == DOUBLE_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função dload_1 da JVM
void Interpreter::i_dload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(2);
    // assert(value.type == PADDING_VALUE);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(1);
    // assert(value.type == DOUBLE_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função dload_2 da JVM
void Interpreter::i_dload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(3);
    // assert(value.type == PADDING_VALUE);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(2);
    // assert(value.type == DOUBLE_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função dload_3 da JVM
void Interpreter::i_dload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value;

    value = topFrame->GetLocalVariable(4);
    // assert(value.type == PADDING_VALUE);
    topFrame->AddOperandStack(value);

    value = topFrame->GetLocalVariable(3);
    // assert(value.type == DOUBLE_VALUE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função aload_0 da JVM
void Interpreter::i_aload_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(0);
    // assert(value.type == ValueType::REFERENCE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função aload_1 da JVM
void Interpreter::i_aload_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(1);
    // assert(value.type == ValueType::REFERENCE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função aload_2 da JVM
void Interpreter::i_aload_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(2);
    // assert(value.type == ValueType::REFERENCE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função aload_3 da JVM
void Interpreter::i_aload_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->GetLocalVariable(3);
    // assert(value.type == ValueType::REFERENCE);
    topFrame->AddOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função iaload da JVM
void Interpreter::i_iaload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	vector<Value> *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    topFrame->AddOperandStack(array->at(index.data.int_value));
    topFrame->pc += 1;
}
//! Essa função representa a função laload da JVM
void Interpreter::i_laload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	vector<Value> *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    Value padding;
    padding.type = PADDING_VALUE;
    
    topFrame->AddOperandStack(padding);
    topFrame->AddOperandStack(array->at(index.data.int_value));
    topFrame->pc += 1;
}
//! Essa função representa a função faload da JVM
void Interpreter::i_faload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    topFrame->AddOperandStack(array->at(index.data.int_value));
    topFrame->pc += 1;
}
//! Essa função representa a função daload da JVM
void Interpreter::i_daload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    Value padding;
    padding.type = PADDING_VALUE;
    
    topFrame->AddOperandStack(padding);
    topFrame->AddOperandStack(array->at(index.data.int_value));
    topFrame->pc += 1;
}
//! Essa função representa a função aaload da JVM
void Interpreter::i_aaload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    topFrame->AddOperandStack(array->at(index.data.int_value));
    topFrame->pc += 1;
}
//! Essa função representa a função baload da JVM
void Interpreter::i_baload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    Value value = array->at(index.data.int_value);
    // assert(value.type == BYTE_VALUE || value.type == BYTE_VALUE);
    
    if (value.type == BYTE_VALUE) {
        value.data.int_value = (uint32_t) value.data.boolean_value;
        value.printType = BYTE_VALUE;
    } else {
        value.data.int_value = (int32_t) value.data.byte_value;
        value.printType = BYTE_VALUE;
    }
    value.type = INT_VALUE;

    topFrame->AddOperandStack(value);
    topFrame->pc += 1;
}
//! Essa função representa a função caload da JVM
void Interpreter::i_caload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    Value char_value = array->at(index.data.int_value);
    char_value.data.int_value = (uint32_t) char_value.data.char_value;
    char_value.printType = CHAR_VALUE;
    char_value.type = INT_VALUE;
    
    topFrame->AddOperandStack(char_value);
    topFrame->pc += 1;
}
//! Essa função representa a função saload da JVM
void Interpreter::i_saload(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    
    Value short_value = array->at(index.data.int_value);
    short_value.data.int_value = (int32_t) short_value.data.short_value;
    // short_value.printType = SHORT_VALUE;
    short_value.type = INT_VALUE;
    
    topFrame->AddOperandStack(short_value);
    topFrame->pc += 1;
}
//! Essa função representa a função istore da JVM
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
//! Essa função representa a função lstore da JVM
void Interpreter::i_lstore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value = topFrame->PopOperandStack();
	// assert(value.type == LONG_VALUE);
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

	Value padding;
	padding.type = PADDING_VALUE;
	topFrame->ChangeLocalVariable(index + 1, padding);
}
//! Essa função representa a função fstore da JVM
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
//! Essa função representa a função dstore da JVM
void Interpreter::i_dstore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value = topFrame->PopOperandStack();
	// assert(value.type == DOUBLE_VALUE);
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
	Value padding;
	padding.type = PADDING_VALUE;
	topFrame->ChangeLocalVariable(index + 1, padding);
}
//! Essa função representa a função astore da JVM
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
//! Essa função representa a função istore_0 da JVM
void Interpreter::i_istore_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::INT);
    topFrame->ChangeLocalVariable(0, value);

    topFrame->pc += 1;
}
//! Essa função representa a função istore_1 da JVM
void Interpreter::i_istore_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::INT);
    topFrame->ChangeLocalVariable(1, value);

    topFrame->pc += 1;
}
//! Essa função representa a função istore_2 da JVM
void Interpreter::i_istore_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::INT);
    topFrame->ChangeLocalVariable(2, value);

    topFrame->pc += 1;
}
//! Essa função representa a função istore_3 da JVM
void Interpreter::i_istore_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::INT);
    topFrame->ChangeLocalVariable(3, value);

    topFrame->pc += 1;
}
//! Essa função representa a função lstore_0 da JVM
void Interpreter::i_lstore_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == LONG_VALUE);
    topFrame->ChangeLocalVariable(0, value);

    value = topFrame->PopOperandStack();
    // assert(value.type == PADDING_VALUE);
    topFrame->ChangeLocalVariable(1, value);

    topFrame->pc += 1;
}
//! Essa função representa a função lstore_1 da JVM
void Interpreter::i_lstore_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == LONG_VALUE);
    topFrame->ChangeLocalVariable(1, value);

    value = topFrame->PopOperandStack();
    // assert(value.type == PADDING_VALUE);
    topFrame->ChangeLocalVariable(2, value);

    topFrame->pc += 1;
}
//! Essa função representa a função lstore_2 da JVM
void Interpreter::i_lstore_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == LONG_VALUE);
    topFrame->ChangeLocalVariable(2, value);

    value = topFrame->PopOperandStack();
    // assert(value.type == PADDING_VALUE);
    topFrame->ChangeLocalVariable(3, value);

    topFrame->pc += 1;
}
//! Essa função representa a função lstore_3 da JVM
void Interpreter::i_lstore_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == LONG_VALUE);
    topFrame->ChangeLocalVariable(3, value);

    value = topFrame->PopOperandStack();
    // assert(value.type == PADDING_VALUE);
    topFrame->ChangeLocalVariable(4, value);

    topFrame->pc += 1;
}
//! Essa função representa a função fstore_0 da JVM
void Interpreter::i_fstore_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::FLOAT);
    topFrame->ChangeLocalVariable(0, value);

    topFrame->pc += 1;
}
//! Essa função representa a função fstore_1 da JVM
void Interpreter::i_fstore_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::FLOAT);
    topFrame->ChangeLocalVariable(1, value);

    topFrame->pc += 1;
}
//! Essa função representa a função fstore_2 da JVM
void Interpreter::i_fstore_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::FLOAT);
    topFrame->ChangeLocalVariable(2, value);

    topFrame->pc += 1;
}
//! Essa função representa a função fstore_3 da JVM
void Interpreter::i_fstore_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::FLOAT);
    topFrame->ChangeLocalVariable(4, value);

    topFrame->pc += 1;
}
//! Essa função representa a função dstore_0 da JVM
void Interpreter::i_dstore_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == DOUBLE_VALUE);
    topFrame->ChangeLocalVariable(0, value);

    value = topFrame->PopOperandStack();
    // assert(value.type == PADDING_VALUE);
    topFrame->ChangeLocalVariable(1, value);

    topFrame->pc += 1;
}
//! Essa função representa a função dstore_1 da JVM
void Interpreter::i_dstore_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == DOUBLE_VALUE);
    topFrame->ChangeLocalVariable(1, value);

    value = topFrame->PopOperandStack();
    // assert(value.type == PADDING_VALUE);
    topFrame->ChangeLocalVariable(2, value);

    topFrame->pc += 1;
}
//! Essa função representa a função dstore_2 da JVM
void Interpreter::i_dstore_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == DOUBLE_VALUE);
    topFrame->ChangeLocalVariable(2, value);

    value = topFrame->PopOperandStack();
    // assert(value.type == PADDING_VALUE);
    topFrame->ChangeLocalVariable(3, value);

    topFrame->pc += 1;
}
//! Essa função representa a função dstore_3 da JVM
void Interpreter::i_dstore_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == DOUBLE_VALUE);
    topFrame->ChangeLocalVariable(3, value);

    value = topFrame->PopOperandStack();
    // assert(value.type == PADDING_VALUE);
    topFrame->ChangeLocalVariable(4, value);

    topFrame->pc += 1;
}
//! Essa função representa a função astore_0 da JVM
void Interpreter::i_astore_0(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::REFERENCE);
    topFrame->ChangeLocalVariable(0, value);

    topFrame->pc += 1;
}
//! Essa função representa a função astore_1 da JVM
void Interpreter::i_astore_1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::REFERENCE);

    topFrame->ChangeLocalVariable(1, value);

    topFrame->pc += 1;
}
//! Essa função representa a função astore_2 da JVM
void Interpreter::i_astore_2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::REFERENCE);
    topFrame->ChangeLocalVariable(2, value);

    topFrame->pc += 1;
}
//! Essa função representa a função astore_3 da JVM
void Interpreter::i_astore_3(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::REFERENCE);
    topFrame->ChangeLocalVariable(3, value);

    topFrame->pc += 1;
}
//! Essa função representa a função iastore da JVM
void Interpreter::i_iastore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::INT);
    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    // value.printType = INT_VALUE;
    
    // assert(value.type == array->arrayContentType());
    array->at(index.data.int_value) = value;
    
    topFrame->pc += 1;
}
//! Essa função representa a função lastore da JVM
void Interpreter::i_lastore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value value = topFrame->PopOperandStack();
    // assert(value.type == LONG_VALUE);
    Value padding = topFrame->PopOperandStack();
    // assert(padding.type == PADDING_VALUE);
    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    // assert(value.type == array->arrayContentType());
    array->at(index.data.int_value) = value;

    topFrame->pc += 1;
}
//! Essa função representa a função fastore da JVM
void Interpreter::i_fastore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::FLOAT);
    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    // assert(value.type == array->arrayContentType());
    array->at(index.data.int_value) = value;
	
    topFrame->pc += 1;
}
//! Essa função representa a função dastore da JVM
void Interpreter::i_dastore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value value = topFrame->PopOperandStack();
    // assert(value.type == DOUBLE_VALUE);
    Value padding = topFrame->PopOperandStack();
    // assert(padding.type == PADDING_VALUE);
    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object_value)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    // assert(value.type == array->arrayContentType());
    array->at(index.data.int_value) = value;
	
    topFrame->pc += 1;
}
//! Essa função representa a função aastore da JVM
void Interpreter::i_aastore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

	Value value = topFrame->PopOperandStack(); // Valor armazenado no index do array
	// assert(value.type == ValueType::REFERENCE);
    Value index = topFrame->PopOperandStack(); // Index do arary
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack(); // Referência ao array
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value >= array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

	array->at(index.data.int_value) = value;
    
    topFrame->pc += 1;
}
//! Essa função representa a função bastore da JVM
void Interpreter::i_bastore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::INT);
    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;
    // assert(array->arrayContentType() == BYTE_VALUE || array->arrayContentType() == BYTE_VALUE);

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    for(unsigned i = 0; i < array->size(); i++){
        if (array->at(i).type == BYTE_VALUE) {
            value.data.boolean_value = (value.data.int_value != 0) ? true : false;
            value.type = BYTE_VALUE;
            // value.printType = BYTE_VALUE;
        } else {
            value.data.byte_value = (uint8_t) value.data.int_value;
            value.type = BYTE_VALUE;
            // value.printType = BYTE_VALUE;
        }
    }
    
    array->at(index.data.int_value) = value;
	
    topFrame->pc += 1;
}
//! Essa função representa a função castore da JVM
void Interpreter::i_castore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::INT);
    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    value.data.char_value = (uint8_t) value.data.int_value;
    // value.printType = ValueType::CHAR;
    value.type = CHAR_VALUE;
    array->at(index.data.int_value) = value;
	
    topFrame->pc += 1;
}
//! Essa função representa a função sastore da JVM
void Interpreter::i_sastore(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
	
    vector<Value> *array;

    Value value = topFrame->PopOperandStack();
    // assert(value.type == ValueType::INT);
    Value index = topFrame->PopOperandStack();
    // assert(index.type == ValueType::INT);
    Value arrayref = topFrame->PopOperandStack();
    // assert(arrayref.type == ValueType::REFERENCE);
    // assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = arrayref.data.array_value;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.int_value > array->size() || index.data.int_value < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    value.data.short_value = (int16_t) value.data.int_value;
    // value.printType = ValueType::SHORT;
    value.type = SHORT_VALUE;
    array->at(index.data.int_value) = value;
	
    topFrame->pc += 1;
}
//! Essa função representa a função pop da JVM
void Interpreter::i_pop(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    Value value = topFrame->PopOperandStack();
    // assert(value.type != LONG_VALUE);
    // assert(value.type != DOUBLE_VALUE);

    topFrame->pc += 1;
}
//! Essa função representa a função pop2 da JVM
void Interpreter::i_pop2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();
    topFrame->PopOperandStack();
    topFrame->PopOperandStack();

    topFrame->pc += 1;
}
//! Essa função representa a função dup da JVM
void Interpreter::i_dup(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value = topFrame->PopOperandStack();
    // assert(value.type != LONG_VALUE);
    // assert(value.type != DOUBLE_VALUE);

    topFrame->PushOperandStack(value);
    topFrame->PushOperandStack(value);

    topFrame->pc += 1;
}
//! Essa função representa a função dup_x1 da JVM
void Interpreter::i_dup_x1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    // assert(value_1.type != LONG_VALUE);
    // assert(value_1.type != DOUBLE_VALUE);
    Value value_2 = topFrame->PopOperandStack();
    // assert(value_2.type != LONG_VALUE);
    // assert(value_2.type != DOUBLE_VALUE);

    topFrame->PushOperandStack(value_1);
    topFrame->PushOperandStack(value_2);
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}
//! Essa função representa a função dup_x2 da JVM
void Interpreter::i_dup_x2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    Value value_2 = topFrame->PopOperandStack();
    Value value_3 = topFrame->PopOperandStack();

    // assert(value_1.type != LONG_VALUE);
    // assert(value_1.type != DOUBLE_VALUE);
    // assert(value_3.type != LONG_VALUE);
    // assert(value_3.type != DOUBLE_VALUE);

    topFrame->PushOperandStack(value_1);
    topFrame->PushOperandStack(value_3);
    topFrame->PushOperandStack(value_2);
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}
//! Essa função representa a função dup2 da JVM
void Interpreter::i_dup2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    Value value_2 = topFrame->PopOperandStack();
    // assert(value_2.type != LONG_VALUE);
    // assert(value_2.type != DOUBLE_VALUE);

    topFrame->PushOperandStack(value_2);
    topFrame->PushOperandStack(value_1);
    topFrame->PushOperandStack(value_2);
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}
//! Essa função representa a função dup2_x1 da JVM
void Interpreter::i_dup2_x1(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    Value value_2 = topFrame->PopOperandStack();
    Value value_3 = topFrame->PopOperandStack();

    // assert(value_2.type != LONG_VALUE);
    // assert(value_2.type != DOUBLE_VALUE);
    // assert(value_3.type != LONG_VALUE);
    // assert(value_3.type != DOUBLE_VALUE);

    topFrame->PushOperandStack(value_2);
    topFrame->PushOperandStack(value_1);
    topFrame->PushOperandStack(value_3);
    topFrame->PushOperandStack(value_2);
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}
//! Essa função representa a função dup2_x2 da JVM
void Interpreter::i_dup2_x2(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    Value value_2 = topFrame->PopOperandStack();
    Value value_3 = topFrame->PopOperandStack();
    Value value_4 = topFrame->PopOperandStack();

    // assert(value_2.type != LONG_VALUE);
    // assert(value_2.type != DOUBLE_VALUE);
    // assert(value_4.type != LONG_VALUE);
    // assert(value_4.type != DOUBLE_VALUE);

    topFrame->PushOperandStack(value_2);
    topFrame->PushOperandStack(value_1);
    topFrame->PushOperandStack(value_4);
    topFrame->PushOperandStack(value_3);
    topFrame->PushOperandStack(value_2);
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}
//! Essa função representa a função swap da JVM
void Interpreter::i_swap(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    Value value_2 = topFrame->PopOperandStack();

    // assert(value_1.type != LONG_VALUE);
    // assert(value_1.type != DOUBLE_VALUE);
    // assert(value_2.type != LONG_VALUE);
    // assert(value_2.type != DOUBLE_VALUE);

    topFrame->PushOperandStack(value_1);
    topFrame->PushOperandStack(value_2);

    topFrame->pc += 1;
}
//! Essa função representa a função iadd da JVM
void Interpreter::i_iadd(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == ValueType::INT);
	// assert(value_1.type == ValueType::INT);

	value_1.data.int_value = value_1.data.int_value + (value_2.data.int_value);
    // value_1.printType = ValueType::INT;

    // cout << "Resultado: " << value_1.data.int_value << endl;
    
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função ladd da JVM
void Interpreter::i_ladd(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); //padding
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);

	value_1.data.long_value = value_1.data.long_value + (value_2.data.long_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função fadd da JVM
void Interpreter::i_fadd(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == ValueType::FLOAT);
	// assert(value_1.type == ValueType::FLOAT);

	value_1.data.float_value = value_1.data.float_value + (value_2.data.float_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função dadd da JVM
void Interpreter::i_dadd(){
    Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == DOUBLE_VALUE);
	// assert(value_1.type == DOUBLE_VALUE);

	value_1.data.double_value = value_1.data.double_value + (value_2.data.double_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//  ALEXANDRE FAZENDO ATE AQUIIIIIIIIIIIIIIIIIIIIIIIII 

//###################################################################################################################################
//###################################################################################################################################

//! Essa função representa a função isub da JVM
void Interpreter::i_isub(){
   
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
    
	value_1.data.int_value = value_1.data.int_value - (value_2.data.int_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;

}
//! Essa função representa a função lsub da JVM
void Interpreter::i_lsub(){
    
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);

	value_1.data.long_value = value_1.data.long_value - (value_2.data.long_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função fsub da JVM
void Interpreter::i_fsub(){
    
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == FLOAT_VALUE);
	// assert(value_1.type == FLOAT_VALUE);

	value_1.data.float_value = value_1.data.float_value - (value_2.data.float_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função dsub da JVM
void Interpreter::i_dsub(){
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == DOUBLE_VALUE);
	// assert(value_1.type == DOUBLE_VALUE);

	value_1.data.double_value = value_1.data.double_value - (value_2.data.double_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função imul da JVM
void Interpreter::i_imul(){
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
    
	value_1.data.int_value = value_1.data.int_value * (value_2.data.int_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função lmul da JVM
void Interpreter::i_lmul(){
    
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == LONG_VALUE);
	// assert(value_1.type == LONG_VALUE);

	value_1.data.long_value = value_1.data.long_value * (value_2.data.long_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função fmul da JVM
void Interpreter::i_fmul() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == FLOAT_VALUE);
	// assert(value_1.type == FLOAT_VALUE);

	value_1.data.float_value = value_1.data.float_value * (value_2.data.float_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função dmul da JVM
void Interpreter::i_dmul() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == DOUBLE_VALUE);
	// assert(value_1.type == DOUBLE_VALUE);

	value_1.data.double_value = value_1.data.double_value * (value_2.data.double_value);
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função idiv da JVM
void Interpreter::i_idiv() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função ldiv da JVM
void Interpreter::i_ldiv() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função fdiv da JVM
void Interpreter::i_fdiv() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função ddiv da JVM
void Interpreter::i_ddiv() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função irem da JVM
void Interpreter::i_irem() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função lrem da JVM
void Interpreter::i_lrem() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função frem da JVM
void Interpreter::i_frem() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função drem da JVM
void Interpreter::i_drem() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função ineg da JVM
void Interpreter::i_ineg() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    // assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.data.int_value = -value_1.data.int_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}
//! Essa função representa a função lneg da JVM
void Interpreter::i_lneg() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

	// Não precisa tirar o padding
    Value value_1 = topFrame->PopOperandStack();
    // assert(value_1.type == LONG_VALUE);

	value_1.data.long_value = -value_1.data.long_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}
//! Essa função representa a função fneg da JVM
void Interpreter::i_fneg() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

    Value value_1 = topFrame->PopOperandStack();
    // assert(value_1.type == FLOAT_VALUE);

	value_1.data.float_value = -value_1.data.float_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}
//! Essa função representa a função dneg da JVM
void Interpreter::i_dneg() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

	// Não precisa tirar o padding
    Value value_1 = topFrame->PopOperandStack();
    // assert(value_1.type == DOUBLE_VALUE);

	value_1.data.double_value = -value_1.data.double_value;
    topFrame->PushOperandStack(value_1);

    topFrame->pc += 1;
}
//! Essa função representa a função ishl da JVM
void Interpreter::i_ishl() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função lshl da JVM
void Interpreter::i_lshl() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função ishr da JVM
void Interpreter::i_ishr() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função lshr da JVM
void Interpreter::i_lshr() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função iushr da JVM
void Interpreter::i_iushr() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função lushr da JVM
void Interpreter::i_lushr() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função iand da JVM
void Interpreter::i_iand() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.data.int_value = value_1.data.int_value & value_2.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função land da JVM
void Interpreter::i_land() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função ior da JVM
void Interpreter::i_ior() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.data.int_value = value_1.data.int_value | value_2.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função lor da JVM
void Interpreter::i_lor() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função ixor da JVM
void Interpreter::i_ixor() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();

	// assert(value_2.type == INT_VALUE);
	// assert(value_1.type == INT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.data.int_value = value_1.data.int_value ^ value_2.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função lxor da JVM
void Interpreter::i_lxor() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

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
//! Essa função representa a função iinc da JVM
void Interpreter::i_iinc() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    u2 index = 0;
    if (wide) {
        index = (topFrame->code.code[topFrame->pc+1] << 8) | topFrame->code.code[topFrame->pc+2];
    } else {
        index += topFrame->code.code[topFrame->pc+1];
    }
    
    Value localVariable = topFrame->GetLocalVariable(index);
    // assert(localVariable.type == INT_VALUE);
    
    int32_t inc;
    if (wide) {
        uint16_t constant = (topFrame->code.code[topFrame->pc+3] << 8) | topFrame->code.code[topFrame->pc+4];
        inc = (int32_t) (int16_t) constant;
    } else {
        inc = (int32_t) (int8_t) topFrame->code.code[topFrame->pc+2];
    }
    
    localVariable.data.int_value += inc;
    topFrame->ChangeLocalVariable(index, localVariable);
    
    topFrame->pc += wide ? 5 : 3;
    wide = false;
}
//! Essa função representa a função i2l da JVM
void Interpreter::i_i2l() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

	Value padding;
	padding.type = PADDING_VALUE;

	topFrame->PushOperandStack(padding);

    value_1.data.long_value = (int64_t) value_1.data.int_value;
	value_1.type = LONG_VALUE;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função i2f da JVM
void Interpreter::i_i2f() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

	value_1.type = FLOAT_VALUE;
	value_1.data.float_value = (float) value_1.data.int_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função i2d da JVM
void Interpreter::i_i2d() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

	Value padding;
	padding.type = PADDING_VALUE;
	topFrame->PushOperandStack(padding);

	value_1.type = DOUBLE_VALUE;
	value_1.data.double_value = (double) value_1.data.int_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função l2i da JVM
void Interpreter::i_l2i() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); //padding

	// assert(value_1.type == LONG_VALUE);

    value_1.data.int_value = (int32_t) value_1.data.int_value;
    // value_1.printType = INT_VALUE;
	value_1.type = INT_VALUE;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função l2f da JVM
void Interpreter::i_l2f() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); //padding

	// assert(value_1.type == LONG_VALUE);

	value_1.type = FLOAT_VALUE;
	value_1.data.float_value = (float) value_1.data.long_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função l2d da JVM
void Interpreter::i_l2d() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	//manter padding na pilha de operandos

	// assert(value_1.type == LONG_VALUE);

	value_1.type = DOUBLE_VALUE;
	value_1.data.double_value = (double) value_1.data.long_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função f2i da JVM
void Interpreter::i_f2i() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == FLOAT_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.type = INT_VALUE;
	value_1.data.int_value = (int32_t) value_1.data.float_value;

	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função f2l da JVM
void Interpreter::i_f2l() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == FLOAT_VALUE);

	Value padding;
	padding.type = PADDING_VALUE;
	topFrame->PushOperandStack(padding);

	value_1.type = LONG_VALUE;
	value_1.data.long_value = (uint64_t) value_1.data.float_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função f2d da JVM
void Interpreter::i_f2d() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == FLOAT_VALUE);

	Value padding;
	padding.type = PADDING_VALUE;
	topFrame->PushOperandStack(padding);

	value_1.type = DOUBLE_VALUE;
	value_1.data.double_value = (double) value_1.data.float_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função d2i da JVM
void Interpreter::i_d2i() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); //padding

	// assert(value_1.type == DOUBLE_VALUE);

    // value_1.printType = INT_VALUE;
	value_1.type = INT_VALUE;
	value_1.data.int_value = (int32_t) value_1.data.double_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função d2l da JVM
void Interpreter::i_d2l() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	//manter padding na pilha de operandos

	// assert(value_1.type == DOUBLE_VALUE);

	value_1.type = LONG_VALUE;
	value_1.data.long_value = (int64_t) value_1.data.double_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função d2f da JVM
void Interpreter::i_d2f() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack(); //padding

	// assert(value_1.type == DOUBLE_VALUE);

	value_1.type = FLOAT_VALUE;
	value_1.data.float_value = (float) value_1.data.double_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função i2b da JVM
void Interpreter::i_i2b() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);
    
    // value_1.printType = BYTE_VALUE;
    
    value_1.data.int_value = (int32_t) (int8_t) value_1.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função i2c da JVM
void Interpreter::i_i2c() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

    // value_1.printType = CHAR_VALUE;
    
    value_1.data.char_value = (uint32_t) (uint8_t) value_1.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função i2s da JVM
void Interpreter::i_i2s() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_1 = topFrame->PopOperandStack();

	// assert(value_1.type == INT_VALUE);

    // value_1.printType = SHORT_VALUE;
    
    value_1.data.int_value = (int32_t) (int16_t) value_1.data.int_value;
	topFrame->PushOperandStack(value_1);

	topFrame->pc += 1;
}
//! Essa função representa a função lcmp da JVM
void Interpreter::i_lcmp() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value resultado;
    // resultado.printType = INT_VALUE;
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
//! Essa função representa a função fcmpl da JVM
void Interpreter::i_fcmpl() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	Value resultado;
    // resultado.printType = INT_VALUE;
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
//! Essa função representa a função fcmpg da JVM
void Interpreter::i_fcmpg() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	Value resultado;
    // resultado.printType = INT_VALUE;
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
//! Essa função representa a função dcmpl da JVM
void Interpreter::i_dcmpl() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value resultado;
    // resultado.printType = INT_VALUE;
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
//! Essa função representa a função dcmpg da JVM
void Interpreter::i_dcmpg() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value_2 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value value_1 = topFrame->PopOperandStack();
	topFrame->PopOperandStack();
	Value resultado;
    // resultado.printType = INT_VALUE;
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
//! Essa função representa a função ifeq da JVM
void Interpreter::i_ifeq() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
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
//! Essa função representa a função ifne da JVM
void Interpreter::i_ifne() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função iflt da JVM
void Interpreter::i_iflt() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função ifge da JVM
void Interpreter::i_ifge() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função ifgt da JVM
void Interpreter::i_ifgt() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função ifle da JVM
void Interpreter::i_ifle() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função if_icmpeq da JVM
void Interpreter::i_if_icmpeq() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função if_icmpne da JVM
void Interpreter::i_if_icmpne() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função if_icmplt da JVM
void Interpreter::i_if_icmplt() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função if_icmpge da JVM
void Interpreter::i_if_icmpge() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == INT_VALUE);
	// assert(value2.type == INT_VALUE);
	
	if (value1.data.int_value >= value2.data.int_value) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		
		u1 byte2 = topFrame->code.code[topFrame->pc+2];

		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}
//! Essa função representa a função if_icmpgt da JVM
void Interpreter::i_if_icmpgt() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função if_icmple da JVM
void Interpreter::i_if_icmple() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
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
//! Essa função representa a função if_acmpeq da JVM
void Interpreter::i_if_acmpeq() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == ValueType::REFERENCE);
	// assert(value2.type == ValueType::REFERENCE);
	
	if (value1.data.object_value == value2.data.object_value) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}
//! Essa função representa a função if_acmpne da JVM
void Interpreter::i_if_acmpne() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	Value value2 = topFrame->PopOperandStack();
	Value value1 = topFrame->PopOperandStack();
	// assert(value1.type == ValueType::REFERENCE);
	// assert(value2.type == ValueType::REFERENCE);

	if (value1.data.object_value != value2.data.object_value) {
		
		u1 byte1 = topFrame->code.code[topFrame->pc+1];
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}
//! Essa função representa a função goto da JVM
void Interpreter::i_goto() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
	
	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	u1 byte2 = topFrame->code.code[topFrame->pc+2];
	int16_t branchOffset = (byte1 << 8) | byte2;
	topFrame->pc += branchOffset;
}
//! Essa função representa a função jsr da JVM
void Interpreter::i_jsr() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();
	
	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	u1 byte2 = topFrame->code.code[topFrame->pc+2];
	int16_t branchOffset = (byte1 << 8) | byte2;
	
	Value value;
	value.type = RETURN_VALUE;
	value.data.return_address = topFrame->pc + 3; 
	topFrame->PushOperandStack(value);
	
	topFrame->pc += branchOffset;
}

// Pode ser modifica//! Essa função representa a função ret da JVMdo pelo wide
void Interpreter::i_ret() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	
	u1 byte1 = topFrame->code.code[topFrame->pc+1]; // índice do vetor de variáveis locais
	uint16_t index = (uint16_t) byte1;

	if (wide) {
		u1 byte2 = topFrame->code.code[topFrame->pc+2];
		index = (byte1 << 8) | byte2;
	}

	// assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->GetLocalVariable(index);

	// assert(value.type == ValueType::RETURN_ADDR);
	topFrame->ChangeLocalVariable(index, value);

	topFrame->pc = value.data.return_address;
	wide = false;
}
//! Essa função representa a função tableswitch da JVM
void Interpreter::i_tableswitch() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    u1 padding = 4 - (topFrame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;
    
    u1 default_byte1 = topFrame->code.code[topFrame->pc + padding + 1];
    u1 default_byte2 = topFrame->code.code[topFrame->pc + padding + 2];
    u1 default_byte3 = topFrame->code.code[topFrame->pc + padding + 3];
    u1 default_byte4 = topFrame->code.code[topFrame->pc + padding + 4];
    int32_t default_bytes = (default_byte1 << 24) | (default_byte2 << 16) | (default_byte3 << 8) | default_byte4;
    
    u1 lowbyte1 = topFrame->code.code[topFrame->pc + padding + 5];
    u1 lowbyte2 = topFrame->code.code[topFrame->pc + padding + 6];
    u1 lowbyte3 = topFrame->code.code[topFrame->pc + padding + 7];
    u1 lowbyte4 = topFrame->code.code[topFrame->pc + padding + 8];
    uint32_t lowbytes = (lowbyte1 << 24) | (lowbyte2 << 16) | (lowbyte3 << 8) | lowbyte4;
    
    u1 highbyte1 = topFrame->code.code[topFrame->pc + padding + 9];
    u1 highbyte2 = topFrame->code.code[topFrame->pc + padding + 10];
    u1 highbyte3 = topFrame->code.code[topFrame->pc + padding + 11];
    u1 highbyte4 = topFrame->code.code[topFrame->pc + padding + 12];
    uint32_t highbytes = (highbyte1 << 24) | (highbyte2 << 16) | (highbyte3 << 8) | highbyte4;
    
    Value key_value = topFrame->PopOperandStack();
    // assert(key_value.type == INT_VALUE);
    int32_t key = key_value.data.int_value;
    
    uint32_t i;
    uint32_t baseIndex = padding + 13;
    int32_t offsets = highbytes - lowbytes + 1;
    bool matched = false;
    for (i = 0; i < offsets; i++) {
        if (key == lowbytes) {
            int32_t offset = (topFrame->code.code[topFrame->pc + baseIndex] << 24) | (topFrame->code.code[topFrame->pc + baseIndex+1] << 16) | (topFrame->code.code[topFrame->pc + baseIndex+2] << 8) | topFrame->code.code[topFrame->pc + baseIndex+3];
            topFrame->pc += offset;
            matched = true;
            break;
        }
        lowbytes++;
        baseIndex += 4;
    }
    
    if (!matched) {
        topFrame->pc += default_bytes; // salto default
    }
}
//! Essa função representa a função lookupswitch da JVM
void Interpreter::i_lookupswitch() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    u1* code = topFrame->code.code;
    u1 padding = 4 - (topFrame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;
    
    u1 defaultbyte1 = code[topFrame->pc + padding + 1];
    u1 defaultbyte2 = code[topFrame->pc + padding + 2];
    u1 defaultbyte3 = code[topFrame->pc + padding + 3];
    u1 defaultbyte4 = code[topFrame->pc + padding + 4];
    int32_t defaultBytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;
    
    u1 npairs1 = code[topFrame->pc + padding + 5];
    u1 npairs2 = code[topFrame->pc + padding + 6];
    u1 npairs3 = code[topFrame->pc + padding + 7];
    u1 npairs4 = code[topFrame->pc + padding + 8];
    uint32_t npairs = (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;
    
    Value keyValue = topFrame->PopOperandStack();
    // assert(keyValue.type == INT_VALUE);
    int32_t key = keyValue.data.int_value;
    
    uint32_t i;
    uint32_t baseIndex = padding + 9;
    bool matched = false;
    for (i = 0; i < npairs; i++) {
        int32_t match = (code[topFrame->pc + baseIndex] << 24) | (code[topFrame->pc + baseIndex+1] << 16) | (code[topFrame->pc + baseIndex+2] << 8) | code[topFrame->pc + baseIndex+3];
        
        if (key == match) {
            int32_t offset = (code[topFrame->pc + baseIndex+4] << 24) | (code[topFrame->pc + baseIndex+5] << 16) | (code[topFrame->pc + baseIndex+6] << 8) | code[topFrame->pc + baseIndex+7];
            
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
//! Essa função representa a função ireturn da JVM
void Interpreter::i_ireturn() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == INT_VALUE);
    
    this->runtime->PopFrame();
    
    Frame *newTopFrame = this->runtime->GetCurrentFrame();

    // cout << "Resultado: " << returnValue.data.int_value << endl;

    
    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função lreturn da JVM
void Interpreter::i_lreturn() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == LONG_VALUE);
    // assert(topFrame->PopOperandStack();().type == PADDING_VALUE); // o debaixo precisa ser padding
    
    this->runtime->PopFrame();
    
    Frame *newTopFrame = this->runtime->GetCurrentFrame();
    Value padding;
    padding.type = PADDING_VALUE;
    newTopFrame->PushOperandStack(padding);
    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função freturn da JVM
void Interpreter::i_freturn() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == FLOAT_VALUE);
    
    this->runtime->PopFrame();
    
    Frame *newTopFrame = this->runtime->GetCurrentFrame();
    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função dreturn da JVM
void Interpreter::i_dreturn() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == DOUBLE_VALUE);
    // assert(topFrame->PopOperandStack();().type == PADDING_VALUE); // o debaixo precisa ser padding
    
    this->runtime->PopFrame();
    
    Frame *newTopFrame = this->runtime->GetCurrentFrame();
    
    Value padding;
    padding.type = PADDING_VALUE;
    newTopFrame->PushOperandStack(padding);
    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função areturn da JVM
void Interpreter::i_areturn() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value returnValue = topFrame->PopOperandStack();
    // assert(returnValue.type == ValueType::REFERENCE);
    
    this->runtime->PopFrame();
    
    Frame *newTopFrame = this->runtime->GetCurrentFrame();
    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função return da JVM
void Interpreter::i_return() {
    
    this->runtime->PopFrame();
}
//! Essa função representa a função getstatic da JVM
void Interpreter::i_getstatic() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    vector<CpInfo *> constantPool = (topFrame->constant_pool);
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    CpInfo* fieldCP = constantPool[fieldIndex-1];
    // assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP->info.Fieldref;

    string className = ReadFile::readString(fieldRef.class_index, constantPool);

    CpInfo* nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    // assert(nameAndTypeCP->tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP->info.NameAndType;
    
    string fieldName = ReadFile::readString(fieldNameAndType.name_index, constantPool);
    // string fieldName = fieldNameVector[0];
    string fieldDescriptor = ReadFile::readString(fieldNameAndType.descriptor_index, constantPool);

    // caso especial
    if (className == "java/lang/System" && fieldDescriptor == "Ljava/io/PrintStream;" ) {
        topFrame->pc += 3;
        return;
    }
    // fim do caso especial
    map<string, MethodAreaSection *> method_area = this->runtime->method_area;
    MethodAreaSection *area = method_area[className];

    while (area != NULL) {
        if (area->static_fields.count(fieldName) == 0) {
            if (area->class_file->super_class == 0) {
                area = NULL;
            } else {
                string superClassName = ReadFile::readString(area->class_file->super_class, area->class_file->constant_pool);
                if(method_area.count(superClassName) > 0)
                    area = method_area[superClassName];
                else{
                    ClassLoaderSubsystem::Resolve(superClassName, this->runtime);
                    area = method_area[superClassName];
                }
            }
        } else {
            break;
        }
    }

    if (area == NULL) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
    if (this->runtime->GetCurrentFrame() != topFrame) return;
    
    Value staticValue = area->static_fields[fieldName];
    switch (staticValue.type) {
        case BOOLEAN_VALUE:
            staticValue.type = INT_VALUE;
            // staticValue.printType = BOOLEAN_VALUE;
            break;
        case BYTE_VALUE:
            staticValue.type = INT_VALUE;
            // staticValue.printType = BYTE_VALUE;
            break;
        case SHORT_VALUE:
            staticValue.type = INT_VALUE;
            // staticValue.printType = SHORT_VALUE;
            break;
        case INT_VALUE:
            staticValue.type = INT_VALUE;
            // staticValue.printType = INT_VALUE;
            break;
        default:
            break;
    }
    
    if (staticValue.type == DOUBLE_VALUE || staticValue.type == LONG_VALUE) {
        Value paddingValue;
        paddingValue.type = PADDING_VALUE;
        topFrame->PushOperandStack(paddingValue);
    }

    topFrame->PushOperandStack(staticValue);

    topFrame->pc += 3;
}
//! Essa função representa a função putstatic da JVM
void Interpreter::i_putstatic() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    vector<CpInfo *>constantPool = topFrame->constant_pool;

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    CpInfo *fieldCP = constantPool[fieldIndex-1];
    // assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP->info.Fieldref;

    string className = ReadFile::readString(fieldRef.class_index, constantPool);

    CpInfo *nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    // assert(nameAndTypeCP->tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP->info.NameAndType;

    string fieldName = ReadFile::readString(fieldNameAndType.name_index, constantPool);
    string fieldDescriptor = ReadFile::readString(fieldNameAndType.descriptor_index, constantPool);

    map<string, MethodAreaSection *> method_area = this->runtime->method_area;
    MethodAreaSection *area = method_area[className];

    while (area != NULL) {
        if (area->static_fields.count(fieldName) == 0) {
            if (area->class_file->super_class == 0) {
                area = NULL;
            } else {
                string superClassName = ReadFile::readString(area->class_file->super_class, area->class_file->constant_pool);
                if(method_area.count(superClassName) > 0)
                    area = method_area[superClassName];
                else{
                    ClassLoaderSubsystem::Resolve(superClassName, this->runtime);
                    area = method_area[superClassName];
                }
            }
        } else {
            break;
        }
    }

    if (area == NULL) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
    if (this->runtime->GetCurrentFrame() != topFrame) return;
    
    Value topValue = topFrame->PopOperandStack();
    if (topValue.type == DOUBLE_VALUE || topValue.type == LONG_VALUE) {
        topFrame->PopOperandStack(); // removendo padding
    } else {
        switch (fieldDescriptor[0]) {
            case 'B':
                topValue.type = BYTE_VALUE;
                // topValue.printType = BYTE_VALUE;
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
                topValue.type = BYTE_VALUE;
                topValue.type = BYTE_VALUE;
                break;
        }
    }

    area->static_fields[fieldName] = topValue;

    topFrame->pc += 3;
}
//! Essa função representa a função getfield da JVM
void Interpreter::i_getfield() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    vector<CpInfo *>constantPool = topFrame->constant_pool;

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    CpInfo *fieldCP = constantPool[fieldIndex-1];
    // assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP->info.Fieldref;

    string className = ReadFile::readString(fieldRef.class_index, constantPool);

    CpInfo *nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    // assert(nameAndTypeCP->tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP->info.NameAndType;

    string fieldName = ReadFile::readString(fieldNameAndType.name_index, constantPool);
    string fieldDescriptor = ReadFile::readString(fieldNameAndType.descriptor_index, constantPool);

    Value objectValue = topFrame->PopOperandStack();
    // assert(objectValue.type == ValueType::REFERENCE);
    ObjectRef *object = objectValue.data.object_value;
    // assert(object->objectType() == ObjectType::CLASS_INSTANCE);
    // ClassInstance *classInstance = (ClassInstance *) object;

    if (object->variables.count(fieldName) == 0) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    Value fieldValue = object->GetVariable(fieldName);
    switch (fieldValue.type) {
        case BYTE_VALUE:
            fieldValue.type = INT_VALUE;
            // fieldValue.printType = BYTE_VALUE;
            break;
        case CHAR_VALUE:
            fieldValue.type = INT_VALUE;
            // fieldValue.printType = BYTE_VALUE;
            break;
        case SHORT_VALUE:
            fieldValue.type = INT_VALUE;
            // fieldValue.printType = SHORT_VALUE;
            break;
        case INT_VALUE:
            fieldValue.type = INT_VALUE;
            // fieldValue.printType = INT_VALUE;
            break;
        default:
            break;
    }
    
    if (fieldValue.type == DOUBLE_VALUE || fieldValue.type == LONG_VALUE) {
        Value paddingValue;
        paddingValue.type = PADDING_VALUE;
        topFrame->PushOperandStack(paddingValue);
    }

    topFrame->PushOperandStack(fieldValue);

    topFrame->pc += 3;
}
//! Essa função representa a função putfield da JVM
void Interpreter::i_putfield() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    vector<CpInfo *>constantPool = topFrame->constant_pool;

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    CpInfo *fieldCP = constantPool[fieldIndex-1];
    // assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP->info.Fieldref;

    string className = ReadFile::readString(fieldRef.class_index, constantPool);

    CpInfo *nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    // assert(nameAndTypeCP->tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP->info.NameAndType;

    string fieldName = ReadFile::readString(fieldNameAndType.name_index, constantPool);
    string fieldDescriptor = ReadFile::readString(fieldNameAndType.descriptor_index, constantPool);

    Value valueToBeInserted = topFrame->PopOperandStack();
    if (valueToBeInserted.type == DOUBLE_VALUE || valueToBeInserted.type == LONG_VALUE) {
        topFrame->PopOperandStack(); // removendo padding
    } else {
        switch (fieldDescriptor[0]) {
            case 'B':
                valueToBeInserted.type = BYTE_VALUE;
                // valueToBeInserted.printType = BYTE_VALUE;
                break;
            case 'C':
                valueToBeInserted.type = CHAR_VALUE;
                // valueToBeInserted.printType = CHAR_VALUE;
                break;
            case 'S':
                valueToBeInserted.type = SHORT_VALUE;
                // valueToBeInserted.printType = SHORT_VALUE;
                break;
            case 'Z':
                valueToBeInserted.type = BYTE_VALUE;
                // valueToBeInserted.printType = BYTE_VALUE;
                break;
        }
    }

    Value objectValue = topFrame->PopOperandStack();
    // assert(objectValue.type == ValueType::REFERENCE);
    ObjectRef *object = objectValue.data.object_value;
    // assert(object->objectType() == ObjectType::CLASS_INSTANCE);
    // ClassInstance *classInstance = (ClassInstance *) object;

    object->ChangeVariable(fieldName, valueToBeInserted);

    topFrame->pc += 3;
}
//! Essa função representa a função invokevirtual da JVM
void Interpreter::i_invokevirtual() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    // vector<Value> save_operand_stack = topFrame->operand_stack;
    
    vector<CpInfo *>constantPool = topFrame->constant_pool;

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    CpInfo *methodCP = constantPool[methodIndex-1];
    // assert(methodCP->tag == CONSTANT_Methodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP->info.Methodref;

    string className = ReadFile::readString(methodInfo.class_index, constantPool);

    CpInfo *nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    // assert(nameAndTypeCP->tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP->info.NameAndType;

    string methodName = ReadFile::readString(methodNameAndType.name_index, constantPool);
    string methodDescriptor = ReadFile::readString(methodNameAndType.descriptor_index, constantPool);

    if (className.find("java/") != string::npos) {
        // simulando println ou print
        if (className == "java/io/PrintStream" && (methodName == "print" || methodName == "println")) {
            if (methodDescriptor != "()V") {
                Value print_value = topFrame->PopOperandStack();

                if (print_value.type == INT_VALUE) {
                    switch (print_value.printType) {
                        case BOOLEAN_VALUE:
                            printf("%s", print_value.data.boolean_value == 0 ? "false" : "true");
                            break;
                        case BYTE_VALUE:
                            printf("%d", print_value.data.byte_value);
                            break;
                        case CHAR_VALUE:
                            printf("%c", print_value.data.char_value);
                            break;
                        case SHORT_VALUE:
                            printf("%d", print_value.data.short_value);
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
                        case STRING_VALUE:
                            // assert(print_value.data.object_value->objectType() == ObjectType::STRING_INSTANCE);
                            printf("%s", print_value.data.string_value->c_str());
                            break;
                        case BOOLEAN_VALUE:
                            printf("%s", print_value.data.boolean_value == 0 ? "false" : "true");
                            break;
                        case BYTE_VALUE:
                            printf("%d", print_value.data.byte_value);
                            break;
                        case CHAR_VALUE:
                            printf("%c", print_value.data.char_value);
                            break;
                        case SHORT_VALUE:
                            printf("%d", print_value.data.short_value);
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
            // assert(strValue1.data.object_value->objectType() == ObjectType::STRING_INSTANCE);
            // assert(strValue2.data.object_value->objectType() == ObjectType::STRING_INSTANCE);
            
            string *str1 = strValue1.data.string_value;
            string *str2 = strValue2.data.string_value;
            
            Value result;
            result.printType = INT_VALUE;
            result.type = INT_VALUE;
            if (str1->c_str() == str2->c_str()) {
                result.data.int_value = 1;
            } else {
                result.data.int_value = 0;
            }
            topFrame->PushOperandStack(result);
        } else if (className == "java/lang/String" && methodName == "length") {	
            Value strValue = topFrame->PopOperandStack();
            // assert(strValue.type == ValueType::REFERENCE);		
            // assert(strValue.data.object_value->objectType() == ObjectType::STRING_INSTANCE);		
                    
            string *str = strValue.data.string_value;		
                    
            Value result;
            result.printType = INT_VALUE;
            result.type = INT_VALUE;		
            result.data.int_value = str->size();		
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
            if (value.type == PADDING_VALUE) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        Value objectValue = topFrame->PopOperandStack();
        // assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
        args.insert(args.begin(), objectValue);

        ObjectRef *object = objectValue.data.object_value;
        // assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
        // ClassInstance *instance = (ClassInstance *) object;

        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[className];

        cout << "Invokando Method: " << methodName << " : " << methodDescriptor << endl;
        this->runtime->InitializeFrame(methodName, methodDescriptor, area->class_file, args);
    }

    topFrame->pc += 3;
}
//! Essa função representa a função invokespecial da JVM
void Interpreter::i_invokespecial() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    // vector<Value> save_operand_stack = topFrame->operand_stack;
    
    vector<CpInfo *> constantPool = topFrame->constant_pool;
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    CpInfo *methodCP = constantPool[methodIndex-1];
    // assert(methodCP->tag == CONSTANT_Methodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP->info.Methodref;

    string className = ReadFile::readString(methodInfo.class_index, constantPool);

    CpInfo * nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    // assert(nameAndTypeCP->tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP->info.NameAndType;

    string methodName = ReadFile::readString(methodNameAndType.name_index, constantPool);
    string methodDescriptor = ReadFile::readString(methodNameAndType.descriptor_index, constantPool);
    
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
            if (value.type == PADDING_VALUE) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        Value objectValue = topFrame->PopOperandStack();
        // assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
        args.insert(args.begin(), objectValue);

        ObjectRef *object = objectValue.data.object_value;
        // assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
        // ClassInstance *instance = (ClassInstance *) object;

        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[className];

        cout << "Invokando Method: " << methodName << " : " << methodDescriptor << endl;
        this->runtime->InitializeFrame(methodName, methodDescriptor, area->class_file, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        // if (this->runtime->GetCurrentFrame() != topFrame) {
        //     topFrame->setOperandStackFromBackup(operandStackBackup);
        //     delete newFrame;
        //     return;
        // }

        // this->runtime->PushFrame(newFrame);
    }

    topFrame->pc += 3;
}
//! Essa função representa a função invokestatic da JVM
void Interpreter::i_invokestatic() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    // stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    vector<CpInfo *> constantPool = topFrame->constant_pool;
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    CpInfo *methodCP = constantPool[methodIndex-1];
    // assert(methodCP->tag == CONSTANT_Methodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP->info.Methodref;

    string className = ReadFile::readString(methodInfo.class_index, constantPool);

    CpInfo * nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    // assert(nameAndTypeCP->tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP->info.NameAndType;

    string methodName = ReadFile::readString(methodNameAndType.name_index, constantPool);
    string methodDescriptor = ReadFile::readString(methodNameAndType.descriptor_index, constantPool);

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
            if (value.type == PADDING_VALUE) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[className];

        cout << "Invokando Method: " << methodName << " : " << methodDescriptor << endl;
        this->runtime->InitializeFrame(methodName, methodDescriptor, area->class_file, args);

        // AttributeInfo attr_code;
        // MethodInfo *method = area->class_file->getMethodByName(methodName);
        // method->getAttributeByName("Code", area->class_file->constant_pool, attr_code);
        
        // Frame *newFrame = new Frame(area->class_file->constant_pool, attr_code.info.Code);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        // if (stackFrame.getTopFrame() != topFrame) {
        //     topFrame->setOperandStackFromBackup(operandStackBackup);
        //     delete newFrame;
        //     return;
        // }

        // cout << "ADICIONOU" << endl;
        // this->runtime->PushFrame(newFrame);
    }

    topFrame->pc += 3;
}
//! Essa função representa a função invokeinterface da JVM
void Interpreter::i_invokeinterface() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    // stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    vector<CpInfo *> constantPool = topFrame->constant_pool;
    

    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    CpInfo *methodCP = constantPool[methodIndex-1];
    // assert(methodCP->tag == CONSTANT_Methodref || methodCP->tag == CONSTANT_InterfaceMethodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP->info.Methodref;

    string className = ReadFile::readString(methodInfo.class_index, constantPool);

    CpInfo * nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    // assert(nameAndTypeCP->tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP->info.NameAndType;

    string methodName = ReadFile::readString(methodNameAndType.name_index, constantPool);
    string methodDescriptor = ReadFile::readString(methodNameAndType.descriptor_index, constantPool);

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
            if (value.type == PADDING_VALUE) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        Value objectValue = topFrame->PopOperandStack();
        // assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
        args.insert(args.begin(), objectValue);

        ObjectRef *object = objectValue.data.object_value;
        // assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
        // ClassInstance *instance = (ClassInstance *) object;

        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[className];

        cout << "Invokando Method: " << methodName << " : " << methodDescriptor << endl;
        this->runtime->InitializeFrame(methodName, methodDescriptor, area->class_file, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        // if (stackFrame.getTopFrame() != topFrame) {
        //     topFrame->setOperandStackFromBackup(operandStackBackup);
        //     delete newFrame;
        //     return;
        // }

        // this->runtime->PushFrame(newFrame);
    }

    topFrame->pc += 5;
}
//! Essa função representa a função new da JVM
void Interpreter::i_new() {
           
    Frame *topFrame = this->runtime->GetCurrentFrame();     
    vector<CpInfo *> constantPool = topFrame->constant_pool;
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t classIndex = (byte1 << 8) | byte2;
    CpInfo * classCP = constantPool[classIndex-1];
    // assert(classCP.tag == CONSTANT_Class);
    
    CONSTANT_Class_info classInfo = classCP->info.Class; // Formata nome da classe
    string className = ReadFile::readString(classInfo.name_index, constantPool);

    Value value_ref;    
    if (className == "java/lang/String" || className == "java/lang/StringBuffer") {
        string *object = new string("");
        value_ref.data.string_value = object;
        value_ref.type = STRING_VALUE;
    } else {
        ClassLoaderSubsystem::Resolve(className, this->runtime);
        ObjectRef *objectref;
        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[className];
       
        objectref = new ObjectRef(area->class_file);
        value_ref.data.object_value = objectref;
        value_ref.type = OBJECT_VALUE;
    }
    
    // Armazena referência na pilha
    topFrame->PushOperandStack(value_ref);
    
    topFrame->pc += 3;
}
//! Essa função representa a função newarray da JVM
void Interpreter::i_newarray() {
           
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value count = topFrame->PopOperandStack(); // Número de elementos no array
    // assert(count.type == INT_VALUE);
    
    if (count.data.int_value < 0) {
        cerr << "NegativeArraySizeException" << endl;
        exit(1);
    }
    
    vector<Value> *array = new vector<Value>; // array que será criado
    Value value; // elemento que irá popular o array
    value.data.long_value = 0; // inicializando Value com 0s
    
    Value padding; // padding poderá ser usado
    padding.type = PADDING_VALUE;
    
    
    switch (topFrame->code.code[topFrame->pc+1]) { // argumento representa tipo do array
        case 4:
            
            value.type = BYTE_VALUE;
            value.printType = BYTE_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->push_back(value);
            }
            break;
        case 5:
            value.type = CHAR_VALUE;
            value.printType = CHAR_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->push_back(value);
            }
            break;
        case 6:
            value.type = FLOAT_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->push_back(value);
            }
            break;
        case 7:
            value.type = DOUBLE_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->push_back(value);
            }
            break;
        case 8:
            value.type = BYTE_VALUE;
            // value.printType = BYTE_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->push_back(value);
            }
            break;
        case 9:
            value.type = SHORT_VALUE;
            // value.printType = SHORT_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->push_back(value);
            }
            break;
        case 10:
            value.type = INT_VALUE;
            // value.printType = INT_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->push_back(value);
            }
            break;
        case 11:
            value.type = LONG_VALUE;
            for (int i = 0; i < count.data.int_value; i++) {
                array->push_back(value);
            }
            break;
    }
    
    Value arrayref; // Referencia pro array na pilha de operandos
    arrayref.type = ARRAY_VALUE;
    arrayref.data.array_value = array;
    
    topFrame->PushOperandStack(arrayref);
    topFrame->pc += 2;
}
//! Essa função representa a função anewarray da JVM
void Interpreter::i_anewarray() {
           
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value count = topFrame->PopOperandStack(); // Número de elementos no array
    // assert(count.type == INT_VALUE);
    if (count.data.int_value < 0) {
        cerr << "NegativeArraySizeException" << endl;
        exit(1);
    }
    
    vector<CpInfo *> constantPool = topFrame->constant_pool;
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];

    uint16_t classIndex = (byte1 << 8) | byte2; // Índice na pool de constantes
    CpInfo * classCP = constantPool[classIndex-1];
    // assert(classCP.tag == CONSTANT_Class);
    
    CONSTANT_Class_info classInfo = classCP->info.Class; // Formata nome da classe
    string className = ReadFile::readString(classInfo.name_index, constantPool);

    if (className != "java/lang/String") {
        int i = 0;
        while (className[i] == '[') i++;
        if (className[i] == 'L') {
            // map<string, MethodAreaSection *> method_area = this->runtime->method_area;
            ClassLoaderSubsystem::Resolve(className, this->runtime);
            // methodArea.loadClassNamed(className.substr(i+1, className.size()-i-2)); // carrega a classe de referência (se ainda não foi).
        }
    }

    // criando objeto da classe instanciada
    Value arrayref;
    arrayref.type = ARRAY_VALUE;
    arrayref.data.array_value = new vector<Value>();
    
    // populando array com NULL
    Value nullValue;
    nullValue.type = OBJECT_VALUE;
    nullValue.data.object_value = NULL;
    for (int i = 0; i < count.data.int_value; i++) {
        arrayref.data.array_value->push_back(nullValue);
    }

    topFrame->PushOperandStack(arrayref);
    
    topFrame->pc += 3;
}
//! Essa função representa a função arraylength da JVM
void Interpreter::i_arraylength() {
           
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value arrayref = topFrame->PopOperandStack();  
    // assert(arrayref.type == ValueType::REFERENCE);
    if (arrayref.data.object_value == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    
    Value length;
    length.type = INT_VALUE;
    length.data.int_value = arrayref.data.array_value->size();
    
    topFrame->PushOperandStack(length);
    topFrame->pc += 1 ;
}
//! Essa função representa a função athrow da JVM
void Interpreter::i_athrow() {
    Frame *topFrame = this->runtime->GetCurrentFrame();
    topFrame->pc += 1;
}
//! Essa função representa a função checkcast da JVM
void Interpreter::i_checkcast() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];
    
    u2 cpIndex = (byte1 << 8) | byte2;
    vector<CpInfo *> constantPool = topFrame->constant_pool;
    // CpInfo * cpElement = constantPool[cpIndex-1];
    // assert(cpElement.tag == CONSTANT_Class);
    string className = ReadFile::readString(cpIndex, constantPool);
    
    Value objectrefValue = topFrame->PopOperandStack();
    // assert(objectrefValue.type == OBJECT_VALUE);
    
    Value resultValue;
    resultValue.type = INT_VALUE;

    map<string, MethodAreaSection *> method_area = this->runtime->method_area;

    if (objectrefValue.data.object_value == NULL && objectrefValue.data.string_value == NULL) {
        cerr << "ClassCastException" << endl;
        exit(1);
    } else {        
        if (objectrefValue.type == OBJECT_VALUE && objectrefValue.data.object_value != NULL) {
            // ClassInstance *classInstance = (ClassInstance *) obj;
            // ClassRuntime *classRuntime = classInstance->getClassRuntime();
            ObjectRef *object = objectrefValue.data.object_value;
            ClassFile *classFile = object->class_file;
            
            bool found = false;
            while (!found) {
                string currClassName = ReadFile::readString(classFile->this_class, classFile->constant_pool);
                
                if (currClassName == className) {
                    found = true;
                } else {
                    if (classFile->super_class == 0) {
                        break;
                    } else {
                        string superClassName = ReadFile::readString(classFile->this_class, classFile->constant_pool);
                        MethodAreaSection *super_area;
                        if(method_area.count(superClassName) != 0){
                            super_area = method_area[superClassName];
                        }else{
                            ClassLoaderSubsystem::Resolve(superClassName, this->runtime);
                            super_area = method_area[superClassName];
                        }

                        classFile = super_area->class_file;                         
                        // classRuntime = methodArea.loadClassNamed(superClassName);
                    }
                }
            }
            
            resultValue.data.int_value = found ? 1 : 0;
        } else if (objectrefValue.type == STRING_VALUE && objectrefValue.data.string_value != NULL) {
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
//! Essa função representa a função instanceof da JVM
void Interpreter::i_instanceof() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    map<string, MethodAreaSection *> method_area = this->runtime->method_area;

    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];
    
    u2 cpIndex = (byte1 << 8) | byte2;
    vector<CpInfo *> constantPool = topFrame->constant_pool;
    CpInfo * cpElement = constantPool[cpIndex-1];
    // assert(cpElement.tag == CONSTANT_Class);
    string className = ReadFile::readString(cpIndex, constantPool);
    
    Value objectrefValue = topFrame->PopOperandStack();
    // assert(objectrefValue.type == ValueType::REFERENCE);
    
    Value resultValue;
    resultValue.type = INT_VALUE;

    // if (objectrefValue.data.object_value == NULL) {
    //     resultValue.data.int_value = 0;
    // } else {
    //     ObjectRef *obj = objectrefValue.data.object_value;
        
    //     if (obj->objectType() == ObjectType::CLASS_INSTANCE) {
    //         ClassInstance *classInstance = (ClassInstance *) obj;
    //         ClassRuntime *classRuntime = classInstance->getClassRuntime();
            
    //         bool found = false;
    //         while (!found) {
    //             ClassFile *classFile = classRuntime->getClassFile();
    //             string currClassName = ReadFile::readString(classFile->constant_pool, classFile->this_class);
                
    //             if (currClassName == className) {
    //                 found = true;
    //             } else {
    //                 if (classFile->super_class == 0) {
    //                     break;
    //                 } else {
    //                     string superClassName = ReadFile::readString(classFile->constant_pool, classFile->this_class);
    //                     classRuntime = methodArea.loadClassNamed(superClassName);
    //                 }
    //             }
    //         }
            
    //         resultValue.data.int_value = found ? 1 : 0;
    //     } else if (obj->objectType() == ObjectType::STRING_INSTANCE) {
    //         resultValue.data.int_value = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
    //     } else {
    //         if (className == "java/lang/Object") {
    //             resultValue.data.int_value = 1;
    //         } else {
    //             resultValue.data.int_value = 0;
    //         }
    //     }
    // }
    
    topFrame->PushOperandStack(resultValue);
    
    topFrame->pc += 3;
}
//! Essa função representa a função monitorenter da JVM
void Interpreter::i_monitorenter() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    topFrame->pc += 1;
}
//! Essa função representa a função monitorexit da JVM
void Interpreter::i_monitorexit() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    topFrame->pc += 1;
}
//! Essa função representa a função wide da JVM
void Interpreter::i_wide() {
	       
    Frame *topFrame = this->runtime->GetCurrentFrame();
	wide = true;
	topFrame->pc += 1;
}
//! Essa função representa a função multianewarray da JVM
void Interpreter::i_multianewarray() {
           
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    vector<CpInfo *> constantPool = topFrame->constant_pool;
    
    u1 byte1 = topFrame->code.code[topFrame->pc+1];
    u1 byte2 = topFrame->code.code[topFrame->pc+2];
    u1 dimensions = topFrame->code.code[topFrame->pc+3];
    // assert(dimensions >= 1);

    uint16_t classIndex = (byte1 << 8) | byte2;
    CpInfo * classCP = constantPool[classIndex-1];
    // assert(classCP.tag == CONSTANT_Class);
    
    CONSTANT_Class_info classInfo = classCP->info.Class;
    string className = ReadFile::readString(classInfo.name_index, constantPool);
    
    // obter o tipo dentro de className:
    char valueType;
    int i = 0;
    while (className[i] == '[') i++;
    
    string multiArrayType = className.substr(i+1, className.size()-i-2); // em caso de ser uma referência (e.g. [[[Ljava/lang/String;)
    
    switch (className[i]) {
        case 'L':
            if (multiArrayType != "java/lang/String") {
                ClassLoaderSubsystem::Resolve(className, this->runtime);
                // map<string, MethodAreaSection *> method_area = this->runtime->method_area;
                // method_area.loadClassNamed(multiArrayType); // verifica se existe classe com esse nome
                valueType = OBJECT_VALUE;
            }else{
                valueType = STRING_VALUE;
            }
            break;
        case 'B':
            valueType = BYTE_VALUE;
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
            valueType = BYTE_VALUE;
            break;
        default:
            cerr << "Descritor invalido em multianewarray" << endl;
            exit(1);
    }
    
    // stack<int> count;
    vector<int> count;
    for (int i = 0; i < dimensions; i++) {
        Value dimLength = topFrame->PopOperandStack();
        // assert(dimLength.type == INT_VALUE);
        count.push_back(dimLength.data.int_value);
    }
    
    vector<Value> *array = new vector<Value>();
    populateMultiarray(array, valueType, count);
    
    Value arrayValue;
    arrayValue.type = ARRAY_VALUE;
    arrayValue.data.array_value = array;
    
    topFrame->PushOperandStack(arrayValue);
    
    topFrame->pc += 4;
}
//! Essa função representa a função ifnull da JVM
void Interpreter::i_ifnull() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value referenceValue = topFrame->PopOperandStack();
    // assert(referenceValue.type == ValueType::REFERENCE);
    
    if (referenceValue.data.object_value == NULL) {
        
        u1 byte1 = topFrame->code.code[topFrame->pc+1];
        u1 byte2 = topFrame->code.code[topFrame->pc+2];
        int16_t branch =  (byte1 << 8) | byte2;
        topFrame->pc += branch;
    } else {
        topFrame->pc += 3;
    }
}
//! Essa função representa a função ifnonnull da JVM
void Interpreter::i_ifnonnull() {
    
    Frame *topFrame = this->runtime->GetCurrentFrame();
    
    Value referenceValue = topFrame->PopOperandStack();
    // assert(referenceValue.type == ValueType::REFERENCE);
    
    if (referenceValue.data.object_value != NULL) {
        
        u1 byte1 = topFrame->code.code[topFrame->pc+1];
        u1 byte2 = topFrame->code.code[topFrame->pc+2];
        int16_t branch =  (byte1 << 8) | byte2;
        topFrame->pc += branch;
    } else {
        topFrame->pc += 3;
    }
}
//! Essa função representa a função goto_w da JVM
void Interpreter::i_goto_w() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	
	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	u1 byte2 = topFrame->code.code[topFrame->pc+2];
	u1 byte3 = topFrame->code.code[topFrame->pc+3];
	u1 byte4 = topFrame->code.code[topFrame->pc+4];
	int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

	topFrame->pc += branchOffset;
	// assert(topFrame->pc < (int32_t)topFrame->sizeCode());
}
//! Essa função representa a função jsr_w da JVM
void Interpreter::i_jsr_w() {
	
	Frame *topFrame = this->runtime->GetCurrentFrame();

	
	u1 byte1 = topFrame->code.code[topFrame->pc+1];
	u1 byte2 = topFrame->code.code[topFrame->pc+2];
	u1 byte3 = topFrame->code.code[topFrame->pc+3];
	u1 byte4 = topFrame->code.code[topFrame->pc+4];
	int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8)| byte4;

	Value returnAddr;
	returnAddr.type = RETURN_VALUE;
	returnAddr.data.return_address = topFrame->pc + 5;
	topFrame->PushOperandStack(returnAddr);

	topFrame->pc += branchOffset;

	// assert(topFrame->pc < (int32_t)topFrame->sizeCode());
}