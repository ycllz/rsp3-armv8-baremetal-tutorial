/*
 * main.cpp
 *
 *  Created on: Jun 16, 2018
 *      Author: 13774
 */

#include <runtime_def.h>
#include <io/Output.h>
#include <exception/svc_call.h>
#include <io/Input.h>
#include <Shell.h>

// 进程能够接受的参数形式： shell
//                   shell  CMD
// 其中，shell部分的名称可以任意
// 当没有给定参数任何参数时，直接退出
// 前者执行一个REPL，后者执行CMD并退出
// Read-Evaluate-Print-Loop(REPL)
//  实现一些常见的管理命令，如ls,cd,pwd,exit等，具体参见代码
// 程序分为两部分：1.接受输入   2.解析输入，分成命令名称多个参数  3.根据命令和参数执行
int main(int argc,char **argv)
{
	Shell shell;
	shell.run(argc,argv);

	kout.flush();//将所有的输出刷新
	return shell.exitCode();
}






