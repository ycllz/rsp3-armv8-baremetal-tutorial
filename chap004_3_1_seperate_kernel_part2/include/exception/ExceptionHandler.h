/*
 * ExceptionHandler.h
 *
 *  Created on: Jun 11, 2018
 *      Author: 13774
 */

#ifndef INCLUDE_EXCEPTION_EXCEPTIONHANDLER_H_
#define INCLUDE_EXCEPTION_EXCEPTIONHANDLER_H_
#include <cstddef>
#include <cstdint>
#include <exception/exception_def.h>
#include <generic/programming.h>

template <class _IntManager>
class ExceptionHandler{
public:
	using IntManager = _IntManager;
	ExceptionHandler(IntManager * intman);
	DELETE_COPY(ExceptionHandler);
	/**
	 * 该处理函数被exceptionCHandler调用，为了效率上的考虑，将其inline
	 * @param savedRegs
	 * @param origin
	 * @param sp
	 */
	void handle(uint64_t  * savedRegs,
			ExceptionType type,
			ExceptionOrigin origin,
			IntID         id
			);
	void handleUndefinedInstruction();
	void handleInstructionAbort();
	void handleDataAbort();
	void handleSPAlignmentFault();
	void handlePCAlignmentFault();
	void handleSVC(size_t num);
	void handleIRQ(IntID id);
	void handleFIQ(IntID id);
	void handleSError();
	void unhandledException();

private:
	IntManager        * _intm;
};



#endif /* INCLUDE_EXCEPTION_EXCEPTIONHANDLER_H_ */
