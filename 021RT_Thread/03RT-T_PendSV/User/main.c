/*
*********************************************
*              ͷ�ļ�����
*********************************************
*/
#include <rtthread.h>
#include <stm32f10x.h>
#include <rthw.h>



/*
*********************************************
*              ��������
*********************************************
*/



PRIMASK = 0;
rt_base_t level1;
rt_base_t level2;



/*
*********************************************
*          �ٽ�δ��뱣��α����
*********************************************
*/
int main()
{
  level1 = rt_hw_interrupt_disable(); 
	{
		level2 = rt_hw_interrupt_disable();
		{
			/*�ٽ�α���*/
		}
		rt_hw_interrupt_enable(level2);
	}
	rt_hw_interrupt_enable(level1);
}
