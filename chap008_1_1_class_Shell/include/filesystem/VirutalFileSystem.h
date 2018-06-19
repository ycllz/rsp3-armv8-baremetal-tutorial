/*
 * VirutalFileSystem.h
 *
 *  Created on: Mar 20, 2018
 *      Author: 13774
 */

#ifndef INCLUDE_FILESYSTEM_VIRUTALFILESYSTEM_H_
#define INCLUDE_FILESYSTEM_VIRUTALFILESYSTEM_H_

#include <filesystem/VirtualFile.h>


// 实现通常是树结构
// 定义 路径寻址方式
class VirtualFileSystem{
public:
	VirtualFileSystem();
	~VirtualFileSystem();
	VirtualFileSystem(const VirtualFileSystem &rhs)=delete;
	VirtualFileSystem & operator=(const VirtualFileSystem &rhs)=delete;
	AS_MACRO void addRootFile(VirtualFile *file){ _root->addFile(file);}
	AS_MACRO VirtualFile * rootFile() { return _root;}
	AS_MACRO const VirtualFile * rootFile()const { return _root;}
private:
	VirtualFile *_root;
};


#endif /* INCLUDE_FILESYSTEM_VIRUTALFILESYSTEM_H_ */
