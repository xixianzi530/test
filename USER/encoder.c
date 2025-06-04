#include "include.h"

#define PINA    P04
#define PINB    P34


/* 上层依赖变量（外部已定义） */
bit     encoder_cnt_en;
uint8   encider_direction;        /* DOWN / UP */

/*─────────────────── 状态变量 ───────────────────*/
static uint8  enc_prev ;      /* 上一次 A/B 组合：0~3   */
static char   enc_acc  ;      /* 一定位一脉冲累加器    */
static bit    EncType  ;      /* 0=一定位一脉冲 1=两定位 */

/* 4×4 跳变 → 步进表：+1=右 -1=左 0=无效           */
static const char code enc_tbl[16] = {
/* prev<<2 | now →      00  01  10  11 (now) */
 /* 00 */                0, +1, -1,  0,
 /* 01 */               -1,  0,  0, +1,
 /* 10 */               +1,  0,  0, -1,
 /* 11 */                0, -1, +1,  0
};

/*─────────────────── 初始化 ───────────────────*/
void Encoder_Init(void)
{
    P0MOD54 = (P0MOD54&0xf0)|0x01;   /* P0.5 / P0.4 设为输入 */
    P3MOD54 = (P3MOD54&0xf0)|0x01;   /* P0.5 / P0.4 设为输入 */
    P3MOD76 = (P3MOD76&0x0f);   /* P0.5 / P0.4 设为输入 */
    enc_prev = (PINA ? 2 : 0) | (PINB ? 1 : 0);
}

/*─────────────────── 扫描函数：轮询或 1 ms 定期调用 ───────────────────*/
/* ── 每旋转 2 格(两次卡位) 才返回一次 ±1 ── */
static char Encoder_Scan(void)          /* return: -1 / 0 / +1 */
{
    uint8 now  = (PINA ? 2 : 0) | (PINB ? 1 : 0);
    char  step = enc_tbl[(enc_prev << 2) | now];   /* 单次跳变：±1 / 0 */
    enc_prev   = now;

    if (!step) return 0;            /* 无跳变 */

    enc_acc += step;                /* 累加范围扩大到 -4..+4 */

    /* 回到稳定态(00 或 11) 且已累积两格(±4) → 输出一次 ±1 */
    if ((now == 0 || now == 3) && (enc_acc == 4 || enc_acc == -4)) {
        step    = enc_acc >> 2;     /* ±1 */
        enc_acc = 0;                /* 重新计数 */
        return step;                /* —— 每 2 格触发一次 —— */
    }
    return 0;                       /* 未满 2 格 */
}





/*─────────────────── 公共动作 ───────────────────*/
static void Encoder_Do(char dir)         /* dir = ±1 */
{
    encider_direction = (dir > 0) ? UP : DOWN;
	AutoSave_Time = 0;
	AutoStop_Time = 15;
	switch(Servant_Page_State)
	{
		case Time_UI:
		case Alarm_UI:
		case Alarm_UI_1:
		case Alarm_UI_2:
			
		case Ajust_Music_SIZE_UI:
				
				Servant_Page_State = Ajust_Music_SIZE_UI;
		break;
	}
    Get_Add_Action();
}
/*─────────────────── 对外入口（主循环调用） ───────────────────*/
void Encoder_Task(void)
{
	char s ;
    if (encoder_cnt_en) return;
   s = Encoder_Scan();
    if      (s > 0) Encoder_Do(-1);
    else if (s < 0) Encoder_Do(+1);
}
/*─────────────────── 代码结束 ───────────────────*/


