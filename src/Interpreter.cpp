#include <math.h>

#include "../header/Interpreter.hpp"
#include "../header/Opcodes.hpp"
#include "../header/ClassLoaderSubsystem.hpp"
#include "../header/ReadFile.hpp"
#include "../header/MethodAreaSection.hpp"
#include "../header/ObjectRef.hpp"
#include "../header/MemoryManager.hpp"

Interpreter::Interpreter(Runtime *runtime)
{
    this->ConstructTable();

    this->runtime = runtime;
    this->wide = false;
}

Interpreter::~Interpreter()
{
    delete this->runtime;

    for( unsigned i = 0; i < MemoryManager::variables_allocated.size(); i++){
        if(MemoryManager::variables_allocated[i].type == OBJECT_VALUE && MemoryManager::variables_allocated[i].data.object_value != NULL)
            delete MemoryManager::variables_allocated[i].data.object_value;
        else if(MemoryManager::variables_allocated[i].type == STRING_VALUE && MemoryManager::variables_allocated[i].data.string_value != NULL){
            delete MemoryManager::variables_allocated[i].data.string_value;
        }else if(MemoryManager::variables_allocated[i].type == ARRAY_VALUE && MemoryManager::variables_allocated[i].data.array_value != NULL)
            delete MemoryManager::variables_allocated[i].data.array_value;
    }
}

//! Essa função representa a função ExecuteInterpreter da JVM
void Interpreter::ExecuteInterpreter()
{
    ClassLoaderSubsystem::Resolve(Runtime::main_class_name, this->runtime);
    Interpreter::ExecuteFrame();
}
//! Essa função representa a função ExecuteFrame da JVM
void Interpreter::ExecuteFrame()
{
    // cout << this->runtime->stack.size() << endl;
    Opcodes::CreateOpcodes();
    // Aqui devemos executar o code.
    while (this->runtime->stack.size() > 0)
    {
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
        // cout << "Executando: " << Opcodes::opcodes[bytecode].first << endl;

        (this->*method_func)();
    }
    // Para isso precisamos saber quantas casas de PC andar a cada função (Fazer isso dentro da própria função)

    // ( não precisa, vai desempilhar e basta colocar ) Colocar invoker_frame dentro das funções de invoke, para sinalizar para quem deve atribuir os return.

    // ( dentro do proprio return, desempilhar ) Pensar em como faremos para o return cancelar o frame atual e cancelar essa função.
}

void Interpreter::ConstructTable()
{
    this->instruction_table[0x00] = &Interpreter::java_nop;
    this->instruction_table[0x01] = &Interpreter::java_aconst_null;
    this->instruction_table[0x02] = &Interpreter::java_iconst_m1;
    this->instruction_table[0x03] = &Interpreter::java_iconst_0;
    this->instruction_table[0x04] = &Interpreter::java_iconst_1;
    this->instruction_table[0x05] = &Interpreter::java_iconst_2;
    this->instruction_table[0x06] = &Interpreter::java_iconst_3;
    this->instruction_table[0x07] = &Interpreter::java_iconst_4;
    this->instruction_table[0x08] = &Interpreter::java_iconst_5;
    this->instruction_table[0x09] = &Interpreter::java_lconst_0;
    this->instruction_table[0x0a] = &Interpreter::java_lconst_1;
    this->instruction_table[0x0b] = &Interpreter::java_fconst_0;
    this->instruction_table[0x0c] = &Interpreter::java_fconst_1;
    this->instruction_table[0x0d] = &Interpreter::java_fconst_2;
    this->instruction_table[0x0e] = &Interpreter::java_dconst_0;
    this->instruction_table[0x0f] = &Interpreter::java_dconst_1;
    this->instruction_table[0x10] = &Interpreter::java_bipush;
    this->instruction_table[0x11] = &Interpreter::java_sipush;
    this->instruction_table[0x12] = &Interpreter::java_ldc;
    this->instruction_table[0x13] = &Interpreter::java_ldc_w;
    this->instruction_table[0x14] = &Interpreter::java_ldc2_w;
    this->instruction_table[0x15] = &Interpreter::java_iload;
    this->instruction_table[0x16] = &Interpreter::java_lload;
    this->instruction_table[0x17] = &Interpreter::java_fload;
    this->instruction_table[0x18] = &Interpreter::java_dload;
    this->instruction_table[0x19] = &Interpreter::java_aload;
    this->instruction_table[0x1a] = &Interpreter::java_iload_0;
    this->instruction_table[0x1b] = &Interpreter::java_iload_1;
    this->instruction_table[0x1c] = &Interpreter::java_iload_2;
    this->instruction_table[0x1d] = &Interpreter::java_iload_3;
    this->instruction_table[0x1e] = &Interpreter::java_lload_0;
    this->instruction_table[0x1f] = &Interpreter::java_lload_1;
    this->instruction_table[0x20] = &Interpreter::java_lload_2;
    this->instruction_table[0x21] = &Interpreter::java_lload_3;
    this->instruction_table[0x22] = &Interpreter::java_fload_0;
    this->instruction_table[0x23] = &Interpreter::java_fload_1;
    this->instruction_table[0x24] = &Interpreter::java_fload_2;
    this->instruction_table[0x25] = &Interpreter::java_fload_3;
    this->instruction_table[0x26] = &Interpreter::java_dload_0;
    this->instruction_table[0x27] = &Interpreter::java_dload_1;
    this->instruction_table[0x28] = &Interpreter::java_dload_2;
    this->instruction_table[0x29] = &Interpreter::java_dload_3;
    this->instruction_table[0x2a] = &Interpreter::java_aload_0;
    this->instruction_table[0x2b] = &Interpreter::java_aload_1;
    this->instruction_table[0x2c] = &Interpreter::java_aload_2;
    this->instruction_table[0x2d] = &Interpreter::java_aload_3;
    this->instruction_table[0x2e] = &Interpreter::java_iaload;
    this->instruction_table[0x2f] = &Interpreter::java_laload;
    this->instruction_table[0x30] = &Interpreter::java_faload;
    this->instruction_table[0x31] = &Interpreter::java_daload;
    this->instruction_table[0x32] = &Interpreter::java_aaload;
    this->instruction_table[0x33] = &Interpreter::java_baload;
    this->instruction_table[0x34] = &Interpreter::java_caload;
    this->instruction_table[0x35] = &Interpreter::java_saload;
    this->instruction_table[0x36] = &Interpreter::java_istore;
    this->instruction_table[0x37] = &Interpreter::java_lstore;
    this->instruction_table[0x38] = &Interpreter::java_fstore;
    this->instruction_table[0x39] = &Interpreter::java_dstore;
    this->instruction_table[0x3a] = &Interpreter::java_astore;
    this->instruction_table[0x3b] = &Interpreter::java_istore_0;
    this->instruction_table[0x3c] = &Interpreter::java_istore_1;
    this->instruction_table[0x3d] = &Interpreter::java_istore_2;
    this->instruction_table[0x3e] = &Interpreter::java_istore_3;
    this->instruction_table[0x3f] = &Interpreter::java_lstore_0;
    this->instruction_table[0x40] = &Interpreter::java_lstore_1;
    this->instruction_table[0x41] = &Interpreter::java_lstore_2;
    this->instruction_table[0x42] = &Interpreter::java_lstore_3;
    this->instruction_table[0x43] = &Interpreter::java_fstore_0;
    this->instruction_table[0x44] = &Interpreter::java_fstore_1;
    this->instruction_table[0x45] = &Interpreter::java_fstore_2;
    this->instruction_table[0x46] = &Interpreter::java_fstore_3;
    this->instruction_table[0x47] = &Interpreter::java_dstore_0;
    this->instruction_table[0x48] = &Interpreter::java_dstore_1;
    this->instruction_table[0x49] = &Interpreter::java_dstore_2;
    this->instruction_table[0x4a] = &Interpreter::java_dstore_3;
    this->instruction_table[0x4b] = &Interpreter::java_astore_0;
    this->instruction_table[0x4c] = &Interpreter::java_astore_1;
    this->instruction_table[0x4d] = &Interpreter::java_astore_2;
    this->instruction_table[0x4e] = &Interpreter::java_astore_3;
    this->instruction_table[0x4f] = &Interpreter::java_iastore;
    this->instruction_table[0x50] = &Interpreter::java_lastore;
    this->instruction_table[0x51] = &Interpreter::java_fastore;
    this->instruction_table[0x52] = &Interpreter::java_dastore;
    this->instruction_table[0x53] = &Interpreter::java_aastore;
    this->instruction_table[0x54] = &Interpreter::java_bastore;
    this->instruction_table[0x55] = &Interpreter::java_castore;
    this->instruction_table[0x56] = &Interpreter::java_sastore;
    this->instruction_table[0x57] = &Interpreter::java_pop;
    this->instruction_table[0x58] = &Interpreter::java_pop2;
    this->instruction_table[0x59] = &Interpreter::java_dup;
    this->instruction_table[0x5a] = &Interpreter::java_dup_x1;
    this->instruction_table[0x5b] = &Interpreter::java_dup_x2;
    this->instruction_table[0x5c] = &Interpreter::java_dup2;
    this->instruction_table[0x5d] = &Interpreter::java_dup2_x1;
    this->instruction_table[0x5e] = &Interpreter::java_dup2_x2;
    this->instruction_table[0x5f] = &Interpreter::java_swap;
    this->instruction_table[0x60] = &Interpreter::java_iadd;
    this->instruction_table[0x61] = &Interpreter::java_ladd;
    this->instruction_table[0x62] = &Interpreter::java_fadd;
    this->instruction_table[0x63] = &Interpreter::java_dadd;

    this->instruction_table[0x64] = &Interpreter::java_isub;
    this->instruction_table[0x65] = &Interpreter::java_lsub;
    this->instruction_table[0x66] = &Interpreter::java_fsub;
    this->instruction_table[0x67] = &Interpreter::java_dsub;
    this->instruction_table[0x68] = &Interpreter::java_imul;
    this->instruction_table[0x69] = &Interpreter::java_lmul;
    this->instruction_table[0x6a] = &Interpreter::java_fmul;
    this->instruction_table[0x6b] = &Interpreter::java_dmul;
    this->instruction_table[0x6c] = &Interpreter::java_idiv;
    this->instruction_table[0x6d] = &Interpreter::java_ldiv;
    this->instruction_table[0x6e] = &Interpreter::java_fdiv;
    this->instruction_table[0x6f] = &Interpreter::java_ddiv;
    this->instruction_table[0x70] = &Interpreter::java_irem;
    this->instruction_table[0x71] = &Interpreter::java_lrem;
    this->instruction_table[0x72] = &Interpreter::java_frem;
    this->instruction_table[0x73] = &Interpreter::java_drem;
    this->instruction_table[0x74] = &Interpreter::java_ineg;
    this->instruction_table[0x75] = &Interpreter::java_lneg;
    this->instruction_table[0x76] = &Interpreter::java_fneg;
    this->instruction_table[0x77] = &Interpreter::java_dneg;
    this->instruction_table[0x78] = &Interpreter::java_ishl;
    this->instruction_table[0x79] = &Interpreter::java_lshl;
    this->instruction_table[0x7a] = &Interpreter::java_ishr;
    this->instruction_table[0x7b] = &Interpreter::java_lshr;
    this->instruction_table[0x7c] = &Interpreter::java_iushr;
    this->instruction_table[0x7d] = &Interpreter::java_lushr;
    this->instruction_table[0x7e] = &Interpreter::java_iand;
    this->instruction_table[0x7f] = &Interpreter::java_land;
    this->instruction_table[0x80] = &Interpreter::java_ior;
    this->instruction_table[0x81] = &Interpreter::java_lor;
    this->instruction_table[0x82] = &Interpreter::java_ixor;
    this->instruction_table[0x83] = &Interpreter::java_lxor;
    this->instruction_table[0x84] = &Interpreter::java_iinc;
    this->instruction_table[0x85] = &Interpreter::java_i2l;
    this->instruction_table[0x86] = &Interpreter::java_i2f;
    this->instruction_table[0x87] = &Interpreter::java_i2d;
    this->instruction_table[0x88] = &Interpreter::java_l2i;
    this->instruction_table[0x89] = &Interpreter::java_l2f;
    this->instruction_table[0x8a] = &Interpreter::java_l2d;
    this->instruction_table[0x8b] = &Interpreter::java_f2i;
    this->instruction_table[0x8c] = &Interpreter::java_f2l;
    this->instruction_table[0x8d] = &Interpreter::java_f2d;
    this->instruction_table[0x8e] = &Interpreter::java_d2i;
    this->instruction_table[0x8f] = &Interpreter::java_d2l;
    this->instruction_table[0x90] = &Interpreter::java_d2f;
    this->instruction_table[0x91] = &Interpreter::java_i2b;
    this->instruction_table[0x92] = &Interpreter::java_i2c;
    this->instruction_table[0x93] = &Interpreter::java_i2s;
    this->instruction_table[0x94] = &Interpreter::java_lcmp;
    this->instruction_table[0x95] = &Interpreter::java_fcmpl;
    this->instruction_table[0x96] = &Interpreter::java_fcmpg;
    this->instruction_table[0x97] = &Interpreter::java_dcmpl;
    this->instruction_table[0x98] = &Interpreter::java_dcmpg;
    this->instruction_table[0x99] = &Interpreter::java_ifeq;
    this->instruction_table[0x9a] = &Interpreter::java_ifne;
    this->instruction_table[0x9b] = &Interpreter::java_iflt;
    this->instruction_table[0x9c] = &Interpreter::java_ifge;
    this->instruction_table[0x9d] = &Interpreter::java_ifgt;
    this->instruction_table[0x9e] = &Interpreter::java_ifle;
    this->instruction_table[0x9f] = &Interpreter::java_if_icmpeq;
    this->instruction_table[0xa0] = &Interpreter::java_if_icmpne;
    this->instruction_table[0xa1] = &Interpreter::java_if_icmplt;
    this->instruction_table[0xa2] = &Interpreter::java_if_icmpge;
    this->instruction_table[0xa3] = &Interpreter::java_if_icmpgt;
    this->instruction_table[0xa4] = &Interpreter::java_if_icmple;
    this->instruction_table[0xa5] = &Interpreter::java_if_acmpeq;
    this->instruction_table[0xa6] = &Interpreter::java_if_acmpne;
    this->instruction_table[0xa7] = &Interpreter::java_goto;
    this->instruction_table[0xa8] = &Interpreter::java_jsr;
    this->instruction_table[0xa9] = &Interpreter::java_ret;
    this->instruction_table[0xaa] = &Interpreter::java_tableswitch;
    this->instruction_table[0xab] = &Interpreter::java_lookupswitch;
    this->instruction_table[0xac] = &Interpreter::java_ireturn;
    this->instruction_table[0xad] = &Interpreter::java_lreturn;
    this->instruction_table[0xae] = &Interpreter::java_freturn;
    this->instruction_table[0xaf] = &Interpreter::java_dreturn;
    this->instruction_table[0xb0] = &Interpreter::java_areturn;
    this->instruction_table[0xb1] = &Interpreter::java_return;
    this->instruction_table[0xb2] = &Interpreter::java_getstatic;
    this->instruction_table[0xb3] = &Interpreter::java_putstatic;
    this->instruction_table[0xb4] = &Interpreter::java_getfield;
    this->instruction_table[0xb5] = &Interpreter::java_putfield;
    this->instruction_table[0xb6] = &Interpreter::java_invokevirtual;
    this->instruction_table[0xb7] = &Interpreter::java_invokespecial;
    this->instruction_table[0xb8] = &Interpreter::java_invokestatic;
    this->instruction_table[0xb9] = &Interpreter::java_invokeinterface;
    this->instruction_table[0xbb] = &Interpreter::java_new;
    this->instruction_table[0xbc] = &Interpreter::java_newarray;
    this->instruction_table[0xbd] = &Interpreter::java_anewarray;
    this->instruction_table[0xbe] = &Interpreter::java_arraylength;
    this->instruction_table[0xbf] = &Interpreter::java_athrow;
    this->instruction_table[0xc0] = &Interpreter::java_checkcast;
    this->instruction_table[0xc1] = &Interpreter::java_instanceof;
    this->instruction_table[0xc2] = &Interpreter::java_monitorenter;
    this->instruction_table[0xc3] = &Interpreter::java_monitorexit;
    this->instruction_table[0xc4] = &Interpreter::java_wide;
    this->instruction_table[0xc5] = &Interpreter::java_multianewarray;
    this->instruction_table[0xc6] = &Interpreter::java_ifnull;
    this->instruction_table[0xc7] = &Interpreter::java_ifnonnull;
    this->instruction_table[0xc8] = &Interpreter::java_goto_w;
    this->instruction_table[0xc9] = &Interpreter::java_jsr_w;
}

