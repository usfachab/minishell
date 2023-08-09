
# Minishell Tests

## Execution Tests

| Status| Test						| Bash						|
|-------|---------------------------|---------------------------|
| 		|`ls`						|`ls` output				|							
| 		|`/usr/bin/ls`				|bash: /usr/bin/ls: No such file or directory| 			
| 		|`usr/bin/ls`				|no such file or dir		|							
| 		|`./ls`						|no such file or dir		|			
| 		|`hello`					|command not found			|	
| 		|`/usr/bin/hello`			|no such file or dir		|		
| 		|`./hello`					|no such file or dir		|		
| 		|`""`						|command not found			|		
| KO	|`.`						|filename arg required		|		
| KO	|`..`						|`..`: command not found	|		
| 		|`$`						|`$`: command not found		|	
|  		|`./`						|is a directory				|	
| 		|`../`						|is a directory				|	
| 		|`../existing_dir`			|is a directory				|	
| 		|`../fake_dir`				|no such file or dir		|	
| KO	|`./Makefile`				|permission denied			|	
| 		|`./does_not_exist`			|no such file or dir		|		
| 		|`./minishell`				|executes new minishell		|	
| 		|`minishell`				|command not found			|			
| 		|`.minishell`				|command not found			|			

## CD

| Status| Test						| Bash								| 
|-------|---------------------------|-----------------------------------|
| 		|`cd ../../../../../..`		|`pwd` shows `/`						|							
| 		|`cd /home/user/`			|`pwd` shows `/home/user`				|						
| 		|`cd $HOME`					|`pwd` shows `/home/user`				|							
| 		|`cd $HOME/Documents`      	|`pwd` shows `/home/user/Documents`		|							
| 		|`unset HOME`, then `cd` 	|HOME not set							|							
| 		|`export HOME=` then `cd`	|No error msg							|							
| KO	|`cd /t /w`					|Too many arguments						|							
| 		|`cd ./fakepath`			|No such directory						|						
|		|`mkdir a`; `mkdir a/b`; `cd a/b`; `rm -r ../../a`; `cd ..`			| 							  

## ECHO

| Status| Test						| Bash				| 
|-------|---------------------------|-------------------|
| 		|`echo -n -n -nnnn -nnnnm`	|`-nnnnm`           |			
| 		|`echo a	-nnnnma`		|`a -nnnnma`		|			
| 		|`echo -n -nnn hello -n`	|`hello -n`			|			
| 		|`echo a	hello -na`		|`a hello -na`		|			

## EXPORT

| Status| Test						| Bash								|
|-------|---------------------------|-----------------------------------|
| 		|`export ""`				|Not a valid identifier				|
| 		|`export 42`				|Not a valid identifier				|
| 		|`export =`					|Not a valid identifier				|
| 		|`export hello`				|`env \| grep hello` shows nothing	|
| 		|`export var=foo`			|`env \| grep var=` shows var		|
| 		|`export $var=test`			|`env \| grep foo=` shows `foo=test`|
| 		|`echo $var $foo`			|`foo test`							|
| 		|`export t="abc def"`		|`env \| grep t` shows `t=abc def`	|

## UNSET

| Status| Test							| Bash							| 
|-------|-------------------------------|-------------------------------|
| 		|`unset PATH`					|`echo $PATH` shows `(newline)`	|
| 	KO	|`ls` (after `unset PATH`)		|No such file or directory		|
| 		|`unset "" test`				|Does nothing					|
| 		|`unset =`						|Does nothing					|
| 		|`unset FAKEVAR`				|Does nothing					|
| 		|`export var1=test`				|`env \| grep var` shows var1	|
| 		|`unset var` (following `var1`)	|Does not delete `var1`			|

## ENV

| Status| Test										| Bash				| 
|-------|-------------------------------------------|-------------------|
| 		|`env` then `export d=3 a=12 c=0` then `env`|					|				

## EXIT

