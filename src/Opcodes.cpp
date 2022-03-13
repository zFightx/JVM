#include "../header/Opcodes.hpp"


void Opcodes::CreateOpcodes(){
    map<int, pair<string, int>> opcodes_map = opcodes;

    opcodes_map[0x00] = make_pair("nop", 0);
    opcodes_map[0x01] = make_pair("aconst_null", 0 );
    opcodes_map[0x02] = make_pair("iconst_m1", 0 );
    opcodes_map[0x03] = make_pair("iconst_0", 0 );
    opcodes_map[0x04] = make_pair("iconst_1", 0 );
    opcodes_map[0x05] = make_pair("iconst_2", 0 );
    opcodes_map[0x06] = make_pair("iconst_3", 0 );
    opcodes_map[0x07] = make_pair("iconst_4", 0 );
    opcodes_map[0x08] = make_pair("iconst_5", 0 );
    opcodes_map[0x09] = make_pair("lconst_0", 0 );
    opcodes_map[0x0a] = make_pair("lconst_1", 0 );
    opcodes_map[0x0b] = make_pair("fconst_0", 0 );
    opcodes_map[0x0c] = make_pair("fconst_1", 0 );
    opcodes_map[0x0d] = make_pair("fconst_2", 0 );
    opcodes_map[0x0e] = make_pair("dconst_0", 0 );
    opcodes_map[0x0f] = make_pair("dconst_1", 0 );
    opcodes_map[0x10] = make_pair("bipush", 1 );
    opcodes_map[0x11] = make_pair("sipush", 2 );
    opcodes_map[0x12] = make_pair("ldc", 1 );
    opcodes_map[0x13] = make_pair("ldc_w", 2 );
    opcodes_map[0x14] = make_pair("ldc2_w", 2 );
    opcodes_map[0x15] = make_pair("iload", 1 );
    opcodes_map[0x16] = make_pair("lload", 1 );
    opcodes_map[0x17] = make_pair("fload", 1 );
    opcodes_map[0x18] = make_pair("dload", 1 );
    opcodes_map[0x19] = make_pair("aload", 1 );
    opcodes_map[0x1a] = make_pair("iload_0", 0 );
    opcodes_map[0x1b] = make_pair("iload_1", 0 );
    opcodes_map[0x1c] = make_pair("iload_2", 0 );
    opcodes_map[0x1d] = make_pair("iload_3", 0 );
    opcodes_map[0x1e] = make_pair("lload_0", 0 );
    opcodes_map[0x1f] = make_pair("lload_1", 0 );
    opcodes_map[0x20] = make_pair("lload_2", 0 );
    opcodes_map[0x21] = make_pair("lload_3", 0 );
    opcodes_map[0x22] = make_pair("fload_0", 0 );
    opcodes_map[0x23] = make_pair("fload_1", 0 );
    opcodes_map[0x24] = make_pair("fload_2", 0 );
    opcodes_map[0x25] = make_pair("fload_3", 0 );
    opcodes_map[0x26] = make_pair("dload_0", 0 );
    opcodes_map[0x27] = make_pair("dload_1", 0 );
    opcodes_map[0x28] = make_pair("dload_2", 0 );
    opcodes_map[0x29] = make_pair("dload_3", 0 );
    opcodes_map[0x2a] = make_pair("aload_0", 0 );
    opcodes_map[0x2b] = make_pair("aload_1", 0 );
    opcodes_map[0x2c] = make_pair("aload_2", 0 );
    opcodes_map[0x2d] = make_pair("aload_3", 0 );
    opcodes_map[0x2e] = make_pair("iaload", 0 );
    opcodes_map[0x2f] = make_pair("laload", 0 );
    opcodes_map[0x30] = make_pair("faload", 0 );
    opcodes_map[0x31] = make_pair("daload", 0 );
    opcodes_map[0x32] = make_pair("aaload", 0 );
    opcodes_map[0x33] = make_pair("baload", 0 );
    opcodes_map[0x34] = make_pair("caload", 0 );
    opcodes_map[0x35] = make_pair("saload", 0 );
    opcodes_map[0x36] = make_pair("istore", 1 );
    opcodes_map[0x37] = make_pair("lstore", 1 );
    opcodes_map[0x38] = make_pair("fstore", 1 );
    opcodes_map[0x39] = make_pair("dstore", 1 );
    opcodes_map[0x3a] = make_pair("astore", 1 );
    opcodes_map[0x3b] = make_pair("istore_0", 0 );
    opcodes_map[0x3c] = make_pair("istore_1", 0 );
    opcodes_map[0x3d] = make_pair("istore_2", 0 );
    opcodes_map[0x3e] = make_pair("istore_3", 0 );
    opcodes_map[0x3f] = make_pair("lstore_0", 0 );
    opcodes_map[0x40] = make_pair("lstore_1", 0 );
    opcodes_map[0x41] = make_pair("lstore_2", 0 );
    opcodes_map[0x42] = make_pair("lstore_3", 0 );
    opcodes_map[0x43] = make_pair("fstore_0", 0 );
    opcodes_map[0x44] = make_pair("fstore_1", 0 );
    opcodes_map[0x45] = make_pair("fstore_2", 0 );
    opcodes_map[0x46] = make_pair("fstore_3", 0 );
    opcodes_map[0x47] = make_pair("dstore_0", 0 );
    opcodes_map[0x48] = make_pair("dstore_1", 0 );
    opcodes_map[0x49] = make_pair("dstore_2", 0 );
    opcodes_map[0x4a] = make_pair("dstore_3", 0 );
    opcodes_map[0x4b] = make_pair("astore_0", 0 );
    opcodes_map[0x4c] = make_pair("astore_1", 0 );
    opcodes_map[0x4d] = make_pair("astore_2", 0 );
    opcodes_map[0x4e] = make_pair("astore_3", 0 );
    opcodes_map[0x4f] = make_pair("iastore", 0 );












}