//! Essa função representa a função nop da JVM
void Interpreter::java_nop()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    current_frame->pc += 1;
}
//! Essa função representa a função aconst_null da JVM
void Interpreter::java_aconst_null()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = OBJECT_VALUE;
    value.data.object_value = nullptr;

    current_frame->PushOperandStack(value);
    current_frame->pc += 1;
}
//! Essa função representa a função iconst_m1 da JVM
void Interpreter::java_iconst_m1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = INT_VALUE;
    value.data.int_value = -1;

    current_frame->PushOperandStack(value);

    // cout << "ICONST_M1 empilhou op_stack: " << value.data.int_value << endl;
    current_frame->pc += 1;
}
//! Essa função representa a função iconst_0 da JVM
void Interpreter::java_iconst_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = INT_VALUE;
    value.data.int_value = 0;

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função iconst_1 da JVM
void Interpreter::java_iconst_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = INT_VALUE;
    value.data.int_value = 1;

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função iconst_2 da JVM
void Interpreter::java_iconst_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = INT_VALUE;
    value.data.int_value = 2;

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função iconst_3 da JVM
void Interpreter::java_iconst_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = INT_VALUE;
    value.data.int_value = 3;

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função iconst_4 da JVM
void Interpreter::java_iconst_4()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = INT_VALUE;
    value.data.int_value = 4;

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função iconst_5 da JVM
void Interpreter::java_iconst_5()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = INT_VALUE;
    value.data.int_value = 5;

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função lconst_0 da JVM
void Interpreter::java_lconst_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value padding;
    padding.type = PADDING_VALUE;

    Value value;
    value.type = LONG_VALUE;
    value.data.long_value = 0;

    current_frame->PushOperandStack(padding);
    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função lconst_1 da JVM
void Interpreter::java_lconst_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value padding;
    padding.type = PADDING_VALUE;

    Value value;
    value.type = LONG_VALUE;
    value.data.long_value = 1;

    current_frame->PushOperandStack(padding);
    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função fconst_0 da JVM
void Interpreter::java_fconst_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = FLOAT_VALUE;
    value.data.float_value = 0;

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função fconst_1 da JVM
void Interpreter::java_fconst_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = FLOAT_VALUE;
    value.data.float_value = 1;

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função fconst_2 da JVM
void Interpreter::java_fconst_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;
    value.type = FLOAT_VALUE;
    value.data.float_value = 2;

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função dconst_0 da JVM
void Interpreter::java_dconst_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value padding;
    padding.type = PADDING_VALUE;

    Value value;
    value.type = DOUBLE_VALUE;
    value.data.double_value = 0;

    current_frame->PushOperandStack(padding);
    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função dconst_1 da JVM
void Interpreter::java_dconst_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value padding;
    padding.type = PADDING_VALUE;

    Value value;
    value.type = DOUBLE_VALUE;
    value.data.double_value = 1;

    current_frame->PushOperandStack(padding);
    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função bipush da JVM
void Interpreter::java_bipush()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte = current_frame->code.code[current_frame->pc + 1];

    Value value;

    value.type = INT_VALUE;
    value.data.int_value = (int32_t)(int8_t)byte;

    current_frame->PushOperandStack(value);

    current_frame->pc += 2;
}
//! Essa função representa a função sipush da JVM
void Interpreter::java_sipush()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t short_value = (byte1 << 8) | byte2;
    Value value;

    value.type = INT_VALUE;
    value.data.int_value = (int32_t)(int16_t)short_value;

    current_frame->PushOperandStack(value);

    current_frame->pc += 3;
}
//! Essa função representa a função ldc da JVM
void Interpreter::java_ldc()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 index = current_frame->code.code[current_frame->pc + 1];

    vector<CpInfo *> constant_pool = current_frame->constant_pool;
    CpInfo *entry = constant_pool[index - 1];

    Value value;

    if (entry->tag == CONSTANT_String)
    {
        CpInfo *utf8_entry = constant_pool[entry->info.String.string_index - 1];

        u1 *bytes = utf8_entry->info.Utf8.bytes;
        char utf8_string[utf8_entry->info.Utf8.length + 1];
        int i;
        for (i = 0; i < utf8_entry->info.Utf8.length; i++)
        {
            utf8_string[i] = bytes[i];
        }
        utf8_string[i] = '\0';

        value.type = STRING_VALUE;
        value.data.string_value = new string(utf8_string);
        MemoryManager::variables_allocated.push_back(value); 

    }
    else if (entry->tag == CONSTANT_Integer)
    {

        value.type = INT_VALUE;
        value.data.int_value = (int32_t)entry->info.Integer.bytes;
    }
    else if (entry->tag == CONSTANT_Float)
    {
        u4 float_bytes = entry->info.Float.bytes;
        int s = ((float_bytes >> 31) == 0) ? 1 : -1;
        int e = ((float_bytes >> 23) & 0xff);
        int m = (e == 0) ? (float_bytes & 0x7fffff) << 1 : (float_bytes & 0x7fffff) | 0x800000;

        float number = s * m * pow(2, e - 150);
        value.type = FLOAT_VALUE;
        value.data.float_value = number;
    }
    else
    {
        cerr << "LDC tentando acessar um constant_pool invalido: " << entry->tag << endl;
        exit(1);
    }

    current_frame->PushOperandStack(value);
    current_frame->pc += 2;
}
//! Essa função representa a função ldc_w da JVM
void Interpreter::java_ldc_w()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    u2 index = (byte1 << 8) | byte2;

    vector<CpInfo *> constant_pool = current_frame->constant_pool;
    CpInfo *entry = constant_pool[index - 1];

    Value value;

    if (entry->tag == CONSTANT_String)
    {
        CpInfo *utf8_entry = constant_pool[entry->info.String.string_index - 1];

        u1 *bytes = utf8_entry->info.Utf8.bytes;
        char utf8_string[utf8_entry->info.Utf8.length + 1];
        int i;
        for (i = 0; i < utf8_entry->info.Utf8.length; i++)
        {
            utf8_string[i] = bytes[i];
        }
        utf8_string[i] = '\0';

        value.type = STRING_VALUE;
        value.data.string_value = new string(utf8_string);
        MemoryManager::variables_allocated.push_back(value);
    }
    else if (entry->tag == CONSTANT_Integer)
    {

        value.type = INT_VALUE;
        value.data.int_value = entry->info.Integer.bytes;
    }
    else if (entry->tag == CONSTANT_Float)
    {
        u4 float_bytes = entry->info.Float.bytes;
        int s = ((float_bytes >> 31) == 0) ? 1 : -1;
        int e = ((float_bytes >> 23) & 0xff);
        int m = (e == 0) ? (float_bytes & 0x7fffff) << 1 : (float_bytes & 0x7fffff) | 0x800000;

        float number = s * m * pow(2, e - 150);
        value.type = FLOAT_VALUE;
        value.data.float_value = number;
    }
    else
    {
        cerr << "LDC_W tentando acessar um constant_pool invalido: " << entry->tag << endl;
        exit(1);
    }

    current_frame->PushOperandStack(value);
    current_frame->pc += 3;
}
//! Essa função representa a função ldc2_w da JVM
void Interpreter::java_ldc2_w()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    u2 index = (byte1 << 8) | byte2;

    vector<CpInfo *> class_file = current_frame->constant_pool;
    CpInfo *entry = class_file[index - 1];

    Value value;

    if (entry->tag == CONSTANT_Long)
    {
        u4 high_bytes = entry->info.Long.high_bytes;
        u4 low_bytes = entry->info.Long.low_bytes;

        int64_t long_number = ((int64_t)high_bytes << 32) + low_bytes;
        value.type = LONG_VALUE;
        value.data.long_value = long_number;

        Value padding;
        padding.type = PADDING_VALUE;

        current_frame->PushOperandStack(padding);
    }
    else if (entry->tag == CONSTANT_Double)
    {
        u4 high_bytes = entry->info.Double.high_bytes;
        u4 low_bytes = entry->info.Double.low_bytes;

        int64_t long_number = ((int64_t)high_bytes << 32) + low_bytes;

        int32_t s = ((long_number >> 63) == 0) ? 1 : -1;
        int32_t e = (int32_t)((long_number >> 52) & 0x7ffL);
        int64_t m = (e == 0) ? (long_number & 0xfffffffffffffL) << 1 : (long_number & 0xfffffffffffffL) | 0x10000000000000L;

        double double_number = s * m * pow(2, e - 1075);
        value.type = DOUBLE_VALUE;
        value.data.double_value = double_number;

        Value padding;
        padding.type = PADDING_VALUE;

        current_frame->PushOperandStack(padding);
    }
    else
    {
        cerr << "ldc2_w tentando acessar um elemento da CP invalido: " << entry->tag << endl;
        exit(1);
    }

    current_frame->PushOperandStack(value);
    current_frame->pc += 3;
}
//! Essa função representa a função iload da JVM
void Interpreter::java_iload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    // cout << "ILOAD BYTE1... " << (int) byte1 << endl;
    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    Value value = current_frame->GetLocalVariable(index);

    // cout << "ILOAD... " << current_frame->local_variables.size() << " : " << index << " : " << value.data.int_value << endl;
    current_frame->PushOperandStack(value);
}
//! Essa função representa a função lload da JVM
void Interpreter::java_lload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];

    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    Value value = current_frame->GetLocalVariable(index);

    Value padding;
    padding.type = PADDING_VALUE;

    current_frame->PushOperandStack(padding);
    current_frame->PushOperandStack(value);
}
//! Essa função representa a função fload da JVM
void Interpreter::java_fload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    Value value = current_frame->GetLocalVariable(index);

    current_frame->PushOperandStack(value);
}
//! Essa função representa a função dload da JVM
void Interpreter::java_dload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    Value value = current_frame->GetLocalVariable(index);

    Value padding;
    padding.type = PADDING_VALUE;

    current_frame->PushOperandStack(padding);
    current_frame->PushOperandStack(value);
}
//! Essa função representa a função aload da JVM
void Interpreter::java_aload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    Value value = current_frame->GetLocalVariable(index);

    current_frame->PushOperandStack(value);
}
//! Essa função representa a função iload_0 da JVM
void Interpreter::java_iload_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    // cout << "ILOAD_0 size: " << current_frame->local_variables.size() << endl;
    Value value = current_frame->GetLocalVariable(0);

    current_frame->PushOperandStack(value);

    // cout << "ILOAD_0 empilhou no op_stack: " << value.data.int_value << endl;
    current_frame->pc += 1;
}
//! Essa função representa a função iload_1 da JVM
void Interpreter::java_iload_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(1);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função iload_2 da JVM
void Interpreter::java_iload_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(2);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função iload_3 da JVM
void Interpreter::java_iload_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(3);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função lload_0 da JVM
void Interpreter::java_lload_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;

    value = current_frame->GetLocalVariable(1);

    current_frame->PushOperandStack(value);

    value = current_frame->GetLocalVariable(0);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função lload_1 da JVM
