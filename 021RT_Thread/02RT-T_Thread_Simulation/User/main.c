/*
*********************************************
*              ͷ�ļ�����
*********************************************
*/
#include <rtthread.h>
#include <stm32f10x.h>


/*
*********************************************
*              ȫ�ֱ���
*********************************************
*/
uint8_t flag1;
uint8_t flag2;
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];


/*
*********************************************
*      �߳̿��ƿ�&�߳�ջ&�߳�����
*********************************************
*/
/*�����߳̿��ƿ�*/
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;


ALIGN(RT_ALIGN_SIZE)
/*�����߳�ջ*/
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];


/*�߳�����*/
void flag1_thread_entry(void *p_arg);
void flag2_thread_entry(void *p_arg);


/*
*********************************************
*              ��������
*********************************************
*/
void delay(uint32_t count);


/*
******************************************
*                ������
******************************************
*/
int main(void)
{
  /*Ӳ����ʼ��*/
	
	
	
	/*�̵߳�������ʼ��*/
	rt_system_scheduler_init();
	
	/*��ʼ���߳�1��rt_thread_init()Ϊ��̬�߳�*/
	rt_thread_init(&rt_flag1_thread,
	               flag1_thread_entry,
	               RT_NULL,
	               &rt_flag1_thread_stack[0],
	               sizeof(rt_flag1_thread_stack));
	/*���̲߳��뵽�����б�*/
	rt_list_insert_before(&(rt_thread_priority_table[0]),&(rt_flag1_thread.tlist));
	
	/*��ʼ���߳�2��rt_thread_init()Ϊ��̬�߳�*/
	rt_thread_init(&rt_flag2_thread,
	               flag2_thread_entry,
	               RT_NULL,
	               &rt_flag2_thread_stack[0],
	               sizeof(rt_flag2_thread_stack));
  /*���̲߳��뵽�����б�*/
	rt_list_insert_before(&(rt_thread_priority_table[1]),&(rt_flag2_thread.tlist));
	
	/*�����̵߳�����*/
	rt_system_scheduler_start();
  
}


/*
*********************************************
*                ����ʵ��
*********************************************
*/
/*�����ʱ*/
void delay(uint32_t count)
{
	for(; count != 0; count--);
}

/*�߳�1*/
void flag1_thread_entry(void *p_arg)
{
  for(;;)
	{
	  flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);
		
		/*Ŀǰ�̲߳�֧�����ȼ����ֶ��л��߳�*/
		rt_schedule();
		
	}
}

/*�߳�2*/
void flag2_thread_entry(void *p_arg)
{
  for(;;)
	{
	  flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);
		
		/*Ŀǰ�̲߳�֧�����ȼ����ֶ��л��߳�*/
		rt_schedule();
	}
}






