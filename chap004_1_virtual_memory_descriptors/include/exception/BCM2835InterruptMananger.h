/*
 * BCM2835InterruptMananger.h
 *
 *  Created on: Jun 11, 2018
 *      Author: 13774
 */

#ifndef INCLUDE_EXCEPTION_BCM2835INTERRUPTMANANGER_H_
#define INCLUDE_EXCEPTION_BCM2835INTERRUPTMANANGER_H_

#include <driver/MemoryMappedDevice.h>
#include <exception/exception_def.h>
#include <utility>
#include <cassert>

class BCM2835InterruptManager
	:public MemoryMappedDevice
{
public:
	enum RegOffset : size_t{
		PENDING_IRQ_BASIC=0x200,//32bits
		PENDING_IRQ_1 = 0x204,
		PENDING_IRQ_2 = 0x208,
		FIQ_CONTROL = 0x20C,
		ENABLE_IRQ_1 = 0x210,
		ENABLE_IRQ_2 = 0x214,
		ENABLE_BASIC_IRQ = 0x218, // 只能用于启用前8个中断，只有启用的中断才能看到pending状态。
		DISABLE_IRQ_1 =0x21C,
		DISABLE_IRQ_2 = 0x220,
		DISABLE_BASIC_IRQ = 0x224
	};
	enum IntSource : IntID{
		SRC_ARM_TIMER,SRC_ARM_MAILBOX,SRC_ARM_DOORBELL0,SRC_ARM_DOORBELL1,SRC_GPU0_HALTED,SRC_GPU1_HALTD,SRC_ILLEG_TYPE1,SRC_ILLEG_TYPE0,
		SRC_SYS_TIMER_FIRST=0+8, SRC_SYS_TIMER_LAST=3+8,// 4个SysTimer Int
		SRC_AUX_INT=29 + 8,SRC_GPIO_INT_FIRST=49 + 8,SRC_GPIO_INT_LAST=52 + 8,
		SRC_SPI_INT=54 + 8, SRC_UART_INT=57 + 8
	};
	// 64个GPU外设中断和8个ARM中断
	static constexpr size_t INT_NUM = 64 + 8;
	template <class ... Args>
	BCM2835InterruptManager(Args && ... args)
		:MemoryMappedDevice(std::forward<Args>(args)...)
	{}
	/**
	 *
	 * @param i 0表示IRQ1， 1表示IRQ2,3表示BASIC
	 * @return
	 */
	AS_MACRO volatile uint32_t& pendingWord(int i)
		{ assert(i>=0 && i<=2);i=(i==2?0:(i+1));return reg32(PENDING_IRQ_BASIC+i*4);}
	AS_MACRO volatile uint32_t& enableWord(int i)
		{assert(i>=0 && i<=2);return reg32(ENABLE_IRQ_1 + i*4);}
	AS_MACRO volatile uint32_t& disableWord(int i)
		{assert(i>=0 && i<=2);return reg32(DISABLE_IRQ_1 + i*4);}
	void disableAllInterrupts() ;
	/**
	 * 注意，返回的irq，如果是ARM中断，就是0-8的范围，如果是GPU中断，则是GPU号+8
	 * @return
	 */
	IntID locateInterrupt() const;
	// INTERFACE
	IntID  standardIntID(StandardInterruptType type)const;
	void    endInterrupt(ExceptionType tp,IntID src);
	void    enableInterrupt(IntID src,bool en);
};




#endif /* INCLUDE_EXCEPTION_BCM2835INTERRUPTMANANGER_H_ */