void Interpreter::java_lload_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;

    value = current_frame->GetLocalVariable(2);

    current_frame->PushOperandStack(value);

    value = current_frame->GetLocalVariable(1);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função lload_2 da JVM
void Interpreter::java_lload_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;

    value = current_frame->GetLocalVariable(3);

    current_frame->PushOperandStack(value);

    value = current_frame->GetLocalVariable(2);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função lload_3 da JVM
void Interpreter::java_lload_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;

    value = current_frame->GetLocalVariable(4);

    current_frame->PushOperandStack(value);

    value = current_frame->GetLocalVariable(3);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função fload_0 da JVM
void Interpreter::java_fload_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(0);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função fload_1 da JVM
void Interpreter::java_fload_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(1);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função fload_2 da JVM
void Interpreter::java_fload_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(2);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função fload_3 da JVM
void Interpreter::java_fload_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(3);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função dload_0 da JVM
void Interpreter::java_dload_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;

    value = current_frame->GetLocalVariable(1);

    current_frame->PushOperandStack(value);

    value = current_frame->GetLocalVariable(0);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função dload_1 da JVM
void Interpreter::java_dload_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;

    value = current_frame->GetLocalVariable(2);

    current_frame->PushOperandStack(value);

    value = current_frame->GetLocalVariable(1);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função dload_2 da JVM
void Interpreter::java_dload_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;

    value = current_frame->GetLocalVariable(3);

    current_frame->PushOperandStack(value);

    value = current_frame->GetLocalVariable(2);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função dload_3 da JVM
void Interpreter::java_dload_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value;

    value = current_frame->GetLocalVariable(4);

    current_frame->PushOperandStack(value);

    value = current_frame->GetLocalVariable(3);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função aload_0 da JVM
void Interpreter::java_aload_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(0);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função aload_1 da JVM
void Interpreter::java_aload_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(1);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função aload_2 da JVM
void Interpreter::java_aload_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(2);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função aload_3 da JVM
void Interpreter::java_aload_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->GetLocalVariable(3);

    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função iaload da JVM
void Interpreter::java_iaload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    current_frame->PushOperandStack(array->at(index.data.int_value));
    current_frame->pc += 1;
}
//! Essa função representa a função laload da JVM
void Interpreter::java_laload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    vector<Value> *array;

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    Value padding;
    padding.type = PADDING_VALUE;

    current_frame->PushOperandStack(padding);
    current_frame->PushOperandStack(array->at(index.data.int_value));
    current_frame->pc += 1;
}
//! Essa função representa a função faload da JVM
void Interpreter::java_faload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    current_frame->PushOperandStack(array->at(index.data.int_value));
    current_frame->pc += 1;
}
//! Essa função representa a função daload da JVM
void Interpreter::java_daload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    Value padding;
    padding.type = PADDING_VALUE;

    current_frame->PushOperandStack(padding);
    current_frame->PushOperandStack(array->at(index.data.int_value));
    current_frame->pc += 1;
}
//! Essa função representa a função aaload da JVM
void Interpreter::java_aaload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    // cout << "HERE" << endl;
    current_frame->PushOperandStack(array->at(index.data.int_value));
    current_frame->pc += 1;
}
//! Essa função representa a função baload da JVM
void Interpreter::java_baload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    Value value = array->at(index.data.int_value);

    if (value.type == BYTE_VALUE)
    {
        value.data.int_value = (uint32_t)value.data.boolean_value;
    }
    else
    {
        value.data.int_value = (int32_t)value.data.byte_value;
    }
    value.type = INT_VALUE;

    current_frame->PushOperandStack(value);
    current_frame->pc += 1;
}
//! Essa função representa a função caload da JVM
void Interpreter::java_caload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    Value char_value = array->at(index.data.int_value);
    char_value.data.int_value = (uint32_t)char_value.data.char_value;

    char_value.type = INT_VALUE;

    current_frame->PushOperandStack(char_value);
    current_frame->pc += 1;
}
//! Essa função representa a função saload da JVM
void Interpreter::java_saload()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    Value short_value = array->at(index.data.int_value);
    short_value.data.int_value = (int32_t)short_value.data.short_value;

    short_value.type = INT_VALUE;

    current_frame->PushOperandStack(short_value);
    current_frame->pc += 1;
}
//! Essa função representa a função istore da JVM
void Interpreter::java_istore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    current_frame->ChangeLocalVariable(index, value);

    // cout << "ISTORE..." << current_frame->local_variables.size() << " : " << index << " : " << value.data.int_value << endl;
}
//! Essa função representa a função lstore da JVM
void Interpreter::java_lstore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->PopOperandStack();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    current_frame->ChangeLocalVariable(index, value);

    Value padding;
    padding.type = PADDING_VALUE;
    current_frame->ChangeLocalVariable(index + 1, padding);

    // cout << "LSTORE..." << current_frame->local_variables.size() << " : " << index << " : " << value.data.int_value << endl;
}
//! Essa função representa a função fstore da JVM
void Interpreter::java_fstore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    current_frame->ChangeLocalVariable(index, value);
}
//! Essa função representa a função dstore da JVM
void Interpreter::java_dstore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->PopOperandStack();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    current_frame->ChangeLocalVariable(index, value);
    Value padding;
    padding.type = PADDING_VALUE;
    current_frame->ChangeLocalVariable(index + 1, padding);

    // cout << "DSTORE..." << current_frame->local_variables.size() << " : " << index << " : " << value.data.int_value << endl;
}
//! Essa função representa a função astore da JVM
void Interpreter::java_astore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    int16_t index = (int16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
        current_frame->pc += 3;
        wide = false;
    }
    else
    {
        current_frame->pc += 2;
    }

    current_frame->ChangeLocalVariable(index, value);

    // cout << "ASTORE..." << current_frame->local_variables.size() << " : " << index << " : " << value.data.int_value << endl;
}
//! Essa função representa a função istore_0 da JVM
void Interpreter::java_istore_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(0, value);

    current_frame->pc += 1;
}
//! Essa função representa a função istore_1 da JVM
void Interpreter::java_istore_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(1, value);

    current_frame->pc += 1;
}
//! Essa função representa a função istore_2 da JVM
void Interpreter::java_istore_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(2, value);

    current_frame->pc += 1;
}
//! Essa função representa a função istore_3 da JVM
void Interpreter::java_istore_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(3, value);

    current_frame->pc += 1;
}
//! Essa função representa a função lstore_0 da JVM
void Interpreter::java_lstore_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(0, value);

    value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(1, value);

    current_frame->pc += 1;
}
//! Essa função representa a função lstore_1 da JVM
void Interpreter::java_lstore_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(1, value);

    value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(2, value);

    current_frame->pc += 1;
}
//! Essa função representa a função lstore_2 da JVM
void Interpreter::java_lstore_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(2, value);

    value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(3, value);

    current_frame->pc += 1;
}
//! Essa função representa a função lstore_3 da JVM
void Interpreter::java_lstore_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(3, value);

    value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(4, value);

    current_frame->pc += 1;
}
//! Essa função representa a função fstore_0 da JVM
void Interpreter::java_fstore_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(0, value);

    current_frame->pc += 1;
}
//! Essa função representa a função fstore_1 da JVM
void Interpreter::java_fstore_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(1, value);

    current_frame->pc += 1;
}
//! Essa função representa a função fstore_2 da JVM
void Interpreter::java_fstore_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(2, value);

    current_frame->pc += 1;
}
//! Essa função representa a função fstore_3 da JVM
void Interpreter::java_fstore_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(4, value);

    current_frame->pc += 1;
}
//! Essa função representa a função dstore_0 da JVM
void Interpreter::java_dstore_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(0, value);

    value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(1, value);

    current_frame->pc += 1;
}
//! Essa função representa a função dstore_1 da JVM
void Interpreter::java_dstore_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(1, value);

    value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(2, value);

    current_frame->pc += 1;
}
//! Essa função representa a função dstore_2 da JVM
void Interpreter::java_dstore_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(2, value);

    value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(3, value);

    current_frame->pc += 1;
}
//! Essa função representa a função dstore_3 da JVM
void Interpreter::java_dstore_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(3, value);

    value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(4, value);

    current_frame->pc += 1;
}
//! Essa função representa a função astore_0 da JVM
void Interpreter::java_astore_0()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(0, value);

    current_frame->pc += 1;
}
//! Essa função representa a função astore_1 da JVM
void Interpreter::java_astore_1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(1, value);

    current_frame->pc += 1;

    // cout << "ASTORE_1..." << current_frame->local_variables.size() << " : " << 1 << " : " << value.data.int_value << endl;
}
//! Essa função representa a função astore_2 da JVM
void Interpreter::java_astore_2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(2, value);

    current_frame->pc += 1;
}
//! Essa função representa a função astore_3 da JVM
void Interpreter::java_astore_3()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->ChangeLocalVariable(3, value);

    current_frame->pc += 1;
}
//! Essa função representa a função iastore da JVM
void Interpreter::java_iastore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value value = current_frame->PopOperandStack();

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    array->at(index.data.int_value) = value;

    current_frame->pc += 1;
}
//! Essa função representa a função lastore da JVM
void Interpreter::java_lastore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value value = current_frame->PopOperandStack();

    Value padding = current_frame->PopOperandStack();

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    array->at(index.data.int_value) = value;

    current_frame->pc += 1;
}
//! Essa função representa a função fastore da JVM
void Interpreter::java_fastore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value value = current_frame->PopOperandStack();

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    array->at(index.data.int_value) = value;

    current_frame->pc += 1;
}
//! Essa função representa a função dastore da JVM
void Interpreter::java_dastore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value value = current_frame->PopOperandStack();

    Value padding = current_frame->PopOperandStack();

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    array->at(index.data.int_value) = value;

    current_frame->pc += 1;
}
//! Essa função representa a função aastore da JVM
void Interpreter::java_aastore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value value = current_frame->PopOperandStack();

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    array->at(index.data.int_value) = value;

    current_frame->pc += 1;
}
//! Essa função representa a função bastore da JVM
void Interpreter::java_bastore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value value = current_frame->PopOperandStack();

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    for (unsigned i = 0; i < array->size(); i++)
    {
        if (array->at(i).type == BYTE_VALUE)
        {
            value.data.boolean_value = (value.data.int_value != 0) ? true : false;
            value.type = BYTE_VALUE;
        }
        else
        {
            value.data.byte_value = (uint8_t)value.data.int_value;
            value.type = BYTE_VALUE;
        }
    }

    array->at(index.data.int_value) = value;

    current_frame->pc += 1;
}
//! Essa função representa a função castore da JVM
void Interpreter::java_castore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value value = current_frame->PopOperandStack();

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    value.data.char_value = (uint8_t)value.data.int_value;

    value.type = CHAR_VALUE;
    array->at(index.data.int_value) = value;

    current_frame->pc += 1;
}
//! Essa função representa a função sastore da JVM
void Interpreter::java_sastore()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> *array;

    Value value = current_frame->PopOperandStack();

    Value index = current_frame->PopOperandStack();

    Value array_ref = current_frame->PopOperandStack();

    array = array_ref.data.array_value;

    value.data.short_value = (int16_t)value.data.int_value;

    value.type = SHORT_VALUE;
    array->at(index.data.int_value) = value;

    current_frame->pc += 1;
}
//! Essa função representa a função pop da JVM
void Interpreter::java_pop()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    Value value = current_frame->PopOperandStack();

    current_frame->pc += 1;
}
//! Essa função representa a função pop2 da JVM
void Interpreter::java_pop2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    current_frame->PopOperandStack();
    current_frame->PopOperandStack();

    current_frame->pc += 1;
}
//! Essa função representa a função dup da JVM
void Interpreter::java_dup()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    current_frame->PushOperandStack(value);
    current_frame->PushOperandStack(value);

    current_frame->pc += 1;
}
//! Essa função representa a função dup_x1 da JVM
void Interpreter::java_dup_x1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    Value value_2 = current_frame->PopOperandStack();

    current_frame->PushOperandStack(value_1);
    current_frame->PushOperandStack(value_2);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função dup_x2 da JVM