| Status| Test							| Bash													| 
|-------|-------------------------------|-------------------------------------------------------|
| 		|`exit 10`						|exits shell											|
| 		|`exit -10`						|exits shell											|							
| 		|`exit abc`						|exits shell; error numeric arg required				|
| 		|`exit --10`					|exits shell; error numeric arg required				|
| 		|`exit ++10`					|exits shell; error numeric arg required				|
| 		|`exit abc 5`					|exits shell; error numeric arg required				|
| 		|`exit 5 abc`					|does not exit shell; too many args						|
| 		|`exit 5 < Makefile`			|exits shell											|
| 		|`exit 8 > test`				|exits shell; write exit to terminal, file empty		|
| 		|`ls \| exit`					|does not exit shell; no output							|
| 		|`ls \| exit 42`				|does not exit shell; no output							|
| 		|`ls \| exit 12 abc`			|does not exit shell; exit too many args				|
| 		|`ls \| exit abc 12`			|does not exit shell; exit numeric arg error			|
| 		|`exit \| ls`					|does not exit shell; `ls` output						|
| 		|`exit 42 \| ls`				|does not exit shell; `ls` output						|
| 		|`exit 12 abc \| ls`			|does not exit shell; exit too many args + `ls` output	|
| 		|`exit abc 12 \| ls`			|does not exit shell; exit numeric arg error + `ls` out	|
| 		|`ls > file \| exit`			|`ls` output in `file` (does not exit shell)			|
| 		|`sleep 5 \| exit`				|Sleeps 5 seconds (does not exit shell)					|
| 		|`ls -l > x \| exit \| wc -l`	|Output `0`; file `x` contains `ls` (no exit)			|
| 		|`exit \| ls`					|`ls` output (does not exit shell)						|
| 		|`exit 1 \| exit 0`				|Does nothing (does not exit shell)						|
| 		|`exit 0 \| exit 1`				|Does nothing (does not exit shell)						|

## Pipe tests

| Status| Test										| Bash									| 
|-------|-------------------------------------------|---------------------------------------|
| 		|`cat \| cat \| cat \| ls`					|`ls` output then hangs, `enter` 3 times|
| 		|`cat Makefile \| grep a \| wc -l \| cd x`	|No such file or directory				|
| 		|`cat Makefile \| grep a \| wc -l \| x`		|command not found						|
| 		|`echo test \|cat`							|`test`									|
| 		|`echo test \|\|\| cat`						|syntax error							|
| 		|`export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8`	|`env` shows vars						|
| 		|`echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H"`		|`1'2$C"$D5"$F"'7'8`					|

## Variable Expansion Tests 
🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰

Leading and trailling spaces in the output are denoted with the `█` character.

| Status| Test					| Bash				| 
|-------|-----------------------|-------------------|
| 		|`echo $USER`			|`username`			|					
| 		|`echo $`				|`$`				|					
| 		|`echo $""`				|`(newline)`		|				
|		|`echo $$$USER`			|`26153username`	|					
|		|`echo $$USER`			|`26153USER`		|					
| 		|`echo $USER$USER`		|`usernameusername`	|					
| 		|`echo $USER""$USER`	|`usernameusername`	|					
| 		|`echo $USER" "$USER`	|`username username`|					
| 		|`echo test$1test`		|`testtest`			|					
| 		|`echo test$FAKE_VAR`	|`test`				|					
| 		|`echo "$USER>>"`		|`username>>`		|					
| 		|`echo "$USER11111ffjf"`|`(newline)`		|					
| 		|`echo $\"echo`			|`$"echo`	|					
|  		|`echo "test$<test"`	|`test$<test`		|					
| 		|`echo test$<test`		|test: no such file	|					
| 		|`echo "test$-r"`		|`testhimBHsr`		|					
| 		|`echo "test$-?"`		|`testhimBHs?`		|					
| 		|`echo $-1$USER`		|`himBHs1username`	|					
| 		|`echo $1`				|`(newline)`		|					
| 		|`echo "$1"`			|`(newline)`		|					
| 		|`echo $"USER"`			|`USER`				|					
| 		|`echo $'USER'`			|`USER`				|					
| 		|`echo $NULL test`		|`test`				|					
| 		|`echo hello$USER`		|`hellousername`	|					
| 		|`echo hello$USERtest`	|`hello`			|					
| 		|`echo $USER.test`		|`username.test`	|					
|		| `echo $0`				|					|					
| 		| `echo "'$fake'"`		|	`''`			|					
| 		| `echo """$fake"""`	| `(newline)`		|					
| 		| `echo "'"$fake"'"`	| 	`''`			|					
| 		| `echo '"'"$fake"'"'`	|	`""`			|					
| 		| `echo $"fake"`		|	`fake`		|					

