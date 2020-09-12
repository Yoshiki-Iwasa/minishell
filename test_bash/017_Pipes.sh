PS1='$ '
echo "017_Pipes"
echo ""

echo "minishell\$ cat Makefile | grep .c | wc -l"
cat Makefile | grep .c | wc -l
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ ls -l | grep ^d | wc -l"
ls -l | grep ^d | wc -l
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ pwd | cut -f 2 -d \"/\""
pwd | cut -f 2 -d "/"
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ ls filethatdoesntexist | grep ls | more"
ls filethatdoesntexist | grep ls | more
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ ls filethatdoesntexist | echo echo"
ls filethatdoesntexist | echo echo
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo '100+1' > a.txt ; bc < a.txt | wc -c > result.txt ; cat result.txt ; rm result.txt a.txt"
echo '100+1' > a.txt ; bc < a.txt | wc -c > result.txt ; cat result.txt ; rm result.txt a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo test | cat"
echo test | cat
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo test > a.txt | cat"
echo test > a.txt | cat
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ cat a.txt"
cat a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ echo echo | cat < a.txt"
echo echo | cat < a.txt
echo "minishell\$ "
echo "minishell\$ "

echo "minishell\$ rm a.txt"
rm a.txt
echo "minishell\$ "
echo "minishell\$ "
