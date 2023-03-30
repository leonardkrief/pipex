# `pipex`

The purpose of this project is to discover in detail the UNIX `pipe` mechanism.

### Description of mandatory part
`pipex` goal is to reproduce the behaviour of the following shell command
```bash
$> < file1 cmd1 | cmd2 > file2
```
Execution command should be as follow:
```bash
$> ./pipex file1 cmd1 cmd2 file2
```
All errors like: wrong commands,  permission to files and etc, must be handled.
### Bonus part
Handle of multiple pipes
```bash
$> < file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2

$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```  

Support `<<` when instead of `file1` is `here_doc`.
```bash
$> cmd1 << LIMITER | cmd2 > file2

$> ./pipex here_doc LIMITER cmd1 cmd2 file2
```

![125/100](img/125.png)