void Interpreter::java_dup_x2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();
    Value value_2 = current_frame->PopOperandStack();
    Value value_3 = current_frame->PopOperandStack();

    current_frame->PushOperandStack(value_1);
    current_frame->PushOperandStack(value_3);
    current_frame->PushOperandStack(value_2);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função dup2 da JVM
void Interpreter::java_dup2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();
    Value value_2 = current_frame->PopOperandStack();

    current_frame->PushOperandStack(value_2);
    current_frame->PushOperandStack(value_1);
    current_frame->PushOperandStack(value_2);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função dup2_x1 da JVM
void Interpreter::java_dup2_x1()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();
    Value value_2 = current_frame->PopOperandStack();
    Value value_3 = current_frame->PopOperandStack();

    current_frame->PushOperandStack(value_2);
    current_frame->PushOperandStack(value_1);
    current_frame->PushOperandStack(value_3);
    current_frame->PushOperandStack(value_2);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função dup2_x2 da JVM
void Interpreter::java_dup2_x2()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();
    Value value_2 = current_frame->PopOperandStack();
    Value value_3 = current_frame->PopOperandStack();
    Value value_4 = current_frame->PopOperandStack();

    current_frame->PushOperandStack(value_2);
    current_frame->PushOperandStack(value_1);
    current_frame->PushOperandStack(value_4);
    current_frame->PushOperandStack(value_3);
    current_frame->PushOperandStack(value_2);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função swap da JVM
