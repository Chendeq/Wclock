/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
//#ifdef __ICCARM__
//	#include <stdint.h>
//	extern uint32_t SystemCoreClock;
//#endif

#if defined(__ICCARM__) || defined(__CC_ARM) ||defined(__GUNC__)
	#include <stdint.h>
	extern uint32_t SystemCoreClock;
#endif

/* 内核设置 */
#define configUSE_PREEMPTION                1    // 使用抢占式调度
#define configUSE_TIME_SLICING              1    // 使用时间片调度
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0     /* 1: 使用硬件计算下一个要运行的任务, 0: 使用软件算法计算下一个要运行的任务, 默认: 0 */
#define configUSE_TICKLESS_IDLE             0    // 低功耗 tickless 模式
#define configCPU_CLOCK_HZ				( SystemCoreClock )  // CPU 时钟频率
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )    // 系统节拍频率 (Hz)
#define configUSE_16_BIT_TICKS			    0		/* 1: 定义系统时钟节拍计数器的数据类型为16位无符号数, 无默认需定义 */
#define configIDLE_SHOULD_YIELD			    0		/* 1: 使能在抢占式调度下,同优先级的任务能抢占空闲任务, 默认: 1 */
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS     0         /* 定义线程本地存储指针的个数, 默认: 0 */

/* 内存配置 */
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 25 * 1024 ) )  // 堆大小
#define configAPPLICATION_ALLOCATED_HEAP    0    // 1应用自定义堆内存
#define configSUPPORT_DYNAMIC_ALLOCATION    1    // 动态内存分配
#define configSUPPORT_STATIC_ALLOCATION     0    // 静态内存分配
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP       0      /* 1: 用户自行实现任务创建时使用的内存申请与释放函数, 默认: 0 */

/* 任务配置 */
#define configMAX_PRIORITIES                (32)    // 最大任务优先级
#define configMINIMAL_STACK_SIZE            ((unsigned short) 128)  // 最小栈大小
#define configMAX_TASK_NAME_LEN             (16)   // 任务名最大长度
#define INCLUDE_vTaskPrioritySet            0     // 包含任务优先级设置
#define INCLUDE_uxTaskPriorityGet           0     // 包含获取任务优先级
#define INCLUDE_eTaskGetState               0     /* 获取任务状态 */

/* 钩子函数 */
#define configUSE_IDLE_HOOK                 0    // 空闲任务钩子
#define configUSE_TICK_HOOK                 0    // 时钟节拍钩子
#define configCHECK_FOR_STACK_OVERFLOW      0    /* 1: 使能栈溢出检测方法1, 2: 使能栈溢出检测方法2, 默认: 0 */
#define configUSE_MALLOC_FAILED_HOOK	    0	 /* 1: 使能动态内存申请失败钩子函数, 默认: 0 */
#define configUSE_DAEMON_TASK_STARTUP_HOOK  0    /* 1: 使能定时器服务任务首次执行前的钩子函数, 默认: 0 */

/* 软件定时器 */
#define configUSE_TIMERS                    0    // 启用软件定时器
#define configTIMER_TASK_PRIORITY           (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH            10
#define configTIMER_TASK_STACK_DEPTH        (configMINIMAL_STACK_SIZE * 2)

/* 同步和通信 */
#define configUSE_MUTEXES                   1    // 使用互斥量
#define configUSE_RECURSIVE_MUTEXES         1    // 使用递归互斥量
#define configUSE_COUNTING_SEMAPHORES       1    // 使用计数信号量
#define configUSE_QUEUE_SETS                0    // 队列集
#define configUSE_APPLICATION_TASK_TAG      0
#define configUSE_TASK_NOTIFICATIONS        1    /* 1: 使能任务间直接的消息传递,包括信号量、事件标志组和消息邮箱, 默认: 1 */
#define configQUEUE_REGISTRY_SIZE		8		//队列注册表大小，用于内核感知调试

#define configUSE_TRACE_FACILITY		1		// 可视化跟踪调试功能

#define configGENERATE_RUN_TIME_STATS	0		//生成运行时统计信息

/* 可选函数, 1: 使能 */
#define INCLUDE_uxTaskGetStackHighWaterMark     1  //包含获取任务栈历史最小剩余空间API
#define INCLUDE_xEventGroupSetBitFromISR        1  /* 在中断中设置事件标志位 */
#define INCLUDE_vTaskDelete                     1  /* 删除任务 */
#define INCLUDE_vTaskSuspend                    1  /* 挂起任务 */
#define INCLUDE_xResumeFromISR                  1  /* 恢复在中断中挂起的任务 */
#define INCLUDE_vTaskDelayUntil                 1  /* 任务绝对延时 */
#define INCLUDE_vTaskDelay                      1  /* 任务延时 */
#define INCLUDE_xTaskGetSchedulerState          1  /* 获取任务调度器状态 */
#define INCLUDE_xTaskGetCurrentTaskHandle       1  /* 获取当前任务的任务句柄 */
#define INCLUDE_xTaskGetIdleTaskHandle          1  /* 获取空闲任务的任务句柄 */
#define INCLUDE_xTimerPendFunctionCall          0  /* 将函数的执行挂到定时器服务任务 */
#define INCLUDE_xTaskAbortDelay                 1  /* 中断任务延时 */
#define INCLUDE_xTaskGetHandle                  1  /* 通过任务名获取任务句柄 */
#define INCLUDE_xTaskResumeFromISR              1  /* 恢复在中断中挂起的任务 */
   
/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
	/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	/* 15 priority levels */  // 默认4位，支持16个优先级级别(0-15)
	#define configPRIO_BITS       		4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf	   // 最低中断优先级(数值最大)

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5		// 可调用FreeRTOS API的最高中断优先级

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )	// 内核中断优先级
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )	 // 可调用FreeRTOS API的最高中断优先级(移位后)

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
//#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */

