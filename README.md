# ICPC Template of 2019

## 模板中被省略的常用声明
 
#define lc (o << 1)    
#define rc (o << 1 | 1)  
#define lb(x) (x & (-x))   
#define mid (l + r >> 1)  

typedef long long ll      
typedef pair<int, int> piir    
typedef unsigned int uint    
typedef unsigned long long ull   

## 目录结构说明    

### commit_script_for_linux.py

提交修改并push到github的脚本  
用法示例:python3 commit_script_for_linux comment  
工作流程:  
git pull  
git add -A  
git commit 'comment'  
git push    
   
### del_space.py

删除代码内多余空行的脚本

### 注意事项/ 
一些简单的训练总结

### latex/ 
生成的模板和tex文件  
ubuntu下使用方法:  
1.先装好texlive(可以参考  
https://www.cnblogs.com/ytytzzz/p/10955912.html)  
2.cd到当前目录，按照tex文件内的格式修改相应内容  
3.执行命令:sh ./command  
  即可生成template.pdf
  
### 其他文件夹/
都是相应的模板
