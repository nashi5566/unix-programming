#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<stdarg.h>
#include<dlfcn.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include "sandbox.h"


int debug;
int output;
__attribute__((constructor)) static void setup(){
    int flag = 0;

	if(flag != 0){
		int (*foo)(const char* path, int flags, ...);
		foo = __func_hook("open");
		debug = foo("/dev/tty", O_WRONLY);
	}
    else{
		int (*foo)(const char* path, int flags, ...);
		foo = __func_hook("open");
		debug = foo("/dev/null", O_WRONLY);
    }

	int(*foo_out)(const char* path, int flags, ...);
	foo_out = __func_hook("open");
	output = foo_out("/dev/tty", O_WRONLY);
}



int execl(const char *path, const char *arg, ...){
    printf("[sandbox] execl(\"%s\")is not allowed\n", path);
	return -1;
}

int execle(const char *path, const char *arg, ...){
    printf("[sandbox] execle(\"%s\") is not allowed\n", path);
	return -1;
}

int execlp(const char *file, const char *arg, ...){
    printf("[sandbox] execlp(\"%s\") is not allowed\n", file);
	return -1;
}

int execv(const char *path, char *const argv[]){
    printf("[sandbox] execv(\"%s\") is not allowed\n", path);
	return -1;
}

int execve(const char *filename, char *const argv[], char *const envp[]){
    printf("[sandbox] execve(\"%s\") is not allowed\n", filename);
	return -1;
}

int execvp(const char *file, char *const argv[]){
    printf("[sandbox] execvp(\"%s\") is not allowed\n", file);
	return -1;
}

int system(const char *command){
    printf("[sandbox] system(\"%s\"): not allowed\n", command);
	return -1;
}

FILE *fopen(const char *path, const char *mode){
    //dprintf(debug, "fopen is called: %s\n", path);
    if (check_access(path, "fopen") == 1) {
        FILE* (*foo_fopen)(const char *path, const char *mode);
        foo_fopen = __func_hook("fopen");

		return foo_fopen(path, mode);
    }
	return NULL;
}



int __xstat(int ver, const char *path, struct stat *buf){
    dprintf(debug, "__xstat is called: %s\n", path);
	
	if (check_access(path, "__xstat") == 1) {
        int (*foo_xstat)(int ver, const char *path, struct stat *buf);
        foo_xstat = __func_hook("__xstat");
        return foo_xstat(ver, path, buf);
    }

	return -1;
}


int chdir(const char *path){
    dprintf(debug, "chdir is called: %s\n", path);
    if (check_access(path, "chdir") == 1) {
        int (*foo_chdir)(const char *path);
        foo_chdir = __func_hook("chdir");
        return foo_chdir(path);
    } 
	
	return -1;
}

int chmod(const char *pathname, mode_t mode){
    dprintf(debug, "chmod is called: %s\n", pathname);
    if (check_access(pathname, "chmod") == 1) {
        int (*foo_chmod)(const char *pathname, mode_t mode);
        foo_chmod = __func_hook("chmod");
        return foo_chmod(pathname, mode);
    } 
	
	return -1;
}

int fchmodat(int dirfd, const char *pathname, mode_t mode, int flags){
    dprintf(debug, "fchmodat is called: %s\n", pathname);
    if (check_access(pathname, "fchmodat")) {
        int (*foo_fchmodat)(int dirfd, const char *pathname, mode_t mode, int flags);
        foo_fchmodat = __func_hook("fchmodat");
        return foo_fchmodat(dirfd, pathname, mode, flags);
    } 
	
	return -1;
}

int chown(const char *pathname, uid_t owner, gid_t group){
    dprintf(debug,"chown is called: %s\n", pathname);
    if (check_access(pathname, "chown") == 1) {
        int (*foo_chown)(const char *pathname, uid_t owner, gid_t group);
        foo_chown = __func_hook("chown");
        return foo_chown(pathname, owner, group);
    } 
	return -1;
}

int open(const char *pathname, int flags, ...){
   // dprintf(debug, "open is called: %s\n", pathname);
    if (check_access(pathname, "open") == 1) {
        int (*foo_open)(const char *pathname, int flags, ...);
        foo_open = __func_hook("open");
        va_list a;
        mode_t mode;
        va_start(a, flags);
        mode = va_arg(a, mode_t);
        va_end(a);
        if (mode != 0) {
            return foo_open(pathname, flags, mode);
        } 
		else {
            return foo_open(pathname, flags);
        }
    } 
	return -1;
}

