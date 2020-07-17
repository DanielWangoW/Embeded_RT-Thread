/*
*********************************************
*              头文件调用
*********************************************
*/
#include <rtthread.h>
#include <stm32f10x.h>
#include <rthw.h>



/*
*********************************************
*              函数声明
*********************************************
*/



PRIMASK = 0;
rt_base_t level1;
rt_base_t level2;



/*
*********************************************
*          临界段代码保护伪代码
*********************************************
*/
int main()
{
  level1 = rt_hw_interrupt_disable(); 
	{
		level2 = rt_hw_interrupt_disable();
		{
			/*临界段保护*/
		}
		rt_hw_interrupt_enable(level2);
	}
	rt_hw_interrupt_enable(level1);
}
