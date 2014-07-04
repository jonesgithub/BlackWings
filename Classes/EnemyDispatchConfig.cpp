//
//  EnemyDispatchConfig.cpp
//  BlackWings
//
//  Created by Jacky on 14-6-29.
//
//

#include "EnemyDispatchConfig.h"

//普通敌人出兵配置
BattleNormalEnemyInfo s_battleNormalEnemyInfo[STAGE_COUNT]=
{
    {s_battleNormalEnemyConfig_Spc_0, STAGE_ENEMY_WAVES_SPC_00, s_battleNormalEnemyConfig_Loop_0, STAGE_ENEMY_WAVES_LOOP_00},
    {s_battleNormalEnemyConfig_Spc_1, STAGE_ENEMY_WAVES_SPC_01, s_battleNormalEnemyConfig_Loop_1, STAGE_ENEMY_WAVES_LOOP_01},
    {s_battleNormalEnemyConfig_Spc_2, STAGE_ENEMY_WAVES_SPC_02, s_battleNormalEnemyConfig_Loop_2, STAGE_ENEMY_WAVES_LOOP_02},
    {s_battleNormalEnemyConfig_Spc_3, STAGE_ENEMY_WAVES_SPC_03, s_battleNormalEnemyConfig_Loop_3, STAGE_ENEMY_WAVES_LOOP_03},
    {s_battleNormalEnemyConfig_Spc_4, STAGE_ENEMY_WAVES_SPC_04, s_battleNormalEnemyConfig_Loop_4, STAGE_ENEMY_WAVES_LOOP_04},
    {s_battleNormalEnemyConfig_Spc_5, STAGE_ENEMY_WAVES_SPC_05, s_battleNormalEnemyConfig_Loop_5, STAGE_ENEMY_WAVES_LOOP_05},
    {s_battleNormalEnemyConfig_Spc_6, STAGE_ENEMY_WAVES_SPC_06, s_battleNormalEnemyConfig_Loop_6, STAGE_ENEMY_WAVES_LOOP_06},
    {s_battleNormalEnemyConfig_Spc_7, STAGE_ENEMY_WAVES_SPC_07, s_battleNormalEnemyConfig_Loop_7, STAGE_ENEMY_WAVES_LOOP_07},
    {s_battleNormalEnemyConfig_Spc_8, STAGE_ENEMY_WAVES_SPC_08, s_battleNormalEnemyConfig_Loop_8, STAGE_ENEMY_WAVES_LOOP_08},
    {s_battleNormalEnemyConfig_Spc_9, STAGE_ENEMY_WAVES_SPC_09, s_battleNormalEnemyConfig_Loop_9, STAGE_ENEMY_WAVES_LOOP_09},
    {s_battleNormalEnemyConfig_Spc_10, STAGE_ENEMY_WAVES_SPC_10, s_battleNormalEnemyConfig_Loop_10, STAGE_ENEMY_WAVES_LOOP_10},
    {s_battleNormalEnemyConfig_Spc_11, STAGE_ENEMY_WAVES_SPC_11, s_battleNormalEnemyConfig_Loop_11, STAGE_ENEMY_WAVES_LOOP_11},
    {s_battleNormalEnemyConfig_Spc_12, STAGE_ENEMY_WAVES_SPC_12, s_battleNormalEnemyConfig_Loop_12, STAGE_ENEMY_WAVES_LOOP_12},
    {s_battleNormalEnemyConfig_Spc_13, STAGE_ENEMY_WAVES_SPC_13, s_battleNormalEnemyConfig_Loop_13, STAGE_ENEMY_WAVES_LOOP_13},
    {s_battleNormalEnemyConfig_Spc_14, STAGE_ENEMY_WAVES_SPC_14, s_battleNormalEnemyConfig_Loop_14, STAGE_ENEMY_WAVES_LOOP_14},
    {s_battleNormalEnemyConfig_Spc_15, STAGE_ENEMY_WAVES_SPC_15, s_battleNormalEnemyConfig_Loop_15, STAGE_ENEMY_WAVES_LOOP_15},
    {s_battleNormalEnemyConfig_Spc_16, STAGE_ENEMY_WAVES_SPC_16, s_battleNormalEnemyConfig_Loop_16, STAGE_ENEMY_WAVES_LOOP_16},
    {s_battleNormalEnemyConfig_Spc_17, STAGE_ENEMY_WAVES_SPC_17, s_battleNormalEnemyConfig_Loop_17, STAGE_ENEMY_WAVES_LOOP_17},
    {s_battleNormalEnemyConfig_Spc_18, STAGE_ENEMY_WAVES_SPC_18, s_battleNormalEnemyConfig_Loop_18, STAGE_ENEMY_WAVES_LOOP_18},
    {s_battleNormalEnemyConfig_Spc_19, STAGE_ENEMY_WAVES_SPC_19, s_battleNormalEnemyConfig_Loop_19, STAGE_ENEMY_WAVES_LOOP_19},
    {s_battleNormalEnemyConfig_Spc_20, STAGE_ENEMY_WAVES_SPC_20, s_battleNormalEnemyConfig_Loop_20, STAGE_ENEMY_WAVES_LOOP_20},
    {s_battleNormalEnemyConfig_Spc_21, STAGE_ENEMY_WAVES_SPC_21, s_battleNormalEnemyConfig_Loop_21, STAGE_ENEMY_WAVES_LOOP_21},
    {s_battleNormalEnemyConfig_Spc_22, STAGE_ENEMY_WAVES_SPC_22, s_battleNormalEnemyConfig_Loop_22, STAGE_ENEMY_WAVES_LOOP_22},
    {s_battleNormalEnemyConfig_Spc_23, STAGE_ENEMY_WAVES_SPC_23, s_battleNormalEnemyConfig_Loop_23, STAGE_ENEMY_WAVES_LOOP_23},
    {s_battleNormalEnemyConfig_Spc_24, STAGE_ENEMY_WAVES_SPC_24, s_battleNormalEnemyConfig_Loop_24, STAGE_ENEMY_WAVES_LOOP_24},
    {s_battleNormalEnemyConfig_Spc_25, STAGE_ENEMY_WAVES_SPC_25, s_battleNormalEnemyConfig_Loop_25, STAGE_ENEMY_WAVES_LOOP_25},
    {s_battleNormalEnemyConfig_Spc_26, STAGE_ENEMY_WAVES_SPC_26, s_battleNormalEnemyConfig_Loop_26, STAGE_ENEMY_WAVES_LOOP_26},
    {s_battleNormalEnemyConfig_Spc_27, STAGE_ENEMY_WAVES_SPC_27, s_battleNormalEnemyConfig_Loop_27, STAGE_ENEMY_WAVES_LOOP_27},
    {s_battleNormalEnemyConfig_Spc_28, STAGE_ENEMY_WAVES_SPC_28, s_battleNormalEnemyConfig_Loop_28, STAGE_ENEMY_WAVES_LOOP_28},
    {s_battleNormalEnemyConfig_Spc_29, STAGE_ENEMY_WAVES_SPC_29, s_battleNormalEnemyConfig_Loop_29, STAGE_ENEMY_WAVES_LOOP_29},
    {s_battleNormalEnemyConfig_Spc_30, STAGE_ENEMY_WAVES_SPC_30, s_battleNormalEnemyConfig_Loop_30, STAGE_ENEMY_WAVES_LOOP_30},
    {s_battleNormalEnemyConfig_Spc_31, STAGE_ENEMY_WAVES_SPC_31, s_battleNormalEnemyConfig_Loop_31, STAGE_ENEMY_WAVES_LOOP_31},
    {s_battleNormalEnemyConfig_Spc_32, STAGE_ENEMY_WAVES_SPC_32, s_battleNormalEnemyConfig_Loop_32, STAGE_ENEMY_WAVES_LOOP_32},
    {s_battleNormalEnemyConfig_Spc_33, STAGE_ENEMY_WAVES_SPC_33, s_battleNormalEnemyConfig_Loop_33, STAGE_ENEMY_WAVES_LOOP_33},
    {s_battleNormalEnemyConfig_Spc_34, STAGE_ENEMY_WAVES_SPC_34, s_battleNormalEnemyConfig_Loop_34, STAGE_ENEMY_WAVES_LOOP_34},
    {s_battleNormalEnemyConfig_Spc_35, STAGE_ENEMY_WAVES_SPC_35, s_battleNormalEnemyConfig_Loop_35, STAGE_ENEMY_WAVES_LOOP_35},
    {s_battleNormalEnemyConfig_Spc_36, STAGE_ENEMY_WAVES_SPC_36, s_battleNormalEnemyConfig_Loop_36, STAGE_ENEMY_WAVES_LOOP_36},
    {s_battleNormalEnemyConfig_Spc_37, STAGE_ENEMY_WAVES_SPC_37, s_battleNormalEnemyConfig_Loop_37, STAGE_ENEMY_WAVES_LOOP_37},
    {s_battleNormalEnemyConfig_Spc_38, STAGE_ENEMY_WAVES_SPC_38, s_battleNormalEnemyConfig_Loop_38, STAGE_ENEMY_WAVES_LOOP_38},
    {s_battleNormalEnemyConfig_Spc_39, STAGE_ENEMY_WAVES_SPC_39, s_battleNormalEnemyConfig_Loop_39, STAGE_ENEMY_WAVES_LOOP_39},
    {s_battleNormalEnemyConfig_Spc_40, STAGE_ENEMY_WAVES_SPC_40, s_battleNormalEnemyConfig_Loop_40, STAGE_ENEMY_WAVES_LOOP_40},
    {s_battleNormalEnemyConfig_Spc_41, STAGE_ENEMY_WAVES_SPC_41, s_battleNormalEnemyConfig_Loop_41, STAGE_ENEMY_WAVES_LOOP_41},
    {s_battleNormalEnemyConfig_Spc_42, STAGE_ENEMY_WAVES_SPC_42, s_battleNormalEnemyConfig_Loop_42, STAGE_ENEMY_WAVES_LOOP_42},
    {s_battleNormalEnemyConfig_Spc_43, STAGE_ENEMY_WAVES_SPC_43, s_battleNormalEnemyConfig_Loop_43, STAGE_ENEMY_WAVES_LOOP_43},
    {s_battleNormalEnemyConfig_Spc_44, STAGE_ENEMY_WAVES_SPC_44, s_battleNormalEnemyConfig_Loop_44, STAGE_ENEMY_WAVES_LOOP_44},
    {s_battleNormalEnemyConfig_Spc_45, STAGE_ENEMY_WAVES_SPC_45, s_battleNormalEnemyConfig_Loop_45, STAGE_ENEMY_WAVES_LOOP_45},
    {s_battleNormalEnemyConfig_Spc_46, STAGE_ENEMY_WAVES_SPC_46, s_battleNormalEnemyConfig_Loop_46, STAGE_ENEMY_WAVES_LOOP_46},
    {s_battleNormalEnemyConfig_Spc_47, STAGE_ENEMY_WAVES_SPC_47, s_battleNormalEnemyConfig_Loop_47, STAGE_ENEMY_WAVES_LOOP_47},
    {s_battleNormalEnemyConfig_Spc_48, STAGE_ENEMY_WAVES_SPC_48, s_battleNormalEnemyConfig_Loop_48, STAGE_ENEMY_WAVES_LOOP_48},
    {s_battleNormalEnemyConfig_Spc_49, STAGE_ENEMY_WAVES_SPC_49, s_battleNormalEnemyConfig_Loop_49, STAGE_ENEMY_WAVES_LOOP_49}
};