void Interpreter::java_swap()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();
    Value value_2 = current_frame->PopOperandStack();

    current_frame->PushOperandStack(value_1);
    current_frame->PushOperandStack(value_2);

    current_frame->pc += 1;
}
//! Essa função representa a função iadd da JVM
void Interpreter::java_iadd()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = value_1.data.int_value + (value_2.data.int_value);

    // cout << "Resultado: " << value_1.data.int_value << endl;

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função ladd da JVM
void Interpreter::java_ladd()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.long_value = value_1.data.long_value + (value_2.data.long_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função fadd da JVM
void Interpreter::java_fadd()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.float_value = value_1.data.float_value + (value_2.data.float_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função dadd da JVM
void Interpreter::java_dadd()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.double_value = value_1.data.double_value + (value_2.data.double_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}

//! Essa função representa a função isub da JVM
void Interpreter::java_isub()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = value_1.data.int_value - (value_2.data.int_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lsub da JVM
void Interpreter::java_lsub()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.long_value = value_1.data.long_value - (value_2.data.long_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função fsub da JVM
void Interpreter::java_fsub()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.float_value = value_1.data.float_value - (value_2.data.float_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função dsub da JVM
void Interpreter::java_dsub()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.double_value = value_1.data.double_value - (value_2.data.double_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função imul da JVM
void Interpreter::java_imul()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = value_1.data.int_value * (value_2.data.int_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lmul da JVM
void Interpreter::java_lmul()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.long_value = value_1.data.long_value * (value_2.data.long_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função fmul da JVM
void Interpreter::java_fmul()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.float_value = value_1.data.float_value * (value_2.data.float_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função dmul da JVM
void Interpreter::java_dmul()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.double_value = value_1.data.double_value * (value_2.data.double_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função idiv da JVM
void Interpreter::java_idiv()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = value_1.data.int_value / (value_2.data.int_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função ldiv da JVM
void Interpreter::java_ldiv()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.long_value = value_1.data.long_value / (value_2.data.long_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função fdiv da JVM
void Interpreter::java_fdiv()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.float_value = value_1.data.float_value / (value_2.data.float_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função ddiv da JVM
void Interpreter::java_ddiv()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.double_value = value_1.data.double_value / (value_2.data.double_value);
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função irem da JVM
void Interpreter::java_irem()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = value_1.data.int_value - (value_1.data.int_value / value_2.data.int_value) * value_2.data.int_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lrem da JVM
void Interpreter::java_lrem()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.long_value = value_1.data.long_value - (value_1.data.long_value / value_2.data.long_value) * value_2.data.long_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função frem da JVM
void Interpreter::java_frem()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.float_value = value_1.data.float_value - ((uint32_t)(value_1.data.float_value / value_2.data.float_value)) * value_2.data.float_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função drem da JVM
void Interpreter::java_drem()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.double_value = value_1.data.double_value - ((uint64_t)(value_1.data.double_value / value_2.data.double_value)) * value_2.data.double_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função ineg da JVM
void Interpreter::java_ineg()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = -value_1.data.int_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lneg da JVM
void Interpreter::java_lneg()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    value_1.data.long_value = -value_1.data.long_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função fneg da JVM
void Interpreter::java_fneg()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    value_1.data.float_value = -value_1.data.float_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função dneg da JVM
void Interpreter::java_dneg()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.double_value = -value_1.data.double_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função ishl da JVM
void Interpreter::java_ishl()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_2.data.int_value = 0x1f & value_2.data.int_value;
    value_1.data.int_value = value_1.data.int_value << value_2.data.int_value;

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lshl da JVM
void Interpreter::java_lshl()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_2.data.long_value = 0x3f & value_2.data.long_value;
    value_1.data.long_value = (value_1.data.long_value) << value_2.data.int_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função ishr da JVM
void Interpreter::java_ishr()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_2.data.int_value = 0x1f & value_2.data.int_value;
    value_1.data.int_value = value_1.data.int_value >> value_2.data.int_value;

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lshr da JVM
void Interpreter::java_lshr()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_2.data.long_value = 0x3f & value_2.data.long_value;
    value_1.data.long_value = value_1.data.long_value >> value_2.data.long_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função iushr da JVM
void Interpreter::java_iushr()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_2.data.int_value = 0x1f & value_2.data.int_value;
    value_1.data.int_value = value_1.data.int_value >> value_2.data.int_value;
    if (value_1.data.int_value < 0)
    {
        value_1.data.int_value = value_1.data.int_value + (2 << ~(value_2.data.int_value));
    }

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lushr da JVM
void Interpreter::java_lushr()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_2.data.int_value = 0x3f & value_2.data.int_value;
    value_1.data.long_value = value_1.data.long_value >> value_2.data.int_value;
    if (value_1.data.long_value < 0)
    {
        value_1.data.long_value = value_1.data.long_value + ((int64_t)2 << ~(value_2.data.int_value));
    }
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função iand da JVM
void Interpreter::java_iand()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = value_1.data.int_value & value_2.data.int_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função land da JVM
void Interpreter::java_land()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.long_value = value_1.data.long_value & value_2.data.long_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função ior da JVM
void Interpreter::java_ior()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = value_1.data.int_value | value_2.data.int_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lor da JVM
void Interpreter::java_lor()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.long_value = value_1.data.long_value | value_2.data.long_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função ixor da JVM
void Interpreter::java_ixor()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = value_1.data.int_value ^ value_2.data.int_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lxor da JVM
void Interpreter::java_lxor()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.long_value = value_1.data.long_value ^ value_2.data.long_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função iinc da JVM
void Interpreter::java_iinc()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    u2 index = 0;
    if (wide)
    {
        index = (current_frame->code.code[current_frame->pc + 1] << 8) | current_frame->code.code[current_frame->pc + 2];
    }
    else
    {
        index += current_frame->code.code[current_frame->pc + 1];
    }

    Value localVariable = current_frame->GetLocalVariable(index);

    int32_t inc;
    if (wide)
    {
        uint16_t constant = (current_frame->code.code[current_frame->pc + 3] << 8) | current_frame->code.code[current_frame->pc + 4];
        inc = (int32_t)(int16_t)constant;
    }
    else
    {
        inc = (int32_t)(int8_t)current_frame->code.code[current_frame->pc + 2];
    }

    localVariable.data.int_value += inc;
    current_frame->ChangeLocalVariable(index, localVariable);

    current_frame->pc += wide ? 5 : 3;
    wide = false;
}
//! Essa função representa a função i2l da JVM
void Interpreter::java_i2l()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    Value padding;
    padding.type = PADDING_VALUE;

    current_frame->PushOperandStack(padding);

    value_1.data.long_value = (int64_t)value_1.data.int_value;
    value_1.type = LONG_VALUE;

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função i2f da JVM
void Interpreter::java_i2f()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    value_1.type = FLOAT_VALUE;
    value_1.data.float_value = (float)value_1.data.int_value;

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função i2d da JVM
void Interpreter::java_i2d()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    Value padding;
    padding.type = PADDING_VALUE;
    current_frame->PushOperandStack(padding);

    value_1.type = DOUBLE_VALUE;
    value_1.data.double_value = (double)value_1.data.int_value;

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função l2i da JVM
void Interpreter::java_l2i()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();

    value_1.data.int_value = (int32_t)value_1.data.long_value;
    value_1.type = INT_VALUE;

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função l2f da JVM
void Interpreter::java_l2f()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();

    value_1.data.float_value = (float)value_1.data.long_value;
    value_1.type = FLOAT_VALUE;

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função l2d da JVM
void Interpreter::java_l2d()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    Value value_1 = current_frame->PopOperandStack();

    value_1.type = DOUBLE_VALUE;
    value_1.data.double_value = (double)value_1.data.long_value;

    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função f2i da JVM
void Interpreter::java_f2i()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    value_1.type = INT_VALUE;
    value_1.data.int_value = (int32_t)value_1.data.float_value;

    current_frame->PushOperandStack(value_1);
    current_frame->pc += 1;
}
//! Essa função representa a função f2l da JVM
void Interpreter::java_f2l()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    Value padding;
    padding.type = PADDING_VALUE;
    current_frame->PushOperandStack(padding);

    value_1.type = LONG_VALUE;
    value_1.data.long_value = (uint64_t)value_1.data.float_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função f2d da JVM
void Interpreter::java_f2d()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    Value padding;
    padding.type = PADDING_VALUE;
    current_frame->PushOperandStack(padding);

    value_1.type = DOUBLE_VALUE;
    value_1.data.double_value = (double)value_1.data.float_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função d2i da JVM
void Interpreter::java_d2i()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();

    value_1.type = INT_VALUE;
    value_1.data.int_value = (int32_t)value_1.data.double_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função d2l da JVM
void Interpreter::java_d2l()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    value_1.type = LONG_VALUE;
    value_1.data.long_value = (int64_t)value_1.data.double_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função d2f da JVM
void Interpreter::java_d2f()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();

    value_1.type = FLOAT_VALUE;
    value_1.data.float_value = (float)value_1.data.double_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função i2b da JVM
void Interpreter::java_i2b()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = (int32_t)(int8_t)value_1.data.int_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função i2c da JVM
void Interpreter::java_i2c()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    Value value_1 = current_frame->PopOperandStack();

    value_1.data.char_value = (uint32_t)(uint8_t)value_1.data.int_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função i2s da JVM
void Interpreter::java_i2s()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_1 = current_frame->PopOperandStack();

    value_1.data.int_value = (int32_t)(int16_t)value_1.data.int_value;
    current_frame->PushOperandStack(value_1);

    current_frame->pc += 1;
}
//! Essa função representa a função lcmp da JVM
void Interpreter::java_lcmp()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value resultado;
    resultado.type = INT_VALUE;

    if (value_1.data.long_value > value_2.data.long_value)
    {
        resultado.data.int_value = 1;
    }
    else if (value_1.data.long_value == value_2.data.long_value)
    {
        resultado.data.int_value = 0;
    }
    else
    {
        resultado.data.int_value = -1;
    }

    current_frame->PushOperandStack(resultado);

    current_frame->pc += 1;
}
//! Essa função representa a função fcmpl da JVM
void Interpreter::java_fcmpl()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();
    Value resultado;
    resultado.type = INT_VALUE;

    if (isnan(value_1.data.float_value) || isnan(value_2.data.float_value))
    {
        resultado.data.int_value = -1;
    }
    else if (value_1.data.float_value > value_2.data.float_value)
    {
        resultado.data.int_value = 1;
    }
    else if (value_1.data.float_value == value_2.data.float_value)
    {
        resultado.data.int_value = 0;
    }
    else
    {
        resultado.data.int_value = -1;
    }

    current_frame->PushOperandStack(resultado);

    current_frame->pc += 1;
}
//! Essa função representa a função fcmpg da JVM
void Interpreter::java_fcmpg()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();
    Value resultado;
    resultado.type = INT_VALUE;

    if (isnan(value_1.data.float_value) || isnan(value_2.data.float_value))
    {
        resultado.data.int_value = 1;
    }
    else if (value_1.data.float_value > value_2.data.float_value)
    {
        resultado.data.int_value = 1;
    }
    else if (value_1.data.float_value == value_2.data.float_value)
    {
        resultado.data.int_value = 0;
    }
    else
    {
        resultado.data.int_value = -1;
    }

    current_frame->PushOperandStack(resultado);

    current_frame->pc += 1;
}
//! Essa função representa a função dcmpl da JVM
void Interpreter::java_dcmpl()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value resultado;
    resultado.type = INT_VALUE;

    if (isnan(value_1.data.double_value) || isnan(value_2.data.double_value))
    {
        resultado.data.int_value = -1;
    }
    else if (value_1.data.double_value > value_2.data.double_value)
    {
        resultado.data.int_value = 1;
    }
    else if (value_1.data.double_value == value_2.data.double_value)
    {
        resultado.data.int_value = 0;
    }
    else
    {
        resultado.data.int_value = -1;
    }

    current_frame->PushOperandStack(resultado);

    current_frame->pc += 1;
}
//! Essa função representa a função dcmpg da JVM
void Interpreter::java_dcmpg()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value_2 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value value_1 = current_frame->PopOperandStack();
    current_frame->PopOperandStack();
    Value resultado;
    resultado.type = INT_VALUE;

    if (isnan(value_1.data.double_value) || isnan(value_2.data.double_value))
    {
        resultado.data.int_value = 1;
    }
    else if (value_1.data.double_value > value_2.data.double_value)
    {
        resultado.data.int_value = 1;
    }
    else if (value_1.data.double_value == value_2.data.double_value)
    {
        resultado.data.int_value = 0;
    }
    else
    {
        resultado.data.int_value = -1;
    }

    current_frame->PushOperandStack(resultado);

    current_frame->pc += 1;
}
//! Essa função representa a função ifeq da JVM
void Interpreter::java_ifeq()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    if (value.data.int_value == 0)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função ifne da JVM
void Interpreter::java_ifne()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    if (value.data.int_value != 0)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função iflt da JVM
void Interpreter::java_iflt()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    if (value.data.int_value < 0)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função ifge da JVM
void Interpreter::java_ifge()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    if (value.data.int_value >= 0)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função ifgt da JVM
void Interpreter::java_ifgt()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    if (value.data.int_value > 0)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função ifle da JVM
void Interpreter::java_ifle()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value = current_frame->PopOperandStack();

    if (value.data.int_value <= 0)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função if_icmpeq da JVM
void Interpreter::java_if_icmpeq()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value2 = current_frame->PopOperandStack();
    Value value1 = current_frame->PopOperandStack();

    if (value1.data.int_value == value2.data.int_value)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função if_icmpne da JVM
void Interpreter::java_if_icmpne()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value2 = current_frame->PopOperandStack();
    Value value1 = current_frame->PopOperandStack();

    if (value1.data.int_value != value2.data.int_value)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função if_icmplt da JVM
void Interpreter::java_if_icmplt()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value2 = current_frame->PopOperandStack();
    Value value1 = current_frame->PopOperandStack();

    if (value1.data.int_value < value2.data.int_value)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função if_icmpge da JVM
void Interpreter::java_if_icmpge()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value2 = current_frame->PopOperandStack();
    Value value1 = current_frame->PopOperandStack();

    // cout << "Comparando... " << value2.data.int_value << " : " << value1.data.int_value << endl;

    if (value1.data.int_value >= value2.data.int_value)
    {
        u1 byte1 = current_frame->code.code[current_frame->pc + 1];

        u1 byte2 = current_frame->code.code[current_frame->pc + 2];

        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função if_icmpgt da JVM
void Interpreter::java_if_icmpgt()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value2 = current_frame->PopOperandStack();
    Value value1 = current_frame->PopOperandStack();

    if (value1.data.int_value > value2.data.int_value)
    {
        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função if_icmple da JVM
void Interpreter::java_if_icmple()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value2 = current_frame->PopOperandStack();
    Value value1 = current_frame->PopOperandStack();

    if (value1.data.int_value <= value2.data.int_value)
    {
        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função if_acmpeq da JVM
void Interpreter::java_if_acmpeq()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value2 = current_frame->PopOperandStack();
    Value value1 = current_frame->PopOperandStack();

    if (value1.data.object_value == value2.data.object_value)
    {

        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função if_acmpne da JVM
void Interpreter::java_if_acmpne()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value value2 = current_frame->PopOperandStack();
    Value value1 = current_frame->PopOperandStack();

    if (value1.data.object_value != value2.data.object_value)
    {
        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch_offset = (byte1 << 8) | byte2;
        current_frame->pc += branch_offset;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função goto da JVM
void Interpreter::java_goto()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];
    int16_t branch_offset = (byte1 << 8) | byte2;
    current_frame->pc += branch_offset;
}
//! Essa função representa a função jsr da JVM
void Interpreter::java_jsr()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];
    int16_t branch_offset = (byte1 << 8) | byte2;

    Value value;
    value.type = RETURN_VALUE;
    value.data.return_address = current_frame->pc + 3;
    current_frame->PushOperandStack(value);

    current_frame->pc += branch_offset;
}

// Pode ser modifica//! Essa função representa a função ret da JVMdo pelo wide
void Interpreter::java_ret()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    uint16_t index = (uint16_t)byte1;

    if (wide)
    {
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        index = (byte1 << 8) | byte2;
    }

    Value value = current_frame->GetLocalVariable(index);

    current_frame->ChangeLocalVariable(index, value);

    current_frame->pc = value.data.return_address;
    wide = false;
}
//! Essa função representa a função tableswitch da JVM
void Interpreter::java_tableswitch()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 padding = 4 - (current_frame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;

    u1 default_byte1 = current_frame->code.code[current_frame->pc + padding + 1];
    u1 default_byte2 = current_frame->code.code[current_frame->pc + padding + 2];
    u1 default_byte3 = current_frame->code.code[current_frame->pc + padding + 3];
    u1 default_byte4 = current_frame->code.code[current_frame->pc + padding + 4];
    int32_t default_bytes = (default_byte1 << 24) | (default_byte2 << 16) | (default_byte3 << 8) | default_byte4;

    u1 lowbyte1 = current_frame->code.code[current_frame->pc + padding + 5];
    u1 lowbyte2 = current_frame->code.code[current_frame->pc + padding + 6];
    u1 lowbyte3 = current_frame->code.code[current_frame->pc + padding + 7];
    u1 lowbyte4 = current_frame->code.code[current_frame->pc + padding + 8];
    uint32_t lowbytes = (lowbyte1 << 24) | (lowbyte2 << 16) | (lowbyte3 << 8) | lowbyte4;

    u1 highbyte1 = current_frame->code.code[current_frame->pc + padding + 9];
    u1 highbyte2 = current_frame->code.code[current_frame->pc + padding + 10];
    u1 highbyte3 = current_frame->code.code[current_frame->pc + padding + 11];
    u1 highbyte4 = current_frame->code.code[current_frame->pc + padding + 12];
    uint32_t highbytes = (highbyte1 << 24) | (highbyte2 << 16) | (highbyte3 << 8) | highbyte4;

    Value key_value = current_frame->PopOperandStack();

    int32_t key = key_value.data.int_value;

    uint32_t i;
    uint32_t baseIndex = padding + 13;
    int32_t offsets = highbytes - lowbytes + 1;
    bool matched = false;
    for (i = 0; i < offsets; i++)
    {
        if (key == lowbytes)
        {
            int32_t offset = (current_frame->code.code[current_frame->pc + baseIndex] << 24) | (current_frame->code.code[current_frame->pc + baseIndex + 1] << 16) | (current_frame->code.code[current_frame->pc + baseIndex + 2] << 8) | current_frame->code.code[current_frame->pc + baseIndex + 3];
            current_frame->pc += offset;
            matched = true;
            break;
        }
        lowbytes++;
        baseIndex += 4;
    }

    if (!matched)
    {
        current_frame->pc += default_bytes;
    }
}
//! Essa função representa a função lookupswitch da JVM
void Interpreter::java_lookupswitch()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 *code = current_frame->code.code;
    u1 padding = 4 - (current_frame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;

    u1 defaultbyte1 = code[current_frame->pc + padding + 1];
    u1 defaultbyte2 = code[current_frame->pc + padding + 2];
    u1 defaultbyte3 = code[current_frame->pc + padding + 3];
    u1 defaultbyte4 = code[current_frame->pc + padding + 4];
    int32_t default_bytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;

    u1 npairs1 = code[current_frame->pc + padding + 5];
    u1 npairs2 = code[current_frame->pc + padding + 6];
    u1 npairs3 = code[current_frame->pc + padding + 7];
    u1 npairs4 = code[current_frame->pc + padding + 8];
    uint32_t npairs = (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;

    Value keyValue = current_frame->PopOperandStack();

    int32_t key = keyValue.data.int_value;

    // cout << "Lookupswitch KEY: " << key << endl;

    uint32_t i;
    uint32_t baseIndex = padding + 9;
    bool matched = false;
    for (i = 0; i < npairs; i++)
    {
        int32_t match = (code[current_frame->pc + baseIndex] << 24) | (code[current_frame->pc + baseIndex + 1] << 16) | (code[current_frame->pc + baseIndex + 2] << 8) | code[current_frame->pc + baseIndex + 3];

        if (key == match)
        {
            int32_t offset = (code[current_frame->pc + baseIndex + 4] << 24) | (code[current_frame->pc + baseIndex + 5] << 16) | (code[current_frame->pc + baseIndex + 6] << 8) | code[current_frame->pc + baseIndex + 7];

            // cout << "Lookupswitch offset: " << offset << endl;
            current_frame->pc += offset;
            matched = true;
            break;
        }
        baseIndex += 8;
    }

    if (!matched)
    {
        // cout << "Lookupswitch matched: " << default_bytes << endl;
        current_frame->pc += default_bytes;
    }
}
//! Essa função representa a função ireturn da JVM
void Interpreter::java_ireturn()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value returnValue = current_frame->PopOperandStack();

    this->runtime->PopFrame();

    Frame *newTopFrame = this->runtime->GetCurrentFrame();

    // cout << "Resultado: " << returnValue.data.int_value << endl;

    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função lreturn da JVM
void Interpreter::java_lreturn()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value returnValue = current_frame->PopOperandStack();

    this->runtime->PopFrame();

    Frame *newTopFrame = this->runtime->GetCurrentFrame();
    Value padding;
    padding.type = PADDING_VALUE;
    newTopFrame->PushOperandStack(padding);
    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função freturn da JVM
void Interpreter::java_freturn()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value returnValue = current_frame->PopOperandStack();

    this->runtime->PopFrame();

    Frame *newTopFrame = this->runtime->GetCurrentFrame();
    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função dreturn da JVM
void Interpreter::java_dreturn()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value returnValue = current_frame->PopOperandStack();

    this->runtime->PopFrame();

    Frame *newTopFrame = this->runtime->GetCurrentFrame();

    Value padding;
    padding.type = PADDING_VALUE;
    newTopFrame->PushOperandStack(padding);
    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função areturn da JVM
void Interpreter::java_areturn()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value returnValue = current_frame->PopOperandStack();

    this->runtime->PopFrame();

    Frame *newTopFrame = this->runtime->GetCurrentFrame();
    newTopFrame->PushOperandStack(returnValue);
}
//! Essa função representa a função return da JVM
void Interpreter::java_return()
{

    this->runtime->PopFrame();
}
//! Essa função representa a função getstatic da JVM
void Interpreter::java_getstatic()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();
    vector<CpInfo *> constant_pool = (current_frame->constant_pool);

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t field_index = (byte1 << 8) | byte2;
    CpInfo *field_cp = constant_pool[field_index - 1];

    CONSTANT_Fieldref_info field_ref = field_cp->info.Fieldref;

    string class_name = ReadFile::readString(field_ref.class_index, constant_pool);

    CpInfo *name_and_type_cp = constant_pool[field_ref.name_and_type_index - 1];

    CONSTANT_NameAndType_info field_name_and_type = name_and_type_cp->info.NameAndType;

    string field_name = ReadFile::readString(field_name_and_type.name_index, constant_pool);
    string field_descriptor = ReadFile::readString(field_name_and_type.descriptor_index, constant_pool);

    // caso especial
    if (class_name == "java/lang/System" && field_descriptor == "Ljava/io/PrintStream;")
    {
        current_frame->pc += 3;
        return;
    }
    // fim do caso especial
    map<string, MethodAreaSection *> method_area = this->runtime->method_area;
    MethodAreaSection *area = method_area[class_name];

    while (area != NULL)
    {
        if (area->static_fields.count(field_name) == 0)
        {
            if (area->class_file->super_class == 0)
            {
                area = NULL;
            }
            else
            {
                string super_class_name = ReadFile::readString(area->class_file->super_class, area->class_file->constant_pool);
                if (method_area.count(super_class_name) > 0)
                    area = method_area[super_class_name];
                else
                {
                    ClassLoaderSubsystem::Resolve(super_class_name, this->runtime);
                    area = method_area[super_class_name];
                }
            }
        }
        else
        {
            break;
        }
    }

    if (this->runtime->GetCurrentFrame() != current_frame)
        return;

    Value staticValue = area->static_fields[field_name];
    switch (staticValue.type)
    {
    case BOOLEAN_VALUE:
        staticValue.type = INT_VALUE;
        break;
    case BYTE_VALUE:
        staticValue.type = INT_VALUE;
        break;
    case SHORT_VALUE:
        staticValue.type = INT_VALUE;
        break;
    case INT_VALUE:
        staticValue.type = INT_VALUE;
        break;
    default:
        break;
    }

    if (staticValue.type == DOUBLE_VALUE || staticValue.type == LONG_VALUE)
    {
        Value padding_value;
        padding_value.type = PADDING_VALUE;
        current_frame->PushOperandStack(padding_value);
    }

    current_frame->PushOperandStack(staticValue);

    current_frame->pc += 3;
}
//! Essa função representa a função putstatic da JVM
void Interpreter::java_putstatic()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t field_index = (byte1 << 8) | byte2;
    CpInfo *field_cp = constant_pool[field_index - 1];

    CONSTANT_Fieldref_info field_ref = field_cp->info.Fieldref;

    string class_name = ReadFile::readString(field_ref.class_index, constant_pool);

    CpInfo *name_and_type_cp = constant_pool[field_ref.name_and_type_index - 1];

    CONSTANT_NameAndType_info field_name_and_type = name_and_type_cp->info.NameAndType;

    string field_name = ReadFile::readString(field_name_and_type.name_index, constant_pool);
    string field_descriptor = ReadFile::readString(field_name_and_type.descriptor_index, constant_pool);

    map<string, MethodAreaSection *> method_area = this->runtime->method_area;
    MethodAreaSection *area = method_area[class_name];

    while (area != NULL)
    {
        if (area->static_fields.count(field_name) == 0)
        {
            if (area->class_file->super_class == 0)
            {
                area = NULL;
            }
            else
            {
                string super_class_name = ReadFile::readString(area->class_file->super_class, area->class_file->constant_pool);
                if (method_area.count(super_class_name) > 0)
                    area = method_area[super_class_name];
                else
                {
                    ClassLoaderSubsystem::Resolve(super_class_name, this->runtime);
                    area = method_area[super_class_name];
                }
            }
        }
        else
        {
            break;
        }
    }

    if (this->runtime->GetCurrentFrame() != current_frame)
        return;

    Value topValue = current_frame->PopOperandStack();
    if (topValue.type == DOUBLE_VALUE || topValue.type == LONG_VALUE)
    {
        current_frame->PopOperandStack();
    }
    else
    {
        switch (field_descriptor[0])
        {
        case 'B':
            topValue.type = BYTE_VALUE;
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

    // cout << "PUTSTATIC: " << field_name << " : " << (int) topValue.type << endl;
    area->static_fields[field_name] = topValue;

    current_frame->pc += 3;
}
//! Essa função representa a função getfield da JVM
void Interpreter::java_getfield()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();
    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t field_index = (byte1 << 8) | byte2;
    CpInfo *field_cp = constant_pool[field_index - 1];

    CONSTANT_Fieldref_info field_ref = field_cp->info.Fieldref;

    string class_name = ReadFile::readString(field_ref.class_index, constant_pool);

    CpInfo *name_and_type_cp = constant_pool[field_ref.name_and_type_index - 1];

    CONSTANT_NameAndType_info field_name_and_type = name_and_type_cp->info.NameAndType;

    string field_name = ReadFile::readString(field_name_and_type.name_index, constant_pool);
    string field_descriptor = ReadFile::readString(field_name_and_type.descriptor_index, constant_pool);

    Value object_value = current_frame->PopOperandStack();

    ObjectRef *object = object_value.data.object_value;

    Value field_value = object->GetVariable(field_name);
    switch (field_value.type)
    {
    case BYTE_VALUE:
        field_value.type = INT_VALUE;
        break;
    case CHAR_VALUE:
        field_value.type = INT_VALUE;
        break;
    case SHORT_VALUE:
        field_value.type = INT_VALUE;
        break;
    case INT_VALUE:
        field_value.type = INT_VALUE;
        break;
    default:
        break;
    }

    if (field_value.type == DOUBLE_VALUE || field_value.type == LONG_VALUE)
    {
        Value padding_value;
        padding_value.type = PADDING_VALUE;
        current_frame->PushOperandStack(padding_value);
    }

    current_frame->PushOperandStack(field_value);

    current_frame->pc += 3;
}
//! Essa função representa a função putfield da JVM
void Interpreter::java_putfield()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t field_index = (byte1 << 8) | byte2;
    CpInfo *field_cp = constant_pool[field_index - 1];

    CONSTANT_Fieldref_info field_ref = field_cp->info.Fieldref;

    string class_name = ReadFile::readString(field_ref.class_index, constant_pool);

    CpInfo *name_and_type_cp = constant_pool[field_ref.name_and_type_index - 1];

    CONSTANT_NameAndType_info field_name_and_type = name_and_type_cp->info.NameAndType;

    string field_name = ReadFile::readString(field_name_and_type.name_index, constant_pool);
    string field_descriptor = ReadFile::readString(field_name_and_type.descriptor_index, constant_pool);
    // cout << "PUTFIELD 4" << endl;
    Value value_insert = current_frame->PopOperandStack();
    if (value_insert.type == DOUBLE_VALUE || value_insert.type == LONG_VALUE)
    {
        current_frame->PopOperandStack();
    }
    else
    {
        switch (field_descriptor[0])
        {
        case 'B':
            value_insert.type = BYTE_VALUE;
            break;
        case 'C':
            value_insert.type = CHAR_VALUE;
            break;
        case 'S':
            value_insert.type = SHORT_VALUE;
            break;
        case 'Z':
            value_insert.type = BYTE_VALUE;
            break;
        }
    }

    Value object_value = current_frame->PopOperandStack();

    ObjectRef *object = object_value.data.object_value;

    object->ChangeVariable(field_name, value_insert);

    current_frame->pc += 3;
}
//! Essa função representa a função invokevirtual da JVM
void Interpreter::java_invokevirtual()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> save_operand_stack = current_frame->operand_stack;

    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    CpInfo *methodCP = constant_pool[methodIndex - 1];

    CONSTANT_Methodref_info methodInfo = methodCP->info.Methodref;

    string class_name = ReadFile::readString(methodInfo.class_index, constant_pool);

    CpInfo *name_and_type_cp = constant_pool[methodInfo.name_and_type_index - 1];

    CONSTANT_NameAndType_info method_name_and_type = name_and_type_cp->info.NameAndType;

    string method_name = ReadFile::readString(method_name_and_type.name_index, constant_pool);
    string method_descriptor = ReadFile::readString(method_name_and_type.descriptor_index, constant_pool);

    if (class_name.find("java/") != string::npos)
    {
        if (class_name == "java/io/PrintStream" && (method_name == "print" || method_name == "println"))
        {
            if (method_descriptor != "()V")
            {
                Value print_value = current_frame->PopOperandStack();
                switch (print_value.type)
                {
                case DOUBLE_VALUE:
                    current_frame->PopOperandStack();
                    printf("%f", print_value.data.double_value);
                    break;
                case FLOAT_VALUE:
                    printf("%f", print_value.data.float_value);
                    break;
                case LONG_VALUE:
                    current_frame->PopOperandStack();
                    printf("%ld", print_value.data.long_value);
                    break;
                case STRING_VALUE:

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
                case INT_VALUE:
                    printf("%d", print_value.data.int_value);
                    break;
                default:
                    cerr << "Tentando printar tipo de dado invalido: " << (int)print_value.type << endl;
                    exit(1);
                    break;
                }
            }

            if (method_name == "println")
                printf("\n");
        }
        else if (class_name == "java/lang/String" && method_name == "equals")
        {
            Value str_value1 = current_frame->PopOperandStack();
            Value strValue2 = current_frame->PopOperandStack();

            string *str1 = str_value1.data.string_value;
            string *str2 = strValue2.data.string_value;

            Value result;
            result.type = INT_VALUE;
            if (str1->c_str() == str2->c_str())
            {
                result.data.int_value = 1;
            }
            else
            {
                result.data.int_value = 0;
            }
            current_frame->PushOperandStack(result);
        }
        else if (class_name == "java/lang/String" && method_name == "length")
        {
            Value strValue = current_frame->PopOperandStack();

            string *str = strValue.data.string_value;

            Value result;
            result.type = INT_VALUE;
            result.data.int_value = str->size();
            current_frame->PushOperandStack(result);
        }
        else
        {
            cerr << "Tentando invocar metodo de instancia invalido: " << method_name << endl;
            exit(1);
        }
    }
    else
    {
        uint16_t nargs = 0;
        uint16_t i = 1;
        while (method_descriptor[i] != ')')
        {
            char baseType = method_descriptor[i];
            if (baseType == 'D' || baseType == 'J')
            {
                nargs += 2;
            }
            else if (baseType == 'L')
            {
                nargs++;
                while (method_descriptor[++i] != ';')
                    ;
            }
            else if (baseType == '[')
            {
                nargs++;
                while (method_descriptor[++i] == '[')
                    ;
                if (method_descriptor[i] == 'L')
                    while (method_descriptor[++i] != ';')
                        ;
            }
            else
            {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++)
        {
            Value value = current_frame->PopOperandStack();
            if (value.type == PADDING_VALUE)
            {
                args.insert(args.begin() + 1, value);
            }
            else
            {
                args.insert(args.begin(), value);
            }
        }

        Value object_value = current_frame->PopOperandStack();

        args.insert(args.begin(), object_value);

        // ObjectRef *object = object_value.data.object_value;

        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[class_name];

        // cout << "Invokando Method: " << method_name << " : " << method_descriptor << endl;
        this->runtime->InitializeFrame(method_name, method_descriptor, area->class_file, args);

        if (this->runtime->stack[this->runtime->stack.size() - 2] != current_frame)
        {
            current_frame->operand_stack = save_operand_stack;
            delete this->runtime->GetCurrentFrame();
            this->runtime->PopFrame();
            return;
        }
    }

    current_frame->pc += 3;
}
//! Essa função representa a função invokespecial da JVM
void Interpreter::java_invokespecial()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> save_operand_stack = current_frame->operand_stack;

    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    CpInfo *methodCP = constant_pool[methodIndex - 1];

    CONSTANT_Methodref_info methodInfo = methodCP->info.Methodref;

    string class_name = ReadFile::readString(methodInfo.class_index, constant_pool);

    CpInfo *name_and_type_cp = constant_pool[methodInfo.name_and_type_index - 1];

    CONSTANT_NameAndType_info method_name_and_type = name_and_type_cp->info.NameAndType;

    string method_name = ReadFile::readString(method_name_and_type.name_index, constant_pool);
    string method_descriptor = ReadFile::readString(method_name_and_type.descriptor_index, constant_pool);

    if ((class_name == "java/lang/Object" || class_name == "java/lang/String") && method_name == "<init>")
    {
        if (class_name == "java/lang/String")
        {
            current_frame->PopOperandStack();
        }

        current_frame->pc += 3;
        return;
    }

    if (class_name.find("java/") != string::npos)
    {
        cerr << "Tentando invocar metodo especial invalido: " << method_name << endl;
        exit(1);
    }
    else
    {
        uint16_t nargs = 0;
        uint16_t i = 1;
        while (method_descriptor[i] != ')')
        {
            char baseType = method_descriptor[i];
            if (baseType == 'D' || baseType == 'J')
            {
                nargs += 2;
            }
            else if (baseType == 'L')
            {
                nargs++;
                while (method_descriptor[++i] != ';')
                    ;
            }
            else if (baseType == '[')
            {
                nargs++;
                while (method_descriptor[++i] == '[')
                    ;
                if (method_descriptor[i] == 'L')
                    while (method_descriptor[++i] != ';')
                        ;
            }
            else
            {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++)
        {
            Value value = current_frame->PopOperandStack();
            if (value.type == PADDING_VALUE)
            {
                args.insert(args.begin() + 1, value);
            }
            else
            {
                args.insert(args.begin(), value);
            }
        }

        Value object_value = current_frame->PopOperandStack();

        args.insert(args.begin(), object_value);

        // ObjectRef *object = object_value.data.object_value;

        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[class_name];

        // cout << "Invokando Method: " << method_name << " : " << method_descriptor << endl;
        this->runtime->InitializeFrame(method_name, method_descriptor, area->class_file, args);

        if (this->runtime->stack[this->runtime->stack.size() - 2] != current_frame)
        {
            current_frame->operand_stack = save_operand_stack;
            delete this->runtime->GetCurrentFrame();
            this->runtime->PopFrame();
            return;
        }

        // this->runtime->PushFrame(newFrame);
    }

    current_frame->pc += 3;
}
//! Essa função representa a função invokestatic da JVM
void Interpreter::java_invokestatic()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> save_operand_stack = current_frame->operand_stack;

    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    CpInfo *methodCP = constant_pool[methodIndex - 1];

    CONSTANT_Methodref_info methodInfo = methodCP->info.Methodref;

    string class_name = ReadFile::readString(methodInfo.class_index, constant_pool);

    CpInfo *name_and_type_cp = constant_pool[methodInfo.name_and_type_index - 1];

    CONSTANT_NameAndType_info method_name_and_type = name_and_type_cp->info.NameAndType;

    string method_name = ReadFile::readString(method_name_and_type.name_index, constant_pool);
    string method_descriptor = ReadFile::readString(method_name_and_type.descriptor_index, constant_pool);

    if (class_name == "java/lang/Object" && method_name == "registerNatives")
    {
        current_frame->pc += 3;
        return;
    }

    if (class_name.find("java/") != string::npos)
    {
        cerr << "Tentando invocar metodo estatico invalido: " << method_name << endl;
        exit(1);
    }
    else
    {
        uint16_t nargs = 0;
        uint16_t i = 1;
        while (method_descriptor[i] != ')')
        {
            char baseType = method_descriptor[i];
            if (baseType == 'D' || baseType == 'J')
            {
                nargs += 2;
            }
            else if (baseType == 'L')
            {
                nargs++;
                while (method_descriptor[++i] != ';')
                    ;
            }
            else if (baseType == '[')
            {
                nargs++;
                while (method_descriptor[++i] == '[')
                    ;
                if (method_descriptor[i] == 'L')
                    while (method_descriptor[++i] != ';')
                        ;
            }
            else
            {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++)
        {
            Value value = current_frame->PopOperandStack();
            if (value.type == PADDING_VALUE)
            {
                args.insert(args.begin() + 1, value);
            }
            else
            {
                args.insert(args.begin(), value);
            }
        }

        ClassLoaderSubsystem::Resolve(class_name, this->runtime);

        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[class_name];

        // cout << "Invokando Method: " << method_name << " : " << method_descriptor << endl;
        this->runtime->InitializeFrame(method_name, method_descriptor, area->class_file, args);

        // cout << "STATIC AQUI " << endl;
        // AttributeInfo attr_code;
        // MethodInfo *method = area->class_file->getMethodByName(method_name);
        // method->getAttributeByName("Code", area->class_file->constant_pool, attr_code);

        if (this->runtime->stack[this->runtime->stack.size() - 2] != current_frame)
        {
            current_frame->operand_stack = save_operand_stack;
            // delete this->runtime->GetCurrentFrame();
            this->runtime->PopFrame();
            return;
        }

        // cout << "ADICIONOU" << endl;
        // this->runtime->PushFrame(newFrame);
    }

    current_frame->pc += 3;
}
//! Essa função representa a função invokeinterface da JVM
void Interpreter::java_invokeinterface()
{

    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<Value> save_operand_stack = current_frame->operand_stack;

    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    CpInfo *methodCP = constant_pool[methodIndex - 1];

    CONSTANT_Methodref_info methodInfo = methodCP->info.Methodref;

    string class_name = ReadFile::readString(methodInfo.class_index, constant_pool);

    CpInfo *name_and_type_cp = constant_pool[methodInfo.name_and_type_index - 1];

    CONSTANT_NameAndType_info method_name_and_type = name_and_type_cp->info.NameAndType;

    string method_name = ReadFile::readString(method_name_and_type.name_index, constant_pool);
    string method_descriptor = ReadFile::readString(method_name_and_type.descriptor_index, constant_pool);

    if (class_name.find("java/") != string::npos)
    {
        cerr << "Tentando invocar metodo de interface invalido: " << method_name << endl;
        exit(1);
    }
    else
    {
        uint16_t nargs = 0;
        uint16_t i = 1;
        while (method_descriptor[i] != ')')
        {
            char baseType = method_descriptor[i];
            if (baseType == 'D' || baseType == 'J')
            {
                nargs += 2;
            }
            else if (baseType == 'L')
            {
                nargs++;
                while (method_descriptor[++i] != ';')
                    ;
            }
            else if (baseType == '[')
            {
                nargs++;
                while (method_descriptor[++i] == '[')
                    ;
                if (method_descriptor[i] == 'L')
                    while (method_descriptor[++i] != ';')
                        ;
            }
            else
            {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++)
        {
            Value value = current_frame->PopOperandStack();
            if (value.type == PADDING_VALUE)
            {
                args.insert(args.begin() + 1, value);
            }
            else
            {
                args.insert(args.begin(), value);
            }
        }

        Value object_value = current_frame->PopOperandStack();

        args.insert(args.begin(), object_value);

        // ObjectRef *object = object_value.data.object_value;

        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[class_name];

        // cout << "Invokando Method: " << method_name << " : " << method_descriptor << endl;
        this->runtime->InitializeFrame(method_name, method_descriptor, area->class_file, args);

        if (this->runtime->stack[this->runtime->stack.size() - 2] != current_frame)
        {
            current_frame->operand_stack = save_operand_stack;
            delete this->runtime->GetCurrentFrame();
            this->runtime->PopFrame();
            return;
        }
    }

    current_frame->pc += 5;
}
//! Essa função representa a função new da JVM
void Interpreter::java_new()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t classIndex = (byte1 << 8) | byte2;
    CpInfo *class_cp = constant_pool[classIndex - 1];

    CONSTANT_Class_info class_info = class_cp->info.Class;
    string class_name = ReadFile::readString(class_info.name_index, constant_pool);

    Value value_ref;
    if (class_name == "java/lang/String" || class_name == "java/lang/StringBuffer")
    {
        string *object = new string("");
        value_ref.data.string_value = object;
        value_ref.type = STRING_VALUE;
        MemoryManager::variables_allocated.push_back(value_ref);
    }
    else
    {
        ClassLoaderSubsystem::Resolve(class_name, this->runtime);
        ObjectRef *objectref;
        map<string, MethodAreaSection *> method_area = this->runtime->method_area;
        MethodAreaSection *area = method_area[class_name];

        objectref = new ObjectRef(area->class_file);
        value_ref.data.object_value = objectref;
        value_ref.type = OBJECT_VALUE;
        MemoryManager::variables_allocated.push_back(value_ref);
    }

    current_frame->PushOperandStack(value_ref);

    current_frame->pc += 3;
}
//! Essa função representa a função newarray da JVM
void Interpreter::java_newarray()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value count = current_frame->PopOperandStack();

    vector<Value> *array = new vector<Value>;
    Value value;
    value.data.long_value = 0;

    MemoryManager::variables_allocated.push_back(value);

    Value padding;
    padding.type = PADDING_VALUE;

    switch (current_frame->code.code[current_frame->pc + 1])
    {
    case 4:

        value.type = BYTE_VALUE;
        for (int i = 0; i < count.data.int_value; i++)
        {
            array->push_back(value);
        }
        break;
    case 5:
        value.type = CHAR_VALUE;
        for (int i = 0; i < count.data.int_value; i++)
        {
            array->push_back(value);
        }
        break;
    case 6:
        value.type = FLOAT_VALUE;
        for (int i = 0; i < count.data.int_value; i++)
        {
            array->push_back(value);
        }
        break;
    case 7:
        value.type = DOUBLE_VALUE;
        for (int i = 0; i < count.data.int_value; i++)
        {
            array->push_back(value);
        }
        break;
    case 8:
        value.type = BYTE_VALUE;
        for (int i = 0; i < count.data.int_value; i++)
        {
            array->push_back(value);
        }
        break;
    case 9:
        value.type = SHORT_VALUE;
        for (int i = 0; i < count.data.int_value; i++)
        {
            array->push_back(value);
        }
        break;
    case 10:
        value.type = INT_VALUE;
        for (int i = 0; i < count.data.int_value; i++)
        {
            array->push_back(value);
        }
        break;
    case 11:
        value.type = LONG_VALUE;
        for (int i = 0; i < count.data.int_value; i++)
        {
            array->push_back(value);
        }
        break;
    }

    Value array_ref;
    array_ref.type = ARRAY_VALUE;
    array_ref.data.array_value = array;

    current_frame->PushOperandStack(array_ref);
    current_frame->pc += 2;
}
//! Essa função representa a função anewarray da JVM
void Interpreter::java_anewarray()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value count = current_frame->PopOperandStack();

    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    uint16_t classIndex = (byte1 << 8) | byte2;
    CpInfo *class_cp = constant_pool[classIndex - 1];

    CONSTANT_Class_info class_info = class_cp->info.Class;
    string class_name = ReadFile::readString(class_info.name_index, constant_pool);

    if (class_name != "java/lang/String")
    {
        int i = 0;
        while (class_name[i] == '[')
            i++;
        if (class_name[i] == 'L')
        {
            // map<string, MethodAreaSection *> method_area = this->runtime->method_area;
            ClassLoaderSubsystem::Resolve(class_name, this->runtime);
        }
    }

    Value array_ref;
    array_ref.type = ARRAY_VALUE;
    array_ref.data.array_value = new vector<Value>();
    MemoryManager::variables_allocated.push_back(array_ref);

    Value null_value;
    null_value.type = OBJECT_VALUE;
    null_value.data.object_value = NULL;
    for (int i = 0; i < count.data.int_value; i++)
    {
        array_ref.data.array_value->push_back(null_value);
    }

    current_frame->PushOperandStack(array_ref);

    current_frame->pc += 3;
}
//! Essa função representa a função arraylength da JVM
void Interpreter::java_arraylength()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value array_ref = current_frame->PopOperandStack();

    Value length;
    length.type = INT_VALUE;
    length.data.int_value = array_ref.data.array_value->size();

    current_frame->PushOperandStack(length);
    current_frame->pc += 1;
}
//! Essa função representa a função athrow da JVM
void Interpreter::java_athrow()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    current_frame->pc += 1;
}
//! Essa função representa a função checkcast da JVM
void Interpreter::java_checkcast()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    u2 cp_index = (byte1 << 8) | byte2;
    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    string class_name = ReadFile::readString(cp_index, constant_pool);

    Value objectref_value = current_frame->PopOperandStack();

    Value result_value;
    result_value.type = INT_VALUE;

    map<string, MethodAreaSection *> method_area = this->runtime->method_area;

    if (objectref_value.type == OBJECT_VALUE && objectref_value.data.object_value != NULL)
    {
        ObjectRef *object = objectref_value.data.object_value;
        ClassFile *class_file = object->class_file;

        bool found = false;
        while (!found)
        {
            string c_class_name = ReadFile::readString(class_file->this_class, class_file->constant_pool);

            if (c_class_name == class_name)
            {
                found = true;
            }
            else
            {
                if (class_file->super_class == 0)
                {
                    break;
                }
                else
                {
                    string super_class_name = ReadFile::readString(class_file->this_class, class_file->constant_pool);
                    MethodAreaSection *super_area;
                    if (method_area.count(super_class_name) != 0)
                    {
                        super_area = method_area[super_class_name];
                    }
                    else
                    {
                        ClassLoaderSubsystem::Resolve(super_class_name, this->runtime);
                        super_area = method_area[super_class_name];
                    }

                    class_file = super_area->class_file;
                }
            }
        }

        result_value.data.int_value = found ? 1 : 0;
    }
    else if (objectref_value.type == STRING_VALUE && objectref_value.data.string_value != NULL)
    {
        result_value.data.int_value = (class_name == "java/lang/String" || class_name == "java/lang/Object") ? 1 : 0;
    }
    else
    {
        if (class_name == "java/lang/Object")
        {
            result_value.data.int_value = 1;
        }
        else
        {
            result_value.data.int_value = 0;
        }
    }

    current_frame->PushOperandStack(result_value);

    current_frame->pc += 3;
}
//! Essa função representa a função instanceof da JVM
void Interpreter::java_instanceof()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    map<string, MethodAreaSection *> method_area = this->runtime->method_area;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];

    u2 cp_index = (byte1 << 8) | byte2;
    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    string class_name = ReadFile::readString(cp_index, constant_pool);

    Value objectref_value = current_frame->PopOperandStack();

    Value result_value;
    result_value.type = INT_VALUE;

    if (objectref_value.data.object_value == NULL && objectref_value.data.string_value == NULL)
    {
        result_value.data.int_value = 0;
    }
    else
    {
        ObjectRef *obj = objectref_value.data.object_value;

        if (objectref_value.type == OBJECT_VALUE && objectref_value.data.object_value != NULL)
        {
            ClassFile *class_file = obj->class_file;

            bool found = false;
            while (!found)
            {
                string c_class_name = ReadFile::readString(class_file->this_class, class_file->constant_pool);

                if (c_class_name == class_name)
                {
                    found = true;
                }
                else
                {
                    if (class_file->super_class == 0)
                    {
                        break;
                    }
                    else
                    {
                        string super_class_name = ReadFile::readString(class_file->this_class, class_file->constant_pool);
                        ClassLoaderSubsystem::Resolve(super_class_name, this->runtime);

                        MethodAreaSection *area = method_area[super_class_name];
                        class_file = area->class_file;
                    }
                }
            }

            result_value.data.int_value = found ? 1 : 0;
        }
        else if (objectref_value.type == STRING_VALUE && objectref_value.data.string_value != NULL)
        {
            result_value.data.int_value = (class_name == "java/lang/String" || class_name == "java/lang/Object") ? 1 : 0;
        }
        else
        {
            if (class_name == "java/lang/Object")
            {
                result_value.data.int_value = 1;
            }
            else
            {
                result_value.data.int_value = 0;
            }
        }
    }

    current_frame->PushOperandStack(result_value);

    current_frame->pc += 3;
}
//! Essa função representa a função monitorenter da JVM
void Interpreter::java_monitorenter()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    current_frame->pc += 1;
}
//! Essa função representa a função monitorexit da JVM
void Interpreter::java_monitorexit()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    current_frame->pc += 1;
}
//! Essa função representa a função wide da JVM
void Interpreter::java_wide()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    wide = true;
    current_frame->pc += 1;
}
//! Essa função representa a função multianewarray da JVM
void Interpreter::java_multianewarray()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    vector<CpInfo *> constant_pool = current_frame->constant_pool;

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];
    u1 dimensions = current_frame->code.code[current_frame->pc + 3];

    uint16_t classIndex = (byte1 << 8) | byte2;
    CpInfo *class_cp = constant_pool[classIndex - 1];

    CONSTANT_Class_info class_info = class_cp->info.Class;
    string class_name = ReadFile::readString(class_info.name_index, constant_pool);

    char type_value;
    int i = 0;
    while (class_name[i] == '[')
        i++;

    string multi_array_type = class_name.substr(i + 1, class_name.size() - i - 2);

    switch (class_name[i])
    {
    case 'L':
        if (multi_array_type != "java/lang/String")
        {
            ClassLoaderSubsystem::Resolve(class_name, this->runtime);
            // map<string, MethodAreaSection *> method_area = this->runtime->method_area;
            type_value = OBJECT_VALUE;
        }
        else
        {
            type_value = STRING_VALUE;
        }
        break;
    case 'B':
        type_value = BYTE_VALUE;
        break;
    case 'C':
        type_value = CHAR_VALUE;
        break;
    case 'D':
        type_value = DOUBLE_VALUE;
        break;
    case 'F':
        type_value = FLOAT_VALUE;
        break;
    case 'I':
        type_value = INT_VALUE;
        break;
    case 'J':
        type_value = LONG_VALUE;
        break;
    case 'S':
        type_value = SHORT_VALUE;
        break;
    case 'Z':
        type_value = BYTE_VALUE;
        break;
    default:
        cerr << "Descritor invalido em multianewarray" << endl;
        exit(1);
    }

    vector<int> count;
    vector<Value> *array = new vector<Value>();

    for (int i = 0; i < dimensions; i++)
    {
        Value dim_length = current_frame->PopOperandStack();

        count.push_back(dim_length.data.int_value);

        // vector<Value> *subarray = new vector<Value>();
        // for (int j = 0; j < dim_length.data.int_value; j++) {
        //     Value arrayvalue;
        //     arrayvalue.type = type_value;
        //     arrayvalue.data.long_value = 0;

        //     subarray->push_back(arrayvalue);
        // }

        // Value subarray_ref;
        // subarray_ref.type = ARRAY_VALUE;
        // subarray_ref.data.array_value = subarray;
        // array->push_back(subarray_ref);
    }

    this->CreateMultiarray(array, type_value, count);

    Value array_value;
    array_value.type = ARRAY_VALUE;
    array_value.data.array_value = array;
    MemoryManager::variables_allocated.push_back(array_value);


    // cout << "Matrix Dim: " << array->size() << endl;
    // for(unsigned i = 0; i < array->size(); i ++){
    //     cout << "Size: " << array->at(i).data.array_value->size() << endl;
    // }
    current_frame->PushOperandStack(array_value);

    current_frame->pc += 4;
}

