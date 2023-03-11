## Personal Dairy
The Personal Diary is a CLI (Command Line Interface) software, consists of three programs:

	pdadd 
	pdlist [ ]
	pdshow 
	pdremove 

pdadd is used to add an entity into the diary for the date. If an entity of the same date is in the diary, the existing one will be replaced. pdadd reads lines of the diary from the stdin, line by line, until a line with single '.' character or the EOF character (Ctrl-D in Unix and Ctrl- Z in Windows).

pdlist lists all entities in the diary ordered by date. If start and end date are provided through command line parameters, it lists entities between start and end only. This program lists to the stdout.

pdshow prints the content of the entity specified by the date to the stdout. 

pdremove removes one entity of the date. It returns 0 at success and -1 at failure.

The software stores diary in one data file, reads to the memory at begining of each program and stores back to the file at the end of process.

Common classes and functions should be shared between programs. No interactive is permitted, so these programs are able to work together by the means of redirection or tee, are able to be used in a shell script.

## 编译与依赖：
使用以下命令编译成4个可执行文件：

	g++ DiaryBase.cpp pdadd.cpp -o pdadd
	g++ DiaryBase.cpp pdlist.cpp -o pdlist
	g++ DiaryBase.cpp pdremove.cpp -o pdremove
	g++ DiaryBase.cpp pdshow.cpp -o pdshow


## 执行方式：
pdadd:
	添加一个日记，如果日期冲突了会自动替换。
	Sample Input:
		11 12 2022
		this is a diary.
		today is ...
		.
	解释：
		第一行为日期，输入格式是： 月 日 年
		从第二行开始输入日记内容，第一行会自动变为主题。

pdlist:
	列出日期内的所有日记。
	Sample:
		命令行方式调用，例如：
			pdlist 11 12 2022 11 13 2022
		将显示这一组日期内的所有日记，没有将不会输出。
		解释：
			pdlist 月 日 年 月 日 年 
			（前一组为起始日期， 后一组为结束日期）

pdremove:
	删除一个日记。
	sample input:
		11 12 2022
	将删除这一个（月 日 年）的日记，成功后返回0，不成功返回-1.

pdshow:
	显示某一天的日记。
	sample input:
		11 12 2022