int openat(int dirfd, const char *pathname, int flags, ...){
    dprintf(debug, "openat is called: %s\n", pathname);
    if (check_access(pathname, "openat") == 1) {
        int (*foo_openat)(int dirfd, const char *pathname, int flags, ...);
        foo_openat = __func_hook("openat");
        va_list a;
        mode_t mode;
        va_start(a, flags);
        mode = va_arg(a, mode_t);
        va_end(a);
        if (mode != 0) {
            return foo_openat(dirfd, pathname, flags, mode);
        } 
		else {
            return foo_openat(dirfd, pathname, flags);
        }
    } 
	
	return -1;
}

/*
int __lxstat(int ver, const char *path, struct stat *buf){
    dprintf(output, "__lxstat is called: %s\n", path);
    if (check_access(path, "__lxstat")) {
        int (*foo_lxstat)(int ver, const char *path, struct stat *buf);
        foo_lxstat = __func_hook("__lxstat");
        return foo_lxstat(ver, path, buf);
    } return -1;
}
*/
/*
int symlink(const char *target, const char *linkpath){
    dprintf(debug, "symlink is called: %s, %s\n", target, linkpath);
    if (check_access(target, "symlink") && checkPathCreate(linkpath, "symlink")) {
        int (*foo_symlink)(const char *target, const char *linkpath);
        foo_symlink = __func_hook("symlink");
        return foo_symlink(target, linkpath);
    } 
	return -1;
}*/

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz){
    dprintf(debug, "readlink is called: %s\n", pathname);
    if (check_access(pathname, "readlink") == 1) {
        int (*foo_readlink)(const char *pathname, char *buf, size_t bufsiz);
        foo_readlink = __func_hook("readlink");
        return foo_readlink(pathname, buf, bufsiz);
    } 
	exit(-1);
}

int remove(const char *pathname){
    dprintf(debug, "remove is called: %s\n", pathname);
    if (check_access(pathname, "remove") == 1) {
        int (*foo_remove)(const char *pathname);
        foo_remove = __func_hook("remove");
        return foo_remove(pathname);
    } 
	return -1;
}

int rename(const char *oldpath, const char *newpath){
    dprintf(debug, "rename is called: %s, %s\n", oldpath, newpath);
    if (check_access(oldpath, "rename") && check_access(newpath, "rename")) {
        int (*foo_rename)(const char *oldpath, const char *newpath);
        foo_rename = __func_hook("rename");
        return foo_rename(oldpath, newpath);
    } 
	return -1;
}

int rmdir(const char *pathname){
    dprintf(debug, "rmdir is called: %s\n", pathname);
    if (check_access(pathname, "rmdir")) {
        int (*foo_rmdir)(const char *pathname);
        foo_rmdir = __func_hook("rmdir");
        return foo_rmdir(pathname);
    } 
	exit(-1);
}

int unlink(const char *pathname){
    dprintf(debug, "unlink is called: %s\n", pathname);
    if (check_access(pathname, "unlink")) {
        int (*foo_unlink)(const char *pathname);
        foo_unlink = __func_hook("unlink");
        return foo_unlink(pathname);
    } 
	
	return -1;
}

int mkdir(const char *pathname, mode_t mode){
    dprintf(debug, "mkdir is called: %s\n", pathname);
    if (check_access(pathname, "mkdir") == 1) {
        int (*foo_mkdir)(const char *pathname, mode_t mode);
        foo_mkdir = __func_hook("mkdir");
		printf("YES\n");
        return foo_mkdir(pathname, mode);
    } 
	
	return -1;
}

int link(const char *oldpath, const char *newpath){
    dprintf(debug, "link is called: %s, %s\n", oldpath, newpath);
    if (check_access(oldpath, "link") && check_access(newpath, "link")) {
        int (*foo_link)(const char *oldpath, const char *newpath);
        foo_link = __func_hook("link");
        return foo_link(oldpath, newpath);
    } 
	return -1;
}

/*
DIR *opendir(const char *name){
    dprintf(debug, "opendir is called: %s\n", name);
    if (check_access(name, "opendir") == 1) {
        DIR* (*foo_opendir)(const char *name);
        foo_opendir = __func_hook("opendir");
        return foo_opendir(name);
    } 
	
	return 0;
}*/

void* __func_hook(const char* symbol){
	void* handle = dlopen("lib.so.6", RTLD_LAZY);
	void* foo = dlsym(handle, symbol);

	return foo;
}

int check_access(const char *path, char *symbol)
{
    char cwd[512];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char root[512];
        char leaf[512];
        realpath(cwd, root);
        realpath(path, leaf);
        if (root == 0 || leaf == 0) {
            dprintf(output, "[sandbox] %s: Access to %s is not allowed\n", symbol, path); 
            return 0;
        }
        if (strcasestr(leaf, root) == 0) {
            dprintf(output, "[sandbox] %s: Access to %s is not allowed\n", symbol, path); 
            return 0;
        } 
    } 
	else{ 
		return 0;
	}
}