//时间间隔，类型，等级，数量下限，数量上限
BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_0[STAGE_ENEMY_WAVES_SPC_00] =
{
    {8,0,2,1,2}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_0[STAGE_ENEMY_WAVES_LOOP_00] =
{
    {8,0,2,1,2}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_1[STAGE_ENEMY_WAVES_SPC_01] =
{
    {8,0,2,3,3},
    {18,1,2,2,2}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_1[STAGE_ENEMY_WAVES_LOOP_01] =
{
    {8,0,2,3,3},
    {18,1,2,2,2}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_2[STAGE_ENEMY_WAVES_SPC_02] =
{
    {8,1,2,2,2},
    {18,2,2,1,1},
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_2[STAGE_ENEMY_WAVES_LOOP_02] =
{
    {8,1,2,2,2},
    {18,2,2,1,1},
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_3[STAGE_ENEMY_WAVES_SPC_03] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_3[STAGE_ENEMY_WAVES_LOOP_03] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_4[STAGE_ENEMY_WAVES_SPC_04] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_4[STAGE_ENEMY_WAVES_LOOP_04] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_5[STAGE_ENEMY_WAVES_SPC_05] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_5[STAGE_ENEMY_WAVES_LOOP_05] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};


BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_6[STAGE_ENEMY_WAVES_SPC_06] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_6[STAGE_ENEMY_WAVES_LOOP_06] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_7[STAGE_ENEMY_WAVES_SPC_07] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_7[STAGE_ENEMY_WAVES_LOOP_07] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_8[STAGE_ENEMY_WAVES_SPC_08] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_8[STAGE_ENEMY_WAVES_LOOP_08] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_9[STAGE_ENEMY_WAVES_SPC_09] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_9[STAGE_ENEMY_WAVES_LOOP_09] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_10[STAGE_ENEMY_WAVES_SPC_10] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_10[STAGE_ENEMY_WAVES_LOOP_10] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_11[STAGE_ENEMY_WAVES_SPC_11] =
{
    {8,3,3,5,5},
    {18,2,7,4,4},
    {30,3,3,2,2},
    {40,2,9,5,5},
    {50,4,4,3,3}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_11[STAGE_ENEMY_WAVES_LOOP_11] =
{
    {8,3,3,5,5},
    {18,2,7,4,4},
    {30,3,3,2,2},
    {40,2,9,5,5},
    {50,4,4,3,3}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_12[STAGE_ENEMY_WAVES_SPC_12] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_12[STAGE_ENEMY_WAVES_LOOP_12] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_13[STAGE_ENEMY_WAVES_SPC_13] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,3}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_13[STAGE_ENEMY_WAVES_LOOP_13] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,3}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_14[STAGE_ENEMY_WAVES_SPC_14] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_14[STAGE_ENEMY_WAVES_LOOP_14] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_15[STAGE_ENEMY_WAVES_SPC_15] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_15[STAGE_ENEMY_WAVES_LOOP_15] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_16[STAGE_ENEMY_WAVES_SPC_16] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_16[STAGE_ENEMY_WAVES_LOOP_16] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_17[STAGE_ENEMY_WAVES_SPC_17] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_17[STAGE_ENEMY_WAVES_LOOP_17] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_18[STAGE_ENEMY_WAVES_SPC_18] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_18[STAGE_ENEMY_WAVES_LOOP_18] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_19[STAGE_ENEMY_WAVES_SPC_19] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_19[STAGE_ENEMY_WAVES_LOOP_19] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_20[STAGE_ENEMY_WAVES_SPC_20] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_20[STAGE_ENEMY_WAVES_LOOP_20] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_21[STAGE_ENEMY_WAVES_SPC_21] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_21[STAGE_ENEMY_WAVES_LOOP_21] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_22[STAGE_ENEMY_WAVES_SPC_22] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_22[STAGE_ENEMY_WAVES_LOOP_22] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_23[STAGE_ENEMY_WAVES_SPC_23] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_23[STAGE_ENEMY_WAVES_LOOP_23] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_24[STAGE_ENEMY_WAVES_SPC_24] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_24[STAGE_ENEMY_WAVES_LOOP_24] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_25[STAGE_ENEMY_WAVES_SPC_25] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_25[STAGE_ENEMY_WAVES_LOOP_25] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_26[STAGE_ENEMY_WAVES_SPC_26] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_26[STAGE_ENEMY_WAVES_LOOP_26] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_27[STAGE_ENEMY_WAVES_SPC_27] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_27[STAGE_ENEMY_WAVES_LOOP_27] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_28[STAGE_ENEMY_WAVES_SPC_28] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_28[STAGE_ENEMY_WAVES_LOOP_28] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_29[STAGE_ENEMY_WAVES_SPC_29] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_29[STAGE_ENEMY_WAVES_LOOP_29] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_30[STAGE_ENEMY_WAVES_SPC_30] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_30[STAGE_ENEMY_WAVES_LOOP_30] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_31[STAGE_ENEMY_WAVES_SPC_31] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_31[STAGE_ENEMY_WAVES_LOOP_31] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_32[STAGE_ENEMY_WAVES_SPC_32] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_32[STAGE_ENEMY_WAVES_LOOP_32] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};


BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_33[STAGE_ENEMY_WAVES_SPC_33] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_33[STAGE_ENEMY_WAVES_LOOP_33] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};


BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_34[STAGE_ENEMY_WAVES_SPC_34] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_34[STAGE_ENEMY_WAVES_LOOP_34] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_35[STAGE_ENEMY_WAVES_SPC_35] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_35[STAGE_ENEMY_WAVES_LOOP_35] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};


BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_36[STAGE_ENEMY_WAVES_SPC_36] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_36[STAGE_ENEMY_WAVES_LOOP_36] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_37[STAGE_ENEMY_WAVES_SPC_37] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_37[STAGE_ENEMY_WAVES_LOOP_37] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_38[STAGE_ENEMY_WAVES_SPC_38] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_38[STAGE_ENEMY_WAVES_LOOP_38] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_39[STAGE_ENEMY_WAVES_SPC_39] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_39[STAGE_ENEMY_WAVES_LOOP_39] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_40[STAGE_ENEMY_WAVES_SPC_40] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_40[STAGE_ENEMY_WAVES_LOOP_40] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_41[STAGE_ENEMY_WAVES_SPC_41] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_41[STAGE_ENEMY_WAVES_LOOP_41] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_42[STAGE_ENEMY_WAVES_SPC_42] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_42[STAGE_ENEMY_WAVES_LOOP_42] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_43[STAGE_ENEMY_WAVES_SPC_43] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_43[STAGE_ENEMY_WAVES_LOOP_43] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_44[STAGE_ENEMY_WAVES_SPC_44] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_44[STAGE_ENEMY_WAVES_LOOP_44] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_45[STAGE_ENEMY_WAVES_SPC_45] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_45[STAGE_ENEMY_WAVES_LOOP_45] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_46[STAGE_ENEMY_WAVES_SPC_46] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_46[STAGE_ENEMY_WAVES_LOOP_46] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_47[STAGE_ENEMY_WAVES_SPC_47] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_47[STAGE_ENEMY_WAVES_LOOP_47] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_48[STAGE_ENEMY_WAVES_SPC_48] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_48[STAGE_ENEMY_WAVES_LOOP_48] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Spc_49[STAGE_ENEMY_WAVES_SPC_49] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

BattleNormalEnemyConfig s_battleNormalEnemyConfig_Loop_49[STAGE_ENEMY_WAVES_LOOP_49] =
{
    {8,1,2,2,2},
    {18,2,2,3,3},
    {30,2,1,1,1}
};

//炮塔配置
BattleTowerEnemyInfo s_battleTowerEnemyInfo[STAGE_COUNT]=
{
    {s_battleTowerEnemyConfig_0, 0},
    {s_battleTowerEnemyConfig_1, STAGE_TOWER_COUNTS_01},
    {s_battleTowerEnemyConfig_2, STAGE_TOWER_COUNTS_02},
    {s_battleTowerEnemyConfig_3, STAGE_TOWER_COUNTS_03},
    {s_battleTowerEnemyConfig_4, STAGE_TOWER_COUNTS_04},
    {s_battleTowerEnemyConfig_5, STAGE_TOWER_COUNTS_05},
    {s_battleTowerEnemyConfig_6, STAGE_TOWER_COUNTS_06},
    {s_battleTowerEnemyConfig_7, STAGE_TOWER_COUNTS_07},
    {s_battleTowerEnemyConfig_8, STAGE_TOWER_COUNTS_08},
    {s_battleTowerEnemyConfig_9, STAGE_TOWER_COUNTS_09},
    {s_battleTowerEnemyConfig_10, STAGE_TOWER_COUNTS_10},
    {s_battleTowerEnemyConfig_11, STAGE_TOWER_COUNTS_11},
    {s_battleTowerEnemyConfig_12, STAGE_TOWER_COUNTS_12},
    {s_battleTowerEnemyConfig_13, STAGE_TOWER_COUNTS_13},
    {s_battleTowerEnemyConfig_14, STAGE_TOWER_COUNTS_14},
    {s_battleTowerEnemyConfig_15, STAGE_TOWER_COUNTS_15},
    {s_battleTowerEnemyConfig_16, STAGE_TOWER_COUNTS_16},
    {s_battleTowerEnemyConfig_17, STAGE_TOWER_COUNTS_17},
    {s_battleTowerEnemyConfig_18, STAGE_TOWER_COUNTS_18},
    {s_battleTowerEnemyConfig_19, STAGE_TOWER_COUNTS_19},
    {s_battleTowerEnemyConfig_20, STAGE_TOWER_COUNTS_20},
    {s_battleTowerEnemyConfig_21, STAGE_TOWER_COUNTS_21},
    {s_battleTowerEnemyConfig_22, STAGE_TOWER_COUNTS_22},
    {s_battleTowerEnemyConfig_23, STAGE_TOWER_COUNTS_23},
    {s_battleTowerEnemyConfig_24, STAGE_TOWER_COUNTS_24},
    {s_battleTowerEnemyConfig_25, STAGE_TOWER_COUNTS_25},
    {s_battleTowerEnemyConfig_26, STAGE_TOWER_COUNTS_26},
    {s_battleTowerEnemyConfig_27, STAGE_TOWER_COUNTS_27},
    {s_battleTowerEnemyConfig_28, STAGE_TOWER_COUNTS_28},
    {s_battleTowerEnemyConfig_29, STAGE_TOWER_COUNTS_29},
    {s_battleTowerEnemyConfig_30, STAGE_TOWER_COUNTS_30},
    {s_battleTowerEnemyConfig_31, STAGE_TOWER_COUNTS_31},
    {s_battleTowerEnemyConfig_32, STAGE_TOWER_COUNTS_32},
    {s_battleTowerEnemyConfig_33, STAGE_TOWER_COUNTS_33},
    {s_battleTowerEnemyConfig_34, STAGE_TOWER_COUNTS_34},
    {s_battleTowerEnemyConfig_35, STAGE_TOWER_COUNTS_35},
    {s_battleTowerEnemyConfig_36, STAGE_TOWER_COUNTS_36},
    {s_battleTowerEnemyConfig_37, STAGE_TOWER_COUNTS_37},
    {s_battleTowerEnemyConfig_38, STAGE_TOWER_COUNTS_38},
    {s_battleTowerEnemyConfig_39, STAGE_TOWER_COUNTS_39},
    {s_battleTowerEnemyConfig_40, STAGE_TOWER_COUNTS_40},
    {s_battleTowerEnemyConfig_41, STAGE_TOWER_COUNTS_41},
    {s_battleTowerEnemyConfig_42, STAGE_TOWER_COUNTS_42},
    {s_battleTowerEnemyConfig_43, STAGE_TOWER_COUNTS_43},
    {s_battleTowerEnemyConfig_44, STAGE_TOWER_COUNTS_44},
    {s_battleTowerEnemyConfig_45, STAGE_TOWER_COUNTS_45},
    {s_battleTowerEnemyConfig_46, STAGE_TOWER_COUNTS_46},
    {s_battleTowerEnemyConfig_47, STAGE_TOWER_COUNTS_47},
    {s_battleTowerEnemyConfig_48, STAGE_TOWER_COUNTS_48},
    {s_battleTowerEnemyConfig_49, STAGE_TOWER_COUNTS_49}
};

//等级，x，y
BattleTowerEnemyConfig s_battleTowerEnemyConfig_0[STAGE_TOWER_COUNTS_00] =
{
    {0,400,400}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_1[STAGE_TOWER_COUNTS_01] =
{
    {0,300,700}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_2[STAGE_TOWER_COUNTS_02] =
{
    {0,500,1100},
    {0,200,2100}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_3[STAGE_TOWER_COUNTS_03] =
{
    {1,300,1400},
    {0,300,2100}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_4[STAGE_TOWER_COUNTS_04] =
{
    {1,350,900},
    {0,200,2100},
    {1,400,2000},
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_5[STAGE_TOWER_COUNTS_05] =
{
    {1,300,1000},
    {1,300,1250},
    {0,300,1500},
    {1,300,1750},
    {1,300,2000}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_6[STAGE_TOWER_COUNTS_06] =
{
    {1,50,980},
    {0,550,980},
    {1,300,1400},
    {1,300,1550},
    {1,300,2000}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_7[STAGE_TOWER_COUNTS_07] =
{
    {1,300,1350},
    {1,80,1900},
    {1,230,1900},
    {1,380,1900},
    {1,530,1900}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_8[STAGE_TOWER_COUNTS_08] =
{
    {1,300,1100},
    {2,300,1700},
    {0,300,1850},
    {2,200,2100},
    {1,400,2100}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_9[STAGE_TOWER_COUNTS_09] =
{
    {1,150,1000},
    {1,450,1000},
    {2,300,1350},
    {1,300,1600},
    {2,150,2100},
    {2,450,2100}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_10[STAGE_TOWER_COUNTS_10] =
{
    {2,300,800},
    {1,300,1200},
    {1,300,1350},
    {2,150,2000},
    {2,450,2000},
    {2,300,2300}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_11[STAGE_TOWER_COUNTS_11] =
{
    {2,150,1000},
    {1,450,1000},
    {1,150,1250},
    {2,450,1250},
    {2,150,1500},
    {2,450,1500},
    {2,150,1750},
    {2,450,1750}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_12[STAGE_TOWER_COUNTS_12] =
{
    {2,300,900},
    {1,300,1150},
    {1,150,1400},
    {2,300,1400},
    {2,450,1400},
    {2,300,1700},
    {2,300,1850}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_13[STAGE_TOWER_COUNTS_13] =
{
    {2,150,1600},
    {2,450,1600},
    {2,150,1900},
    {3,300,1900},
    {2,450,1900},
    {2,300,2100},
    {3,300,2300}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_14[STAGE_TOWER_COUNTS_14] =
{
    {2,300,1050},
    {3,300,1400},
    {3,300,2100},
    {3,100,2300},
    {3,250,2300},
    {3,350,2300},
    {2,450,2300},
    {3,550,2300}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_15[STAGE_TOWER_COUNTS_15] =
{
    {3,300,1000},
    {2,150,1200},
    {3,450,1200},
    {2,300,1400},
    {3,300,1750},
    {3,150,1900},
    {2,450,1900},
    {3,300,2100}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_16[STAGE_TOWER_COUNTS_16] =
{
    {3,300,900},
    {3,100,1200},
    {3,550,1350},
    {3,100,1500},
    {3,550,1650},
    {3,100,1800},
    {3,550,1950},
    {3,100,2100},
    {3,550,2250}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_17[STAGE_TOWER_COUNTS_17] =
{
    {3,300,1000},
    {3,150,1400},
    {3,300,1400},
    {3,450,1400},
    {3,550,1550},
    {3,150,2000},
    {3,300,2000},
    {3,550,2000}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_18[STAGE_TOWER_COUNTS_18] =
{
    {3,300,1200},
    {3,300,1400},
    {4,100,1600},
    {3,200,1600},
    {4,300,1600},
    {3,400,1600},
    {4,500,1600},
    {3,300,1800},
    {3,300,2000},
    {3,300,2400}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_19[STAGE_TOWER_COUNTS_19] =
{
    {3,300,1200},
    {4,300,1400},
    {4,200,1700},
    {4,450,1700},
    {4,200,1900},
    {3,450,1900},
    {4,200,2200},
    {4,450,2200}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_20[STAGE_TOWER_COUNTS_20] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_21[STAGE_TOWER_COUNTS_21] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_22[STAGE_TOWER_COUNTS_22] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_23[STAGE_TOWER_COUNTS_23] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_24[STAGE_TOWER_COUNTS_24] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_25[STAGE_TOWER_COUNTS_25] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_26[STAGE_TOWER_COUNTS_26] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_27[STAGE_TOWER_COUNTS_27] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_28[STAGE_TOWER_COUNTS_28] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_29[STAGE_TOWER_COUNTS_29] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_30[STAGE_TOWER_COUNTS_30] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_31[STAGE_TOWER_COUNTS_31] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_32[STAGE_TOWER_COUNTS_32] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_33[STAGE_TOWER_COUNTS_33] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_34[STAGE_TOWER_COUNTS_34] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_35[STAGE_TOWER_COUNTS_35] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_36[STAGE_TOWER_COUNTS_36] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_37[STAGE_TOWER_COUNTS_37] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_38[STAGE_TOWER_COUNTS_38] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_39[STAGE_TOWER_COUNTS_39] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_40[STAGE_TOWER_COUNTS_40] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_41[STAGE_TOWER_COUNTS_41] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_42[STAGE_TOWER_COUNTS_42] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_43[STAGE_TOWER_COUNTS_43] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_44[STAGE_TOWER_COUNTS_44] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_45[STAGE_TOWER_COUNTS_45] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_46[STAGE_TOWER_COUNTS_46] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_47[STAGE_TOWER_COUNTS_47] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_48[STAGE_TOWER_COUNTS_48] =
{
    {2,300,1300},
    {0,400,1800}
};

BattleTowerEnemyConfig s_battleTowerEnemyConfig_49[STAGE_TOWER_COUNTS_49] =
{
    {2,300,1300},
    {0,400,1800}
};


//Boss配置
BattleBossEnemyInfo s_battleBossEnemyInfo[STAGE_COUNT] =
{
    //等级，出现时间间隔
    {1,NO_BOSS},{1,NO_BOSS},{3,NO_BOSS},{4,NO_BOSS},{5,NO_BOSS},//1～5
    {1,10},{2,10},{3,10},{4,10},{5,10},//6～10
    {1,10},{2,10},{3,10},{4,10},{5,10},//11～15
    {1,10},{2,10},{3,10},{4,10},{5,10},//16～20
    {1,10},{2,10},{3,10},{4,10},{5,10},//21～25
    {1,10},{2,10},{3,10},{4,10},{5,10},//26~30
    {1,10},{2,10},{3,10},{4,10},{5,10},//31~35
    {1,10},{2,10},{3,10},{4,10},{5,10},//36~40
    {1,10},{2,10},{3,10},{4,10},{5,10},//41~45
    {1,10},{2,10},{3,10},{4,10},{5,10}//46~50
};