## Quote Handling Tests

Leading and trailling spaces in the output are denoted with the `█` character.

| Status| Test					| Bash				| 
|-------|-----------------------|-------------------|
|   	|`ec""ho test`			|`test` 			|			
| 		|`""echo test`			|`test`				|				
| 		|`echo"" test`			|`test`				|				
|  		|`echo "" test`			|`█test`			|		---->	
| 		|`echo $USE""R`			|`R`				|			
| 		|`echo ""$USER`			|`username`			|		
| 		|`echo "$"USER`			|`$USER`			|			
| 		|`echo  $""USER`		|`USER`				|				
| 		|`ec''ho test`			|`test`				|				
| 		|`''echo test`			|`test`				|				
| 		|`echo'' test`			|`test`				|				
|  		|`echo '' test`			|`█test`			|			
| 		|`echo $USE''R`			|`R`				|				
| 		|`echo ''$USER`			|`username`			|			
| 		|`echo '$'USER`			|`$USER`			|			
| 		|`echo  $''USER`		|`USER`				|		
| 		|`echo "" "" "" test`	|`███test`			|			
| 		|`echo """""" test`		|`█test`			|			
| 		|`echo $USER"" ''`		|`username`			|			
| 		|`ls ""`				|ls: : No such file or directory|	
| 		|`ls '"`				|syntax error msg	|	
| 		|`ls "'`				|syntax error msg	|	
| 		|`ls " "`				|ls:  : No such file or directory	| 
| 		|`ls " ' "`				|ls:  ' : No such file or directory|				
| 		|`"ls"`					|`ls` output	|					
| 		|`l"s"`					|`ls` output	|	
| 		|`ls"" -la`				|`ls -la` output		|	
| 		|`ls "" -la`			|ls: : No such file or directory / ls: -la: No such file or directory	|
| 		|`ls """"-la`			|`ls -la` output		|		
| 		|`ls ""-la`				|`ls -la` normal output		|		
| 		|`echo test""test`		|`testtest`			|		
| 		|`echo test ""test`		|`test test`		|		
| 		|`echo test "'"test`	|`test 'test`		|		
| 		|`echo "\|" ls`			|`\| ls`			|			
| 		|`echo "t \| es <>t"`	|`t \| es <>t`		|		
| 		|`echo '"abc"'`			|`"abc"`			|			
| 		|`echo '  "abc" '`		|`█"abc"█`			|	
| 		|`echo "'abc'"`			|`'abc'`			|			
| 		|`echo " $ " \| cat -e`	|`█$ $`				|	
| 		|`echo $:$= \| cat -e`	|`$:$=$`			|	
| 		|`export FOO=' " '`		|`env` shows `FOO`	|			
| DIFF	|`echo "$FOO" \| cat -e`|`$`				|	
| 		|`echo "\x"`			|`\x`				|		
| 		|`echo "\\x"`			|`\x`				|	
| 		|`echo "\\\x"`			|`\\x`				|	
| 		| `echo '"'"$fake"'"'`		|	`""`			|		


