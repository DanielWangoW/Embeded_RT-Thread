/*
*********************************************
*              头文件调用
*********************************************
*/
#include <rtthread.h>
#include <stm32f10x.h>


/*
*********************************************
*              全局变量
*********************************************
*/
uint8_t flag1;
uint8_t flag2;
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];


/*
*********************************************
*      线程控制块&线程栈&线程声明
*********************************************
*/
/*定义线程控制块*/
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;


ALIGN(RT_ALIGN_SIZE)
/*定义线程栈*/
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];


/*线程声明*/
void flag1_thread_entry(void *p_arg);
void flag2_thread_entry(void *p_arg);


/*
*********************************************
*              函数声明
*********************************************
*/
void delay(uint32_t count);


/*
******************************************
*                主函数
******************************************
*/
int main(void)
{
  /*硬件初始化*/
	
	
	
	/*线程调度器初始化*/
	rt_system_scheduler_init();
	
	/*初始化线程1，rt_thread_init()为静态线程*/
	rt_thread_init(&rt_flag1_thread,
	               flag1_thread_entry,
	               RT_NULL,
	               &rt_flag1_thread_stack[0],
	               sizeof(rt_flag1_thread_stack));
	/*将线程插入到就绪列表*/
	rt_list_insert_before(&(rt_thread_priority_table[0]),&(rt_flag1_thread.tlist));
	
	/*初始化线程2，rt_thread_init()为静态线程*/
	rt_thread_init(&rt_flag2_thread,
	               flag2_thread_entry,
	               RT_NULL,
	               &rt_flag2_thread_stack[0],
	               sizeof(rt_flag2_thread_stack));
  /*将线程插入到就绪列表*/
	rt_list_insert_before(&(rt_thread_priority_table[1]),&(rt_flag2_thread.tlist));
	
	/*启动线程调度器*/
	rt_system_scheduler_start();
  
}


/*
*********************************************
*                函数实现
*********************************************
*/
/*软件延时*/
void delay(uint32_t count)
{
	for(; count != 0; count--);
}

/*线程1*/
void flag1_thread_entry(void *p_arg)
{
  for(;;)
	{
	  flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);
		
		/*目前线程不支持优先级，手动切换线程*/
		rt_schedule();
		
	}
}

/*线程2*/
void flag2_thread_entry(void *p_arg)
{
  for(;;)
	{
	  flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);
		
		/*目前线程不支持优先级，手动切换线程*/
		rt_schedule();
	}
}






