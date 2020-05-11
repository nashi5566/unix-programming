# Play with sandbox

原本第一版寫出來的 sandbox 是正常的，但在交作業前幾個小時，電腦炸掉我的 source code 還沒推上 github 就炸了，所以目前憑印想寫的 code 並沒有完全正確的實作完，功能會怪怪的。

## exec* & system prohitbit

這部分應該沒有問題，執行 sh 基本上都會被禁止。

## 其餘 hook 部分

* chdir x
* chmod x
* chown x
* creat
* fopen x
* link x
* mkdir
* open x
* openat x
* opendir
* readlink x
* remove x
* rename x
* rmdir x
* __xstat x
* symlink
* unlink x
* fchmodat x

打叉是沒問題的，沒打叉的是實作之後會有問題的。
基本上都是跟讀取 symbol link 有關的 API ，會解壞。
另外在檢查路徑的部分，因曾發生過 segfault 的狀況用 Valgrind 把錯誤訊息看過一次， realpath 會有無限迴圈。

還有發現一個滿有趣的點就是，原本我的 debug 訊息是用 fprintf 印的，但加入 fopen 之後會有 seg fault，也是出在 realpath 會給到不對的路徑，後來改成用 open 及 dprintf 來 redirect 訊息就可以了，這部分還在查 doc 理解。

## Usage
```
make // 編譯
```

```
./sandbox [sandbox command] -- [command to launcher]
```

```
make clean // delete sandbox.so sandbox
```