## Heredoc Tests
| Status| Test								| Bash							| 
|-------|-----------------------------------|-------------------------------|
| 		|`<< END cat`; `$USER$USER`; `END`	|`usernameusername`				|		
| 		|`<< END cat`; `$USER'$USER'`; `END`|`username'username'`			|		
| 		|`<< END cat`; `$USER"$USER"`; `END`|`username"username"`			|		
|  		|`<< END cat`; `$USER $USER`; `END`	|`username username`			|			
| 		|`<< END cat`; `helloEND`			|Heredoc keeps waiting for input|
| 		|`<< END cat`; `ENDhello`			|Heredoc keeps waiting for input|
| 		|`<< END cat`; `helloENDhello`		|Heredoc keeps waiting for input|						
| 		|`< Makefile cat \| << END cat`		|Heredoc + cat execute			|		
| 		|`export $VAR=test`					|`env` shows `VAR=test`			|			
| 		|`<< $VAR cat`; `$USER`; `$VAR`		|Heredoc ends with `$VAR` input	|	

## Redirection Tests
🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰 
| Status| Test					| Bash													|
|-------|-----------------------|-------------------------------------------------------|
| (parse)	|`< hello`				|hello: no such file or directory						|
| (parse)	|`cat <t`				|t: no such file or directory							|     			  	
| 	(parse)	|`> x`					|`x` file created empty									|									
| 	(parse)	|`< Ma < Makefile cat`	|Ma: no such file or directory (no cat output)			|												
| 	(parse)	|`<a cat <b <c`			|`cat` shows contents of file `c` only					|		
| 	(parse)	|`<a cat <b <c`			|`b: Permission denied`, does not show `c`				|		
| 	(parse)	|`>a cat <b >>c`		|Create empty `a`, `c` gets contents of `b` (because `cat<b` will output content of b)|		
| 	(parse)	|`>a ls >b >>c >d`		|`a`, `b`, `c`, `d` created, `ls` ouput only in `d`		|	
| 	(parse)	|`>a ls <e >>b >c`		|`e`: no such file; `a` created `b` and `c` not created	|			
| 	(parse)	|`cat -e >t1 <t2`		|`t2`: no such file; `t1` created						|			
| 	(parse)	|`echo 2 >o1 >>o2`		|`2` written to `o2`, `o1` empty						|		
| 	(parse)	|`echo 42 >o2 >>o1`		|`o1` contains `42`, `o2` empty							|				
| 	(parse)	|`echo hello > k\ 1`	|Creates file "`k 1`"									|	
| 	(parse)	|`echo test >f test1`	|Creates file `f` with contents `test test1`			|							
| 	(parse)	|`fakecmd hello > z`	|Command not found, file `z` created					|	
| 	(parse)	| `ls > a > b -l`		| create empty `a` and `b` with content of `ls -l`		|		
| 	(parse)	|`ls > p \| env > q`	|`p` contains `ls` output; `q` contains `env` output	|												
| 	(parse)	|`echo "File A" > a`	|Create file `a` with contents `File A`					|												
| 	(parse)	|`echo "File B" >> b`	|Create file `b` with contents `File B`					|											
| 	(parse)	|`echo File C >c`		|Create file `c` with contents `File C`					|												
| 	(parse)	|`chmod 000 b`			|Remove rights to `b` file								|					
| 	(parse)	|`chmod 644 b`; `rm a`	|Restore rights to `b` file, delete `a`					|			
| 	(parse)	|`rm a b c`				|Delete `a`, `b` and `c` files							|				
| 	(parse)	|`< Ma < Maa echo a`	| bash: Ma: No such file or directory + `echo a` don't get executed|	
| 	(parse)	|`echo a < Ma < Maa`	| bash: Ma: No such file or directory + `echo a` don't get executed|	
| 	(parse)	| `echo hello < txt sweetie` (txt exist)	| `hello sweetie` |					
|			| `ls > e \| cat<e`  | bash: e: No such file or directory + `e` created with content of ls |		
|			| `cat<f \| ls >f`			|	bash: f: No such file or directory + `f` get created with ls content |	
|			| `echo hello > a \| echo fuck > a` | behavior change; sometimes a contains `hello` sometimes `fuck` |	
|			| `echo hello > a > b \| echo fuck >b` | `a` and `b` created b contains hello, b doesn't get overwritten |	
|			| ` echo hello > b\| echo ddd>> b` | `b` created b contains hello, b doesn't get overwritten |		

