#git常用命令

###安装配置

Ubuntu下安装：sudo apt-get install git  

配置用户名：git config --global user.name "你的名字"  

配置e-mail：git config --global user.email "你的邮箱@xx.com"

###添加

将当前目录变为仓库：git init  

将文件添加到暂存区：git add 文件名 [可选：另一个文件名]  

将暂存区提交到仓库：git commit –m "描述"

###查询

查询仓库状态：git status  

比较文件差异（请在git add之前使用）：git diff 文件名  

查看仓库历史记录(详细)：git log  

查看仓库历史记录(单行)：git log --pretty=online 或 git log --online 
 
查看所有版本的commit ID：git reflog

###撤销

撤销工作区的修改：git checkout -- 文件名  

撤销暂存区的修改：git reset HEAD 文件名  

回退到历史版本：git reset --hard 该版本ID  

回退到上个版本：git reset --hard HEAD^  

上上版本是HEAD^^，也可用HEAD~2表示，以此类推

###标签

为当前版本打标签：git tag 标签名  

为历史版本打标签：git tag 标签名 该版本ID  

指定标签说明：git tag –a 标签名 –m "标签说明" [可选：版本ID]  

查看所有标签：git tag  

查看某一标签：git show 标签名  

删除某一标签：git tag –d 标签名

###GitHub

先有本地库，后有远程库，将本地库push到远程库

关联本地仓库和GitHub库：git remote add origin 网站上的仓库地址  

第一次将本地仓库推送到GitHub上：git push –u origin master

先有远程库，后有本地库，从远程库clone到本地库

从远程库克隆到本地：git clone 网站上的仓库地址

网站地址可以选择HTTPS协议（https://github.com...）、SSH协议（git@github.com...）。
如果选择SSH协议，必须将Ubuntu的公钥添加到GitHub上。见下一步

SSH Key

生成SSH Key：ssh-keygen –t rsa –C "你的邮箱@xx.com"  
生成Key时弹出选项，回车选择默认即可。  
Key保存位置：/root/.ssh  
登陆GitHub，创建new SSH key，其内容为/root/.ssh/id_rsa.pub中文本

已经有了本地库和远程库，二者实现同步

本地库的改动提交到远程库：git push origin master  
更新本地库至远程库的最新改动：git pull 