void Interpreter::CreateMultiarray(vector<Value> *array, char type_value, vector<int> count)
{
    int c_count = count[count.size() - 1];
    count.pop_back();

    // [[I
    // 0 iconst_5
    // 1 iconst_5
    // 2 multianewarray #2 <[[I> dim 2
    if (count.size() == 0)
    {
        for (int i = 0; i < c_count; i++)
        {
            Value subarray_value;
            subarray_value.type = type_value;
            subarray_value.data.long_value = 0;
            array->push_back(subarray_value);
        }
    }
    else
    {
        for (int i = 0; i < c_count; i++)
        {
            vector<Value> *subarray = new vector<Value>();
            this->CreateMultiarray(subarray, type_value, count);

            Value subarray_value;
            subarray_value.type = ARRAY_VALUE;
            subarray_value.data.array_value = subarray;
            MemoryManager::variables_allocated.push_back(subarray_value);
            array->push_back(subarray_value);
        }
    }
}

//! Essa função representa a função ifnull da JVM
void Interpreter::java_ifnull()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();
    Value reference_value = current_frame->PopOperandStack();

    if (reference_value.data.object_value == NULL)
    {
        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch = (byte1 << 8) | byte2;
        current_frame->pc += branch;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função ifnonnull da JVM
void Interpreter::java_ifnonnull()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    Value reference_value = current_frame->PopOperandStack();

    if (reference_value.data.object_value != NULL)
    {
        u1 byte1 = current_frame->code.code[current_frame->pc + 1];
        u1 byte2 = current_frame->code.code[current_frame->pc + 2];
        int16_t branch = (byte1 << 8) | byte2;
        current_frame->pc += branch;
    }
    else
    {
        current_frame->pc += 3;
    }
}
//! Essa função representa a função goto_w da JVM
void Interpreter::java_goto_w()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];
    u1 byte3 = current_frame->code.code[current_frame->pc + 3];
    u1 byte4 = current_frame->code.code[current_frame->pc + 4];
    int32_t branch_offset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    current_frame->pc += branch_offset;
}
//! Essa função representa a função jsr_w da JVM
void Interpreter::java_jsr_w()
{
    Frame *current_frame = this->runtime->GetCurrentFrame();

    u1 byte1 = current_frame->code.code[current_frame->pc + 1];
    u1 byte2 = current_frame->code.code[current_frame->pc + 2];
    u1 byte3 = current_frame->code.code[current_frame->pc + 3];
    u1 byte4 = current_frame->code.code[current_frame->pc + 4];
    int32_t branch_offset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

    Value return_addr;
    return_addr.type = RETURN_VALUE;
    return_addr.data.return_address = current_frame->pc + 5;
    current_frame->PushOperandStack(return_addr);

    current_frame->pc += branch_offset;
}