## Signal Tests
| Status| Test						| Bash								| 
|-------|---------------------------|-----------------------------------|
| 		|`ctrl+c`					|`^C` + new prompt on new line		|	| 
| 		|`abc` + `ctrl + c`			|`abc^C` + new prompt				|				
| 		|`ctrl+d`					|print `exit` + exit shell			|			
| 		|`abc` + `ctrl+d`			|does nothing						|					
| 		|`ctrl+\`					|does nothing						|						
| 		|`abc` + `ctrl+\`			|does nothing						|						
| 		|`cat` + `enter` + `ctrl+c`	|interrupt cat; do not quit shell	|	
| 		|`cat` + `enter` + `ctrl+d`	|quit cat; do not quit shell		|		
| 		|`cat` + `enter` + `ctrl+\`	|quit cat; do not kill shell		|		

🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰 
## Other Syntax Error Tests
| Status| Test						| Bash						| 
|-------|---------------------------|---------------------------|
| 		|`\|`						|syntax error near `\|`		|
| 		|`ls \|`					|syntax unexpected EOF		|
| 		|`ls < \|`					|syntax error near `\|`		|		
| 		|`ls << \|`					|syntax error near `\|`		|		
| 		|`ls > \|`					|syntax error near `\|`		|		
| 		|`ls >> \|`					|syntax error near `\|`		|	
| 		|`ls \| <`					|syntax error near `newline`|	
| 		|`ls \| <<`					|syntax error near `newline`|		
| 		|`ls \| >`					|syntax error near `newline`|		
| 		|`ls \| >>`					|syntax error near `newline`|		
| 		|`ls >> >`					|syntax error near `>`		|		
| 		|`ls > >>`					|syntax error near `>>`		|		
| 		|`ls << <`					|syntax error near `<`		|		
| 		|`ls < <<`					|syntax error near `<<`		|		
| 		|`ls > >> \|`				|syntax error near `>>`		|		
| 		|`ls >>`					|syntax error near `newline`|		
| 		|`echo test > > out`		|syntax error near `>`		|		
| 		|`echo test >> > out`		|syntax error near `>`		|		
| 		|`echo hello > $fakevar`	|ambiguous redirect			|		
| 		|`echo hello >> $fakevar`	|ambiguous redirect			|			
| 		|`echo hello < $fakevar`	|ambiguous redirect			|			
| 		|`cat < $fakevar`			|ambiguous redirect			|		
| 		|`echo hello > $realvar`	|write to var file			|		
| 		|`echo hello >> $realvar`	|append to var file			|		
| 		|`< $realvar cat`			|read from var file			|		
| 		|`export t="abc def"`		|`env` shows `t=abc def`	|	| 
| 		|`echo test > $t"`			|bash: unexpected EOF while lo	ing for matching `"' bash ..|				
| 		|`echo test > "$t"`			|write to file `"abc def"`	|		
| 		|`echo hello >>> test`		|syntax error near `>`		|
| 		|`echo hello \| \|`			|syntax error near `\|`		|
| 		|`echo hello \|;`			|syntax error near `;`		|		
| 		|`echo\ a`					|`echo a` cmd not found		|	
|		|`<`						|							|	
|		|`<<`						|							|			
|		|`<<<`							|							|
|		| `<<<<`						|							|
|		| `>`							|							|	
|		| `>>`							|							|
|		| `>>>`							|							|
|		| `>>>`							|							|	

## Other Exit Status Tests
| Status| Test					| Bash						|
|-------|-----------------------|---------------------------|
| 		|`fake_cmd`				|Command not found			|
| 		|`ls not_a_path`		|No such file or dir		|
| 		|`./not_executable_file`|Permission denied			|
| 		|`cat clac 3`			|2 error msg				|
| 		|`cd $?`				|Number: no such file or dir|
| 		|`cat \|\|\|`			|syntax error				|
| 		|`echo "hell`			|unexpected EOF + syntax	|
